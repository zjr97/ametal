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
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �� MOSI ���ź� MISO ��������������ģ��ӻ��豸���ػ����ԡ�
 *
 * - ʵ������
 *   1. ����ͨ�� MISO �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_zlg_hw_spi_master.c src_zlg_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_zlg_hw_spi_master
 * \copydoc demo_zlg_hw_spi_master.c
 */
 
/** [src_zlg_hw_spi_master] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
//#include "am_zlg116.h"
#include "hw/amhw_zlg_spi.h"

/**
 * \name SPI����ṹ�����ò���
 */
#define SPI_CFG_LSB         AM_BIT(0)   /**< \brief ��λ���ȷ��� */
#define SPI_CFG_16BIT       AM_BIT(1)   /**< \brief �������ݿ��Ϊ16λ */

#define SPI_CFG_MODE_0      0           /**< \brief ģʽ0 */
#define SPI_CFG_MODE_1      1           /**< \brief ģʽ1 */
#define SPI_CFG_MODE_2      2           /**< \brief ģʽ2 */
#define SPI_CFG_MODE_3      3           /**< \brief ģʽ3 */

/** @} */

/** 
 * \brief SPI����ṹ��
 */
typedef struct spi_transfer {
    const void  *p_txbuf;           /**< \brief ָ�������ݻ����ָ�� */
    void        *p_rxbuf;           /**< \brief ָ��������ݻ����ָ�� */
    uint32_t     nbytes;            /**< \brief ���ݳ��� */
    uint32_t     flags;             /**< \brief SPI������Ʊ�־λ */
} spi_transfer_t;

spi_transfer_t g_spi_transfer;      /* ����һ��SPI����ṹ��ʵ�� */

static void spi_speed_cfg (amhw_zlg_spi_t *p_hw_spi,
                           uint32_t        target_speed,
                           uint32_t        clk_rate)
{
    uint32_t best_pdiv;              /* ��������ٶ� */

    best_pdiv = clk_rate / target_speed;

    amhw_zlg_spi_baud_rate_set(p_hw_spi, best_pdiv);
}

static void spi_master_cfg (amhw_zlg_spi_t *p_hw_spi)
{
    amhw_zlg_spi_first_bit_sel(p_hw_spi, AMHW_ZLG_SPI_DATA_MSB);
    amhw_zlg_spi_data_len_sel(p_hw_spi, AMHW_ZLG_SPI_DATA_LEN_8BIT);
    amhw_zlg_spi_valid_data_sel(p_hw_spi,AMHW_ZLG_SPI_VALID_DATA_8BIT);

    /* ����ʱ����λ�ͼ��� */
    amhw_zlg_spi_clk_mode_set(p_hw_spi, SPI_CFG_MODE_1 ^ 0x01);
}

static void spi_master_cs_ctr (amhw_zlg_spi_t *p_hw_spi,
                               int                pin,
                               uint8_t            active_level,
                               am_bool_t          state)
{

    /* Ƭѡ��Ч */
    if (state) {
        amhw_zlg_spi_cs_sel(p_hw_spi,AM_TRUE);

    /* Ƭѡ��Ч */
    } else {
        amhw_zlg_spi_cs_sel(p_hw_spi, AM_FALSE);
    }
}

/**
 * \brief SPI�ػ��������
 */
void spi_loop_trans (amhw_zlg_spi_t *p_hw_spi,
                     spi_transfer_t *p_trans,
                     int32_t         cs_pin)
{
    uint32_t pos = 0;

    spi_master_cfg(p_hw_spi);

    spi_master_cs_ctr(p_hw_spi, cs_pin, AM_GPIO_LEVEL_LOW, AM_TRUE);

    while(pos < p_trans->nbytes) {

        /* �ȴ����Է��� */
        while ((amhw_zlg_spi_reg_cstat_get(p_hw_spi) &
                AMHW_ZLG_SPI_CSTAT_TX_EMPTY) == 0);

            amhw_zlg_spi_tx_data8_put(p_hw_spi,
                                        *((uint8_t*)(p_trans->p_txbuf) + pos));

        /* �ȴ����Խ��� */
        while ((amhw_zlg_spi_reg_cstat_get(p_hw_spi) &
                AMHW_ZLG_SPI_CSTAT_RXVAL) == 0);

            *(uint8_t*)((uint8_t*)p_trans->p_rxbuf + pos) =
                                         amhw_zlg_spi_rx_data8_get(p_hw_spi);
            pos += 1;
    }

    /* ����Ƭѡ */
    spi_master_cs_ctr(p_hw_spi, cs_pin, AM_GPIO_LEVEL_LOW, AM_FALSE);
}

/**
 * \brief �������
 */
void demo_zlg_hw_spi_master_entry (amhw_zlg_spi_t *p_hw_spi,
                                   int32_t         cs_pin,
                                   uint32_t        clk_rate)
{
    uint8_t         i;
    uint8_t         spi_send_buf[16];
    uint8_t         spi_recv_buf[16];
    const uint32_t  length     = 16;
    am_bool_t       error_ocur = AM_FALSE;
    spi_transfer_t *p_trans    = &g_spi_transfer;

    p_trans->p_txbuf = spi_send_buf;
    p_trans->p_rxbuf = spi_recv_buf;
    p_trans->nbytes  = length;

    amhw_zlg_spi_mode_sel(p_hw_spi, AMHW_ZLG_SPI_MODE_MASTER);
    spi_speed_cfg(p_hw_spi, 100000, clk_rate);
    amhw_zlg_spi_tx_enable(p_hw_spi, AM_TRUE);
    amhw_zlg_spi_rx_enable(p_hw_spi, AM_TRUE);
    amhw_zlg_spi_module_enable(p_hw_spi, AM_TRUE);

    /* �������� */
    for (i = 0; i < length; i++) {
        spi_send_buf[i] = i;
    }

    /* ���ݴ��� */
    spi_loop_trans(p_hw_spi, p_trans, cs_pin);

    /* ���ݼ��� */
    for (i = 0; i < length; i++) {
        if (spi_recv_buf[i] != spi_send_buf[i]) {
            error_ocur = AM_TRUE;
            break;
        }
    }

    if (!error_ocur) {
        am_kprintf("trans done!\n");
    } else {
        am_kprintf("trans error!\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_spi_master] */

/* end of file */
