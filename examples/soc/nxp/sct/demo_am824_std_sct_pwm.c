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
 * \brief SCT PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIO0_27(SCT_OUT4) ��� 4KHz �� PWM��ռ�ձ�Ϊ 25%��
 *   3. LED0 �� 0.2s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc82x_std_sct_pwm.c src_lpc82x_std_sct_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-07  hgo, modified
 * - 1.00 15-07-15  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_sct_pwm
 * \copydoc demo_lpc82x_std_sct_pwm.c
 */

/** [src_lpc82x_std_sct_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief �������
 */
void demo_lpc82x_std_sct_pwm_entry (void)
{
    am_pwm_handle_t sct_pwm_handle = NULL;

    AM_DBG_INFO("The SCT demo for standard pwm service\r\n");
    AM_DBG_INFO("The PIO0_23(SCT_OUT0) PWM: freq is 4kHz, "
                "The duty ratio is 50%% \r\n");
    AM_DBG_INFO("The PIO0_27(SCT_OUT4) PWM: freq is 4kHz, "
                "The duty ratio is 25%% \r\n");

    sct_pwm_handle = am_lpc82x_sct0_pwm_inst_init();

    /* ͨ�� 0 ʹ�� PIO0_23 */
    am_pwm_config(sct_pwm_handle, 0, 125000, 250000);
    am_pwm_enable(sct_pwm_handle, 0);

    /* ͨ�� 4 ʹ�� PIO0_27 */
    am_pwm_config(sct_pwm_handle, 4, 62500, 250000);
    am_pwm_enable(sct_pwm_handle, 4);

    AM_FOREVER {
        am_led_toggle(LED0);
        am_mdelay(200);
    }
}
/** [src_lpc82x_std_sct_pwm] */

/* end of file */
