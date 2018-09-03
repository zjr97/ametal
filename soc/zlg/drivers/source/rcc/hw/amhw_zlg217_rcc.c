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
 * \brief RCC
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  sdy, first implementation
 * \endinternal
 */
 
#include "amhw_zlg217_rcc.h"

/* ʹ�ܻ�������� */
static void __rcc_ahb_cmd(amhw_zlg217_ahb_peripheral peri, uint8_t cmd)
{
    uint32_t temp = 0;

    temp = ZLG217_RCC->ahbenr;

    temp = 0x000000ff & temp;

    if (cmd) {
        temp = (1ul << peri) | temp;
    } else {
        temp = (~(1ul << peri)) & temp;
    }

    ZLG217_RCC->ahbenr = temp;
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_zlg217_rcc_ahb_enable (amhw_zlg217_ahb_peripheral peri)
{
    __rcc_ahb_cmd(peri, 1);
}

/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_zlg217_rcc_ahb_disable (amhw_zlg217_ahb_peripheral peri)
{

    __rcc_ahb_cmd(peri, 0);
}

/* end of file */
