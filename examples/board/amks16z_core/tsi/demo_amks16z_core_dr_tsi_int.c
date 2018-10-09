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
 * \snippet demo_amks16z_core_dr_tsi_int.c src_amks16z_core_dr_tsi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_dr_tsi_int
 * \copydoc demo_amks16z_core_dr_tsi_int.c
 */
 
/** [src_amks16z_core_dr_tsi_int] */
#include "ametal.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_fsl_tsi.h"
#include "am_KL26_inst_init.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_fsl_entrys.h"

/**
 * \brief ���������
 */
void demo_amks16z_core_dr_tsi_int_entry (void)
{
    AM_DBG_INFO("demo amks16z_core dr tsi int!\r\n");

    /* TSI�豸��ʼ�� */
    am_kl26_tsi_inst_init();

    demo_fsl_dr_tsi_int_entry();
}

/** [src_amks16z_core_dr_tsi_int] */
 
/* end of file */

