/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI ������ʵ�ֺ���
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  tee, first implementation.
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "am_clk.h"
#include "am_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc82x_dma.h"
#include "am_lpc82x_spi_dma.h"
#include "hw/amhw_lpc_spi.h"

/*******************************************************************************
  SPI ״̬���¼�����
*******************************************************************************/

/**
 * SPI ������״̬
 */

#define __SPI_ST_IDLE               0                   /* ����״̬ */
#define __SPI_ST_MSG_START          1                   /* ��Ϣ��ʼ */
#define __SPI_ST_TRANS_START        2                   /* ���俪ʼ */
#define __SPI_ST_DMA_TRANS_DATA     3                   /* DMA ���� */

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
#define __SPI_EVT_DMA_TRANS_DATA    __SPI_EVT(2, 0)     /* DMA�������� */

/*******************************************************************************
  ģ���ڱ�������
*******************************************************************************/

static const uint16_t  __const_high = 0xFFFF;     /* SPI����ʱMOSIΪ�ߵ�ƽ */
static const uint16_t  __const_low  = 0x0000;     /* SPI����ʱMOSIΪ�͵�ƽ */


/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_lpc82x_spi_dma_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_lpc82x_spi_dma_dev_t *p_this, am_spi_device_t *p_dev);

am_local int  __spi_hard_init (am_lpc82x_spi_dma_dev_t *p_this);
am_local int  __spi_config (am_lpc82x_spi_dma_dev_t *p_this);

am_local int  __spi_dma_trans (am_lpc82x_spi_dma_dev_t *p_dev);
am_local void __spi_dma_isr (void *p_arg, int stat);

am_local int  __spi_mst_sm_event (am_lpc82x_spi_dma_dev_t *p_dev, uint32_t event);
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
void __spi_cs_on (am_lpc82x_spi_dma_dev_t *p_this, am_spi_device_t *p_dev)
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
void __spi_cs_off (am_lpc82x_spi_dma_dev_t   *p_this,
                   am_spi_device_t  *p_dev)
{
    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

/**
 * \brief SPI Ӳ����ʼ��
 */
am_local
int __spi_hard_init (am_lpc82x_spi_dma_dev_t *p_this)
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

/******************************************************************************/
am_local
int __spi_setup (void *p_arg, am_spi_device_t *p_dev)
{
    am_lpc82x_spi_dma_dev_t *p_this   = (am_lpc82x_spi_dma_dev_t *)p_arg;

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


am_local
int __spi_info_get (void *p_arg, am_spi_info_t *p_info)
{
    am_lpc82x_spi_dma_dev_t  *p_this   = (am_lpc82x_spi_dma_dev_t *)p_arg;

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


am_local
int __spi_config (am_lpc82x_spi_dma_dev_t *p_this)
{
    amhw_lpc_spi_t  *p_hw_spi  = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);
    am_spi_transfer_t  *p_trans   = p_this->p_cur_trans;

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
    if (p_trans->bits_per_word > 16 || p_trans->bits_per_word < 1) {
        return -AM_EINVAL;
    }

    /* ���÷�Ƶֵ��Ч�Լ�� */
    if (p_trans->speed_hz >  am_clk_rate_get(p_this->p_devinfo->clk_id) ||
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

    /* ����ģʽ(���������������ӻ�ģʽ) */
    amhw_lpc_spi_cfg_set(p_hw_spi,
                     (mode_flag              |
                         AMHW_LPC_SPI_CFG_ENABLE |
                         AMHW_LPC_SPI_CFG_MASTER));

    /* ���õ�֡����λ�� */
    amhw_lpc_spi_data_flen_set(p_hw_spi, p_trans->bits_per_word);

    /* ���÷�Ƶֵ����SPI���� */
    div_val = (am_clk_rate_get(p_this->p_devinfo->clk_id) / p_trans->speed_hz);
    amhw_lpc_spi_div_set(p_hw_spi, div_val);

    /* ���״̬λ */
  amhw_lpc_spi_stat_clear(p_hw_spi,
                      AMHW_LPC_SPI_STAT_RXOVERRUN   |
              AMHW_LPC_SPI_STAT_TXUNDERRUN  |
              AMHW_LPC_SPI_STAT_SELNASSERT  |
              AMHW_LPC_SPI_STAT_SELNDEASSERT);

  /* ʹ��SPI���շ�������ж�,�ڴӻ�ģʽ�²Ż�������  */
  amhw_lpc_spi_int_enable(p_hw_spi,
                AMHW_LPC_SPI_INTENSET_RXOVERRUN |
                AMHW_LPC_SPI_INTENSET_TXUNDERRUN);

    return AM_OK;
}



am_local
void __spi_dma_isr (void *p_arg, int stat)
{
    am_lpc82x_spi_dma_dev_t  *p_this   = (am_lpc82x_spi_dma_dev_t *)p_arg;
    amhw_lpc_spi_t           *p_hw_spi = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    /* ������ж�A���� */
    if (stat == AM_LPC82X_DMA_STAT_INTA) {

        if (p_this->dma_trans_flg == 1) {
            p_this->dma_trans_num -= 1024;
            p_this->dma_trans_count++;

            /* ���Ŵ��䵱ǰtrans */
            __spi_mst_sm_event(p_this, __SPI_EVT_DMA_TRANS_DATA);

        /* ������ǰ�����Ѿ�С��1024�����ȣ���һ���жϲ���ʱ����ǰ��Tran�϶�������� */
        } else {

            /* ��¼�ɹ������ֽ��� */
            if (p_this->p_cur_trans->p_txbuf != NULL) {
                p_this->p_cur_msg->actual_length += (p_this->p_cur_trans->nbytes)
                                *(p_this->p_cur_spi_dev->bits_per_word < 9 ? 1 : 2);
            }

            /* ��һ��trans������� */
            __spi_mst_sm_event(p_this, __SPI_EVT_TRANS_LAUNCH);

            /* �ȴ�SPI���ݳ��׷��ͽ��� */
             while(!(amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_IDLE));
        }

    } else {
        /* �ж�Դ��ƥ�� */
    }
}

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
am_static_inline
void __spi_msg_in (am_lpc82x_spi_dma_dev_t *p_dev, struct am_spi_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                                             &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_spi_message *__spi_msg_out (am_lpc82x_spi_dma_dev_t *p_dev)
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
    am_lpc82x_spi_dma_dev_t *p_this   = (am_lpc82x_spi_dma_dev_t *)p_drv;
    amhw_lpc_spi_t   *p_hw_spi = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    int key;

    p_this->p_cur_spi_dev  = p_dev;                         /* ����ǰ�豸������Ϣ���� */
    p_this->p_cur_msg      = p_msg;                         /* ����ǰ�豸������Ϣ���� */

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
    if (p_this->busy) {
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


/**
 * \brief  SPI ʹ��DMA����
 */
am_local
int __spi_dma_trans (am_lpc82x_spi_dma_dev_t *p_dev)
{
    am_lpc82x_spi_dma_dev_t             *p_this      = (am_lpc82x_spi_dma_dev_t *)p_dev;
    const am_lpc82x_spi_dma_devinfo_t   *p_devinfo   = p_this->p_devinfo;
    amhw_lpc_spi_t                      *p_hw_spi    = (amhw_lpc_spi_t *)(p_devinfo->spi_regbase);
    am_spi_transfer_t                   *p_cur_trans = p_dev->p_cur_trans;
    am_lpc82x_dma_controller_t          *p_ctr_tx    = p_this->p_ctr_tx;
    am_lpc82x_dma_controller_t          *p_ctr_rx    = p_this->p_ctr_rx;

    const uint16_t                      *p_tx_buf    = NULL; /* ָ���û����ͻ�����ָ�� */
          uint16_t                      *p_rx_buf    = NULL; /* ָ���û����ջ�����ָ�� */

          p_this->rx_trash      = 0;                         /* �������ݵ���ʱ���ձ��� */

          p_this->p_tx_buf_eot = 0;                          /* һ֡�е����һ������ */



    uint8_t    eot_nbyte    = 0;    /* ���ͽ����ֵ������ֽ��� */
    uint32_t   dma_flags[3] = {0};  /* DMA����ͨ�������� */

    /* ֻ���ղ��������� */
    if (p_cur_trans->p_txbuf == NULL) {
        if (p_cur_trans->flags & AM_SPI_READ_MOSI_HIGH) {
            p_tx_buf = &__const_high;                       /* MOSI����ʱ�ߵ�ƽ */
        } else {
            p_tx_buf = &__const_low;                        /* MOSI����ʱ�͵�ƽ */
        }
        p_this->p_tx_buf_eot = AM_SBF(p_cur_trans->bits_per_word - 1, 24) |
                       *((uint16_t *)p_tx_buf);

    /* ���ڷ������� */
    } else {
        p_tx_buf = (const uint16_t *)p_cur_trans->p_txbuf; /* MOSI�����û����� */
        if (p_cur_trans->bits_per_word > 8) {

            /*
             * �������������SPI�����ݿ��ƼĴ���TXDATCTL����16λ�����÷������ݵĻ�������
             * ��24 ~ 27λ�����ô�������ݿ��, ��20λ�����ô���Ľ���(���������һ�δ�������SPI���ͷ�Ƭѡ�ź�)
             *
             */
            p_this->p_tx_buf_eot = AM_SBF(p_cur_trans->bits_per_word - 1, 24) |
                           ((uint16_t *)p_tx_buf)[p_cur_trans->nbytes/2 - 1];
        } else {
            p_this->p_tx_buf_eot = AM_SBF(p_cur_trans->bits_per_word - 1, 24) |
                           ((uint8_t *)p_tx_buf)[p_cur_trans->nbytes - 1];
        }
    }

    /* ����֡���������һ���ַ��Ƿ����Ƭѡ�źţ�Ӳ��Ƭѡ�� */
    p_this->p_tx_buf_eot |= AMHW_LPC_SPI_TXDATCTL_EOT;

    /* ֻ���Ͳ��������� */
    if (p_cur_trans->p_rxbuf == NULL) {
        p_rx_buf = &p_this->rx_trash ;                           /* ָ��������������� */

      /* ���ڽ������� */
    } else {
       p_rx_buf = p_cur_trans->p_rxbuf;                 /* ָ���û����ջ����� */
    }

    /* DMA����ͨ������ */
    dma_flags[0] = AM_LPC82X_DMA_XFER_VALID        |    /* ��ǰͨ����������Ч */
                   AM_LPC82X_DMA_XFER_RELOAD       |    /* ��������ͨ�������� */
                   AM_LPC82X_DMA_XFER_SWTRIG       |    /* ������� */
                   AM_LPC82X_DMA_XFER_DSTINC_NOINC;     /* ����Ŀ���ַ������ */

    /* DMA���ͽ�����ͨ������ */
    dma_flags[1] = AM_LPC82X_DMA_XFER_VALID        |    /* ��ǰͨ����������Ч */
                   AM_LPC82X_DMA_XFER_SWTRIG       |    /* ������� */
                   AM_LPC82X_DMA_XFER_CLRTRIG      |    /* ���������־ */
                   AM_LPC82X_DMA_XFER_DSTINC_NOINC |    /* ����Ŀ���ַ������ */
                   AM_LPC82X_DMA_XFER_WIDTH_32BIT  |    /* ���ݿ��32λ */
                   AM_LPC82X_DMA_XFER_SRCINC_NOINC;     /* Դ��ַ������ */


    /* DMA����ͨ������ */
    dma_flags[2] = AM_LPC82X_DMA_XFER_VALID        |      /* ��ǰ������������Ч */
                   AM_LPC82X_DMA_XFER_SWTRIG       |      /* ������� */
                   AM_LPC82X_DMA_XFER_CLRTRIG      |      /* ���������־ */
                   AM_LPC82X_DMA_XFER_SRCINC_NOINC |      /* Դ��ַ������ */
                   AM_LPC82X_DMA_XFER_SETINTA;            /* ʹ���ж�A */

    /* ����DMA����λ�� */
    if (p_cur_trans->bits_per_word > 8) {
        dma_flags[0] |= AM_LPC82X_DMA_XFER_WIDTH_16BIT;
        dma_flags[2] |= AM_LPC82X_DMA_XFER_WIDTH_16BIT;
        eot_nbyte     = 2;
    } else {
        dma_flags[0] |= AM_LPC82X_DMA_XFER_WIDTH_8BIT;
        dma_flags[2] |= AM_LPC82X_DMA_XFER_WIDTH_8BIT;
        eot_nbyte     = 1;
    }

    /* ���ͻ�������Ч */
    if (p_cur_trans->p_txbuf != NULL) {
        dma_flags[0] |= AM_LPC82X_DMA_XFER_SRCINC_1X;      /* Դ��ַ������� */
    } else {
        dma_flags[0] |= AM_LPC82X_DMA_XFER_SRCINC_NOINC;   /* Դ��ַ������ */
    }

    /* ���ջ�������Ч */
    if (p_cur_trans->p_rxbuf != NULL) {
        dma_flags[2] |= AM_LPC82X_DMA_XFER_DSTINC_1X;      /* Ŀ���ַ������� */
    } else {
        dma_flags[2] |= AM_LPC82X_DMA_XFER_DSTINC_NOINC ;            /* Ŀ���ַ������   */
    }

    /* ��ֻ����һ�δ���ʱ */
    if (p_this->dma_trans_num == 1) {

        /* ����������ͨ�������� */
        am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[0],                                  /* ������ */
                                        (uint32_t)&p_this->p_tx_buf_eot,                             /* Դ��BUFF */
                                        (uint32_t)&(p_hw_spi->txdatctl),                     /* Ŀ��BUFF */
                                         4,                                                  /* TX�ֽ��� */
                                         dma_flags[1]);                                      /* �������� */
        /* RX */
        if (p_cur_trans->p_rxbuf != NULL) {
            /* ����RXͨ�������� */
            am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                  /* ������ */
                                            (uint32_t)&(p_hw_spi->rxdat),                        /* Դ��BUFF */
                                            (uint32_t)&p_rx_buf[p_this->dma_trans_count * 512 * eot_nbyte], /* Ŀ��BUFF */
                                            p_this->dma_trans_num * eot_nbyte,                   /* RX�ֽ��� */                                            dma_flags[2]);                                       /* �������� */
        } else {

            /* ����RXͨ�������� */
            am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                  /* ������ */
                                            (uint32_t)&(p_hw_spi->rxdat),                        /* Դ��BUFF */
                                            (uint32_t)p_rx_buf,                                  /* Ŀ��BUFF */
                                            p_this->dma_trans_num * eot_nbyte,                   /* TX�ֽ��� */
                                            dma_flags[2]);

        }

        p_this->dma_trans_flg = 0;

    /* ���Ͷ�δ���ʱ */
    } else {

         /* ���䳬��1024������ʱ */
         if (p_this->dma_trans_num > 1024) {

             /* TX */
             if (p_cur_trans->p_txbuf != NULL) {
                 /* ����TXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[0],                                    /* ������.  */
                                                  (uint32_t)&p_tx_buf[p_this->dma_trans_count * 512 * eot_nbyte],  /* Դ��BUFF */
                                                  (uint32_t)&(p_hw_spi->txdat),                         /* Ŀ��BUFF */
                                                  1024 *  eot_nbyte,                                    /* TX�ֽ��� */
                                                  dma_flags[0]);                                        /* �������� */
             } else {

                 /* ����TXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[0],                                    /* ������.  */
                                                  (uint32_t)p_tx_buf,                                   /* Դ��BUFF */
                                                  (uint32_t)&(p_hw_spi->txdat),                         /* Ŀ��BUFF */
                                                  1024 *  eot_nbyte,                                    /* TX�ֽ��� */
                                                  dma_flags[0]);

             }

             /* RX */
             if (p_cur_trans->p_rxbuf != NULL) {

                 /* ����RXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                    /* ������ */
                                                 (uint32_t)&(p_hw_spi->rxdat),                          /* Դ��BUFF */
                                                 (uint32_t)&p_rx_buf[p_this->dma_trans_count * 512 * eot_nbyte],   /* Ŀ��BUFF */
                                                  1024 *  eot_nbyte,                                    /* RX�ֽ��� */
                                                  dma_flags[2]);                                        /* �������� */
             } else {
                 /* ����RXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                      /* ������ */
                                                 (uint32_t)&(p_hw_spi->rxdat),                            /* Դ��BUFF */
                                                 (uint32_t)p_rx_buf,                                      /* Ŀ��BUFF */
                                                  1024 *  eot_nbyte,                                      /* RX�ֽ��� */
                                                  dma_flags[2]);                                          /* �������� */

             }

             /*����Ǵ��䳤�ȴ���1024������,��ʱ����Ҫ��������������� */
             p_this->dma_trans_flg = 1;

         } else { /* ����С�ڻ����1024������ʱ  */

             /* TX */
             if (p_cur_trans->p_txbuf != NULL) {
                 /* ����TXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[0],                                    /* ������ */
                                                  (uint32_t)&p_tx_buf[p_this->dma_trans_count * 512 * eot_nbyte],  /* Դ��BUFF */
                                                  (uint32_t)&(p_hw_spi->txdat),                         /* Ŀ��BUFF */
                                                  p_this->dma_trans_num * eot_nbyte - eot_nbyte,        /* TX�ֽ��� */
                                                  dma_flags[0]);                                        /* �������� */
             } else {

                 /* ����TXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[0],                                    /* ������.  */
                                                  (uint32_t)p_tx_buf,                                   /* Դ��BUFF */
                                                  (uint32_t)&(p_hw_spi->txdat),                         /* Ŀ��BUFF */
                                                  p_this->dma_trans_num * eot_nbyte - eot_nbyte,        /* TX�ֽ��� */
                                                  dma_flags[0]);

             }

             /* ����������ͨ�������� */
             am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[1],              /* ������ */
                                             (uint32_t)&p_this->p_tx_buf_eot,         /* Դ��BUFF */
                                             (uint32_t)&(p_hw_spi->txdatctl), /* Ŀ��BUFF */
                                              4,                              /* TX�ֽ��� */
                                              dma_flags[1]);                  /* �������� */

             /* RX */
             if (p_cur_trans->p_rxbuf != NULL) {


                 /* ����RXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                    /* ������ */
                                                 (uint32_t)&(p_hw_spi->rxdat),                          /* Դ��BUFF */
                                                 (uint32_t)&p_rx_buf[p_this->dma_trans_count * 512 * eot_nbyte],   /* Ŀ��BUFF */
                                                 p_this->dma_trans_num * eot_nbyte,                     /* TX�ֽ��� */
                                                 dma_flags[2]);

             } else {
                 /* ����RXͨ�������� */
                 am_lpc82x_dma_xfer_desc_build(&p_this->g_desc[2],                                      /* ������ */
                                                 (uint32_t)&(p_hw_spi->rxdat),                            /* Դ��BUFF */
                                                 (uint32_t)p_rx_buf,                                      /* Ŀ��BUFF */
                                                 p_this->dma_trans_num * eot_nbyte,                       /* TX�ֽ��� */
                                                 dma_flags[2]);                                           /* �������� */

             }


             p_this->dma_trans_flg = 0;

         }


         if (p_this->dma_trans_flg == 0) {
             /* DMA���ӷ���ͨ�� */
             am_lpc82x_dma_xfer_desc_link(&p_this->g_desc[0], &p_this->g_desc[1]);
         }
    }

//    if (amhw_lpc82x_dma_chan_periph_is_enable(AMHW_LPC82X_DMA, p_ctr_tx->chan))


    /* ��λƬѡ�ź� */
    __spi_cs_on(p_this, p_this->p_cur_spi_dev);

    /* ����DMA���䣬���Ͽ�ʼ���� */
    am_lpc82x_dma_xfer_desc_startup(p_ctr_rx,
                                    &p_this->g_desc[2],
                                    __spi_dma_isr,
                                    (void *)p_this);

    /* ����DMA���䣬���Ͽ�ʼ���� */
    am_lpc82x_dma_xfer_desc_startup(p_ctr_tx,
                                    &p_this->g_desc[0],
                  __spi_dma_isr,
                                    (void *)p_this);
    return AM_OK;

}

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
int __spi_mst_sm_event (am_lpc82x_spi_dma_dev_t *p_dev, uint32_t event)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    volatile uint32_t new_event = __SPI_EVT_NONE;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    while (1) {

        if (new_event != __SPI_EVT_NONE) {     /* ������¼��Ƿ������ڲ� */
            event     = new_event;
            new_event = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        case __SPI_ST_IDLE:         /* ���������ڿ���״̬ */
        {
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ����״̬�ȴ�����Ϣ�������������� */
            }
            /* �л�����Ϣ��ʼ״̬������break */
        }
        /* No break */

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
                                         AMHW_LPC_SPI_INTENCLR_SELNASSERT |
                                         AMHW_LPC_SPI_INTENCLR_SELNDEASSERT);
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

                event     = new_event;
                new_event = __SPI_EVT_NONE;
            }
        }
        /* No break */

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

                /* ����SPI������� */
                __spi_config(p_dev);

                /* ����DMA��������ݳ��� */
                if (p_cur_trans->bits_per_word > 8) {
                    p_dev->dma_trans_num = p_cur_trans->nbytes / 2;
                } else {
                    p_dev->dma_trans_num = p_cur_trans->nbytes;
                }

                p_dev->dma_trans_flg = 0;
                p_dev->dma_trans_count = 0;

                /* ��һ״̬��ʹ��DMA�������� */
               __SPI_NEXT_STATE(__SPI_ST_DMA_TRANS_DATA, __SPI_EVT_DMA_TRANS_DATA);
            }
            break;
        }

        case __SPI_ST_DMA_TRANS_DATA:    /* DMA�������� */
        {
            if (event != __SPI_EVT_DMA_TRANS_DATA) {
                return -AM_EINVAL;  /* ��������״̬�ȴ�����Ϣ�����Ƿ������� */
            }

            if (p_dev->dma_trans_num > 1024) {
                /* ��һ״̬���Ƿ���״̬ */
                __SPI_NEXT_STATE(__SPI_ST_DMA_TRANS_DATA, __SPI_EVT_NONE);
            } else {
                 /* ��һ״̬�����»�ȡ��һ��trans���д���  */
                __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_NONE);
            }


            /* ʹ��DMA���� */
            __spi_dma_trans(p_dev);

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
am_spi_handle_t am_lpc82x_spi_dma_init (am_lpc82x_spi_dma_dev_t           *p_dev,
                                        const am_lpc82x_spi_dma_devinfo_t *p_devinfo)
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

    p_dev->dma_trans_count = 0;
    p_dev->dma_trans_flg   = 0;
    p_dev->dma_trans_num   = 0;

    p_dev->state            = __SPI_ST_IDLE;     /* ��ʼ��Ϊ����״̬ */

    am_list_head_init(&(p_dev->msg_list));

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }


    /* ����DMA����ͨ�� */
    p_dev->p_ctr_tx = am_lpc82x_dma_controller_get(p_devinfo->dma_chan_tx,
                                                   p_devinfo->dma_chan_prio_tx |
                                                   DMA_CHAN_OPT_PERIPH_REQ_EN);
    /* ����DMA����ͨ�� */
    p_dev->p_ctr_rx = am_lpc82x_dma_controller_get(p_devinfo->dma_chan_rx,
                                                   p_devinfo->dma_chan_prio_rx |
                                                   DMA_CHAN_OPT_PERIPH_REQ_EN);

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_lpc82x_spi_dma_deinit (am_spi_handle_t handle)
{
    am_lpc82x_spi_dma_dev_t *p_dev    = (am_lpc82x_spi_dma_dev_t *)handle;
    amhw_lpc_spi_t          *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_lpc_spi_disable(p_hw_spi);

    /* �ͷ�DMA������ */
    am_lpc82x_dma_controller_release(p_dev->p_ctr_tx);
    am_lpc82x_dma_controller_release(p_dev->p_ctr_rx);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}
