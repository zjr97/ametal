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
 * \brief FTFA����,ͨ��������Ľӿ�ʵ��
 *
 * - �������裺
 *      - ���ڽӵ��Դ���
 *
 * - ʵ������
 *      - �����������ڴ�ӡ ��erase error!��
 *      - д��������ڴ�ӡ "program error!"
 *      - д��ɹ������ڴ�ӡ 55������ (1024/4) ��32bitʮ����������
 *
 * \par Դ����
 * \snippet demo_fsl_dr_ftfa.c src_fsl_dr_ftfa
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_dr_ftfa
 * \copydoc demo_fsl_dr_ftfa.c
 */

/** [src_fsl_dr_ftfa] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_fsl_ftfa.h"
#include "am_int.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

void demo_fsl_dr_ftfa_entry (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    int i;
    uint32_t data[1024 / 4]; /** Ҫд��flash������ */
    uint32_t status;         /** flash����ִ��״̬ */
    uint32_t key = 0;

    /** ���ݳ�ʼ�� */
    for (i = 0; i < 1024 / 4; i++) {
        data[i] = i;
    }

    key = am_int_cpu_lock();
    /** FTFA��ʼ�� */
    am_fsl_ftfa_init();
    am_int_cpu_unlock (key);

    key = am_int_cpu_lock();
    /** �������� 55 */
    status = am_fsl_ftfa_sector_erase(p_hw_ftfa, 55 * 1024);
    am_int_cpu_unlock (key);

    /** ������������ ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        while (1) {
            ;
        }
    }

    key = am_int_cpu_lock();
    /** ������ 55��д������ */
    status = am_fsl_ftfa_flash_program(p_hw_ftfa,
                                       55 * 1024,
                                       data,
                                       1024 / 4);
    am_int_cpu_unlock (key);

    /** ����д���������ͣ�ڴ˴� */
    if ((1024/4) != status) {
        AM_DBG_INFO("program error!\r\n");

        while (1);
    }

    /** д��ɹ������ݴ�flash�ж��� */
    for (i = 0; i < 1024; i += 4) {
        AM_DBG_INFO("%8x ", *(uint32_t *)(1024 * 55 + i));
    }

    AM_DBG_INFO("flash test finished!\r\n");
    /** ��ѭ������ֹ���� */
    while (1) {
        ;
    }
}

/** [src_fsl_dr_ftfa] */

/* end of file */
