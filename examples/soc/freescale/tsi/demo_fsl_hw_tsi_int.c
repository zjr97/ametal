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
 * \brief   TSI�����жϼ�⣬Ӳ����ʵ��
 *
 *  ʵ������
 *  1.���ֲ��Ӵ�PIOA_1����ʱ�������⵽�Ļ���ֵ
 *  2.������PIOA_1���ź󣬵��ݼ����ڷ�ֵ����1000ʱ�������жϣ�LED1״̬��ת
 *
 *  ע�⣺
 *  1.���и�����ʱPIOA_1�������óɴ������š�
 *
 * \par Դ����
 * \snippet demo_fsl_hw_tsi_int.c src_fsl_hw_tsi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-26  xjc, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_tsi_int
 * \copydoc demo_fsl_hw_tsi_int.c
 */
 
/** [src_fsl_hw_tsi_int] */
#include "ametal.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
    
static void tsi_isr(void *p_arg)
{
    amhw_fsl_tsi_t *p_hw_tsi = (amhw_fsl_tsi_t *)p_arg;

    /* �峬��ֵ��־ */
    amhw_fsl_tsi_outrgf_clr(p_hw_tsi);
       
    /* ��ɨ�������־ */
    amhw_fsl_tsi_eosf_clr(p_hw_tsi);
    am_led_toggle(LED1);
}

/**
 * \brief ���������
 */
void demo_fsl_hw_tsi_int_entry(amhw_fsl_tsi_t *p_hw_tsi,
                               int             inum)
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

    /* ���ô���ɨ��ģʽ */
    amhw_fsl_tsi_scan_trig_set(p_hw_tsi, AMHW_FSL_TSI_TRIG_SOFTWARE);

    /* ʹ��TSIͨ�� */
    amhw_fsl_tsi_chan_set(p_hw_tsi, AMHW_FSL_TSI_CHAN2);

    /* ʹ��TSIģ�� */
    amhw_fsl_tsi_mode_enable(p_hw_tsi);
    
    /* ����TSI�жϷ����� */
    am_int_connect(inum, tsi_isr, p_hw_tsi);
    
    /* TSI�ж�ʹ�� */
    amhw_fsl_tsi_int_enable(p_hw_tsi);
    
    /* ϵͳ�ж�ʹ�� */
    am_int_enable(inum);
    
    /* ���÷�ֵ���� */
    amhw_fsl_tsi_wake_chan_thresholdh_write(p_hw_tsi, 1000);
    
    /* ���÷�ֵ���� */
    amhw_fsl_tsi_wake_chan_thresholdl_write(p_hw_tsi, 100);
       
    while (1) {

        /* �����������ɨ�� */
        amhw_fsl_tsi_soft_tirg_start(p_hw_tsi);
        
        /* ��ȡ������ */
        value = amhw_fsl_tsi_convert_value_get(p_hw_tsi);

        am_kprintf("%d\r\n",value);
        am_mdelay(100);

    }
}

/** [src_fsl_hw_tsi_int] */
 
/* end of file */

