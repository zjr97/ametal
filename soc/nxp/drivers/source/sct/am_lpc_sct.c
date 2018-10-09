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
 * \brief Timing driver implementation for SCT
 *
 * 1. SCT��״̬�����ö�ʱ������һ���Լ�����Ϊ���������¼�Ϊ���ģ�״̬״̬�����õĶ�ʱ��
 * 2. SCT������
 *    - һ�����32λ�����ļ�������
 *    - ��ʵ�ֵ��������������˫�������
 *    - �ɱ�SCT�¼�Ӳ�����Զ����ƣ���������������ֹͣ��������ֹͣ��
 *    - �ɱ�SCT�¼�Ӳ�����Զ������趨��ƥ��ֵ���ж��Ƿ�ƥ�䣻
 *    - �ɱ�SCT�¼�Ӳ�����Զ���ȡ����ֵ���Ա�ʵ�ֲ����߼���
 * 3. SCT�¼�
 *    - �¼��໥�������¼���Ŀ�ߴ�13����
 *    - ����������¼�����������������������IO������ƥ��������������������IO��ƥ��������ϣ�
 *    - ����������¼�����ЩSCT״̬�¿��Բ����ģ�
 *    - ����������¼�����ʱ���Լ������Ĳ����������ƣ�����������������ֹ����������ֹ��
 *    - ����������¼�����ʱ���Ƿ񴥷�DMA��������֧������DMA����ͨ����
 *    - ����������¼�����ʱ�������IOͨ�����п��ƣ�
 *    - ����������¼�����ʱ������SCT�¼��жϣ�
 *    - ����������¼������󣬶�SCT״̬��Ӱ�졣
 * 4. SCT״̬
 *    - SCT�ṩ��13��״̬
 *    - ��������SCT�����ĸ�״̬��
 *    - ״̬֮���ͨ��SCT�¼������Զ��л���
 * 5. SCT ����IOͨ��
 *    - �ṩ��8������IOͨ����
 *    - ÿ��ͨ������������ΪSCT�¼�������IO�������߲�������״̬�����룻
 *    - 4��ͨ����ͨ�����ؾ�����й������������š�
 * 6. SCT ���IOͨ��
 *    - �ṩ��8������IOͨ����
 *    - ÿ��ͨ������������ΪSCT�¼�������IO���������¼�����ʱ�������Ƶ����IOͨ����
 *    - ������¼���ͬʱ����ͬһ�����ͨ��ʱ���ҷ����˵�ƽ��ͻ��������������ֳ�ͻ�Ľ��������
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-14  hgo, fix potential bug caused by incorrect p_arg on callback
 * - 1.00 15-12-01  hgo, first implementation.
 * \endinternal
 */
#include "am_lpc_sct.h"
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "hw/amhw_lpc_sct.h"
#include "am_clk.h"
/******************************************************************************/
/** \brief �ж�δ���ӱ�ʶ */
#define __INT_NOT_CONNECTED      0xFF


/* SCT�жϴ����� */
void __sct_int (void *handle)
{
    const am_lpc_sct_devinfo_t  *p_devinfo =
                                   ((am_lpc_sct_handle_t)handle)->p_devinfo;
    amhw_lpc_sct_t              *p_hw_sct  = NULL;

    int           slot;
    int           evt_num;
    am_pfnvoid_t  pfn_isr;
    void         *p_arg;
    uint32_t      int_flags;

    p_hw_sct = (amhw_lpc_sct_t *)(p_devinfo->sct_regbase);

    int_flags = amhw_lpc_sct_event_flag_get(p_hw_sct);
    for (evt_num = 0; evt_num < p_devinfo->evt_isr_cnt; evt_num++) {
        if (AM_BIT_ISSET(int_flags, evt_num)) {

            slot = p_devinfo->p_isrmap[evt_num];
            if (slot == __INT_NOT_CONNECTED) {
                continue;
            }

            pfn_isr = p_devinfo->p_isrinfo[slot].pfn_isr;
            p_arg   = p_devinfo->p_isrinfo[slot].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg);
            }
            /* ����ж� */
            amhw_lpc_sct_event_flag_clr(p_hw_sct, evt_num);
        }
    }
}

/**
 * \brief SCT�¼����Ƽ�ʱ������
 */
static void __sct_evt_ctrl_cnt_cfgs(amhw_lpc_sct_t  *p_hw_sct,
                                    uint8_t             evt_num,
                                    uint8_t             out_cnt_flags)
{
    /* ���Ƽ����� */
    if(AM_BIT_ISSET(out_cnt_flags, AM_LPC_SCT_LIMIT_BITS_START)) {
        amhw_lpc_sct_event_limit_enable(p_hw_sct,
                                         AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    } else {
        amhw_lpc_sct_event_limit_disable(p_hw_sct,
                                         AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    }
    /* ֹͣ������ */
    if(AM_BIT_ISSET(out_cnt_flags, AM_LPC_SCT_STOP_BITS_START)) {
        amhw_lpc_sct_event_stop_enable(p_hw_sct,
                                        AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    } else {
        amhw_lpc_sct_event_stop_disable(p_hw_sct,
                                         AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    }
    /* ���������� */
    if(AM_BIT_ISSET(out_cnt_flags, AM_LPC_SCT_START_BITS_START)) {
        amhw_lpc_sct_event_start_enable(p_hw_sct,
                                         AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    } else {
        amhw_lpc_sct_event_start_disable(p_hw_sct,
                                          AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    }
    /* ��ֹ������ */
    if(AM_BIT_ISSET(out_cnt_flags, AM_LPC_SCT_HALT_BITS_START)) {
        amhw_lpc_sct_event_halt_enable(p_hw_sct,
                                        AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    } else {
        amhw_lpc_sct_event_halt_disable(p_hw_sct,
                                         AMHW_LPC_SCT_MODE_UNIFY, evt_num);
    }
}

/**
 * \brief SCT�¼��������IO����
 */
static void __sct_evt_ctrl_io_cfgs(am_lpc_sct_handle_t sct_handle,
                                   uint8_t             evt_num,
                                   uint16_t            out_io_flags)
{
    uint8_t i  = 0;
    uint8_t ch ;

    amhw_lpc_sct_t              *p_hw_sct  = NULL;


    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    /* �������ͨ����λ */
    ch = AM_BITS_GET(out_io_flags, AM_LPC_SCT_IOSET_CH_BITS_START,
                               sct_handle->p_devinfo->sct_out_num);

    for (i = 0; i < sct_handle->p_devinfo->sct_out_num; i++) {
        if (AM_BIT_ISSET(ch, i)) {
            amhw_lpc_sct_out_set_enable(p_hw_sct, i, evt_num);
        } else {
            amhw_lpc_sct_out_set_disable(p_hw_sct, i, evt_num);
        }
    }

    /* �������ͨ������ */
    ch = AM_BITS_GET(out_io_flags,
            AM_LPC_SCT_IOCLR_CH_BITS_START,
      sct_handle->p_devinfo->sct_out_num);

    for (i = 0; i < sct_handle->p_devinfo->sct_out_num; i++) {
        if (AM_BIT_ISSET(ch, i)) {
            amhw_lpc_sct_out_clr_enable(p_hw_sct, i, evt_num);
        } else {
            amhw_lpc_sct_out_clr_disable(p_hw_sct, i, evt_num);
        }
    }
}

/**
 * \brief SCT�¼�ƥ��򲶻�������
 */
static void __sct_evt_matchcap_cfgs(amhw_lpc_sct_t  *p_hw_sct,
                                      uint8_t      evt_num,
                                      uint64_t     cond_flags)
{
    uint32_t tmp;
    uint8_t matcap_num;

    /* ��ȡͨ�� */
    matcap_num     = AM_BITS_GET(cond_flags,
                                 AM_LPC_SCT_MATCAP_CH_BITS_START,
                                 AM_LPC_SCT_MATCAP_CH_BITS_LEN);

    tmp = AM_BIT_ISSET(cond_flags,
                       AM_LPC_SCT_MATCAP_ISCAP_BITS_START) ?
                       AMHW_LPC_SCT_MATCAP_CAPTURE :
                       AMHW_LPC_SCT_MATCAP_MATCH;

    /* ����ƥ��/����Ĵ���Ϊƥ��ģʽ  */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                   AMHW_LPC_SCT_MODE_UNIFY,
                                   matcap_num,
                                   (amhw_lpc_sct_matcap_mode_t)tmp);

    /* �����ƥ������ */
    if (tmp == AMHW_LPC_SCT_MATCAP_MATCH) {
        tmp = (cond_flags >> AM_LPC_SCT_MAT_VAL_BITS_START) &
               0xFFFFFFFF;

        /* ƥ���¼�������ƥ��ֵ */
        if (amhw_lpc_sct_halt_check(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY)) {

            amhw_lpc_sct_mat_val_set(p_hw_sct,
                                        AMHW_LPC_SCT_MODE_UNIFY,
                                        matcap_num,
                                        tmp - 1);
        }
        /* ����ƥ����������ֵ  */
        amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                           AMHW_LPC_SCT_MODE_UNIFY,
                                           matcap_num,
                                           tmp - 1);
    }

}


/**
 * \brief SCT�¼��ж�����
 */
static void __sct_evt_ctrl_int_cfg (am_lpc_sct_handle_t sct_handle,
                                    uint8_t                evt_num,
                                    am_pfnvoid_t           pfn_isr,
                                    void                  *p_arg,
                                    int                    slot)
{
    const am_lpc_sct_devinfo_t  *p_devinfo = sct_handle->p_devinfo;
    amhw_lpc_sct_t              *p_hw_sct  = NULL;

    p_hw_sct = (amhw_lpc_sct_t *)(p_devinfo->sct_regbase);

    if (NULL != pfn_isr) {
        p_devinfo->p_isrmap[evt_num]       = slot;
        p_devinfo->p_isrinfo[slot].p_arg   = p_arg ;
        p_devinfo->p_isrinfo[slot].pfn_isr = pfn_isr;

        if (p_hw_sct->even == 0) {
            am_int_connect(p_devinfo->inum, __sct_int, (void *)sct_handle);
            am_int_enable(p_devinfo->inum);       /* ʹ���ж� */
        }
        amhw_lpc_sct_event_int_enable(p_hw_sct, evt_num);
    } else {
        amhw_lpc_sct_event_int_disable(p_hw_sct, evt_num);
        if (p_hw_sct->even == 0) { /* ������û���¼������жϣ��ر��ж� */
            am_int_disable(p_devinfo->inum);
            am_int_disconnect(p_devinfo->inum, __sct_int, (void *)sct_handle);
        }
        if (slot != __INT_NOT_CONNECTED) {
            p_devinfo->p_isrinfo[slot].pfn_isr = NULL;
            p_devinfo->p_isrinfo[slot].p_arg   = NULL ;
            p_devinfo->p_isrmap[evt_num]       = __INT_NOT_CONNECTED;
        }

    }
}

/**
 * \brief SCT�¼�����DMA����
 */
static void __sct_evt_ctrl_dma_cfgs (am_lpc_sct_handle_t sct_handle,
                                     uint8_t            evt_num,
                                     uint8_t            out_dma_flags)
{
    uint8_t i  = 0;
    uint8_t ch ;

    const am_lpc_sct_devinfo_t  *p_devinfo = sct_handle->p_devinfo;
    amhw_lpc_sct_t              *p_hw_sct  = NULL;

    p_hw_sct = (amhw_lpc_sct_t *)(p_devinfo->sct_regbase);


    /* �������ͨ������ */
    ch = AM_BITS_GET(out_dma_flags, AM_LPC_SCT_DMA_REQ_CH_BITS_START,
                 p_devinfo->sct_dma_req_num);

    for (i = 0; i < p_devinfo->sct_dma_req_num; i++) {
        if (AM_BIT_ISSET(ch, i)) {
          amhw_lpc_sct_dma_request_event_enable(p_hw_sct, i, evt_num);
        } else {
          amhw_lpc_sct_dma_request_event_disable(p_hw_sct, i, evt_num);
        }
    }
}
/**
 * \brief ���SCT�¼�
 */
int am_lpc_sct_evt_add (am_lpc_sct_handle_t sct_handle,
                           uint8_t                evt_num,
                           am_lpc_sct_evt_t   *p_evt)
{
  am_lpc_sct_dev_t *p_dev = (am_lpc_sct_dev_t *)sct_handle;

    amhw_lpc_sct_t *p_hw_sct        = NULL;
    uint32_t           evt_ctrl_cfgs   = 0;  /* �¼��������ò��� */
    uint8_t            matcap_num      = 0;
    int                slot            = __INT_NOT_CONNECTED;
    int                i               = 0;
    uint32_t           tmp;

    if (NULL     == sct_handle                     ||
        NULL     == p_evt                          ||
        AM_FALSE == sct_handle->valid_flg          ||
        evt_num >= p_dev->p_devinfo->evt_isr_cnt   ||
        AM_BIT_ISSET(sct_handle->evt_stat, evt_num)) {

        return -AM_EINVAL;
    }

    /* �ж������¼��Ĳ���������Ч�� */
    if (p_evt->cond_flags == 0) {
        return -AM_EINVAL;
    }

    /* �ж��Ƿ������жϣ��Ƿ�ӳ���ڴ��Ƿ��㹻 */
    tmp = p_evt->out_int_flag & 0xFFFFFFFF;
    if (0 != tmp) {
        if (NULL == sct_handle->p_devinfo->p_isrmap  ||
            NULL == sct_handle->p_devinfo->p_isrinfo ||
            evt_num >= sct_handle->p_devinfo->evt_isr_cnt ) {
            return -AM_EINVAL;
        }
        slot =  sct_handle->p_devinfo->p_isrmap[evt_num];
        if (slot == __INT_NOT_CONNECTED) {
            for (i = 0; i < sct_handle->p_devinfo->evt_isr_cnt; i++) {
                if (sct_handle->p_devinfo->p_isrinfo[i].pfn_isr == NULL) {
                    slot = i;
                    break;
                }
            }
        }
        if (slot == __INT_NOT_CONNECTED) {
            return -AM_EPERM;                           /* û�пյ��ڴ�ӳ�� */
        }
    }

    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    /* �����¼�ǰ���ȹرո��¼� */
    amhw_lpc_sct_event_state_cfg(p_hw_sct, evt_num, 0);

    /* �¼����ж����õĿ��� */
    __sct_evt_ctrl_int_cfg(sct_handle, evt_num,
                          (am_pfnvoid_t)tmp,
                          (void *)((uint32_t)(p_evt->out_int_flag >>
                                   AM_LPC_SCT_CBPARAM_BITS_START)),
                          slot);

    /* ���������ò�������ȡ���Ĵ������ò��� */
    /*
     * ��ȡIO���ò���
     * 0x1FFΪIO�������õ�λ�򳤶�
     * 5ΪIO����������SCT�¼����ƼĴ�����EV[0:7]_CTRL���е�λ��ƫ��
     */
    evt_ctrl_cfgs |= AM_SBF(p_evt->cond_flags & 0x1FF, 5) ;

    /* ��ȡƥ��򲶻�ͨ�� */
    matcap_num     = AM_BITS_GET(p_evt->cond_flags,
                                 AM_LPC_SCT_MATCAP_CH_BITS_START,
                                 AM_LPC_SCT_MATCAP_CH_BITS_LEN);
    evt_ctrl_cfgs |= matcap_num;

    /*
     * ��ȡ�¼�����SCT״̬�ı仯
     * 0x3FΪ״̬�仯���õ�λ�򳤶�
     * 14Ϊ״̬�仯������SCT�¼����ƼĴ�����EV[0:7]_CTRL���е�λ��ƫ��
     */
    evt_ctrl_cfgs |= AM_SBF(((uint32_t)p_evt->out_stat_flag & 0x3F), 14);

    /* �����¼� */
    amhw_lpc_sct_event_ctrl(p_hw_sct, evt_num, evt_ctrl_cfgs);

    /* �Ƿ������˲������ƥ���¼� */
    if(AM_BIT_ISSET(p_evt->cond_flags, AM_LPC_SCT_MATCAP_ISSET_BITS_START)) {
        __sct_evt_matchcap_cfgs(p_hw_sct, evt_num, p_evt->cond_flags);
    }

    /* �¼��Լ������Ŀ��� */
    __sct_evt_ctrl_cnt_cfgs(p_hw_sct, evt_num, p_evt->out_cnt_flags);

    /* �¼���IO����Ŀ��� */
    __sct_evt_ctrl_io_cfgs(sct_handle, evt_num, p_evt->out_io_flags);

    /* �¼���DMA�����Ŀ��� */
    __sct_evt_ctrl_dma_cfgs(sct_handle, evt_num, p_evt->out_dma_flags);

    /* ʹ��һ���¼���ĳЩ״̬�з��� */
    amhw_lpc_sct_event_state_cfg(p_hw_sct, evt_num, p_evt->stat_en_flags);

    AM_BIT_SET(sct_handle->evt_stat, evt_num);        /* ��¼���¼��ѱ�ʹ�� */

    return AM_OK;
}

/**
 * \brief ɾ��SCT�¼�
 */
int am_lpc_sct_evt_del (am_lpc_sct_handle_t   sct_handle,
                             uint8_t                  evt_num)
{
    amhw_lpc_sct_t              *p_hw_sct  = NULL;



    if (NULL      == sct_handle              ||
        AM_FALSE  == sct_handle->valid_flg   ||
        evt_num   >= sct_handle->p_devinfo->evt_isr_cnt ||
        !AM_BIT_ISSET(sct_handle->evt_stat, evt_num)) {

        return -AM_EINVAL;
    }

    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    amhw_lpc_sct_event_state_cfg(p_hw_sct, evt_num, 0);

    /* �رո��¼�ע����ж� */
    __sct_evt_ctrl_int_cfg (sct_handle, evt_num,
                            NULL, NULL,
                            sct_handle->p_devinfo->p_isrmap[evt_num]);

    AM_BIT_CLR(sct_handle->evt_stat, evt_num);        /* ��¼���¼�δʹ�� */

    return AM_OK;
}


/**
 * \brief ��ֹSCT
 */
int am_lpc_sct_halt (am_lpc_sct_handle_t sct_handle)
{
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if (NULL == sct_handle || AM_FALSE == sct_handle->valid_flg ) {
        return -AM_EINVAL;
    }
    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    /* ������ֹλ����ֹ SCT */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_HALT_L);

    return AM_OK;
}

/**
 * \brief ֹͣSCT
 *
 */
int am_lpc_sct_stop (am_lpc_sct_handle_t sct_handle)
{
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if (NULL == sct_handle) {
        return -AM_EINVAL;
    }
    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    /* ����ֹͣλ����ͣ SCT */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L);
    return AM_OK;
}

/**
 * \brief ����SCT
 */
int am_lpc_sct_start (am_lpc_sct_handle_t sct_handle)
{
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if (NULL == sct_handle || AM_FALSE == sct_handle->valid_flg) {
        return -AM_EINVAL;
    }

    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    /* �����ֹ��ֹͣλ������ SCT */
    amhw_lpc_sct_ctrl_clr(p_hw_sct,
                             AMHW_LPC_SCT_CTRL_STOP_L |
                             AMHW_LPC_SCT_CTRL_HALT_L);
    return AM_OK;
}



/**
 * \brief ���������ų�ͻ
 */
int am_lpc_sct_conflict_res_config (am_lpc_sct_handle_t sct_handle,
                                       uint8_t                out_num,
                                       uint8_t                value)
{
    amhw_lpc_sct_t              *p_hw_sct  = NULL;

    if (NULL == sct_handle || AM_FALSE == sct_handle->valid_flg) {
        return -AM_EINVAL;
    }

    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    amhw_lpc_sct_conflict_res_config(p_hw_sct, out_num, value);

    return AM_OK;
}

int am_lpc_sct_state_set (am_lpc_sct_handle_t sct_handle,
                             uint16_t               state)
{
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if (NULL == sct_handle || AM_FALSE == sct_handle->valid_flg) {
        return -AM_EINVAL;
    }
    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    if (!amhw_lpc_sct_halt_check(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY)) {
        return -AM_EPERM;
    }

    amhw_lpc_sct_state_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, state);

    return AM_OK;
}

/**
 * \brief ͨ��ʱ�䣬��ȡ��Ҫ�趨��ƥ��ֵ
 */
uint32_t am_lpc_sct_time_to_match(am_lpc_sct_handle_t sct_handle,
                                  uint32_t               period_ns)
{
    uint32_t period_mat;
    uint32_t clkfreq;

    clkfreq = am_clk_rate_get(sct_handle->p_devinfo->clk_id);

    /* ��ʱ��ת��Ϊ���� ƥ��ֵ */
    period_mat = (uint64_t)(period_ns) * (clkfreq) /
               (uint64_t)1000000000;

    /* ��������Ϊ1 */
    if (period_mat == 0) {
        period_mat = 1;
    } else if (period_mat > 4294967295UL) {
        period_mat = 4294967295UL;
    }

    return period_mat;
}

/**
 * \brief ����SCT���ͨ����״̬
 */
int am_lpc_sct_out_state_set (am_lpc_sct_handle_t sct_handle,
                                 uint8_t                out_num,
                                 uint8_t                value)
{
    am_lpc_sct_dev_t *p_dev    = (am_lpc_sct_dev_t *)sct_handle;
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if (NULL     == sct_handle ||
        AM_FALSE == sct_handle->valid_flg ||
        out_num >=  p_dev->p_devinfo->evt_isr_cnt) {
        return -AM_EINVAL;
    }

    p_hw_sct = (amhw_lpc_sct_t *)(sct_handle->p_devinfo->sct_regbase);

    if (!amhw_lpc_sct_halt_check(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY)) {
        return -AM_EPERM;
    }
    if (value == AM_GPIO_LEVEL_LOW) {
      amhw_lpc_sct_output_state_set(p_hw_sct, out_num);
    } else {
      amhw_lpc_sct_output_state_clr(p_hw_sct, out_num);
    }

    return AM_OK;
}

am_lpc_sct_handle_t am_lpc_sct_init (am_lpc_sct_dev_t     *p_dev,
                                     const am_lpc_sct_devinfo_t *p_devinfo)
{
    uint8_t     i;
    amhw_lpc_sct_t *p_hw_sct  = NULL;

    if ((NULL == p_devinfo) || (NULL == p_devinfo) ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_sct                  = (amhw_lpc_sct_t *)(p_devinfo->sct_regbase);
    p_dev->p_devinfo          = p_devinfo;
    p_dev->evt_stat           = 0;               /* �����¼�δ��ʹ��  */
    p_dev->valid_flg          = AM_TRUE;

    if ((p_devinfo->p_isrmap != NULL) && (p_devinfo->p_isrinfo != NULL)) {
        for (i = 0; i < p_devinfo->evt_isr_cnt; i++) {
            p_devinfo->p_isrmap[i] = __INT_NOT_CONNECTED;
        }

        for (i = 0; i < p_devinfo->isrinfo_cnt; i++) {
            p_devinfo->p_isrinfo[i].pfn_isr = NULL;
        }
    }

    /* ����ֹSCT */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                       AMHW_LPC_SCT_CTRL_HALT_L);

    /* ���� SCT ƥ��Ĵ���0 Ϊ�Զ����ƣ�SCTΪ32λ��ʱ�� */
    amhw_lpc_sct_config(p_hw_sct,
                AMHW_LPC_SCT_CONFIG_32BIT_COUNTER  | /* 32Ϊ��ʱ��            */
          AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK); /* ϵͳʱ��              */

    /* ����Ԥ��ƵΪ0.ʹ��ϵͳʱ�ӣ���ƵΪ0 */
    amhw_lpc_sct_prescale_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);

    /* SCT״̬Ĭ��Ϊ״̬0 */
    amhw_lpc_sct_state_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);

    return p_dev;
}

void am_lpc_sct_deinit (am_lpc_sct_handle_t handle)
{
    am_lpc_sct_dev_t *p_dev    = (am_lpc_sct_dev_t *)handle;
    amhw_lpc_sct_t   *p_hw_sct = NULL;
    uint8_t              evt_num;

    if (p_dev                      == NULL ||
        p_dev->p_devinfo           == NULL ||
        p_dev->valid_flg           == AM_FALSE ) {
        return ;
    }

    p_hw_sct = (amhw_lpc_sct_t *)(handle->p_devinfo->sct_regbase);

    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                       AMHW_LPC_SCT_CTRL_HALT_L);

    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __sct_int, (void *)p_dev);

    /* �ر������¼� */
    for (evt_num = 0; evt_num < p_dev->p_devinfo->evt_isr_cnt; evt_num++) {
        amhw_lpc_sct_event_state_cfg(p_hw_sct, evt_num, 0);
    }
    p_dev->evt_stat  = 0;               /* �����¼�δ��ʹ��  */
    p_dev->valid_flg = AM_FALSE;        /* ������Ч */

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}


/* end of file */
