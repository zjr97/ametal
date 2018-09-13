/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief GPIO ģ��SPI ����
 *
 * \internal
 * \par Modification history
 * - 1.00 18-04-10  vir, first implementation.
 * \endinternal
 */

#include "am_spi_gpio.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_delay.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
/**
 * \brief ״̬����
 */
#define __SPI_GPIO_ST_IDLE             (0x10u)          /* ����״̬ */
#define __SPI_GPIO_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬ */
#define __SPI_GPIO_ST_TRANS_START      (0x12u)          /* ��ȡ���俪ʼ״̬ */
#define __SPI_GPIO_ST_TX_RX_DATA       (0x13u)          /* �������� */

/**
 * \brief �¼�����
 */
#define __SPI_GPIO_EVT_NONE            (0xFFu)          /* ���¼� */
#define __SPI_GPIO_EVT_MSG_LAUNCH      (0xFEu)          /* ��ʼ����һ���µ���Ϣ */
#define __SPI_GPIO_EVT_TRANS_LAUNCH    (0xFDu)          /* ��ʼ����һ���µĴ��� */

/**
 * \brief ����δʹ�õ�
 */
#define __VAR_NO_USE(a)      (void)(a)

/* ��ȡ��ǰ��Ϣ */
#define __spi_gpio_cur_msg(p_dev) \
    ((p_dev)->p_cur_msg)

/* �жϴ������Ƿ�Ϊ�� */
#define __spi_gpio_trans_empty(p_dev) \
                  am_list_empty(&(p_cur_msg->transfers))

/* ��ȡ��ǰ������ */
#define __spi_gpio_cur_trans(p_dev) \
    ((p_dev)->p_cur_trans)


/******************************************************************************/
am_local int __spi_gpio_info_get(void *p_drv, am_spi_info_t *p_info);
am_local int __spi_gpio_set_up(void *p_drv, struct am_spi_device *p_dev);
am_local int __spi_gpio_msg_start (void              *p_drv,
                                   am_spi_device_t   *p_dev,
                                   am_spi_message_t  *p_msg);

am_local int __spi_mst_sm_event(am_spi_gpio_dev_t *p_dev, uint32_t event);

am_local struct am_spi_drv_funcs   __g_spi_gpio_drv_funcs = {
        __spi_gpio_info_get,
        __spi_gpio_set_up,
        __spi_gpio_msg_start,
 };


/******************************************************************************
 SPI Э��ʵ��
*******************************************************************************/

/**
 * \biref ��ʱ
 */
am_local
void __spi_gpio_delay(am_spi_gpio_dev_t *p_this)
{
    volatile unsigned int i = p_this->p_devinfo->speed_exp;

    while (i--);
}

/**
 * \brief ����SCK�Ŀ���״̬
 */
am_static_inline
void __spi_gpio_sck_idle_state_set( am_spi_gpio_dev_t *p_this )
{
    p_this->sck_state = (p_this->p_cur_spi_dev->mode & AM_SPI_CPOL)? 1:0;
    am_gpio_set(p_this->p_devinfo->sck_pin, p_this->sck_state);
}

/**
 * \brief ��תʱ��SCK
 */
am_static_inline
void __spi_gpio_sck_toggle(am_spi_gpio_dev_t *p_this)
{
    p_this->sck_state = !p_this->sck_state;
    am_gpio_set(p_this->p_devinfo->sck_pin, p_this->sck_state);
}


/**
 * \brief SPI ��д1~32λ����
 */
am_local uint32_t __gpio_spi_rw_data (am_spi_gpio_dev_t *p_this,
                                      uint32_t           w_data,
                                      uint8_t            bits_per_word)
{
    am_spi_device_t *p_dev                 = p_this->p_cur_spi_dev;
    const am_spi_gpio_devinfo_t *p_devinfo = p_this->p_devinfo;

    uint32_t         r_data = 0;
    uint8_t          i      = 0;
    uint8_t          bit    = 0;

    if (p_dev->mode & AM_SPI_LSB_FIRST) {
        bit = 0;
    } else {
        bit = bits_per_word - 1;
    }

    /* ����ʱ����λ�����һ������ */
    am_gpio_set(p_devinfo->mosi_pin, AM_BIT_GET(w_data, bit));

    if (p_dev->mode & AM_SPI_CPHA) {
        __spi_gpio_sck_toggle(p_this);
    }
    __spi_gpio_delay(p_this);

    if ( p_dev->mode & AM_SPI_3WIRE ) {
        am_gpio_pin_cfg(p_devinfo->mosi_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        AM_BIT_MODIFY(r_data, bit, am_gpio_get(p_devinfo->mosi_pin));
        am_gpio_pin_cfg(p_devinfo->mosi_pin,
           AM_BIT_GET(w_data, bit) ? AM_GPIO_OUTPUT_INIT_HIGH :AM_GPIO_OUTPUT_INIT_LOW);
    } else {
        AM_BIT_MODIFY(r_data, bit, am_gpio_get(p_devinfo->miso_pin));
    }

    __spi_gpio_sck_toggle(p_this);
    __spi_gpio_delay(p_this);

    for (i=0; i< (p_dev->bits_per_word -1); i++) {

        if (p_dev->mode & AM_SPI_LSB_FIRST) {
            bit++;
        } else {
            bit--;
        }

        am_gpio_set(p_devinfo->mosi_pin, AM_BIT_GET(w_data, bit));

        __spi_gpio_sck_toggle(p_this);
        __spi_gpio_delay(p_this);

        if ( p_dev->mode & AM_SPI_3WIRE ) {
            am_gpio_pin_cfg(p_devinfo->mosi_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
            AM_BIT_MODIFY(r_data, bit, am_gpio_get(p_devinfo->mosi_pin));
            am_gpio_pin_cfg(p_devinfo->mosi_pin, AM_GPIO_OUTPUT_INIT_HIGH);
        } else {
            AM_BIT_MODIFY(r_data, bit, am_gpio_get(p_devinfo->miso_pin));
        }

        __spi_gpio_sck_toggle(p_this);
        __spi_gpio_delay(p_this);
    }
    __spi_gpio_sck_idle_state_set(p_this);

    return r_data;
}

/*
 * \brief ���������ݴ���
 */
am_local
void __spi_gpio_trans_data_start(am_spi_gpio_dev_t *p_this,
                                 am_spi_transfer_t *p_trans)
{
    uint32_t  len = 0;

    if( p_trans->bits_per_word > 32) {
        return;
    }

    if(p_trans->bits_per_word == 0) {
        p_trans->bits_per_word = p_this->p_cur_spi_dev->bits_per_word;
    }
    switch( AM_ROUND_UP(p_trans->bits_per_word,8)) {

    /* ���� 1 ~ 8 λ���� */
    case 8:
    {
        uint8_t  *p_tx    = NULL;
        uint8_t  *p_rx    = NULL;
        uint8_t   tx_data = 0;
        uint8_t   rx_data = 0;

        p_tx  = (uint8_t *)p_trans->p_txbuf;
        p_rx  = (uint8_t *)p_trans->p_rxbuf;
        len   = p_trans->nbytes / 1;

        if( p_trans->flags & AM_SPI_READ_MOSI_HIGH ) {
            tx_data = 0XFF;
        }

        while (len--) {
            if (p_tx) {
                tx_data = *p_tx;
                p_tx++;
            }

            rx_data = __gpio_spi_rw_data(p_this, tx_data, p_trans->bits_per_word);

            if (p_rx) {
                *p_rx = rx_data;
                p_rx++;
            }
        }
        break;
    }

    /* ���� 9 ~ 16 λ���� */
    case 16:
    {
        uint16_t  *p_tx    = NULL;
        uint16_t  *p_rx    = NULL;
        uint16_t   tx_data = 0;
        uint16_t   rx_data = 0;

        p_tx  = (uint16_t *)p_trans->p_txbuf;
        p_rx  = (uint16_t *)p_trans->p_rxbuf;
        len   = p_trans->nbytes / 2;

        if( p_trans->flags & AM_SPI_READ_MOSI_HIGH ) {
            tx_data = 0XFFFF;
        }

        while (len--) {
            if (p_tx) {
                tx_data = *p_tx;
                p_tx++;
            }

            rx_data = __gpio_spi_rw_data(p_this, tx_data, p_trans->bits_per_word);

            if (p_rx) {
                *p_rx = rx_data;
                p_rx++;
            }
        }
        break;
    }

    /* ���� 17 ~ 32 λ���� */
    case 24:
    case 32:
    {
        uint32_t  *p_tx    = NULL;
        uint32_t  *p_rx    = NULL;
        uint32_t   tx_data = 0;
        uint32_t   rx_data = 0;

        p_tx  = (uint32_t *)p_trans->p_txbuf;
        p_rx  = (uint32_t *)p_trans->p_rxbuf;
        len   = p_trans->nbytes / 4;

        if( p_trans->flags & AM_SPI_READ_MOSI_HIGH ) {
            tx_data = 0XFFFF;
        }

        while (len--) {
            if (p_tx) {
                tx_data = *p_tx;
                p_tx++;
            }

            rx_data = __gpio_spi_rw_data(p_this, tx_data, p_trans->bits_per_word);

            if (p_rx) {
                *p_rx = rx_data;
                p_rx++;
            }
        }
        break;
    }

    default:
        break;
    }
}

/******************************************************************************/

/**
 * \brief Ӳ����ʼ��
 */
am_local void __spi_gpio_hw_init(const am_spi_gpio_devinfo_t *p_devinfo)
{
   am_gpio_pin_cfg(p_devinfo->sck_pin,
                         AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL);

   if (p_devinfo->miso_pin != -1) {
       am_gpio_pin_cfg(p_devinfo->miso_pin,
                         AM_GPIO_INPUT | AM_GPIO_PULLUP);
   }

   if(p_devinfo->mosi_pin != -1) {
       am_gpio_pin_cfg(p_devinfo->mosi_pin,
                          AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL );
   }
}

/**
* \brief ���һ�� message �������������б�ĩβ
*
* \attention ���ô˺�����������������
*/
am_static_inline
void __spi_gpio_msg_in (am_spi_gpio_dev_t *p_dev, struct am_spi_message *p_msg)
{
 am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                 &(p_dev->msg_list));
}

/**
* \brief �ӿ����������б��ͷȡ��һ�� message
*
* \attention ���ô˺�����������������
*/
am_static_inline
struct am_spi_message *__spi_gpio_msg_out (am_spi_gpio_dev_t *p_dev)
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
struct am_spi_transfer *__spi_gpio_trans_out (am_spi_message_t *msg)
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
* \brief Ĭ��CS�ſ��ƺ������ߵ�ƽ��Ч
*/
am_local
void __spi_gpio_default_cs_ha (am_spi_device_t *p_dev, int state)
{
 am_gpio_set(p_dev->cs_pin, state ? 1 : 0);
}

/**
* \brief Ĭ��CS�ſ��ƺ������͵�ƽ��Ч
*/
am_local
void __spi_gpio_default_cs_la (am_spi_device_t *p_dev, int state)
{
 am_gpio_set(p_dev->cs_pin, state ? 0 : 1);
}

/**
* \brief Ĭ��CS�ſ��ƺ�������Ӳ�����п���
*/
am_local
void __spi_gpio_default_cs_dummy (am_spi_device_t *p_dev, int state)
{
 return;
}

/**
* \brief CS���ż���
*/
am_local
void __spi_gpio_cs_on (am_spi_gpio_dev_t *p_this, am_spi_device_t *p_dev)
{
 p_dev->pfunc_cs(p_dev, 1);
}

/**
 * \brief CS����ȥ��
 */
am_local
void __spi_gpio_cs_off (am_spi_gpio_dev_t *p_this, am_spi_device_t   *p_dev)
{
    p_dev->pfunc_cs(p_dev, 0);
}

/**
 * \brief SPI����
 */
void __spi_gpio_config(am_spi_gpio_dev_t *p_this, am_spi_transfer_t *p_trans)
{
    __spi_gpio_sck_idle_state_set(p_this);

}


/******************************************************************************/
/**
 * \brief ��ȡSPI��������Ϣ
 */
am_local int __spi_gpio_info_get(void *p_drv, am_spi_info_t *p_info)
{
    if (p_info == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʵ��� PCLK */
    p_info->max_speed = 0;
    p_info->min_speed = 0;
    p_info->features  = AM_SPI_CS_HIGH   |
                        AM_SPI_LSB_FIRST |
                        AM_SPI_MODE_0    |
                        AM_SPI_MODE_1    |
                        AM_SPI_MODE_2    |
                        AM_SPI_MODE_3    |
                        AM_SPI_3WIRE     |
                        AM_SPI_NO_CS     ;   /* features */
    return AM_OK;
}

/**
 * \brief ����SPI�ӻ��豸
 */
am_local int __spi_gpio_set_up(void *p_drv, struct am_spi_device *p_dev)
{
    am_spi_gpio_dev_t *p_this = (am_spi_gpio_dev_t *)p_drv;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* Ĭ������Ϊ8λ����󲻳���16λ */
    if (p_dev->bits_per_word == 0) {
        p_dev->bits_per_word = 8;
    } else if (p_dev->bits_per_word > 32) {
        return -AM_ENOTSUP;
    }

    /* ��Ƭѡ���� */
    if (p_dev->mode & AM_SPI_NO_CS) {
        p_dev->pfunc_cs = __spi_gpio_default_cs_dummy;

    /* ��Ƭѡ���� */
    }  else {

        /* ���ṩ��Ĭ��Ƭѡ���� */
        if (p_dev->pfunc_cs == NULL) {

            /* Ƭѡ�ߵ�ƽ��Ч */
            if (p_dev->mode & AM_SPI_CS_HIGH) {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_LOW);
                p_dev->pfunc_cs = __spi_gpio_default_cs_ha;

            /* Ƭѡ�͵�ƽ��Ч */
            } else {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_HIGH);
                p_dev->pfunc_cs = __spi_gpio_default_cs_la;
            }
        }
    }

    /* ���Ƭѡ�ź� */
    __spi_gpio_cs_off(p_this, p_dev);

    return AM_OK;
}

/**
 * \brief ��Ϣ��ʼ
 */
am_local int __spi_gpio_msg_start (void              *p_drv,
                                   am_spi_device_t   *p_dev,
                                   am_spi_message_t  *p_msg)
{
    am_spi_gpio_dev_t *p_this    = (am_spi_gpio_dev_t *)p_drv;
    int key;

    if ( (p_this             == NULL) ||
         (p_dev              == NULL) ||
         (p_msg              == NULL)) {

        return -AM_EINVAL;
    }

    p_msg->p_spi_dev = p_dev; /* ������Ϣ��Ӧ���豸*/

    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_this->busy == AM_TRUE) {

        __spi_gpio_msg_in(p_this, p_msg);

        am_int_cpu_unlock(key);

        return AM_OK;

    } else {
        p_this->busy = AM_TRUE;
        __spi_gpio_msg_in(p_this, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        return __spi_mst_sm_event(p_this, __SPI_GPIO_EVT_MSG_LAUNCH);
    }
}

/******************************************************************************/

#define __spi_gpio_next_state(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/**
 * \brief  SPI_GPIO ״̬������
 */
am_local int __spi_mst_sm_event(am_spi_gpio_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t new_event = __SPI_GPIO_EVT_NONE;
    
    __VAR_NO_USE(event);
 
    while (1) {

        /* ����Ƿ����µ��¼���״̬���ڲ����� */
        if (new_event != __SPI_GPIO_EVT_NONE) {
            event     = new_event;
            new_event = __SPI_GPIO_EVT_NONE;
        }

        switch (p_dev->state) {

        /*
         * ����״̬�Ϳ�ʼ��Ϣ����״̬Ҫ�����������һ�����¼�ֻӦ�ǣ�
         * __SPI_EVT_TRANS_LAUNCH
         */
        case __SPI_GPIO_ST_IDLE:
        case __SPI_GPIO_ST_MSG_START:
        {
            am_spi_message_t *p_cur_msg = NULL;

            int key;

            key = am_int_cpu_lock();
            p_cur_msg        = __spi_gpio_msg_out(p_dev);
            p_dev->p_cur_msg     = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {
                p_dev->busy = AM_FALSE;
            }

            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {

                __spi_gpio_next_state(__SPI_GPIO_ST_IDLE, __SPI_GPIO_EVT_NONE);

                break;
            } else {

                p_dev->p_cur_spi_dev = p_cur_msg->p_spi_dev;

                p_cur_msg->actual_length = 0;

                __spi_gpio_next_state(__SPI_GPIO_ST_TRANS_START,
                                      __SPI_GPIO_EVT_TRANS_LAUNCH);

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                event     = new_event;
                new_event = __SPI_GPIO_EVT_NONE;

            }
        }
        /* no break */

        /*�����俪ʼ */
        case __SPI_GPIO_ST_TRANS_START:
        {
            struct am_spi_message *p_cur_msg =  __spi_gpio_cur_msg(p_dev);

            /* ��ǰ��Ϣ������� */
            if (__spi_gpio_trans_empty(p_dev)) {


                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                /* �ص���Ϣ��ɺ���  */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }

                /* Ƭѡ�ر� */
                __spi_gpio_cs_off(p_dev, p_dev->p_cur_spi_dev);

                __spi_gpio_next_state(__SPI_GPIO_ST_MSG_START,
                                            __SPI_GPIO_EVT_MSG_LAUNCH);

            } else {                    /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */

                am_spi_transfer_t *p_cur_trans = __spi_gpio_trans_out(p_cur_msg);
                p_dev->p_cur_trans              = p_cur_trans;

                /* ����SPI ������� */
                __spi_gpio_config(p_dev, p_dev->p_cur_trans);

                /* CSѡͨ */
                __spi_gpio_cs_on(p_dev, p_dev->p_cur_spi_dev);

                __spi_gpio_next_state(__SPI_GPIO_ST_TX_RX_DATA, __SPI_GPIO_EVT_TRANS_LAUNCH);

            }
            break;
        }

        /* ���Ͳ���������״̬ */
        case __SPI_GPIO_ST_TX_RX_DATA:
        {
            struct am_spi_transfer *p_cur_trans = __spi_gpio_cur_trans(p_dev);

            /* ��ʼ�������� */
            __spi_gpio_trans_data_start(p_dev, p_cur_trans);

            if( p_cur_trans->delay_usecs != 0) {
                am_udelay(p_cur_trans->delay_usecs);
            }

            /* Ӱ��Ƭѡ */
            if( 1 == p_cur_trans->cs_change) {
                __spi_gpio_cs_off(p_dev, p_dev->p_cur_spi_dev);
            }

            p_dev->p_cur_msg->actual_length += p_dev->p_cur_trans->nbytes;

            __spi_gpio_next_state(__SPI_GPIO_ST_TRANS_START, __SPI_GPIO_EVT_TRANS_LAUNCH);

            break;
        }


        default:
            break;
        }

        /* ���¼��˳� */
        if (new_event == __SPI_GPIO_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}

/******************************************************************************/

am_spi_handle_t am_spi_gpio_init (am_spi_gpio_dev_t           *p_dev,
                                  const am_spi_gpio_devinfo_t *p_devinfo)
{
    p_dev->p_devinfo = p_devinfo;

    p_dev->spi_serv.p_drv = p_dev;
    p_dev->spi_serv.p_funcs = (struct am_spi_drv_funcs *)&__g_spi_gpio_drv_funcs;

    p_dev->p_cur_trans = NULL;
    p_dev->p_cur_msg   = NULL;
    p_dev->sck_state   = 0;
    p_dev->busy        = AM_FALSE;
    p_dev->state       = __SPI_GPIO_ST_IDLE;

    am_list_head_init(&(p_dev->msg_list));

    __spi_gpio_hw_init(p_devinfo);

    return &(p_dev->spi_serv);
}

void am_spi_gpio_deinit (am_spi_handle_t handle)
{
}

/* end of file */
