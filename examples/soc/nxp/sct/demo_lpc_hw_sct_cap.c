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
 * \brief SCT 32 λ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ����ⲿ�ṩ�� PWM �ź��� PIO0_25 ���ӡ�
 *
 * - ʵ������
 *   1. PIO0_25(SCT_IN_2) ����Ϊ�����ܣ����� PWM ���ں�Ƶ�ʲ�ͨ�����������
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ����ʾ�������߼������ǵ����������ԶԱ��������Ƶ�ʺ����ڣ��Ƿ��벶�����
 *       ��һ�£�
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc_hw_sct_cap.c src_lpc_hw_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.01 15-09-23  zxl, modified
 * - 1.00 15-07-14  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_cap
 * \copydoc demo_lpc_hw_sct_cap.c
 */

/** [src_lpc_hw_sct_cap] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_sct.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \brief ������ʹ���� 1 �� SCT �¼�
 *
 * 1. �¼� 2�����ڼ�Ⲷ��������ʹ�ò���ͨ�� 2���¼�����������������װ������Ĵ����У�
 *           �������жϡ�
 * �����¼��� SCT ״̬ 0 ����Ч���¼������� SCT ״̬�������ı䣻
 */

/** \brief �����ز��� */
#define    __SCT_CAP_TRIGGER_RISE    1

/** \brief �½��ز��� */
#define    __SCT_CAP_TRIGGER_FALL    2

am_local volatile am_bool_t __g_flag =  AM_FALSE;   /**< \brief �����־ */

/**
 * \brief ��ʼ�� SCT
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_cap_init (amhw_lpc_sct_t *p_hw_sct)
{

    /* ����ֹλ��SCT ��ֹ���� */
    amhw_lpc_sct_ctrl_set(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);

    /* ʹ�� 32 λ������������ͬ����ϵͳʱ��ģʽ */
    amhw_lpc_sct_config(p_hw_sct,
                        AMHW_LPC_SCT_CONFIG_32BIT_COUNTER |
                        AMHW_LPC_SCT_CONFIG_INSYNC_ALL |
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK );

    /* �� CLRCTR λ���������Ϊ 0 */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);

    /* ���õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct,
                           AMHW_LPC_SCT_MODE_UNIFY,
                           AMHW_LPC_SCT_STATE(0));

    /* Ԥ��ƵΪ 0��ʹ��ϵͳʱ�� */
    amhw_lpc_sct_prescale_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);
}

/**
 * \brief ���� CAP ����
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] cap_num  ������
 * \param[in] cap_edge �������ѡ��(#__SCT_CAP_TRIGGER_RISE)��
 *                     (#__SCT_CAP_TRIGGER_FALL)
 *
 * \return  ��
 */
am_local void __sct_cap_chan_config (amhw_lpc_sct_t *p_hw_sct,
                                     uint32_t        cap_num,
                                     uint8_t         cap_edge)
{
    uint32_t iocond = 0;

    /* ���ò������ */
    if (cap_edge == __SCT_CAP_TRIGGER_RISE) {
        iocond = AMHW_LPC_SCT_EV_CTRL_IOCOND_RISE;
    } else {
        iocond = AMHW_LPC_SCT_EV_CTRL_IOCOND_FALL;
    }

    /* ��ƥ�䲶׽�Ĵ�������Ϊ������ */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                AMHW_LPC_SCT_MODE_UNIFY,
                                AMHW_LPC_SCT_MAT(cap_num),
                                AMHW_LPC_SCT_MATCAP_CAPTURE);

    /* ʹ���¼�ԭ�� CAPn_L (UNIFY = 0) �Ĵ����ؼ��� */
    amhw_lpc_sct_cap_ctrl(p_hw_sct,
                          AMHW_LPC_SCT_MODE_UNIFY,
                          AMHW_LPC_SCT_CAP(cap_num),
                          AMHW_LPC_SCT_EVT(cap_num),
                          AM_TRUE);

    /* ʹ���¼����ͬ��ͨ���š��¼�ֻ���� IO ������������ƥ��Ĵ��� */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            AMHW_LPC_SCT_EVT(cap_num),
                            AMHW_LPC_SCT_EV_CTRL_OUTSEL_INPUT    |
                            AMHW_LPC_SCT_EV_CTRL_IOSEL(cap_num)  |
                            iocond                               |

                            /* ʹ��ָ�� IO */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_IO     |

                            /*  STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD     |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));
}

/**
 * \brief ʹ�� CAP ����
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] num      ���� CAP �Ĳ���ͨ�����
 *
 * \return ��
 */
am_local int __sct_cap_chan_enable (amhw_lpc_sct_t *p_hw_sct, uint32_t cap_num)
{

    /* ʹ��״̬ 0 ���¼� 0 ���� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(cap_num),
                                    AMHW_LPC_SCT_STATE(0));

    /* ����¼���־ */
    amhw_lpc_sct_event_flag_clr(p_hw_sct, AMHW_LPC_SCT_EVT(cap_num));

    /* ʹ���¼������ж� */
    amhw_lpc_sct_event_int_enable(p_hw_sct, AMHW_LPC_SCT_EVT(cap_num));

    /* ������ƼĴ�������Ӧλ */
    amhw_lpc_sct_ctrl_clr(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                    AMHW_LPC_SCT_CTRL_HALT_L);

    return AM_OK;
}

/**
 * \brief SCT �����жϷ�����
 *
 * \param[in] p_arg �û��Զ���������� am_int_connect() ��������
 *
 * \return ��
 */
am_local void __sct_cap_isr (void *p_arg)
{
    amhw_lpc_sct_t *p_hw_sct = (amhw_lpc_sct_t *)p_arg;

    /* ����ͨ�� 2 ʹ���¼� 2 */
    if (amhw_lpc_sct_event_flag_chk(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(2)) == AM_TRUE ) {
        __g_flag = AM_TRUE;

        /* ���¼���־ */
        amhw_lpc_sct_event_flag_clr(p_hw_sct, AMHW_LPC_SCT_EVT(2));
    }
}

void demo_lpc_hw_sct_cap_entry (amhw_lpc_sct_t *p_hw_sct, 
                                int             inum, 
                                uint32_t        frq)
{
    am_bool_t first   = AM_TRUE; /* �״β��� */
    uint32_t  count1  = 0;       /* �״β������ */
    uint32_t  cap_val = 0;       /* ����˲�����ֵ */
    uint32_t  time_ns = 0;       /* ������� */
    uint32_t  freq    = 0;       /* ����Ƶ�� */

    /* ���� SCT �жϷ����� */
    am_int_connect(inum, __sct_cap_isr, (void *)p_hw_sct);

    /* ʹ�� SCT �ж� */
    am_int_enable(inum);

    __sct_cap_init(p_hw_sct);
    __sct_cap_chan_config(p_hw_sct, 2, __SCT_CAP_TRIGGER_RISE);
    __sct_cap_chan_enable(p_hw_sct, 2);

    AM_FOREVER {
        if (__g_flag == AM_TRUE) {

            /* ��ȡ������� */
            cap_val = amhw_lpc_sct_cap_val_get(p_hw_sct,
                                               AMHW_LPC_SCT_MODE_UNIFY,
                                               2);
            /* �Ƿ�Ϊ��һ�μ��� */
            if (first == AM_TRUE) {
                count1 = cap_val;
                first  =  AM_FALSE;
            } else {

                /* ת������ֵΪʱ�� */
                time_ns = 1000000000 / frq * (cap_val - count1);

                first = AM_TRUE;

                /* ���������� */
                freq = 1000000000 / time_ns;
                AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                             time_ns,
                             freq);
                am_mdelay(200);
            }
            __g_flag =  AM_FALSE;
        }
    }
}
/** [src_lpc_hw_sct_cap] */

/* end of file */
