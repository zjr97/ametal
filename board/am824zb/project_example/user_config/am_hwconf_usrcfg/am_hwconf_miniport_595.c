/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Miniport-595 �����ļ�
 * \sa am_hwconf_miniport_595.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "am_hc595_gpio.h"
#include "am_hc595_spi.h"
#include "lpc82x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_595
 * \copydoc am_hwconf_miniport_595.c
 * @{
 */

/*******************************************************************************
   Public functions
*******************************************************************************/
static  am_hc595_spi_info_t __hc595_spi_info = {
    PIO0_14,                                       /* ������������ */
    -1,                                            /* δʹ��oe���� */
    300000,                                        /* ʱ��300KHZ */
    AM_TRUE                                        /* ���ݵ�λ�ȷ��� */
};

/* MiniPort-595 ʵ����ʼ�� */
am_hc595_handle_t am_miniport_595_inst_init (void)
{
#if 0
    static am_hc595_gpio_dev_t         miniport_595;
    static const am_hc595_gpio_info_t  miniport_595_info = {
        PIO0_10,
        PIO0_11,
        PIO0_14,
        -1,                     /* OE�̶�Ϊ�͵�ƽ��δʹ�� */
        AM_TRUE                 /* ��λ�ȷ��� */
    };

    return  am_hc595_gpio_init(&miniport_595, &miniport_595_info);

#else

    static am_hc595_spi_dev_t    miniport_595;

    return  am_hc595_spi_init(&miniport_595,
                              &__hc595_spi_info,
                               am_lpc82x_spi1_dma_inst_init());
#endif

}

/**
 * @}
 */

/* end of file */
