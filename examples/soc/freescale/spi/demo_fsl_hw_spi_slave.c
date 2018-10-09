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
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӻ��ӿں������ӿڶ�Ӧ��������;
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. �ӻ������������ݣ���ͨ�����ڽ����յ������ݴ�ӡ������
 *   2. �ӻ��������ݵ���������ͨ�����ڽ����͵����ݴ�ӡ������
 *
 * - ע�⣺
 *   1. ��Ҫʹ�������豸�䵱������
 *
 * \par Դ����
 * \snippet demo_fsl_hw_spi_slave.c src_fsl_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.00 16-09-27  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_spi_slave
 * \copydoc demo_fsl_hw_spi_slave.c
 */
 
/** [src_fsl_hw_spi_slave] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_spi.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"


/**
 * \brief SPI�ӻ���ʼ����8bit���ݿ�� SPI_MODE1��
 */
static void __spi_slv_init (amhw_fsl_spi_t *p_hw_spi)
{
    /* ����SPIΪ�ӻ� */
    amhw_fsl_spi_workmode_cfg(p_hw_spi, AMHW_FSL_SPI_WMODE_SLAVE);

    /* ����8bit���ݿ�� */
    amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_8BIT_WIDTH);

    /* ����ʱ����λ�ͼ��� */
    amhw_fsl_spi_mode_cfg(p_hw_spi, AMHW_FSL_SPI_MODE_1);

    /* ʹ��SPIģ�� */
    amhw_fsl_spi_enable(p_hw_spi);
}

/**
 * \brief SPI�ӻ���������
 */
static void __spi_slv_send (amhw_fsl_spi_t  *p_hw_spi,
                            uint8_t         *p_buf,
                            uint32_t         count)
{
    uint32_t i = 0;
    
    for (i = 0; i < count ; i++) {

        while ((amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_T_EMPTY) == 0);
        amhw_fsl_spi_data8_wirte(p_hw_spi, p_buf[i]);
    }
    
}

/**
 * \brief SPI�ӻ���������
 */
static void __spi_slv_recv (amhw_fsl_spi_t  *p_hw_spi,
                            uint8_t         *p_buf,
                            uint32_t         count)
{
    uint32_t i = 0;

    for (i = 0; i < count; i++) {
        while ( (amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_R_FULL) == 0 );

        p_buf[i] = amhw_fsl_spi_data8_read(p_hw_spi);
    }
}


/**
 * \brief �������
 */
void demo_fsl_hw_spi_slave_entry (amhw_fsl_spi_t *p_hw_spi)
{
    uint8_t spi_slv_txbuf[32] = {0};
    uint8_t spi_slv_rxbuf[32] = {0};
    uint8_t length =32;
    uint8_t i;

    /* SPI �ӻ���ʼ�� */
    __spi_slv_init(p_hw_spi);

    /* ���췢�͵����� */
    for (i = 0; i < length; i++) {
        spi_slv_txbuf[i] = i;
    }


    while (1) {
        /* �ӻ��������ݵ����� */
        __spi_slv_send(p_hw_spi, spi_slv_txbuf, length);
        AM_DBG_INFO("\r\n--Slave transmit Data:\r\n");
        for (i = 0; i < length; i++) {
            AM_DBG_INFO("The %2dst data is %2d \r\n", i, spi_slv_txbuf[i]);
        }

        __spi_slv_recv(p_hw_spi, spi_slv_rxbuf, length);
        AM_DBG_INFO("\r\n--Slave receive Data:\r\n");
        for (i = 0; i<length; i++) {
            AM_DBG_INFO("The %2dst data is %2d \r\n", i, spi_slv_rxbuf[i]);
        }

    }
}

/** [src_fsl_hw_spi_slave] */

/* end of file */

