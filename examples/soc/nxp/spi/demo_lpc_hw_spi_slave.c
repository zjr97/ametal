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
 * \brief SPI �ӻ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��������Ϊ�ӻ� SPI����������ӻ� SPI �����������ӡ�
 *
 * - ʵ������
 *   1. SPI ���յ����ݣ�ͨ�����ڽ����ݴ�ӡ��������������յ��������� "nihao"��
 *      �� LED0 ����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ��������Ҫ�� demo_am824_hw_spi_master.c һͬ���ԣ�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    4. ���� PIO0_12 ���ͻᵼ�µ�Ƭ����λʱ���� ISP ģʽ������ PIO0_12 Ӧ
 *       ��Ƭ����λ�������ӡ�
 *
 * \par Դ����
 * \snippet demo_lpc_hw_spi_slave.c src_lpc_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.01 15-11-26  sky, modified
 * - 1.00 15-07-15  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_spi_slave
 * \copydoc demo_lpc_hw_spi_slave.c
 */

/** [src_lpc_hw_spi_slave] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_spi.h"
#include <string.h>

#define __SPI_SPEED        100000  /**< \brief SPI ���ʺ궨�� */
#define __SPI_PRE_DELAY    0       /**< \brief SSEL ��λ����ʼ֡����ʱ */
#define __SPI_POST_DELAY   0       /**< \brief ֡ĩβ�� SSEL �����λ����ʱ */
#define __SPI_FRAME_DELAY  0       /**< \brief SPI ��������֡����ʱ */
#define __SPI_TRANS_DELAY  0       /**< \brief ���δ��� SSEL �����λ����ʱ */

#define __TIME1            100000  /**< \brief �궨��Ϊʱ�ӵȴ�ʱ�䣨ѭ�������� */

am_local uint8_t __g_spi_rev_buf[255] = {0}; /**< \brief SPI���ջ���������� */

/**
 * \brief SPI0 Ӳ����ʼ��
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __spi_slave_hard_init (amhw_lpc_spi_t *p_hw_spi,
                                     uint32_t        clk)
{

    /* ���� SPI ��Ƶֵ */
    amhw_lpc_spi_div_set(p_hw_spi, (clk / __SPI_SPEED));

    /* ���� SPI ������ʱ */
    amhw_lpc_spi_pre_delay(p_hw_spi, __SPI_PRE_DELAY);
    amhw_lpc_spi_post_delay(p_hw_spi, __SPI_POST_DELAY);
    amhw_lpc_spi_frame_delay(p_hw_spi, __SPI_FRAME_DELAY);
    amhw_lpc_spi_trans_delay(p_hw_spi, __SPI_TRANS_DELAY);

    /* ���� SPI ������� */
    amhw_lpc_spi_cfg_set(p_hw_spi, AMHW_LPC_SPI_CFG_CHANGE);
    amhw_lpc_spi_enable(p_hw_spi);

    /* ���� SPI һ�����ݳ���Ϊ 8 λ */
    amhw_lpc_spi_data_flen_set(p_hw_spi, 8);
}

/**
 * \brief SPI �����ַ�������
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 *
 * \return ���ջ��������׵�ַ
 */
am_local uint8_t *__spi_recive (amhw_lpc_spi_t *p_hw_spi)
{
    am_local uint8_t  i;                               /* ������������ i */
    volatile uint32_t timer1 = __TIME1;                /* ����Ϊʱ�ӱ��� */

    AM_FOREVER {

        /* ��һ��ʱ���ڵȴ����յ�����״̬��λ */
        while (!(amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_RXRDY)
               && --timer1) {};

        /* ���յ����ݶ����ǳ�ʱ�����ȴ� */
        if (timer1 != 0) {

            /* ������д�뻺����������� */
            __g_spi_rev_buf[i] = (uint8_t)amhw_lpc_spi_rxdat_with_flags(p_hw_spi);
            i++;
            __g_spi_rev_buf[i] = 0;   /* �Խ��յ�������ĩβд 0 �����ַ��� */
            timer1 = __TIME1;         /* ���õȴ�Ϊʱ��ʱ�� */
        } else {                      /* ����ʱ�����ȴ�ʱ���˳��������� */
            i = 0;
            break;                    /* ���� while��1�� */
        }
    }

    return __g_spi_rev_buf;           /* ���ؽ��ջ�����������׵�ַ */
}

void demo_lpc_hw_spi_slave_entry (amhw_lpc_spi_t *p_hw_spi,
                                  uint32_t        clk)
{
    /* SPI0 Ӳ����ʼ�� */
    __spi_slave_hard_init(p_hw_spi, clk);
    
    /* ���վ��� */
    AM_DBG_INFO("recv ready!\r\n");
  
    AM_FOREVER {

        /* ���� SPI ���� */
        __spi_recive(p_hw_spi);

        if ('\0' != __g_spi_rev_buf[0]) {

            /* ͨ�����ڷ��� SPI ���� */
            AM_DBG_INFO("SPI: %s\r\n", __g_spi_rev_buf);
        }

        /* �жϴ� SPI ���յ� "nihao" */
        if (strstr((am_const char *)__g_spi_rev_buf, "nihao")) {

            /* ��ת LED ״̬ */
            am_led_toggle(LED0);
        }
        /* ��ս��ջ������� */
        __g_spi_rev_buf[0] = 0;
    }
}
/** [src_lpc_hw_spi_slave] */

/* end of file */
