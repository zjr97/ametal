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
 * \brief ADC���̣��������ת����DMA����ת�������ʹ�ö��������������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ���ʱ�ο���ѹΪ2.5v����
 *   4. PIOE_20(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_adc_descs_st.c src_amks16z_core_std_adc_descs_st
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-18  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_std_adc_descs_st
 * \copydoc demo_amks16z_core_std_adc_descs_st.c
 */

/** [src_amks16z_core_std_adc_descs_st] */
#include "demo_fsl_entrys.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_int.h"
#include "am_adc.h"
#include "am_kl26_inst_init.h"

/**
 * \brief adc���������DMA��������һ�β�������ADC������
 * \return ��
 */
void demo_amks16z_core_std_adc_descs_st_entry (void)
{
    am_adc_handle_t     adc0_handle;

    AM_DBG_INFO("demo amks16z_core std adc descs!\r\n");

    am_kl26_dma_inst_init();        /* DMAʵ����ʼ�� */
    adc0_handle = am_kl26_adc0_inst_init(); /* ADCʵ����ʼ��������ȡADC���ֵ */

    demo_fsl_std_adc_descs_st_entry(adc0_handle);

}

/** [src_amks16z_core_std_adc_descs_st] */

/* end of file */
