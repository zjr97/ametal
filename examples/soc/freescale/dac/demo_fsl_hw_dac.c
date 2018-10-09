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
 * \brief DAC��ģת�����̣�ͨ��HW�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �ɼ���ģת���������PE30�ĵ�ѹֵ
 *   2. ʹ��DACREF_2�ο���ѹ��DACREF_2����VDDA�ܽţ���ѹֵΪ3.3V��
 *   3. �����ѹֵΪ1.823V
 *
 *
 * \par Դ����
 * \snippet demo_fsl_hw_dac.c src_fsl_hw_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_dac
 * \copydoc demo_fsl_hw_dac.c
 */

 /** [src_fsl_hw_dac] */
#include "hw/amhw_fsl_dac.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "demo_fsl_entrys.h"

/**
 * \brief FSL DAC��ʼ������
 */

static void __fsl_dac_init (amhw_fsl_dac_t *p_hw_dac)
{
    /*
     * ����DAC��ع���
     */
    amhw_fsl_dac_c0_cfg(p_hw_dac,
                        AMHW_FSL_DAC_C0_EN                                |
                        AMHW_FSL_DAC_C0_VREF_SEL(AMHW_FSL_DAC_VREF_2)     |
                        AMHW_FSL_DAC_C0_TRG_SEL(AMHW_FSL_DAC_TRG_SOFT)    |
                        AMHW_FSL_DAC_C0_POWER_SEL(AMHW_FSL_DAC_POWER_LOW));
}

/** \brief DAC����ģʽ���� */
static void  __fsl_dac_trigger (amhw_fsl_dac_t *p_hw_dac,
                                uint16_t        data)
{
     /*  DAC�Ĵ�����ֵ*/
    amhw_fsl_dac_dat_set(p_hw_dac, AMHW_FSL_DAC_DAT_0, data);

     /* ʹ��DAC�������            */
    amhw_fsl_dac_soft_trg_enable(p_hw_dac);
}

/**
 * \brief DAC�����ѹֵ������HW��ʵ��
 */
void demo_fsl_hw_dac_entry (amhw_fsl_dac_t *p_hw_dac,
                             uint16_t       voltage_mv)
{
    /* ����ת��ֵ              */
    uint16_t v_out = (uint32_t)voltage_mv * 4096 / 3300;

    __fsl_dac_init(p_hw_dac);

    __fsl_dac_trigger(p_hw_dac, v_out);

    am_kprintf("FSL HW DAC Demo Test\n");

    while (1) {
        am_kprintf("FSL DAC OUTPUT...\n");
        am_mdelay(500);
    }
}


 /** [src_fsl_hw_dac] */

/* end of file */


