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
 * \brief I2C drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-19   ari , first implementation.
 * - 1.00 18-01-03   sdq , make somd changes.
 * \endinternal
 */

#include "am_list.h"
#include "am_fsl_i2c.h"
#include "hw/amhw_fsl_i2c.h"
#include "am_clk.h"
#include "am_led.h"

#define __I2C_ST_IDLE             (0x10u)          /* ����״̬             */
#define __I2C_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬     */
#define __I2C_ST_TRANS_START      (0x12u)          /* �������俪ʼ״̬     */
#define __I2C_ST_SEND_SLA_ADDR    (0x13u)          /* ���ʹӻ���ַ״̬     */
#define __I2C_ST_M_SEND_DATA      (0x14u)          /* ��������״̬         */
#define __I2C_ST_M_RECV_DATA      (0x15u)          /* ��������״̬         */
#define __I2C_ST_ARBI_LOST        (0x16u)          /* �ٲö�ʧ״̬         */
#define __I2C_ST_SEND_START_SIGNAL (0x17u)         /* ������ʼ�ź�״̬     */

#define __I2C_EVT_NONE            (0xFFu)          /* ���¼�               */
#define __I2C_EVT_MSG_LAUNCH      (0xFEu)          /* ��ʼ����һ���µ���Ϣ */
#define __I2C_EVT_TRANS_LAUNCH    (0xFDu)          /* ��ʼ����һ���µĴ��� */

#define __I2C_EVT_MST_IDLE         AM_SBF(0x0, 1)  /* ���������¼�         */
#define __I2C_EVT_MST_RX           AM_SBF(0x1, 1)  /* ���Խ�������         */
#define __I2C_EVT_MST_TX           AM_SBF(0x2, 1)  /* ���Է�������         */

#define __I2C_EVT_MST_ADDR_NO_ACK  AM_SBF(0x3, 1)  /* ��ַ��Ӧ��           */
#define __I2C_EVT_MST_DATA_NO_ACK  AM_SBF(0x4, 1)  /* ������Ӧ��           */

#define __I2C_EVT_MST_BERR         AM_SBF(0x5, 1)  /* ���ߴ���             */

#define __I2C_EVT_MST_TIMEOUT      AM_SBF(0x6, 1)  /* ��ʱ����             */


/*******************************************************************************
  Functions declaration
*******************************************************************************/

/* I2C Ӳ����ʼ�����ú���   */
static int __i2c_speed_set(am_fsl_i2c_dev_t *p_dev , uint32_t speed);
static int __i2c_hard_init(am_fsl_i2c_dev_t *p_dev);

/* I2C �жϴ�����   */
void       __i2c_irq_handler(void *p_arg);

/* ��Ϣ���� */
static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_msg);
static int __i2c_mst_sm_event(am_fsl_i2c_dev_t *p_arg, uint32_t event);

/**
 * \brief I2C ������������
 */
static am_const struct am_i2c_drv_funcs __g_i2c_drv_funcs = {
    __i2c_msg_start
};

/**
 * \brief I2Cʱ�����ýṹ��
 */
typedef struct __i2c_div_table {
    uint8_t   icr;         /**< \brief I2C ��������        */
    uint16_t  scl_div;     /**< \brief I2C ��Ƶ����        */
} __i2c_div_table_t;

/******************************************************************************/


/**
 * \brief I2C ���������ú���
 */
static int __i2c_speed_set(am_fsl_i2c_dev_t *p_dev , uint32_t speed)
{
	  amhw_fsl_i2c_t  *p_hw_i2c   = p_dev->p_devinfo->p_hw_i2c;
    uint8_t  mult , i , multiplier;
    uint32_t source_clk , rate , abs_error;
    uint32_t min_error = 0xffffffff;
    uint32_t best_mult = 0;
    uint32_t best_icr = 0;
	
    /* I2C ʱ�ӷ�Ƶ�����б�  */
    const __i2c_div_table_t div_table[50] = {
        { 0x00, 20 },   { 0x01, 22 },   { 0x02, 24 },   { 0x03, 26 },
        { 0x04, 28 },   { 0x05, 30 },   { 0x09, 32 },   { 0x06, 34 },
        { 0x0a, 36 },   { 0x07, 40 },   { 0x0c, 44 },   { 0x10, 48 },
        { 0x11, 56 },   { 0x12, 64 },   { 0x0f, 68 },   { 0x13, 72 },
        { 0x14, 80 },   { 0x15, 88 },   { 0x19, 96 },   { 0x16, 104 },
        { 0x1a, 112 },  { 0x17, 128 },  { 0x1c, 144 },  { 0x1d, 160 },
        { 0x1e, 192 },  { 0x22, 224 },  { 0x1f, 240 },  { 0x23, 256 },
        { 0x24, 288 },  { 0x25, 320 },  { 0x26, 384 },  { 0x2a, 448 },
        { 0x27, 480 },  { 0x2b, 512 },  { 0x2c, 576 },  { 0x2d, 640 },
        { 0x2e, 768 },  { 0x32, 896 },  { 0x2f, 960 },  { 0x33, 1024 },
        { 0x34, 1152 }, { 0x35, 1280 }, { 0x36, 1536 }, { 0x3a, 1792 },
        { 0x37, 1920 }, { 0x3b, 2048 }, { 0x3c, 2304 }, { 0x3d, 2560 },
        { 0x3e, 3072 }, { 0x3f, 3840 }
    };	
		
    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /*  ��ȡ��ǰI2C����ʱ��  */
    source_clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    if(speed > 1000000) {
        return  -AM_EINVAL;
    }
    for (mult = 0 ; mult <= 2 ; mult++) {
        multiplier = 1 << mult;
        for (i = 0 ; i < 50 ; i++) {
            rate = source_clk / (multiplier * div_table[i].scl_div);
            abs_error = speed > rate ? speed - rate : rate - speed;
            if (abs_error < min_error) {
                best_mult = mult;
                best_icr  =  div_table[i].icr;
                min_error = abs_error;
            }
            if (min_error == 0) {
                break;
            }
        }
    }

    /* д���Ƶ���ӣ����ò�����  */
    amhw_fsl_i2c_clk_div_set(p_hw_i2c , (best_mult << 6)|best_icr);
    return AM_OK;
}

/**
 * \brief I2C ��ʱ����
 */
static int __i2c_set_timeout (am_fsl_i2c_dev_t *p_dev, uint16_t time_out)
{
    amhw_fsl_i2c_t  *p_hw_i2c = NULL;
    uint32_t clk;
    uint32_t reg_val;

    if (p_dev == NULL) {
        return  -AM_EINVAL;
    }

    p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;

    amhw_fsl_i2c_timeout_clk_sel(p_hw_i2c, AMHW_FSL_I2C_MODULE_CLOCK_64);
    clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);
    reg_val = time_out  * (clk / (64 * 1000));
    if (reg_val > 65535) {
        reg_val = 65535;
    }
    amhw_fsl_i2c_scl_timeout_val_set(p_hw_i2c, reg_val);
    return AM_OK;
}
/**
 * \brief I2C Ӳ����ʼ������
 */
static int __i2c_hard_init (am_fsl_i2c_dev_t *p_dev)
{
    amhw_fsl_i2c_t  *p_hw_i2c = NULL;

    if (p_dev == NULL) {
        return  -AM_EINVAL;
    }

    p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;

    if (p_hw_i2c == NULL) {
        return  -AM_EINVAL;
    }

    amhw_fsl_i2c_disable(p_hw_i2c);

    __i2c_set_timeout(p_dev, p_dev->p_devinfo->timeout_ms);

    /* I2C ����������  */
    __i2c_speed_set(p_dev, p_dev->p_devinfo->bus_speed);

    /* �˲����� */
    amhw_fsl_i2c_flt_fact(p_hw_i2c, 15);

    amhw_fsl_i2c_enable(p_hw_i2c);

    return AM_OK;
}


/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
am_static_inline
void __i2c_msg_in (am_fsl_i2c_dev_t *p_dev, struct am_i2c_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                     &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_i2c_message *__i2c_msg_out (am_fsl_i2c_dev_t *p_dev)
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
 * \brief ��Ϣ��ʼ
 */
static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_msg)
{
    am_fsl_i2c_dev_t *p_dev  = (am_fsl_i2c_dev_t *)p_drv;

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

        __i2c_msg_in(p_dev, p_msg);

        am_int_cpu_unlock(key);

        return AM_OK;

    } else {
        p_dev->busy = AM_TRUE;
        __i2c_msg_in(p_dev, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        p_dev->stop_signal = AM_FALSE;
        am_int_cpu_unlock(key);
        

        __i2c_mst_sm_event(p_dev, __I2C_ST_MSG_START);

        /* �����жϣ��ж�Ҫ��״̬���˳�����������״̬��Ƕ�ף� */
        amhw_fsl_i2c_int_enable((amhw_fsl_i2c_t *)p_dev->p_devinfo->p_hw_i2c,
                                 AMHW_FSL_I2C_INT_IICIE |
                                 AMHW_FSL_I2C_INT_SHTF2IE |
                                 AMHW_FSL_I2C_INT_SSIE);

        return AM_OK;
    }
}

/**
 * \brief �����ʱ���ص�����
 *
 * \param[in] p_arg ָ��I2C �豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __softimer_callback (void *p_arg)
{
	am_fsl_i2c_dev_t *p_dev = (am_fsl_i2c_dev_t *)p_arg;

    if (p_arg == NULL) {
        return;
    }
    __i2c_mst_sm_event(p_dev,__I2C_EVT_MST_TIMEOUT);
}

/**
 * \brief I2C �жϺ���
 */
void __i2c_irq_handler (void *p_arg)
{
    am_fsl_i2c_dev_t  *p_dev    = (am_fsl_i2c_dev_t *)p_arg;
    amhw_fsl_i2c_t    *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;

    volatile uint8_t i2c_status  = amhw_fsl_i2c_stat_get(p_hw_i2c);
    volatile uint8_t i2c_timeout = amhw_fsl_i2c_tmout_flag_get(p_hw_i2c);
	
    if (p_arg == NULL) {
        return;
    }


 
    if (i2c_status == 0) {
        return;
    }

    /* ��ʼ�ź��ж� */
    if (amhw_fsl_i2c_start_is_dec(p_hw_i2c)) {
        amhw_fsl_i2c_start_dec_clr(p_hw_i2c);
        amhw_fsl_i2c_stat_clr(p_hw_i2c , AMHW_FSL_I2C_STAT_IICIF);

        __i2c_mst_sm_event(p_dev, __I2C_EVT_TRANS_LAUNCH);
        return;
    }

    /* ֹͣ�ź��ж� */
    if (amhw_fsl_i2c_stop_is_dec(p_hw_i2c)) {
        amhw_fsl_i2c_stop_dec_clr(p_hw_i2c);
        amhw_fsl_i2c_stat_clr(p_hw_i2c , AMHW_FSL_I2C_STAT_IICIF);

        __i2c_mst_sm_event(p_dev, __I2C_ST_MSG_START);
        return;
    }

    /* ����жϱ�ʶ���д���Ӧ�÷��ڴ������и���״̬֮ǰ��������ܵ���״̬������ */
    /* Ӧ�÷��������ʼ��ʶ��ֹͣ��ʶ֮�󣬷����жϱ�ʶ���ٴα���λ */
    amhw_fsl_i2c_stat_clr(p_hw_i2c , AMHW_FSL_I2C_STAT_IICIF);

    if (i2c_status & AMHW_FSL_I2C_STAT_IICIF) {
        if (i2c_status & AMHW_FSL_I2C_STAT_ARBL) {
            amhw_fsl_i2c_stat_clr (p_hw_i2c , AMHW_FSL_I2C_STAT_ARBL);
            __i2c_mst_sm_event(p_dev, __I2C_ST_MSG_START);
        } else if (i2c_timeout & AMHW_FSL_I2C_TMOUT_FLAG_SCL_LOW) {
            amhw_fsl_i2c_tmout_flag_clr(p_hw_i2c , AMHW_FSL_I2C_TMOUT_FLAG_SCL_LOW);
            __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_TIMEOUT);
        } else if (i2c_timeout & AMHW_FSL_I2C_TMOUT_FLAG_SDA_LOW) {
            amhw_fsl_i2c_tmout_flag_clr(p_hw_i2c , AMHW_FSL_I2C_TMOUT_FLAG_SDA_LOW);
            __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_TIMEOUT);
        } else if(i2c_status & AMHW_FSL_I2C_STAT_TCF) {
            __i2c_mst_sm_event(p_dev, __I2C_ST_MSG_START);
        }
    }
}

/**
 * \brief I2C ��ʼ��
 */
am_i2c_handle_t am_fsl_i2c_init(am_fsl_i2c_dev_t            *p_dev ,
                                 const am_fsl_i2c_devinfo_t  *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    /* PMUƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }
    p_dev->i2c_serv.p_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_drv_funcs;
    p_dev->i2c_serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->busy         = AM_FALSE;
    p_dev->p_cur_trans  = NULL;
    p_dev->p_cur_msg    = NULL;
    p_dev->data_ptr     = 0;
    p_dev->state        = __I2C_ST_IDLE;

    am_list_head_init(&(p_dev->msg_list));

    __i2c_hard_init(p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    if (am_softimer_init(&p_dev->softimer,
                          __softimer_callback,
                          p_dev) != AM_OK) {
        return NULL;
    }

    return &(p_dev->i2c_serv);
}

/**
 * \brief I2C ���ʼ��
 */
void am_fsl_i2c_deinit (am_i2c_handle_t handle)
{

    am_fsl_i2c_dev_t *p_dev = (am_fsl_i2c_dev_t *)handle;

    amhw_fsl_i2c_t *p_hw_i2c  = p_dev->p_devinfo->p_hw_i2c;

    p_dev->i2c_serv.p_funcs = NULL;
    p_dev->i2c_serv.p_drv   = NULL;
	
    if (handle == NULL) {
        return;
    }
    amhw_fsl_i2c_disable(p_hw_i2c);
    am_int_disable(p_dev->p_devinfo->inum);

    amhw_fsl_i2c_disable(p_hw_i2c);

    am_int_disconnect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);
    am_int_disable(p_dev->p_devinfo->inum);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/*  ״̬���ڲ�״̬�л� */
#define __I2C_NEXT_STATE(s, e) \
    do {                     \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/* check if transfers empty */
#define __I2C_TRANS_EMPTY(p_dev) \
    ((p_dev)->p_cur_trans >= (p_dev)->p_cur_msg->p_transfers \
                             + (p_dev)->p_cur_msg->trans_num)


/**
 * \brief I2C ״̬������
 */
static int __i2c_mst_sm_event (am_fsl_i2c_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t new_event = __I2C_EVT_NONE;
    amhw_fsl_i2c_t *p_hw_i2c = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }


    p_hw_i2c  = (amhw_fsl_i2c_t *)p_dev->p_devinfo->p_hw_i2c;

    while (1) {

        /* ����Ƿ����µ��¼���״̬���ڲ����� */
        if (new_event != __I2C_EVT_NONE) {
            event     = new_event;
            new_event = __I2C_EVT_NONE;
        }

        /* ���豸��״̬Ϊ��׼����״̬������ */
        switch(p_dev->state) {

        /*
         * ����״̬�Ϳ�ʼ��Ϣ����״̬Ҫ�����������һ�����¼�ֻӦ�ǣ�
         * __I2C_EVT_TRANS_LAUNCH
         */
        case __I2C_ST_IDLE:
        case __I2C_ST_MSG_START:
        {

            am_i2c_message_t *p_cur_msg = NULL;

            int key;

            /* �ر������ʱ�� */
            am_softimer_stop(&p_dev->softimer);

            key = am_int_cpu_lock();
            p_cur_msg        = __i2c_msg_out(p_dev);
            p_dev->p_cur_msg = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;

                am_int_cpu_unlock(key);

                p_cur_msg->done_num = 0;
                p_dev->p_cur_trans  = p_cur_msg->p_transfers;
                p_dev->data_ptr     = 0;

                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                event     = new_event;
                new_event = __I2C_EVT_NONE;
            } else {

                /* �ر��ж� */
                amhw_fsl_i2c_int_disable(p_hw_i2c,
                                         AMHW_FSL_I2C_INT_IICIE  |
                                         AMHW_FSL_I2C_INT_SHTF2IE |
                                         AMHW_FSL_I2C_INT_SSIE);

                p_dev->busy = AM_FALSE;

                am_int_cpu_unlock(key);

                __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);

                break;
            }
        }
        /* no break */

        case __I2C_ST_TRANS_START :
        {
            struct am_i2c_message *p_cur_msg = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans;
            /* ��ǰ��Ϣ������� */
            if (__I2C_TRANS_EMPTY(p_dev)) {

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                amhw_fsl_i2c_stop_signal_send(p_hw_i2c);
                p_dev->stop_signal = AM_TRUE;

                p_cur_trans = p_cur_msg->p_transfers + (p_cur_msg->trans_num - 1);

                /* ��������ʱ ���һ��������ֹͣ�ź�֮�����  */
                if ((p_dev->data_ptr < p_cur_trans->nbytes) &&
                    (p_cur_trans->flags & AM_I2C_M_RD)) {
                    p_cur_trans->p_buf[p_dev->data_ptr++] =  amhw_fsl_i2c_data_read(p_hw_i2c);
                    p_dev->dummy_rx_flg = 0;
                }

                /* �ص���Ϣ��ɺ���  */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }

                /** ���������ʱ��ʱ�� */
                am_softimer_start(&p_dev->softimer,20);

                __I2C_NEXT_STATE(__I2C_ST_MSG_START, __I2C_EVT_NONE);
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
                        __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA, __I2C_EVT_TRANS_LAUNCH);
                    } else {

                        /* ������������ */
                        __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA, __I2C_EVT_TRANS_LAUNCH);
                    }
                } else {

                    /* ��һ�������Ƿ�����ʼ�ź�   */
                    __I2C_NEXT_STATE(__I2C_ST_SEND_START_SIGNAL, __I2C_EVT_TRANS_LAUNCH);
                }
            }
            break;
        }

        case __I2C_ST_SEND_SLA_ADDR :    /* ���ʹӻ���ַ */
        {
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;
            uint8_t dev_addr = (p_cur_trans->addr) << 1;

            /* �ر������ʱ�� */
            am_softimer_stop(&p_dev->softimer);

            if (p_cur_trans->flags & AM_I2C_M_RD) {
                dev_addr |= 0x1;            /* ������ */
                /* ��һ���ǽ������� */
                __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA, __I2C_EVT_NONE);
            } else {
                /* ������������ģʽ  */
                __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA, __I2C_EVT_NONE);
            }

            /** ���������ʱ��ʱ�� */
            am_softimer_start(&p_dev->softimer,20);

            /* д����豸��ַ   */
            amhw_fsl_i2c_data_write(p_hw_i2c , dev_addr);
        }
        break;

        case __I2C_ST_SEND_START_SIGNAL :    /* ������ʼ�ź� */
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            uint8_t dev_addr = (p_cur_trans->addr) << 1;

            /* �ݲ�֧��10bit ģʽ */
            if (p_cur_trans->flags & AM_I2C_ADDR_10BIT) {

                /* ������Ϣ״̬ */
                p_cur_msg->status = -AM_ENOTSUP;

                /* ����ʣ�µ�transfer */
                p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                     p_cur_msg->trans_num;

                /* ������ǰ����Ϣ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);

                break;
            }

            /** ���������ʱ��ʱ�� */
            am_softimer_start(&p_dev->softimer,20);

            amhw_fsl_i2c_transmode_set(p_hw_i2c, AMHW_FSL_I2C_TRANSMODE_SEND);
            /* ���������ź�  */
            if (p_cur_trans->flags & AM_I2C_M_RD) {

                dev_addr |= 0x1;            /* ������ */
                if((p_cur_trans != p_cur_msg->p_transfers) && (p_dev->stop_signal == AM_FALSE)) {
                    amhw_fsl_i2c_restart_signal_send(p_hw_i2c);
                } else {
                    amhw_fsl_i2c_start_signal_send(p_hw_i2c);
                    p_dev->stop_signal = AM_FALSE;
                }
                /* ���������ȡ */
                p_dev->dummy_rx_flg = 1;

            } else {
                dev_addr &= ~0x1;            /* д���� */

                amhw_fsl_i2c_start_signal_send(p_hw_i2c);
                p_dev->stop_signal = AM_FALSE;
            }

            /* ��һ״̬�����ʹӻ���ַ */
            __I2C_NEXT_STATE(__I2C_ST_SEND_SLA_ADDR, __I2C_EVT_NONE);
        }
        break;

        /* ��ǰ���ڽ�������״̬ */
        case __I2C_ST_M_RECV_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            /* �ر������ʱ�� */
            am_softimer_stop(&p_dev->softimer);

            if (((amhw_fsl_i2c_stat_get(p_hw_i2c) & AMHW_FSL_I2C_STAT_RXAK)) &&
                (p_dev->data_ptr < p_cur_trans->nbytes - 1)) {

                event = __I2C_EVT_MST_DATA_NO_ACK;

            }
            /* �������ݣ�������Ӧ�����ֻ���ܲ�����ַ��Ӧ�� */
            if ((event == __I2C_EVT_MST_ADDR_NO_ACK) ||
                (event == __I2C_EVT_MST_DATA_NO_ACK)) {

                if (!(p_cur_trans->flags & AM_I2C_M_IGNORE_NAK)) {

                    p_cur_msg->status = -AM_ENODEV;

                    /* ����ʣ�µ�transfer */
                    p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                         p_cur_msg->trans_num;

                    __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);
                    break;

                /* ����������� */
                } else {
                    event = __I2C_EVT_MST_RX;
                }
            }

            /* �ٲö�ʧ��������ֹͣ���� */
            if (event == __I2C_EVT_MST_BERR || event == __I2C_EVT_MST_TIMEOUT) {
                __I2C_NEXT_STATE(__I2C_ST_ARBI_LOST, __I2C_EVT_MST_BERR);
                break;
            }

            amhw_fsl_i2c_transmode_set(p_hw_i2c, AMHW_FSL_I2C_TRANSMODE_RECV);

            /* ��һ�ζ�ȡΪд����豸��ַ ��һ�μٶ�ȡ  */

            if (1 == p_dev->dummy_rx_flg) {
                if (p_cur_trans->nbytes > 1) {
                     amhw_fsl_i2c_ack_respond(p_hw_i2c);
                 } else {
                     amhw_fsl_i2c_nak_respond(p_hw_i2c);
                 }
                /* �ٶ�*/
                (void)amhw_fsl_i2c_data_read(p_hw_i2c);
                p_dev->dummy_rx_flg = 0;
                break;
            }

            if (p_dev->data_ptr < p_cur_trans->nbytes - 1) {
                if ((p_cur_trans->nbytes > 1) &&
                    (p_dev->data_ptr  == p_cur_trans->nbytes - 2)) {
                     amhw_fsl_i2c_nak_respond(p_hw_i2c);
                }

                /* �����������ݣ�״̬���ֲ��� */
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                                              amhw_fsl_i2c_data_read(p_hw_i2c);
            } else {  /* ���ݽ�����ϣ� �ô������ */

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

                /* ��������ϣ�������һ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);
            }

            break;
        }

        case __I2C_ST_M_SEND_DATA :
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            /* �ر������ʱ�� */
            am_softimer_stop(&p_dev->softimer);

            amhw_fsl_i2c_transmode_set(p_hw_i2c, AMHW_FSL_I2C_TRANSMODE_SEND);

            /* ��Ӧ�� */
            if (amhw_fsl_i2c_stat_get(p_hw_i2c) & AMHW_FSL_I2C_STAT_RXAK) {
               if (p_cur_trans == p_cur_msg->p_transfers) {
                   event = __I2C_EVT_MST_ADDR_NO_ACK;     /* ��һ������ Ϊ��ַ��Ӧ�� */

               } else {
                   event = __I2C_EVT_MST_DATA_NO_ACK;
               }
            }

            /* ��ַ��������Ӧ�� */
            if ( (event == __I2C_EVT_MST_ADDR_NO_ACK) ||
                 (event == __I2C_EVT_MST_DATA_NO_ACK)) {

                if (!(p_cur_trans->flags & AM_I2C_M_IGNORE_NAK)) {

                    p_cur_msg->status = (event == __I2C_EVT_MST_ADDR_NO_ACK) \
                                        ? -AM_ENODEV : -AM_ENOENT;

                    /* ����ʣ�µ�transfer */
                    p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                         p_cur_msg->trans_num;

                    __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                                     __I2C_EVT_TRANS_LAUNCH);
                    break;

                /* ����������� */
                } else {
                    event = __I2C_EVT_MST_TX;
                }

            }

            /* �ٲö�ʧ��������ֹͣ���� */
            if (event == __I2C_EVT_MST_BERR || event == __I2C_EVT_MST_TIMEOUT) {
                __I2C_NEXT_STATE(__I2C_ST_ARBI_LOST, __I2C_EVT_MST_BERR);
                break;
            }

            if (p_dev->data_ptr < p_cur_trans->nbytes) {
                amhw_fsl_i2c_data_write(p_hw_i2c,
                                     (p_cur_trans->p_buf)[p_dev->data_ptr++]);
            } else {

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

                /* ��������ϣ�������һ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);
            }

            break;
        }

        case __I2C_ST_ARBI_LOST:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;

            amhw_fsl_i2c_disable(p_hw_i2c);
            amhw_fsl_i2c_enable(p_hw_i2c);

            /* ������Ϣ״̬ */
            p_cur_msg->status = -AM_EIO;

            /* ����ʣ�µ�transfer */
            p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                 p_cur_msg->trans_num;

            /* ������ǰ��Ϣ���� */
            __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);


            break;
        }

        default:
            break;
        }

        /* �ڲ�û�����¼����������� */
        if (new_event == __I2C_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}

/* end of file */
