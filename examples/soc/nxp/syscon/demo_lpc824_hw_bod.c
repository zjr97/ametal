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
 * \brief ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ�鲽�裺
 *   1. �ı乩���ѹ��ʹ֮���� 2.85V��
 *
 * - ʵ������
 *   1. ���ⲿ��������ĸ�λ��������� "Reset by External Reset Pin"��
 *   2. ������������ĸ�λ��������� "Reset by BOD"��
 *   3. ���������£�LED0 �������������ѹ���Ͻ��ͣ����� 2.85V ʱ��LED0 ����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_bod.c src_lpc824_hw_bod
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-17  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_bod
 * \copydoc demo_lpc824_hw_bod.c
 */

/** [src_lpc824_hw_bod] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \brief BOD �жϴ�����
 *
 * \param[in] p_arg �ж���ڲ���
 *
 * \return ��
 */
am_local void __bod_irq_callback (void *p_arg)
{
    am_led_on(LED0);
}

/**
 * \brief �������
 */
void demo_lpc824_hw_bod_entry (void)
{

    /* ������������λ�����������ʾ�ַ���LED0 �� */
    if ((amhw_lpc82x_syscon_rst_stat_get() &
         AMHW_LPC82X_SYSCON_RSTSTAT_BOD) != 0) {

        amhw_lpc82x_syscon_rst_stat_clr(AMHW_LPC82X_SYSCON_RSTSTAT_BOD);

        AM_DBG_INFO("Reset by BOD\r\n");

    } else if ((amhw_lpc82x_syscon_rst_stat_get() &
                AMHW_LPC82X_SYSCON_RSTSTAT_EXTRST) != 0) {

        AM_DBG_INFO("Reset by External Reset Pin\r\n");
    }

    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_BOD);

    /* �趨�������жϵ�ѹ 2.85V���豸��λ��ѹ 1.46V */
    amhw_lpc82x_syscon_bod_level_set(AMHW_LPC82X_SYSCON_BODRSTLVL_1_46V,
                                     AMHW_LPC82X_SYSCON_BODINTLVL_2_85V);

    amhw_lpc82x_syscon_bod_rst_enable();

    am_int_connect(INUM_BOD, __bod_irq_callback, (void *)LED0);
    am_int_enable(INUM_BOD);

    AM_FOREVER {
        ; /* VOID */
    }

}
/** [src_lpc824_hw_bod] */

/* end of file */
