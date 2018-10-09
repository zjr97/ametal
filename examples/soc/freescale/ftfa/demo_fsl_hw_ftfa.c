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
 * \brief FTFA����,ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *      - ʹ�õ��Դ��ڴ�ӡ��Ϣ
 *      - д��ʧ��ʱ����ӡ ��write error!��
 *      - д�����ʱ����ӡ ��data not wrote correct!��
 *      - �ɹ�д��ʱ����ӡд�������(32bit)�� ��flash test finished��
 * - ʵ������
 *
 *
 * \par Դ����
 * \snippet demo_fsl_hw_ftfa.c src_fsl_hw_ftfa
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_ftfa
 * \copydoc demo_fsl_hw_ftfa.c
 */


/** [src_fsl_hw_ftfa] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_ftfa.h"
#include "am_int.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

void deme_fsl_hw_ftfa_entry (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    int i = 10;
    uint32_t status;
    uint32_t key = 0;

    key = am_int_cpu_lock();
    /** ��flash����ִ�к���������RAM */
    amhw_fsl_ftfa_func_copy();
    am_int_cpu_unlock (key);

    key = am_int_cpu_lock();
    /** ����60����  */
    status = amhw_fsl_ftfa_sector_erase(p_hw_ftfa, 60 * 1024);
    am_int_cpu_unlock (key);

    /** ������������ ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        while (1) {
            ;
        }
    }

    key = am_int_cpu_lock();
    /** �ж�60�����Ƿ�ȫΪ1�����ɱ�� */
    status = amhw_fsl_ftfa_1s_read(p_hw_ftfa, 60 * 1024, 1024 / 4, 0x00);
    am_int_cpu_unlock (key);

    if (0 == status) {
        for (i = 0; i < 1024; i += 4) {
            key = am_int_cpu_lock();
            status = amhw_fsl_ftfa_word_program(p_hw_ftfa,
                                                60 * 1024 + i,
                                                i);
            am_int_cpu_unlock (key);

            /** д�벻�ɹ�ʱ����ͣ�ڴ˴� */
            if (0 != status) {
                AM_DBG_INFO("write error!\r\n");

                while (1);
            }

            key = am_int_cpu_lock();
            status = amhw_fsl_ftfa_program_check(p_hw_ftfa,
                                                 60 * 1024 + i,
                                                 i,
                                                 0x1);
            am_int_cpu_unlock (key);

            /** д�벻��ȷʱ����ͣ�ڴ˴� */
            if (0 != status) {
                AM_DBG_INFO("data not wrote correct!\r\n");

                while (1);
            }
        }
    }


    for (i = 0; i < 1024; i += 4) {
        AM_DBG_INFO("%8x ", *(uint32_t *)(60 * 1024 + i));
    }

    AM_DBG_INFO("flash test finished\r\n");

    /** ��ѭ������ֹMCU���� */
    while (1) {
        i++;
    }
}

/** [src_fsl_hw_ftfa] */

/* end of file */
