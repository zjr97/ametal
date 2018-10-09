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
 * \brief ģ��Ƚ����Ƚϵ�ѹ���̣�ͨ��HW��Ľӿ��жϷ�ʽʵ��

 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. PIOC_6��ӿɵ��ĵ�ѹ���루���û�������������
 * - ʵ������
 *   �������ѹ����1.65v����ʱ��LED��ת�������ڹ����⣩�����ڴ�ӡ��Ϣ����CMP INT����
 *
 *
 * \par Դ����
 * \snippet demo_fsl_hw_cmp_int.c src_fsl_hw_cmp_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-22  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_cmp_int
 * \copydoc demo_fsl_hw_cmp_int.c
 */

/** [src_fsl_hw_cmp_int] */
#include "hw/amhw_fsl_cmp.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
/**
 * \brief CMP�жϻص�����
 * \param[in] p_arg : �ص���������
 */
static void cmp_complete(void *p_arg)
{
    amhw_fsl_cmp_t *p_hw_cmp = (amhw_fsl_cmp_t *)p_arg;

    /* ����жϱ�־λ         */
    amhw_fsl_cmp_cff_clr(p_hw_cmp);

    am_kprintf("CMP INIT!\r\n");
    am_led_toggle(0);
}

/**
 * \brief  CMP ���ú���
 * \param[in] ��
 * \return    ��
 */
static void cmp_init (amhw_fsl_cmp_t *p_hw_cmp,
                      int             inum)
{
    /* ����6λDAC */
    /* ѡ��VDD��Vin2����ΪDAC�ο������ѹVin */
    amhw_fsl_cmp_dac_vin2_enable(p_hw_cmp);

    /* ���õ�ѹ���Ϊ1.65V = (3.3 / 64) * (31 + 1))*/
    amhw_fsl_cmp_dac_vol_set(p_hw_cmp, 31);

    /* ʹ��6λDAC */
    amhw_fsl_cmp_dac_enable(p_hw_cmp);

    /* 6λDAC������ӵ���������� */
    amhw_fsl_cmp_msel_set(p_hw_cmp, 7);

    /* CMP0_IN0������ӵ�ͬ������� */
    amhw_fsl_cmp_psel_set(p_hw_cmp, 0);

    /* ʹ�ܱȽ�������� */
    amhw_fsl_cmp_ope_enable(p_hw_cmp);

    /* ʹ�ܱȽ��½����ж� */
    amhw_fsl_cmp_ief_enable(p_hw_cmp);

    /* ����жϱ�־ */
    amhw_fsl_cmp_cff_clr(p_hw_cmp);

    extern int am_int_connect (int inum, am_pfnvoid_t pfn_isr, void *p_arg);
    extern int am_int_enable (int inum);

    /* �����ж� */
    am_int_connect(inum, cmp_complete, p_hw_cmp);
    am_int_enable(inum);

    /* ʹ��CMPģ��*/
    amhw_fsl_cmp_enable(p_hw_cmp);
}

/**
 * \brief CMP�Ƚ���HW���ж�����
 * \return ��
 */
void demo_fsl_hw_cmp_int_entry (amhw_fsl_cmp_t *p_hw_cmp,
                                int             inum)
{
    am_kprintf("CMP Demo:\r\n");

    /* ��ʼ��CMPģ�� */
    cmp_init(p_hw_cmp, inum);

    while (1) {
        am_mdelay(1000);
        am_kprintf("CMP...\r\n");
    }

}

/** [src_fsl_hw_cmp_int] */

/* end of file */
