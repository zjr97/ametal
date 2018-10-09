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
 * \brief   TSI������⣬Ӳ����ʵ��
 *
 *  ʵ������
 *  1.���ֲ��Ӵ�PIOA_1����ʱ�������⵽�Ļ���ֵ
 *  2.������PIOA_1���ź󣬼�⵽��ֵ��󣬲��������
 *
 *  ע�⣺
 *  1.���и�����ʱPIOA_1�������óɴ������š�
 *
 * \par Դ����
 * \snippet demo_fsl_hw_tsi.c src_fsl_hw_tsi
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_tsi
 * \copydoc demo_fsl_hw_tsi.c
 */
 
/** [src_fsl_hw_tsi] */
#include "ametal.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
    
/**
 * \brief ���������
 */
void demo_fsl_hw_tsi_entry (amhw_fsl_tsi_t *p_hw_tsi)
{  
    uint16_t value = 0;

    /* �����ⲿ�����㶨����Ϊ16uA */
    amhw_fsl_tsi_extchrg_val_set(p_hw_tsi, AMHW_FSL_TSI_EXTCHRG_16UA);

    /* ���õ�ѹ����Ϊ600mV (Vp - Vm)*/
    amhw_fsl_tsi_dvolt_set (p_hw_tsi, AMHW_FSL_TSI_DV073);

    /* ɨ��Ԥ��Ƶ����Ϊ2��Ƶ */
    amhw_fsl_tsi_oscfreq_div_set(p_hw_tsi, AMHW_FSL_TSI_OSCFRQ_DIV_2);

    /* ���õ缫ɨ�����Ϊ16 */
    amhw_fsl_tsi_scan_num_set(p_hw_tsi, 16);

    /* ���òο�������ŵ����Ϊ32uA */
    amhw_fsl_tsi_refchrg_val_set(p_hw_tsi, AMHW_FSL_TSI_REFCHRG_32UA);

    /* �жϽ��� */
    amhw_fsl_tsi_int_disable(p_hw_tsi);

    /* ���ô���ɨ��ģʽ */
    amhw_fsl_tsi_scan_trig_set(p_hw_tsi, AMHW_FSL_TSI_TRIG_SOFTWARE);

    /* ʹ��TSIͨ�� */
    amhw_fsl_tsi_chan_set(p_hw_tsi, AMHW_FSL_TSI_CHAN2);

    /* ʹ��TSIģ�� */
    amhw_fsl_tsi_mode_enable(p_hw_tsi);
    
    while (1) {

        /* �����������ɨ�� */
        amhw_fsl_tsi_soft_tirg_start(p_hw_tsi);

        /* ��ȡɨ�������־,�ȴ�ɨ����� */
        while ( !amhw_fsl_tsi_eosf_get(p_hw_tsi));

        /* ��ȡ������ */
        value = amhw_fsl_tsi_convert_value_get(p_hw_tsi);

        /* ��ɨ�������־ */
        amhw_fsl_tsi_eosf_clr(p_hw_tsi);

        am_kprintf("%d\r\n",value);
        am_led_toggle (LED1);
        am_mdelay(1000);

    }
}

/** [src_fsl_hw_tsi] */
 
/* end of file */

