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
 * \brief ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������Ὣǩ����Ϣͨ�����ڴ�ӡ���ն��ϣ�
 *   2. ��ʾ��Ϊ�����֣��ֱ�Ϊ�������Ľ����Ӳ������Ľ����
 *   3. �����������Ӳ��������Ӧ����ͬ��
 *   4. LED �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \note
 *   �ɷ��ʵĵ�ַ��ΧΪ FLASH �ռ�(0x0000~0x8000)��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_flash_ctrl.c src_lpc824_hw_flash_ctrl
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-04  sky, modified
 * - 1.00 15-07-16  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_flash_ctrl
 * \copydoc demo_lpc824_hw_flash_ctrl.c
 */

/** [src_lpc824_hw_flash_ctrl] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_fmc.h"

/**
 * \brief ������� FLASH ǩ��
 *
 * \param[in] start ǩ����ʼ��ַ
 * \param[in] end   ǩ��������ַ
 *
 * \note ǩ���������ȣ����ɳ��� MCU Flash �ܿռ�(0x0000~0x8000)
 */
am_local uint32_t __cal_sign (uint32_t start, uint32_t end)
{
    uint32_t sign = 0, addr = 0, f_q = 0;

    /* ǩ�����ɵ�ַ(��Ӧ�� AHB �ֽڵ�ַλ [20:4] �� 16 λ����) */
    start = start >> 4;
    end   = end >> 4;

    /* ���� FLASH ǩ�� */
    for (addr = start; addr <= end; addr++) {

        /* ��ȡ FLASH ��ֵ��������(�ֶ���) */
        f_q = (uint32_t)(*(volatile int *)(4 * addr));

        sign = f_q ^  (sign >> 1)
                   ^ ((sign << 31) & 0x80000000)
                   ^ ((sign << 21) & 0x80000000)
                   ^ ((sign << 1 ) & 0x80000000)
                   ^ ((sign << 0 ) & 0x80000000);
    }

    /* ���� 32 λǩ����Ϣ */
    return sign;
}

void demo_lpc824_hw_flash_ctrl_entry(amhw_lpc82x_fmc_time_t time)
{

    amhw_lpc82x_fmc_flashtim_set(time);

    /* ��ȡ����ӡǩ����Ϣ */
    AM_DBG_INFO("hard calculate id: 0x%x\r\n",
                amhw_lpc82x_fmc_flash_sign(0x0, 0x7000));
    AM_DBG_INFO("soft calculate id: 0x%x\r\n\r\n", __cal_sign(0x0, 0x7000));

    AM_FOREVER {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_lpc824_hw_flash_ctrl] */

/* end of file */
