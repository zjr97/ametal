/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I2C drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-10  jon, first implementation.
 * \endinternal
 */

#include "am_lpc_i2c.h"
#include "am_clk.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define __I2C_ST_IDLE             (0x10u)          /* ����״̬             */
#define __I2C_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬     */
#define __I2C_ST_TRANS_START      (0x12u)          /* �������俪ʼ״̬     */
#define __I2C_ST_SEND_SLA_ADDR    (0x13u)          /* ���ʹӻ���ַ״̬     */
#define __I2C_ST_M_SEND_DATA      (0x14u)          /* ��������״̬         */
#define __I2C_ST_M_RECV_DATA      (0x15u)          /* ��������״̬         */
#define __I2C_ST_ARBI_LOST        (0x16u)          /* �ٲö�ʧ״̬         */
#define __I2C_ST_TIMEOUT          (0x17u)          /* ��ʱ״̬            */

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
  ��������
*******************************************************************************/

/** \brief I2C �������ú��� */
static int __i2c_speed_set (am_lpc_i2c_dev_t *p_dev, uint32_t bus_speed);

/** \brief I2C Ӳ����ʼ�� */
static int __i2c_hard_init (am_lpc_i2c_dev_t *p_dev);

/** \brief I2C �жϴ����� */
static void __i2c_irq_handler (void *p_arg);

/** \brief I2C ״̬������ */
static int __i2c_mst_sm_event (am_lpc_i2c_dev_t *p_dev, uint32_t event);

/** \brief I2C ��Ϣ������ */
static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_trans);


/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**
 * \brief I2C ������������
 */
static am_const struct am_i2c_drv_funcs __g_i2c_drv_funcs = {
    __i2c_msg_start
};

/******************************************************************************/

/**
 * \brief I2C ������������
 *
 * \param[in] p_dev     : ָ��I2C�豸�ṹ��
 * \param[in] bus_speed : ��������
 *
 * \retval  AM_OK     : ���óɹ�
 * \retval -AM_EINVAL : �����Ƿ�
 */
static int __i2c_speed_set (am_lpc_i2c_dev_t *p_dev, uint32_t bus_speed)
{
    amhw_lpc_i2c_t *p_hw_i2c  = NULL;

    uint32_t    scl, div, div_top;
    uint32_t    scl_h, scl_l;
    uint32_t    sum_div, cur_div;
    uint32_t    f_scl = 0, f_div = 0;

    uint32_t    err, min_err;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c  = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    if (bus_speed > 1000000) {
        return -AM_EINVAL;        /* ֧�ֵ����Ƶ��Ϊ1MHz */
    }

    /*
     * I2Cʱ�ӵĸߵ�ƽ�͵͵�ƽ����2 ~ 9֮�䣬����Ƶ��
     * Ӧ��ʹ��4 ~ 18��ʱ����ɵ�ʱ�ӿ��Եõ���Ҫ��Ƶ��
     */
    sum_div = am_clk_rate_get(p_dev->p_devinfo->clk_id) / bus_speed;

    /* ��ΪSCL��СֵΪ4�����Է�Ƶֵ���ֻ��ҪΪ���ܷ�Ƶֵ / 4 */
    div_top = sum_div / 4 + 1;

    /* �ܵķ�ƵС�� 65536 */
    if (div_top >= 65536) {
        div_top = 65536;    /* ��Ƶ���ķ�Ƶֵ���Ϊ65536 */
    }

    min_err = 0xFFFFFFFF;

    for (div = 1; div <= div_top; div++) {
        for (scl = 4; scl <= 18; scl += 2) {

            cur_div = div * scl;

            if (cur_div > sum_div) {
                err = cur_div - sum_div;
            } else {
                err = sum_div - cur_div;
            }

            /* �ҵ�����ѷ�Ƶֵ  */
            if (err == 0) {
                f_scl = scl;
                f_div = div;
                break;
            }

            if (err < min_err) {     /* �������С���ϴ���� */
                f_scl   = scl;
                f_div   = div;
                min_err = err;
            }
        }

        /* �ҵ�����ѷ�Ƶֵ  */
        if (err == 0) {
            break;
        }
    }

    amhw_lpc_i2c_clkdiv_set(p_hw_i2c, f_div);

    p_dev->i2c_clkrate = am_clk_rate_get(p_dev->p_devinfo->clk_id) / f_div;

    scl_h = f_scl >> 1;               /* ռ�ձ�����Ĭ��Ϊ50% */
    scl_l = (f_scl - scl_h);

    if (scl_h < 2) {
        scl_h = 2;
    } else if (scl_h > 9) {
        scl_h = 9;
    }

    if (scl_l < 2) {
        scl_l = 2;
    } else if (scl_l > 9) {
        scl_l = 9;
    }

    amhw_lpc_i2c_msttime_set(p_hw_i2c, scl_h, scl_l);

    return AM_OK;
}

/******************************************************************************/

static int __i2c_slv_timeout_set (am_lpc_i2c_dev_t *p_dev,
                                  uint32_t             timeout_ms)
{
    amhw_lpc_i2c_t *p_hw_i2c = NULL;
    uint32_t    ticks;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    /* ����Ҫ��ʱ */
    if (timeout_ms == 0) {
        amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);
        amhw_lpc_i2c_int_disable(p_hw_i2c,
                                    AMHW_LPC_I2C_INTENSET_EVTIMEOUT |
                                    AMHW_LPC_I2C_INTENSET_SCLTIMEOUT);
        return AM_OK;
    }

    /* ������Ҫ��ʱ��ticks */
    ticks = p_dev->i2c_clkrate / 1000 * timeout_ms;

    /* ���tickΪ65536 */
    if (ticks > 65536) {
        ticks = 65536;
    }

    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);

    amhw_lpc_i2c_timeout_set(p_hw_i2c, ticks >> 4);

    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);

    amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_EVTIMEOUT |
                                         AMHW_LPC_I2C_INTENSET_SCLTIMEOUT);
    return AM_OK;
}

/******************************************************************************/

/** \brief I2C Ӳ����ʼ�� */
static int __i2c_hard_init(am_lpc_i2c_dev_t *p_dev)
{
    amhw_lpc_i2c_t *p_hw_i2c = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }
    
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    __i2c_speed_set(p_dev, p_dev->p_devinfo->bus_speed);

    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    __i2c_slv_timeout_set(p_dev, p_dev->p_devinfo->timeout_ms);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
am_static_inline
void __i2c_msg_in (am_lpc_i2c_dev_t *p_dev, struct am_i2c_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                     &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_i2c_message *__i2c_msg_out (am_lpc_i2c_dev_t *p_dev)
{
    if (am_list_empty_careful(&(p_dev->msg_list))) {
        return NULL;
    } else {
        struct am_list_head *p_node = p_dev->msg_list.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_i2c_message, ctlrdata);
    }
}

/******************************************************************************/

/**
 * \brief I2C �жϴ�����
 *
 * \param[in] p_arg : ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
static void __i2c_irq_handler (void *p_arg)
{
    am_lpc_i2c_dev_t *p_dev    = NULL;
    amhw_lpc_i2c_t   *p_hw_i2c = NULL;
    uint32_t i2c_status;

    if (p_arg == NULL) {
        return;
    }

    p_dev    = (am_lpc_i2c_dev_t *)p_arg;
    p_hw_i2c = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    i2c_status = amhw_lpc_i2c_intstat_get(p_hw_i2c);


    /* ��������״̬       */
    if ((i2c_status & AMHW_LPC_I2C_STAT_MSTPEND)           &&
        ((i2c_status & AMHW_LPC_I2C_STAT_EVTIMEOUT)  == 0) &&
        ((i2c_status & AMHW_LPC_I2C_STAT_SCLTIMEOUT) == 0) &&
        ((i2c_status & AMHW_LPC_I2C_STAT_MSTARBLOSS) == 0) &&
        ((i2c_status & AMHW_LPC_I2C_STAT_MSTSSERR)   == 0)) {

        __i2c_mst_sm_event(p_dev, (amhw_lpc_i2c_stat_get(p_hw_i2c) &
                                   AMHW_LPC_I2C_MASTER_STATE_MASK));
    }

    /* ��ʱ */
    if  ((i2c_status & AMHW_LPC_I2C_STAT_EVTIMEOUT) ||
         (i2c_status & AMHW_LPC_I2C_STAT_SCLTIMEOUT)) {

        /* ���״̬          */
        amhw_lpc_i2c_stat_clr(p_hw_i2c,
                                 AMHW_LPC_I2C_STAT_EVTIMEOUT  |
                                 AMHW_LPC_I2C_STAT_SCLTIMEOUT |
                                 AMHW_LPC_I2C_STAT_MSTARBLOSS |
                                 AMHW_LPC_I2C_STAT_MSTSSERR);

        __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_TIMEOUT);

        /* ���ܺ���ʹ�ܳ�ʱ���ܣ���λ��ʱ�ڲ��߼� */
        amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);

        amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);


      /* �����ٲö�ʧ������/ֹͣ���� */
    } else if ((i2c_status & AMHW_LPC_I2C_STAT_MSTARBLOSS)||
               (i2c_status & AMHW_LPC_I2C_STAT_MSTSSERR)) {

       /* ���״̬          */
        amhw_lpc_i2c_stat_clr(p_hw_i2c,
                                 AMHW_LPC_I2C_STAT_MSTARBLOSS |
                                 AMHW_LPC_I2C_STAT_MSTSSERR);
        __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_BERR);
    }
}

/******************************************************************************/

static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_msg)
{
    am_lpc_i2c_dev_t *p_dev    = (am_lpc_i2c_dev_t *)p_drv;

    amhw_lpc_i2c_t   *p_hw_i2c = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;

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

        am_int_cpu_unlock(key);

        /* �򿪹����ٲö�ʧ������/ֹͣ�����ж� */
        amhw_lpc_i2c_int_enable(p_hw_i2c,
                                   AMHW_LPC_I2C_INTENSET_MSTPEND    |
                                   AMHW_LPC_I2C_INTENSET_MSTARBLOSS |
                                   AMHW_LPC_I2C_INTENSET_MSTSSERR);

        return AM_OK;
    }
}

/**
 * \brief I2C ��ʼ��
 */
am_i2c_handle_t am_lpc_i2c_init (am_lpc_i2c_dev_t           *p_dev,
                                    const am_lpc_i2c_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->i2c_serv.p_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_drv_funcs;
    p_dev->i2c_serv.p_drv   = p_dev;
  
    p_dev->p_devinfo = p_devinfo;
    
    p_dev->busy        = AM_FALSE;
    p_dev->p_cur_trans = NULL;
    p_dev->p_cur_msg   = NULL;
    p_dev->data_ptr    = 0;
    p_dev->state       = __I2C_ST_IDLE;                   /* ��ʼ��Ϊ����״̬ */

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    am_list_head_init(&(p_dev->msg_list));

    __i2c_hard_init(p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->i2c_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_lpc_i2c_deinit (am_i2c_handle_t handle)
{
    amhw_lpc_i2c_t   *p_hw_i2c = NULL;
    am_lpc_i2c_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_lpc_i2c_dev_t *)handle;
    p_hw_i2c = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    p_dev->i2c_serv.p_funcs = NULL;
    p_dev->i2c_serv.p_drv   = NULL;

    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);
    
    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/******************************************************************************/

/*  ״̬���ڲ�״̬�л� */
#define __I2C_NEXT_STATE(s, e) \
    do { \
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
static int __i2c_mst_sm_event (am_lpc_i2c_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t new_event       = __I2C_EVT_NONE;


    amhw_lpc_i2c_t *p_hw_i2c = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c  = (amhw_lpc_i2c_t *)p_dev->p_devinfo->i2c_regbase;


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

            key = am_int_cpu_lock();
            p_cur_msg        = __i2c_msg_out(p_dev);
            p_dev->p_cur_msg = p_cur_msg;

            if (p_cur_msg) {

                p_cur_msg->status = -AM_EINPROGRESS;

            } else {

                /* �ر��ж� */
                amhw_lpc_i2c_int_disable(p_hw_i2c,
                                            AMHW_LPC_I2C_INTENSET_MSTPEND    |
                                            AMHW_LPC_I2C_INTENSET_MSTARBLOSS |
                                            AMHW_LPC_I2C_INTENSET_MSTSSERR);

                p_dev->busy = AM_FALSE;
            }

            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {

                __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);

                break;

            } else {

                p_cur_msg->done_num = 0;
                p_dev->p_cur_trans  = p_cur_msg->p_transfers;
                p_dev->data_ptr     = 0;

                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                event     = new_event;
                new_event = __I2C_EVT_NONE;
            }
        }
        /* no break */
        case __I2C_ST_TRANS_START :
        {
            struct am_i2c_message *p_cur_msg = p_dev->p_cur_msg;

            if (event != __I2C_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ���俪ʼ״̬�ȴ�����Ϣ�������������� */
            }


            /* ��ǰ��Ϣ������� */
            if (__I2C_TRANS_EMPTY(p_dev)) {

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                /* �ص���Ϣ��ɺ���  */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }


                /* ֹͣ���� */
                amhw_lpc_i2c_mst_stop(p_hw_i2c);

                __I2C_NEXT_STATE(__I2C_ST_MSG_START, __I2C_EVT_MSG_LAUNCH);

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

                        /* ����ǽ��գ���Ҫ����һ��continue���Ա������������ */
                        if (amhw_lpc_i2c_stat_get(p_hw_i2c) &
                            AMHW_LPC_I2C_STAT_MSTPEND) {

                            amhw_lpc_i2c_mst_continue(p_hw_i2c);
                        }

                        /* ������������ */
                        __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA, __I2C_EVT_MSG_LAUNCH);
                    } else {

                        /* ������������ */
                        __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA, __I2C_EVT_MSG_LAUNCH);
                    }

                /* ���ʹӻ���ַ */
                } else {
                    /* ��һ�������Ƿ��ʹӻ���ַ */
                    __I2C_NEXT_STATE(__I2C_ST_SEND_SLA_ADDR, __I2C_EVT_MSG_LAUNCH);
                }
            }

            break;
        }
        
        case __I2C_ST_SEND_SLA_ADDR :                         /* ���ʹӻ���ַ */
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


            /* ���������ź� + �ӻ���ַ */
            if (p_cur_trans->flags & AM_I2C_M_RD) {
                dev_addr |= 0x1;            /* ������ */

                /* ��һ���ǽ������� */
                __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA, __I2C_EVT_NONE);

            } else {
                dev_addr |= 0x0;            /* д���� */

                /* ������������ģʽ */
                __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA, __I2C_EVT_NONE);
            }

            /* �����豸��ַ */
            amhw_lpc_i2c_mstdat_write(p_hw_i2c, dev_addr);
            amhw_lpc_i2c_mst_start(p_hw_i2c);

            break;
        }

        /* ��ǰ���ڽ�������״̬ */
        case __I2C_ST_M_RECV_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            /* �������ݣ�������Ӧ�����ֻ���ܲ�����ַ��Ӧ�� */
            if ((event == __I2C_EVT_MST_ADDR_NO_ACK) ||
                (event == __I2C_EVT_MST_DATA_NO_ACK)) {

                if (!(p_cur_trans->flags & AM_I2C_M_IGNORE_NAK)) {

                    p_cur_msg->status = -AM_ENODEV;

                    /* ����ʣ�µ�transfer */
                    p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                         p_cur_msg->trans_num;

                    __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                                     __I2C_EVT_TRANS_LAUNCH);
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

            (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                                         amhw_lpc_i2c_mstdat_read(p_hw_i2c);

            if (p_dev->data_ptr < p_cur_trans->nbytes) {
                /* �����������ݣ�״̬���ֲ��� */
                amhw_lpc_i2c_mst_continue(p_hw_i2c);

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

                amhw_lpc_i2c_mstdat_write(p_hw_i2c,
                                     (p_cur_trans->p_buf)[p_dev->data_ptr++]);

                amhw_lpc_i2c_mst_continue(p_hw_i2c);
            } else {

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

                /* ��������ϣ�������һ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START, __I2C_EVT_TRANS_LAUNCH);
            }

            break;
        }

        /* �ٲô����ʱ�����������쳣��ֱ�ӽ�����һ�δ��� */
        case __I2C_ST_ARBI_LOST:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;

            /* ������ʹ�ܣ���λӲ�����ڲ��߼� */
            amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);
            amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

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
