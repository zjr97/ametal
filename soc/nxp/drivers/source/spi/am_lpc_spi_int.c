/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_lpc_spi_int.h"

/*******************************************************************************
  SPI ״̬���¼�����
*******************************************************************************/

/**
 * SPI ������״̬
 */

#define __SPI_ST_IDLE               0                   /* ����״̬ */
#define __SPI_ST_MSG_START          1                   /* ��Ϣ��ʼ */
#define __SPI_ST_TRANS_START        2                   /* ���俪ʼ */
#define __SPI_ST_M_SEND_DATA        3                   /* �������� */
#define __SPI_ST_M_RECV_DATA        4                   /* �������� */
#define __SPI_ST_DMA_TRANS_DATA     5                   /* DMA ���� */

/**
 * SPI �������¼�
 *
 * ��32λ����16λ���¼���ţ���16λ���¼�����
 */

#define __SPI_EVT_NUM_GET(event)    ((event) & 0xFFFF)
#define __SPI_EVT_PAR_GET(event)    ((event >> 16) & 0xFFFF)
#define __SPI_EVT(evt_num, evt_par) (((evt_num) & 0xFFFF) | ((evt_par) << 16))

#define __SPI_EVT_NONE              __SPI_EVT(0, 0)     /* ���¼� */
#define __SPI_EVT_TRANS_LAUNCH      __SPI_EVT(1, 0)     /* ������� */
#define __SPI_EVT_M_SEND_DATA       __SPI_EVT(2, 0)     /* �������� */
#define __SPI_EVT_M_RECV_DATA       __SPI_EVT(3, 0)     /* �������� */

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_lpc_spi_int_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_lpc_spi_int_dev_t *p_this, am_spi_device_t *p_dev);

am_local void __spi_write_data (am_lpc_spi_int_dev_t *p_dev);
am_local void __spi_read_data (am_lpc_spi_int_dev_t *p_dev);

am_local void __spi_irq_handler (void *p_arg);
am_local int  __spi_hard_init (am_lpc_spi_int_dev_t *p_this);
am_local int  __spi_config (am_lpc_spi_int_dev_t *p_this);

am_local int  __spi_mst_sm_event (am_lpc_spi_int_dev_t *p_dev, uint32_t event);
/*******************************************************************************
  SPI������������
*******************************************************************************/
am_local int __spi_info_get (void *p_arg, am_spi_info_t   *p_info);
am_local int __spi_setup    (void *p_arg, am_spi_device_t *p_dev );
am_local int __spi_msg_start (void              *p_drv,
                              am_spi_device_t   *p_dev,
                              am_spi_message_t  *p_msg);

/**
 * \brief SPI ��������
 */
am_local am_const struct am_spi_drv_funcs __g_spi_drv_funcs = {
    __spi_info_get,
    __spi_setup,
    __spi_msg_start,
};

/******************************************************************************/

/**
 * \brief Ĭ��CS�ſ��ƺ������ߵ�ƽ��Ч
 */
am_local
void __spi_default_cs_ha (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 1 : 0);
}

/**
 * \brief Ĭ��CS�ſ��ƺ������͵�ƽ��Ч
 */
am_local
void __spi_default_cs_la (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 0 : 1);
}

/**
 * \brief Ĭ��CS�ſ��ƺ�������Ӳ�����п���
 */
am_local
void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state)
{
    return;
}

/**
 * \brief CS���ż���
 */
am_local
void __spi_cs_on (am_lpc_spi_int_dev_t *p_this, am_spi_device_t *p_dev)
{
    /* if last device toggled after message */
    if (p_this->p_tgl_dev != NULL) {

        /* last message on defferent device */
        if (p_this->p_tgl_dev != p_dev) {
            p_this->p_tgl_dev->pfunc_cs(p_this->p_tgl_dev, 0);
        }
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 1);
}

/**
 * \brief CS����ȥ��
 */
am_local
void __spi_cs_off (am_lpc_spi_int_dev_t   *p_this,
                   am_spi_device_t  *p_dev)
{
    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

/**
 * \brief SPI�жϴ�����
 */
am_local
void __spi_irq_handler (void *p_arg)
{
    am_lpc_spi_int_dev_t  *p_dev      = (am_lpc_spi_int_dev_t *)p_arg;
    amhw_lpc_spi_t    *p_hw_spi   = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    uint32_t spi_status = (uint32_t)amhw_lpc_spi_intstat_get(p_hw_spi);

    if ((spi_status & AMHW_LPC_SPI_STAT_SELNASSERT)  ||
        (spi_status & AMHW_LPC_SPI_STAT_SELNDEASSERT)) {
        amhw_lpc_spi_stat_clear(p_hw_spi,
                                AMHW_LPC_SPI_STAT_SELNASSERT |
                                AMHW_LPC_SPI_STAT_SELNDEASSERT);
    }

    if ((spi_status & AMHW_LPC_SPI_STAT_RXOVERRUN)  ||
        (spi_status & AMHW_LPC_SPI_STAT_TXUNDERRUN)) {

        /* �������״̬ */
        amhw_lpc_spi_stat_clear(p_hw_spi,
                                AMHW_LPC_SPI_STAT_RXOVERRUN   |
                                AMHW_LPC_SPI_STAT_TXUNDERRUN  |
                                AMHW_LPC_SPI_STAT_SELNASSERT  |
                                AMHW_LPC_SPI_STAT_SELNDEASSERT);

        /* ���������ж� */
        amhw_lpc_spi_int_disable(p_hw_spi,
                                 AMHW_LPC_SPI_INTENSET_RXRDY      |
                                 AMHW_LPC_SPI_INTENSET_TXRDY      |
                                 AMHW_LPC_SPI_INTENSET_RXOVERRUN  |
                                 AMHW_LPC_SPI_INTENSET_TXUNDERRUN |
                                 AMHW_LPC_SPI_INTENSET_SELNASSERT |
                                 AMHW_LPC_SPI_INTENSET_SELNDEASSERT);
    }

    /* �������� */
    if (spi_status & AMHW_LPC_SPI_STAT_TXRDY) {
        /* run the state machine */
        __spi_mst_sm_event(p_dev, __SPI_EVT_M_SEND_DATA);
    }

    /* �������� */
    if (spi_status & AMHW_LPC_SPI_STAT_RXRDY) {
        __spi_mst_sm_event(p_dev, __SPI_EVT_M_RECV_DATA);
    }
}

/**
 * \brief SPI Ӳ����ʼ��
 */
am_local
int __spi_hard_init (am_lpc_spi_int_dev_t *p_this)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* �ȴ�SPI���У������������üĴ��� */
    while ((amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_IDLE) == 0);
    amhw_lpc_spi_cfg_set(p_hw_spi,
                         (AMHW_LPC_SPI_CFG_ENABLE |
                         AMHW_LPC_SPI_CFG_MASTER));

    /* ��ʼ������SPI */
    return AM_OK;
}

am_local
int __spi_info_get (void *p_arg, am_spi_info_t *p_info)
{
    am_lpc_spi_int_dev_t  *p_this   = (am_lpc_spi_int_dev_t *)p_arg;

    if (p_info == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʵ��� PCLK */
    p_info->max_speed = am_clk_rate_get(p_this->p_devinfo->clk_id);
    p_info->min_speed = p_info->max_speed / 65536;
    p_info->features  = AM_SPI_CPHA  |
                        AM_SPI_CPOL  |
                        AM_SPI_NO_CS |
                        AM_SPI_LOOP  |
                        AM_SPI_CS_HIGH;   /* features */
    return AM_OK;
}

/******************************************************************************/
am_local
int __spi_config (am_lpc_spi_int_dev_t *p_this)
{
    const am_lpc_spi_int_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_lpc_spi_t                 *p_hw_spi  = (amhw_lpc_spi_t *)(p_devinfo->spi_regbase);
    am_spi_transfer_t              *p_trans   = p_this->p_cur_trans;

    uint32_t                       mode_flag = 0;
    uint32_t                       div_val;

    /* ���Ϊ0��ʹ��Ĭ�ϲ���ֵ */
    if (p_trans->bits_per_word == 0) {
        p_trans->bits_per_word = p_this->p_cur_spi_dev->bits_per_word;
    }

    if (p_trans->speed_hz == 0) {
        p_trans->speed_hz = p_this->p_cur_spi_dev->max_speed_hz;
    }

    /* �����ֽ�����Ч�Լ�� */
    if (p_trans->bits_per_word > 16 || p_trans->bits_per_word < 4) {
        return -AM_EINVAL;
    }

    /* ���÷�Ƶֵ��Ч�Լ�� */
    if (p_trans->speed_hz > am_clk_rate_get(p_this->p_devinfo->clk_id) ||
        p_trans->speed_hz < (am_clk_rate_get(p_this->p_devinfo->clk_id) / 65536)) {
        return -AM_EINVAL;
    }

    /* ���ͺͽ��ջ�������Ч�Լ�� */
    if ((p_trans->p_txbuf == NULL) && (p_trans->p_rxbuf == NULL)) {
        return -AM_EINVAL;
    }

    /* �����ֽ������ */
    if (p_trans->nbytes == 0) {
        return -AM_ELOW;
    }

    /**
     * ���õ�ǰ�豸ģʽ
     */
    mode_flag = 0;

    if (p_this->p_cur_spi_dev->mode & AM_SPI_CPHA) {
        mode_flag |= AMHW_LPC_SPI_CFG_CHANGE;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_CPOL) {
        mode_flag |= AMHW_LPC_SPI_CFG_STAT_HIGH;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_CS_HIGH) {
        mode_flag |= AMHW_LPC_SPI_CFG_SPOL0_HIGH;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_LSB_FIRST) {
        mode_flag |= AMHW_LPC_SPI_CFG_LSB;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_LOOP) {
        mode_flag |= AMHW_LPC_SPI_CFG_LOOP;
    }

    /* ����ʱ��ֹͣ����  */
    amhw_lpc_spi_disable(p_hw_spi);

    /* ����ģʽ(���������������ӻ�ģʽ) */
    amhw_lpc_spi_cfg_set(p_hw_spi, (mode_flag               |
                                    AMHW_LPC_SPI_CFG_ENABLE |
                                    AMHW_LPC_SPI_CFG_MASTER));

    /* ���õ�֡����λ�� */
    amhw_lpc_spi_data_flen_set (p_hw_spi, p_trans->bits_per_word);

    /* ���÷�Ƶֵ����SPI���� */
    div_val = (am_clk_rate_get(p_this->p_devinfo->clk_id) / p_trans->speed_hz);
    amhw_lpc_spi_div_set(p_hw_spi, div_val);

    /* ���״̬λ */
    amhw_lpc_spi_stat_clear(p_hw_spi, AMHW_LPC_SPI_STAT_RXOVERRUN   |
                                      AMHW_LPC_SPI_STAT_TXUNDERRUN  |
                                      AMHW_LPC_SPI_STAT_SELNASSERT  |
                                      AMHW_LPC_SPI_STAT_SELNDEASSERT);

    /* ʹ��SPI���շ�������ж� */
    amhw_lpc_spi_int_enable(p_hw_spi,
                            AMHW_LPC_SPI_INTENSET_RXOVERRUN |
                            AMHW_LPC_SPI_INTENSET_TXUNDERRUN);

    return AM_OK;
}

/******************************************************************************/
am_local
int __spi_setup (void *p_arg, am_spi_device_t *p_dev)
{
    am_lpc_spi_int_dev_t *p_this   = (am_lpc_spi_int_dev_t *)p_arg;

    uint32_t max_speed, min_speed;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* Ĭ������Ϊ8λ����󲻳���16λ */
    if (p_dev->bits_per_word == 0) {
        p_dev->bits_per_word = 8;
    } else if (p_dev->bits_per_word > 16) {
        return -AM_ENOTSUP;
    }

    /* ���SPI���ʲ��ܳ�����ʱ�ӣ���С����С����ʱ��65536��Ƶ */
    max_speed = am_clk_rate_get(p_this->p_devinfo->clk_id);
    min_speed = max_speed / 65536;

    if (p_dev->max_speed_hz > max_speed) {
        p_dev->max_speed_hz = max_speed;
    } else if (p_dev->max_speed_hz < min_speed) {
        return -AM_ENOTSUP;
    }

    /* ��Ƭѡ���� */
    if (p_dev->mode & AM_SPI_NO_CS) {
        p_dev->pfunc_cs = __spi_default_cs_dummy;

    /* ��Ƭѡ���� */
    }  else {

        /* ���ṩ��Ĭ��Ƭѡ���� */
        if (p_dev->pfunc_cs == NULL) {

            /* Ƭѡ�ߵ�ƽ��Ч */
            if (p_dev->mode & AM_SPI_CS_HIGH) {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_LOW);
                p_dev->pfunc_cs = __spi_default_cs_ha;

            /* Ƭѡ�͵�ƽ��Ч */
            } else {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_HIGH);
                p_dev->pfunc_cs = __spi_default_cs_la;
            }
        }
    }

    /* ���Ƭѡ�ź� */
    __spi_cs_off(p_this, p_dev);

    return AM_OK;
}

/******************************************************************************/

am_local
void __spi_write_data (am_lpc_spi_int_dev_t *p_dev)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;

    if (p_dev == NULL) {
        return ;
    }

    /* tx_buf ��Ч */
    if (p_trans->p_txbuf != NULL) {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
            /** \brief ���������ݵĻ�ַ+ƫ�� */
            uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
            amhw_lpc_spi_txdat_write(p_hw_spi, *ptr);
        } else {
            uint16_t *ptr = (uint16_t *)((uint8_t *)(p_trans->p_txbuf)
                                                     + p_dev->data_ptr);
            amhw_lpc_spi_txdat_write(p_hw_spi, *ptr);
        }
    /* tx_buf ��Ч */
    } else {
        /** \brief ������������Ч ֱ�ӷ�0, ������ȫ˫����ϵ�����ڶ���ʱ�����Ҫ�����ݣ�оƬ�Ż���һ��Ҫ��������  */
        amhw_lpc_spi_txdat_write(p_hw_spi, 0x0000);
    }

    /** \brief ��������ݵ�byte�� */
    p_dev->nbytes_to_recv = p_dev->p_cur_spi_dev->bits_per_word < 9 ? 1 : 2;
    p_dev->p_cur_msg->actual_length += p_dev->nbytes_to_recv;
}

am_local
void __spi_read_data (am_lpc_spi_int_dev_t *p_dev)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;
    uint8_t *p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;

    if (p_dev == NULL) {
        return ;
    }

    /* rx_buf ��Ч */
    if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
             *p_buf8 = amhw_lpc_spi_rxdata_8bit_read(p_hw_spi);
        } else {
             *(uint16_t *)(p_buf8) = amhw_lpc_spi_rxdata_16bit_read(p_hw_spi);
        }

    /* rx_buf ��Ч���߲���Ҫ�������� */
    } else {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
            (void)amhw_lpc_spi_rxdata_8bit_read(p_hw_spi);

        } else {
            (void)amhw_lpc_spi_rxdata_16bit_read(p_hw_spi);
        }
    }

    /* �Ѿ����ͻ���յ�����byte�� */
    p_dev->data_ptr += p_dev->nbytes_to_recv;
    p_dev->nbytes_to_recv = 0;
}

/******************************************************************************/

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
am_static_inline
void __spi_msg_in (am_lpc_spi_int_dev_t *p_dev, struct am_spi_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                                             &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_spi_message *__spi_msg_out (am_lpc_spi_int_dev_t *p_dev)
{
    if (am_list_empty_careful(&(p_dev->msg_list))) {
        return NULL;
    } else {
        struct am_list_head *p_node = p_dev->msg_list.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_spi_message, ctlrdata);
    }
}

/**
 * \brief ��message�б��ͷȡ��һ�� transfer
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_spi_transfer *__spi_trans_out (am_spi_message_t *msg)
{
    if (am_list_empty_careful(&(msg->transfers))) {
        return NULL;
    } else {
        struct am_list_head *p_node = msg->transfers.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_spi_transfer, trans_node);
    }
}

/**
 * \brief SPI �������ݺ���
 */
am_local
int __spi_msg_start (void              *p_drv,
                     am_spi_device_t   *p_dev,
                     am_spi_message_t  *p_msg)
{
    am_lpc_spi_int_dev_t *p_this   = (am_lpc_spi_int_dev_t *)p_drv;
    amhw_lpc_spi_t      *p_hw_spi  = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    int key;

    p_this->p_cur_spi_dev  = p_dev;                         /* ����ǰ�豸������Ϣ���� */
    p_this->p_cur_msg      = p_msg;                         /* ����ǰ�豸������Ϣ���� */
    p_this->nbytes_to_recv = 0;                             /* �������ַ�����0 */
    p_this->data_ptr       = 0;                             /* �ѽ����ַ�����0 */


    /* �豸��Ч�Լ�� */
    if ((p_drv              == NULL) ||
        (p_dev              == NULL) ||
        (p_msg              == NULL) ){
        return -AM_EINVAL;
    }

    /* ���������ɽ���λ */
    amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);

    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_this->busy == AM_TRUE) {
        __spi_msg_in(p_this, p_msg);
        am_int_cpu_unlock(key);
        return AM_OK;
    } else {
        p_this->busy = AM_TRUE;
        __spi_msg_in(p_this, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        /* ����״̬�� */
        return __spi_mst_sm_event(p_this, __SPI_EVT_TRANS_LAUNCH);
    }
}


/******************************************************************************/

/******************************************************************************/

/*  ״̬���ڲ�״̬�л� */
#define __SPI_NEXT_STATE(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/**
 * \brief  SPI ʹ��״̬������
 */
am_local
int __spi_mst_sm_event (am_lpc_spi_int_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t new_event = __SPI_EVT_NONE;

    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    while (1) {

        if (new_event != __SPI_EVT_NONE) {     /* ������¼��Ƿ������ڲ� */
            event     = new_event;
            new_event  = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        case __SPI_ST_IDLE:         /* ���������ڿ���״̬ */
        {

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ����״̬�ȴ�����Ϣ�������������� */
            }
            /* �л�����Ϣ��ʼ״̬������break */
        }
        /* no break */

        case __SPI_ST_MSG_START:    /* ��Ϣ��ʼ */
        {
            am_spi_message_t  *p_cur_msg   = NULL;

            int key;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ��Ϣ��ʼ״̬�ȴ�����Ϣ�������������� */
            }

            key = am_int_cpu_lock();
            p_cur_msg          = __spi_msg_out(p_dev);
            p_dev->p_cur_msg   = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {
                /* ���������ж� */
                amhw_lpc_spi_int_disable(p_hw_spi,
                                         AMHW_LPC_SPI_INTENCLR_RXRDY      |
                                         AMHW_LPC_SPI_INTENCLR_TXRDY      |
                                         AMHW_LPC_SPI_INTENCLR_RXOVERRUN  |
                                         AMHW_LPC_SPI_INTENCLR_TXUNDERRUN |
                                         AMHW_LPC_SPI_INTENCLR_SELNASSERT        |
                                         AMHW_LPC_SPI_INTENCLR_SELNDEASSERT );

                p_dev->busy = AM_FALSE;
            }
            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {
                __SPI_NEXT_STATE(__SPI_ST_IDLE, __SPI_EVT_NONE);
                break;
            } else {

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_TRANS_LAUNCH);

                /* new_event ��Ϊ__SPI_EVT_NONE, ����״̬���ڲ����¼����� */
                event     = new_event;
                new_event = __SPI_EVT_NONE;
            }
        }
        /* no break */

        case __SPI_ST_TRANS_START:  /* ���俪ʼ */
        {
            am_spi_message_t  *p_cur_msg   = p_dev->p_cur_msg;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ���俪ʼ״̬�ȴ�����Ϣ�������������� */
            }

            /* ��ǰ��Ϣ������� */
            if (am_list_empty(&(p_cur_msg->transfers))) {

                p_cur_msg->actual_length = 0;

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                /* notify the caller  */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }

                /* Ƭѡ�ر� */
                __spi_cs_off(p_dev, p_dev->p_cur_spi_dev);

                __SPI_NEXT_STATE(__SPI_ST_MSG_START, __SPI_EVT_TRANS_LAUNCH);

            } else {
                /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */
                am_spi_transfer_t *p_cur_trans = __spi_trans_out(p_cur_msg);
                p_dev->p_cur_trans             = p_cur_trans;

                /* reset current data pointer */
                p_dev->data_ptr       = 0;
                p_dev->nbytes_to_recv = 0;

                /* ����SPI������� */
                __spi_config(p_dev);

                /* CSѡͨ */
                __spi_cs_on(p_dev, p_dev  ->p_cur_spi_dev);

                /* ��һ״̬��ʹ���жϷ�ʽ�������� */
                 __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);
            }
            break;
        }

        case __SPI_ST_M_SEND_DATA:    /* �������� */
        {
            am_spi_transfer_t *p_cur_trans = p_dev->p_cur_trans;

            if (event != __SPI_EVT_M_SEND_DATA) {
                return -AM_EINVAL;  /* ��������״̬�ȴ�����Ϣ�����Ƿ������� */
            }

            /* û�и�����Ҫ���͵������� */
            if (p_dev->data_ptr >= p_cur_trans->nbytes) {

                /* ���ܷ����ж�  */
                amhw_lpc_spi_int_disable(p_hw_spi, AMHW_LPC_SPI_INTENCLR_TXRDY);

                 /* �ص����俪ʼ״̬ */
                 __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_TRANS_LAUNCH);

                 break;
            } else {

                if ((amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_TXRDY) != 0) {
                    /* ���һ���ֵĴ������� */
                    if (p_dev->p_cur_spi_dev->bits_per_word <= 8) {
                        if ((p_dev->data_ptr == (p_cur_trans->nbytes - 1))) {
                            amhw_lpc_spi_txctl_set(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                        } else {
                            amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                        }
                    } else {
                        if ((p_dev->data_ptr == (p_cur_trans->nbytes - 2))) {
                            amhw_lpc_spi_txctl_set(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                        } else {
                            amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                        }
                    }

                    /* ����Ҫ�������� */
                    if (p_cur_trans->p_rxbuf == NULL) {
                        amhw_lpc_spi_txctl_set(p_hw_spi,   AMHW_LPC_SPI_TXDATCTL_RX_IGNORE);
                    } else {
                        amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_RX_IGNORE);
                    }

                    /* ���ܷ����ж� */
                    amhw_lpc_spi_int_disable(p_hw_spi, AMHW_LPC_SPI_INTENCLR_TXRDY);

                    /* ��ӻ�д���� */
                    __spi_write_data(p_dev);

                    /* �����˽��� */
                     if (p_cur_trans->p_rxbuf == NULL) {
                         p_dev->nbytes_to_recv = 0;

                         /* p_dev->data_ptrΪ��Ч���͸��� */
                         p_dev->data_ptr += (p_dev->p_cur_spi_dev->bits_per_word < 9 ? 1 : 2);

                         /* �����˽��գ���һ״̬���Ƿ���״̬ */
                         __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_NONE);

                         /* �رս����ж� */
                         amhw_lpc_spi_int_disable(p_hw_spi, AMHW_LPC_SPI_INTENCLR_RXRDY);

                         /* ���������жϣ�ͨ����������л�����һ��״̬ */
                         amhw_lpc_spi_int_enable(p_hw_spi, AMHW_LPC_SPI_INTENSET_TXRDY);
                     } else {

                         /* δ���Խ��գ���һ״̬�ǽ���״̬ */
                         __SPI_NEXT_STATE(__SPI_ST_M_RECV_DATA, __SPI_EVT_NONE);

                         /* ʹ����ģʽ�����ж�(��ʵ�������ж����ڴ�ģʽ�²�������) */
                         amhw_lpc_spi_int_enable(p_hw_spi,
                                                 AMHW_LPC_SPI_INTENSET_RXRDY      |
                                                 AMHW_LPC_SPI_INTENSET_RXOVERRUN  |
                                                 AMHW_LPC_SPI_INTENSET_TXUNDERRUN);
                     }
                 } else {
                     /* ʹ�ܷ����жϵȴ����;��� */
                     amhw_lpc_spi_int_enable(p_hw_spi, AMHW_LPC_SPI_INTENSET_TXRDY);
                 }
            }
            break;
        }

        case __SPI_ST_M_RECV_DATA:      /* �������� */
        {
            if (event != __SPI_EVT_M_RECV_DATA) {
                return -AM_EINVAL;      /* ��������״̬�ȴ�����Ϣ�����ǽ������� */
            }

            /* ��ȡ���� */
            __spi_read_data(p_dev);

            /* û�и����������Ҫ������ */
            if (p_dev->nbytes_to_recv == 0) {

                /* ����ʣ������ */
                __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);


                /* ���������ж� */
                amhw_lpc_spi_int_disable(p_hw_spi,
                                         AMHW_LPC_SPI_INTENSET_RXRDY      |
                                         AMHW_LPC_SPI_INTENSET_TXRDY      |
                                         AMHW_LPC_SPI_INTENSET_RXOVERRUN  |
                                         AMHW_LPC_SPI_INTENSET_TXUNDERRUN |
                                         AMHW_LPC_SPI_INTENSET_SELNASSERT |
                                         AMHW_LPC_SPI_INTENSET_SELNDEASSERT);

            /* ��Ҫ���ո������� */
            } else {
                /* ���ʲôҲ��Ҫ�� */
            }
            break;
        }

        /*
         * ��ԶҲ�������е����
         */
        default:
            break;
        }

        /* û�������ڲ�����Ϣ, ���� */
        if (new_event == __SPI_EVT_NONE) {
            break;
        }
    }
    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI ��ʼ��
 */
am_spi_handle_t am_lpc_spi_int_init (am_lpc_spi_int_dev_t           *p_dev,
                                          const am_lpc_spi_int_devinfo_t *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_serve.p_funcs = (struct am_spi_drv_funcs *)&__g_spi_drv_funcs;
    p_dev->spi_serve.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_cur_spi_dev    = NULL;
    p_dev->p_tgl_dev        = NULL;
    p_dev->busy             = AM_FALSE;
    p_dev->p_cur_msg        = NULL;
    p_dev->p_cur_trans      = NULL;
    p_dev->data_ptr         = 0;
    p_dev->nbytes_to_recv   = 0;
    p_dev->state            = __SPI_ST_IDLE;     /* ��ʼ��Ϊ����״̬ */

    am_list_head_init(&(p_dev->msg_list));

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    am_int_connect(p_dev->p_devinfo->inum,
                   __spi_irq_handler,
                   (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);


    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_lpc_spi_int_deinit (am_spi_handle_t handle)
{
    am_lpc_spi_int_dev_t *p_dev    = (am_lpc_spi_int_dev_t *)handle;
    amhw_lpc_spi_t       *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_lpc_spi_disable(p_hw_spi);

    /* �ر�SPI�жϺŲ��Ͽ����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum,
                      __spi_irq_handler,
                     (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}
/* end of file */
