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
 * \brief   TSI�����жϼ�⣬������ʵ��
 *
 *  ʵ������
 *  1.ʵ������PIOA_1����ΪTSIͨ��2���ܣ����ֲ��Ӵ�PIOA_1����ʱ���ᴥ���ж�
 *  2.������PIOA_1���ź󣬵��ݼ����ڷ�ֵ����1ֵʱ�������жϣ�LED1״̬��ת
 *
 *  ע�⣺
 *  1.��TSI����Ϊ�������ģʽʱ����Ҫִ���������ɨ�躯������ִ��һ��ɨ�裬����
 *  ��ʹ��ʱ��������Ϊ�������ģʽʱ����Ҫһֱ���߶�ʱִ������ɨ�躯����
 *  2.���и�����ʱPIOA_1�������óɴ������š�
 *
 * \par Դ����
 * \snippet demo_fsl_dr_tsi_int.c src_fsl_dr_tsi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_dr_tsi_int
 * \copydoc demo_fsl_dr_tsi_int.c
 */
 
/** [src_fsl_dr_tsi_int] */
#include "ametal.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_fsl_tsi.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

static void tsi_isr(void * p_arg)
{
    /* TSI�жϽ��� */
    am_fsl_tsi_int_disable();

    /* �峬��ֵ��־ */
    amhw_fsl_tsi_outrgf_clr(KL26_TSI);

    am_led_toggle(LED1);
    am_mdelay(100);

    /* TSI�ж�ʹ�� */
    am_fsl_tsi_int_enable();
}

/**
 * \brief ���������
 */
void demo_fsl_dr_tsi_int_entry (void)
{

    /* TSI�������� */
    am_fsl_tsi_fun_cfg(AMHW_FSL_TSI_CHAN2,
                       AMHW_FSL_TSI_CAP_SENSING,
                       AMHW_FSL_TSI_TRIG_SOFTWARE);

     /* TSI�жϴ���ģʽΪ����ֵ����ģʽ */
    am_fsl_tsi_trigger_cfg(AMHW_FSL_TSI_OUT_RANGE);

    /* ����TSI�жϷ����� */
    am_fsl_tsi_trigger_connect(&tsi_isr);

    /* ����TSI������ */
    am_fsl_tsi_sens_set(500);

    /* TSI�ж�ʹ�� */
    am_fsl_tsi_int_enable();

    while (1) {

        /* �����������ɨ�� */
        amhw_fsl_tsi_soft_tirg_start(KL26_TSI);

    }
}

/** [src_fsl_dr_tsi_int] */
 
/* end of file */

