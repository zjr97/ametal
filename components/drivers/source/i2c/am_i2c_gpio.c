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
 * \brief I2C implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-04-09  vir, first implementation.
 * \endinternal
 */

#include "am_i2c_gpio.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_delay.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
/**
 * \brief ״̬����
 */
#define __I2C_GPIO_ST_IDLE             (0x10u)          /* ����״̬ */
#define __I2C_GPIO_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬ */
#define __I2C_GPIO_ST_TRANS_START      (0x12u)          /* �������俪ʼ״̬ */
#define __I2C_GPIO_ST_SEND_SLA_ADDR    (0x13u)          /* ���ʹӻ���ַ״̬ */
#define __I2C_GPIO_ST_M_SEND_DATA      (0x14u)          /* ��������״̬ */
#define __I2C_GPIO_ST_M_RECV_DATA      (0x15u)          /* ��������״̬ */
#define __I2C_GPIO_ST_ARBI_LOST        (0x16u)          /* �ٲö�ʧ״̬ */

/**
 * \brief �¼�����
 */

#define __I2C_GPIO_EVT_START_SENT          (0x08u)  /* �Ѵ��Ϳ�ʼ�ź�*/
#define __I2C_GPIO_EVT_RESTART_SENT        (0x10u)  /* �Ѵ��Ϳ�ʼ�ź�*/

#define __I2C_GPIO_EVT_ARBI_LOST           (0x38u)  /* �ٲö�ʧ */

#define __I2C_GPIO_EVT_M_TX_SLA_ACK        (0x18u)     /* д��ַ��Ӧ */
#define __I2C_GPIO_EVT_M_TX_SLA_NACK       (0x20u)     /* д��ַ����Ӧ */
#define __I2C_GPIO_EVT_M_TX_DAT_ACK        (0x28u)     /* ����������Ӧ */
#define __I2C_GPIO_EVT_M_TX_DAT_NACK       (0x30u)     /* ������������Ӧ */

#define __I2C_GPIO_EVT_M_RX_SLA_ACK        (0x40u)     /* ����ַ��Ӧ */
#define __I2C_GPIO_EVT_M_RX_SLA_NACK       (0x48u)     /* ����ַ����Ӧ */
#define __I2C_GPIO_EVT_M_RX_DAT_R_ACK      (0x50u)     /* �������ݷ�����Ӧ */
#define __I2C_GPIO_EVT_M_RX_DAT_R_NACK     (0x58u)     /* �������ݷ�������Ӧ */

#define __I2C_GPIO_EVT_NONE            (0xFFu)          /* ���¼� */
#define __I2C_GPIO_EVT_MSG_LAUNCH      (0xFEu)          /* ��ʼ����һ���µ���Ϣ */
#define __I2C_GPIO_EVT_TRANS_LAUNCH    (0xFDu)          /* ��ʼ����һ���µĴ��� */


#define __I2C_GPIO_USER_DEALY(p_devinfo)   __i2c_gpio_delay(p_devinfo);

#define __I2C_GPIO_SCL_HIGH(p_devinfo)     am_gpio_set(p_devinfo->scl_pin, 1)
#define __I2C_GPIO_SCL_LOW(p_devinfo)      am_gpio_set(p_devinfo->scl_pin, 0)

#define __I2C_GPIO_SDA_HIGH(p_devinfo)     am_gpio_set(p_devinfo->sda_pin, 1)
#define __I2C_GPIO_SDA_LOW(p_devinfo)      am_gpio_set(p_devinfo->sda_pin, 0)

#define __I2C_GPIO_SDA_INPUT(p_devinfo)    \
    am_gpio_pin_cfg(p_devinfo->sda_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP)

#define __I2C_GPIO_SDA_OUTPUT(p_devinfo)   \
    am_gpio_pin_cfg(p_devinfo->sda_pin, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL)

#define __I2C_GPIO_SDA_VAL_GET(p_devinfo)  am_gpio_get(p_devinfo->sda_pin)


/* ��ȡ��ǰ��Ϣ */
#define __i2c_gpio_cur_msg(p_dev) \
    ((p_dev)->p_cur_msg)

/* �жϴ������Ƿ�Ϊ�� */
#define __i2c_gpio_trans_empty(p_dev) \
    ((p_dev)->p_cur_trans >= (p_dev)->p_cur_msg->p_transfers \
                             + (p_dev)->p_cur_msg->trans_num)

/* ��ȡ��ǰ������ */
#define __i2c_gpio_cur_trans(p_dev) \
    ((p_dev)->p_cur_trans)

/* �˶Դ��������Ƿ񳬹� */
#define __i2c_gpio_data_ptr_ov(p_dev) \
    ((p_dev)->data_ptr >= (p_dev)->p_cur_trans->nbytes)

/* �ж��Ƿ������һ������ */
#define __i2c_gpio_data_ptr_last(p_dev) \
    ((p_dev)->data_ptr == (p_dev)->p_cur_trans->nbytes - 1)

/* ��ǰ����  */
#define __i2c_gpio_cur_data(p_dev) \
    ((p_dev)->p_cur_trans->p_buf[(p_dev)->data_ptr])

 /******************************************************************************/

am_local int __i2c_gpio_msg_start(void *p_drv, struct am_i2c_message *p_msg);
 am_local int __i2c_mst_sm_event(am_i2c_gpio_dev_t *p_dev, uint32_t event);

am_local struct am_i2c_drv_funcs   __g_i2c_gpio_drv_funcs = {
         __i2c_gpio_msg_start,
 };


 /******************************************************************************
  I2C Э��ʵ��
 *******************************************************************************/
/**
 * \brief ʱ����ʱ
 */
 am_local void __i2c_gpio_delay (const am_i2c_gpio_devinfo_t *p_devinfo)
 {
     volatile unsigned int i = p_devinfo->speed_exp;

     while (i--);
 }

 /**
  * \brief ��ʼ�ź�
  */
 am_local void __i2c_gpio_start (const am_i2c_gpio_devinfo_t *p_devinfo)
 {
     __I2C_GPIO_SDA_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SCL_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SDA_LOW(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SCL_LOW(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     return;
 }

 /**
  * \brief ֹͣ�ź�
  */
 am_local void __i2c_gpio_stop (const am_i2c_gpio_devinfo_t *p_devinfo)
 {
     __I2C_GPIO_SDA_LOW(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SCL_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SDA_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     return;
 }

 /**
  * \brief ��ȡ��Ӧ״̬
  */
 am_local am_bool_t __i2c_gpio_ack_get (const am_i2c_gpio_devinfo_t *p_devinfo)
 {
     am_bool_t acked = AM_FALSE;

     __I2C_GPIO_SDA_HIGH(p_devinfo);
     __I2C_GPIO_SDA_INPUT(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SCL_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     acked = __I2C_GPIO_SDA_VAL_GET(p_devinfo) ? AM_FALSE : AM_TRUE;

     __I2C_GPIO_SCL_LOW(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);
     __I2C_GPIO_SDA_OUTPUT(p_devinfo);

     return acked;
 }

 /**
  * \brief ������Ӧ
  */
 am_local void __i2c_gpio_ack_put (const am_i2c_gpio_devinfo_t *p_devinfo,
                                   am_bool_t                    ack)
 {
     __I2C_GPIO_SDA_OUTPUT(p_devinfo);

     ack == AM_TRUE ?  __I2C_GPIO_SDA_LOW(p_devinfo)
                   :  __I2C_GPIO_SDA_HIGH(p_devinfo);

     __I2C_GPIO_SCL_HIGH(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

     __I2C_GPIO_SCL_LOW(p_devinfo);
     __I2C_GPIO_USER_DEALY(p_devinfo);

 }

 /**
  * \brief дһ���ֽ�
  */
 am_local am_bool_t __i2c_gpio_write_byte (const am_i2c_gpio_devinfo_t *p_devinfo,
                                           uint8_t                      data)
 {
     int i;

     for (i = 7; i >= 0; i--) {
         AM_BIT_ISSET(data, i) ? __I2C_GPIO_SDA_HIGH(p_devinfo)
                               : __I2C_GPIO_SDA_LOW(p_devinfo);
         __I2C_GPIO_USER_DEALY(p_devinfo);

         __I2C_GPIO_SCL_HIGH(p_devinfo);
         __I2C_GPIO_USER_DEALY(p_devinfo);

         __I2C_GPIO_SCL_LOW(p_devinfo);
         __I2C_GPIO_USER_DEALY(p_devinfo);
     }

     return __i2c_gpio_ack_get(p_devinfo);
 }

 /**
  * \brief ��ȡһ���ֽ�
  */
 am_local uint8_t __i2c_gpio_read_byte (const am_i2c_gpio_devinfo_t *p_devinfo,
                                        am_bool_t                    ack)
 {
     int i;
     uint8_t data;

     __I2C_GPIO_SDA_INPUT(p_devinfo);

     data = 0;
     for (i = 7; i >= 0; i--) {

         __I2C_GPIO_SCL_HIGH(p_devinfo);
         __I2C_GPIO_USER_DEALY(p_devinfo);

         if (__I2C_GPIO_SDA_VAL_GET(p_devinfo)) {
             data |= 1 << i;
         };

         __I2C_GPIO_SCL_LOW(p_devinfo);
         __I2C_GPIO_USER_DEALY(p_devinfo);
     }

     __i2c_gpio_ack_put(p_devinfo, ack);

     return data;
 }

/******************************************************************************/

 /**
  * \brief ���һ�� message �������������б�ĩβ
  *
  * \attention ���ô˺�����������������
  */
 am_static_inline
 void __i2c_gpio_msg_in (am_i2c_gpio_dev_t *p_dev, struct am_i2c_message *p_msg)
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
 struct am_i2c_message *__i2c_gpio_msg_out (am_i2c_gpio_dev_t *p_dev)
 {
     if (am_list_empty_careful(&(p_dev->msg_list))) {
         return NULL;
     } else {
         struct am_list_head *p_node = p_dev->msg_list.next;
         am_list_del(p_node);
         return am_list_entry(p_node, struct am_i2c_message, ctlrdata);
     }
 }


 /**
  * \brief Ӳ����ʼ��
  */
am_local void __i2c_gpio_hw_init(const am_i2c_gpio_devinfo_t *p_devinfo)
{
    am_gpio_pin_cfg(p_devinfo->scl_pin, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL);
    am_gpio_pin_cfg(p_devinfo->sda_pin, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL);
}

/**
 * \brief ��Ϣ��ʼ
 */
am_local int __i2c_gpio_msg_start(void *p_drv, struct am_i2c_message *p_msg)
{
    am_i2c_gpio_dev_t *p_dev    = (am_i2c_gpio_dev_t *)p_drv;
    int key;

    if ( (p_dev              == NULL) ||
         (p_msg              == NULL) ||
         (p_msg->p_transfers == NULL) ||
         (p_msg->trans_num   == 0)) {

        return -AM_EINVAL;
    }

    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_dev->busy == AM_TRUE) {

        __i2c_gpio_msg_in(p_dev, p_msg);

        am_int_cpu_unlock(key);

        return AM_OK;

    } else {
        p_dev->busy = AM_TRUE;
        __i2c_gpio_msg_in(p_dev, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        return __i2c_mst_sm_event(p_dev, __I2C_GPIO_EVT_MSG_LAUNCH);
    }
}


#define __i2c_gpio_next_state(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/**
 * \brief  I2C_GPIO ״̬������
 */
am_local int __i2c_mst_sm_event(am_i2c_gpio_dev_t *p_dev, uint32_t event)
{
    const am_i2c_gpio_devinfo_t *p_devinfo = p_dev->p_devinfo;

    volatile uint32_t new_event = __I2C_GPIO_EVT_NONE;

    while (1) {

        /* ����Ƿ����µ��¼���״̬���ڲ����� */
        if (new_event != __I2C_GPIO_EVT_NONE) {
            event     = new_event;
            new_event = __I2C_GPIO_EVT_NONE;
        }

        switch (p_dev->state) {

        /*
         * ����״̬�Ϳ�ʼ��Ϣ����״̬Ҫ�����������һ�����¼�ֻӦ�ǣ�
         * __I2C_EVT_TRANS_LAUNCH
         */
        case __I2C_GPIO_ST_IDLE:
        case __I2C_GPIO_ST_MSG_START:
        {
            am_i2c_message_t *p_cur_msg = NULL;

            int key;

            key = am_int_cpu_lock();
            p_cur_msg        = __i2c_gpio_msg_out(p_dev);
            p_dev->p_cur_msg = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {
                p_dev->busy = AM_FALSE;
            }

            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {

                __i2c_gpio_next_state(__I2C_GPIO_ST_IDLE, __I2C_GPIO_EVT_NONE);

                break;
            } else {

                p_cur_msg->done_num = 0;
                p_dev->p_cur_trans  = p_cur_msg->p_transfers;
                p_dev->data_ptr     = 0;

                __i2c_gpio_next_state(__I2C_GPIO_ST_TRANS_START,
                                      __I2C_GPIO_EVT_TRANS_LAUNCH);

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                event     = new_event;
                new_event = __I2C_GPIO_EVT_NONE;

            }
        }
        /* no break */

        /*�����俪ʼ */
        case __I2C_GPIO_ST_TRANS_START:
        {
            struct am_i2c_message *p_cur_msg =  __i2c_gpio_cur_msg(p_dev);

            /* ��ǰ��Ϣ������� */
            if (__i2c_gpio_trans_empty(p_dev)) {

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                /* �ص���Ϣ��ɺ���  */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }


                __i2c_gpio_stop(p_devinfo);

                __i2c_gpio_next_state(__I2C_GPIO_ST_IDLE,
                                            __I2C_GPIO_EVT_MSG_LAUNCH);

            } else {                    /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */

                struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;


                p_dev->data_ptr = 0;

                /*
                 * ����Ҫ�����źţ�ֱ�Ӵ��䣬����ͬʱ������������������
                 * 1.�����˱�־ AM_I2C_M_NOSTART
                 * 2.��ǰ���䲻��һ����Ϣ�еĵ�һ������
                 * 3.��ǰ��������һ������ķ���һ��
                 */
                if ((p_cur_trans->flags & AM_I2C_M_NOSTART) &&
                    (p_cur_trans != p_cur_msg->p_transfers) &&
                    ((p_cur_trans->flags & AM_I2C_M_RD) ==
                    ((p_cur_trans - 1)->flags & AM_I2C_M_RD))) {

                    am_bool_t is_read = (p_cur_trans->flags & AM_I2C_M_RD) ?
                                     AM_TRUE : AM_FALSE;

                    if (is_read == AM_TRUE) {

                        /* ������������ */
                        __i2c_gpio_next_state(__I2C_GPIO_ST_M_RECV_DATA,
                                              __I2C_GPIO_EVT_M_RX_SLA_ACK);

                    } else {

                        /* ������������ */
                        __i2c_gpio_next_state(__I2C_GPIO_ST_M_SEND_DATA,
                                              __I2C_GPIO_EVT_M_TX_SLA_ACK);
                    }

                /* ���ʹӻ���ַ */
                } else {

                    /* ��һ�������Ƿ��ʹӻ���ַ */
                    __i2c_gpio_next_state(__I2C_GPIO_ST_SEND_SLA_ADDR,
                                          __I2C_GPIO_EVT_START_SENT);

                    __i2c_gpio_start(p_devinfo);
                }
            }
            break;
        }

        /* ���ʹӻ���ַ */
        case __I2C_GPIO_ST_SEND_SLA_ADDR:
        {
            uint8_t   flag   = 0X00;
            am_bool_t acked  = AM_FALSE;
            struct am_i2c_transfer *p_cur_trans = __i2c_gpio_cur_trans(p_dev);

            /* ���ʹӻ���ַ*/
            if (p_cur_trans->flags & AM_I2C_M_RD) {
                flag = 0X01;
            } else {
                flag = 0X00;
            }

            if( p_cur_trans->flags & AM_I2C_M_10BIT) {
                acked = __i2c_gpio_write_byte(p_devinfo, (p_cur_trans->addr >> 8) << 1 | flag);
                __i2c_gpio_write_byte(p_devinfo, p_cur_trans->addr & 0XFF);
            } else {
                acked = __i2c_gpio_write_byte(p_devinfo, p_cur_trans->addr << 1 | flag);
            }

            if (p_cur_trans->flags & AM_I2C_M_RD) {
                __i2c_gpio_next_state(__I2C_GPIO_ST_M_RECV_DATA,
                                   acked == AM_TRUE ? __I2C_GPIO_EVT_M_RX_SLA_ACK
                                                 : __I2C_GPIO_EVT_M_RX_SLA_NACK);
            } else {
                __i2c_gpio_next_state(__I2C_GPIO_ST_M_SEND_DATA,
                                   acked == AM_TRUE ? __I2C_GPIO_EVT_M_TX_SLA_ACK
                                                 : __I2C_GPIO_EVT_M_TX_SLA_NACK);
            }

            break;
        }

        /* ��ǰ���ڷ�������״̬ */
        case __I2C_GPIO_ST_M_SEND_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = __i2c_gpio_cur_msg(p_dev);
            struct am_i2c_transfer *p_cur_trans = __i2c_gpio_cur_trans(p_dev);

            /* ���͵�ַ����������Ӧ */
            if ((event == __I2C_GPIO_EVT_M_TX_SLA_NACK) ||
                (event == __I2C_GPIO_EVT_M_TX_DAT_NACK)) {

                /* ���ܺ��Դ��� */
                if (!(p_cur_trans->flags & AM_I2C_M_IGNORE_NAK)) {

                    /* ������Ϣ״̬  */
                    p_cur_msg->status = (event == __I2C_GPIO_EVT_M_TX_SLA_NACK ?
                                                 -AM_ENODEV : -AM_ENOENT);

                    /* ����ʣ�µ�trans */
                    p_dev->p_cur_trans = p_cur_msg->p_transfers
                                         + p_cur_msg->trans_num;

                    /* ������ǰ��Ϣ���� */
                    __i2c_gpio_next_state(__I2C_GPIO_ST_TRANS_START,
                                       __I2C_GPIO_EVT_TRANS_LAUNCH);

                    break;

                /* ���Դ��� */
                } else {

                }
            }

            /* û�и�������ݴ��� */
            if (__i2c_gpio_data_ptr_ov(p_dev)) {

                /* ׼����ȡ��һ�������� */
                __i2c_gpio_next_state(__I2C_GPIO_ST_TRANS_START, __I2C_GPIO_EVT_TRANS_LAUNCH);
                p_dev->p_cur_trans++;
                p_cur_msg->done_num++;

            /* ������һ������ */
            } else {
                am_bool_t acked;
                acked = __i2c_gpio_write_byte(p_devinfo, __i2c_gpio_cur_data(p_dev));
                p_dev->data_ptr++;

                __i2c_gpio_next_state(__I2C_GPIO_ST_M_SEND_DATA,
                                   acked == AM_TRUE ? __I2C_GPIO_EVT_M_TX_DAT_ACK
                                                 : __I2C_GPIO_EVT_M_TX_DAT_NACK);
            }

            break;
        }

        /* ��������״̬ */
        case __I2C_GPIO_ST_M_RECV_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = __i2c_gpio_cur_msg(p_dev);
            struct am_i2c_transfer *p_cur_trans = __i2c_gpio_cur_trans(p_dev);

            /* �ӻ�����Ӧ  */
            if (event == __I2C_GPIO_EVT_M_RX_SLA_NACK) {

                /* ���ܺ��Դ��� */
                if (!(p_cur_trans->flags & AM_I2C_M_IGNORE_NAK)) {

                    /* ������Ϣ״̬ */
                    p_cur_msg->status = -AM_ENODEV;

                    /* ����ʣ���trans */
                    p_dev->p_cur_trans = p_cur_msg->p_transfers + p_cur_msg->trans_num;

                    /* ������ǰ��Ϣ���� */
                    __i2c_gpio_next_state(__I2C_GPIO_ST_TRANS_START, __I2C_GPIO_EVT_TRANS_LAUNCH);

                    break;

                /* ���Դ��� */
                } else {
                    event = __I2C_GPIO_EVT_M_RX_SLA_ACK;
                }
            }

            /* �������� */
            while (!__i2c_gpio_data_ptr_last(p_dev)) {
                __i2c_gpio_cur_data(p_dev) = __i2c_gpio_read_byte(p_devinfo, AM_TRUE);
                p_dev->data_ptr++;
            }

            /* ���һ������  ������Ӧ  */
            __i2c_gpio_cur_data(p_dev) = __i2c_gpio_read_byte(p_devinfo, AM_FALSE);

            /* �������������� */
            p_cur_msg->done_num++;
            p_dev->p_cur_trans++;

            /* ��ȡ��һ��������*/
            __i2c_gpio_next_state(__I2C_GPIO_ST_TRANS_START, __I2C_GPIO_EVT_TRANS_LAUNCH);

            break;
        }


        default:
            break;
        }

        /* ���¼��˳� */
        if (new_event == __I2C_GPIO_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}

am_i2c_handle_t am_i2c_gpio_init (am_i2c_gpio_dev_t           *p_dev,
                                  const am_i2c_gpio_devinfo_t *p_devinfo)
{
    p_dev->p_devinfo = p_devinfo;

    p_dev->i2c_serv.p_drv = p_dev;
    p_dev->i2c_serv.p_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_gpio_drv_funcs;

    p_dev->p_cur_trans = NULL;
    p_dev->p_cur_msg   = NULL;
    p_dev->data_ptr    = 0;
    p_dev->busy        = AM_FALSE;
    p_dev->state       = __I2C_GPIO_ST_IDLE;

    am_list_head_init(&(p_dev->msg_list));

    __i2c_gpio_hw_init(p_devinfo);

    return &(p_dev->i2c_serv);
}

void am_i2c_gpio_deinit (am_i2c_handle_t handle)
{
}

/* end of file */
