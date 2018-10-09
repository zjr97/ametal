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
 *   1. ��SPI0�ӻ��ӿں�SPI1�����ӿڶ�Ӧ��������(PIOC_4 == PIOD_4, PIOC_5 == PIOD_5,
 *   PIOC6 == PIOD_6, PIOC_7 == PIOD_7)��
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. ����SPI1�ʹӻ�SPI0��������(SPI0ʹ���жϷ�ʽ�շ�����)��
 *   2. �Ƚ�SPI1��SPI0���ݣ������ͬ��LED0һֱ����������LED0��200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_spi_slave_irq.c src_fsl_hw_spi_slave_irq
 *
 * \internal
 * \par History
 * - 1.00 16-09-27  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_spi_slave_irq
 * \copydoc demo_fsl_hw_spi_slave_irq.c
 */
 
/** [src_fsl_hw_spi_slave_irq] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_fsl_spi.h"
#include "am_board.h"
#include "am_vdebug.h"


#define __NUM_COUNT   32                            /**< \brief ��������С     */

static uint8_t __g_spi0_slve_txbuf[__NUM_COUNT]   = {0};     /**< \brief �ӻ����ͻ����� */
static uint8_t __g_spi0_slve_rxbuf[__NUM_COUNT]   = {0};     /**< \brief �ӻ����ջ����� */
static uint8_t __g_spi1_master_txbuf[__NUM_COUNT] = {0};     /**< \brief �������ͻ����� */
static uint8_t __g_spi1_master_rxbuf[__NUM_COUNT] = {0};     /**< \brief �������ջ����� */


/**
 * \brief SPI0�ӻ��жϴ�����
 */
static void __spi0_irq(void *p_arg)
{
    amhw_fsl_spi_t *p_hw_spi = (amhw_fsl_spi_t*)p_arg;
    
    static uint8_t send_pos = 0;
    static uint8_t recv_pos = 0;
    
    /* �������� */
    if (amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_R_FULL) {
        __g_spi0_slve_rxbuf[recv_pos++] = amhw_fsl_spi_data8_read(p_hw_spi);
    }
    
    /* �������� */
    if (amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_T_EMPTY) {
        amhw_fsl_spi_data8_wirte(p_hw_spi,__g_spi0_slve_txbuf[send_pos++]);
    }
}



static void __spi_speed_cfg (amhw_fsl_spi_t *p_hw_spi,
                             uint32_t target_speed,
                             uint32_t spi_freq)
{

    uint32_t real_speed;              /* ��������ٶ�    */
    uint32_t pdiv, best_pdiv;         /* Ԥ��Ƶֵ        */
    uint32_t div, best_div;           /* ����ֵ          */
    uint32_t diff, min_diff;          /* �ٶȲ�ֵ        */

   min_diff = 0xFFFFFFFFU;

   /* ����Ϊ���ķ�Ƶֵ,�ٶ�Ϊ��С */
   best_pdiv  = 7;
   best_div   = 8;

   /* ��������ʵ��ٶ� */
   for (pdiv = 0; (pdiv <= 7) && min_diff; pdiv++)
   {
       for (div = 0; (div <= 8) && min_diff; div++)
       {
           /* all_div = (pdiv+1) * 2^(div+1) */
           real_speed = (spi_freq / ((pdiv + 1) << (div+1)));

           /* ʵ���ٶ�ӦС��Ŀ���ٶ� */
           if (target_speed >= real_speed)
           {
               diff = target_speed-real_speed;

               if (min_diff > diff)
               {
                   /* ����ʵ��ٶ� */
                   min_diff   = diff;
                   best_pdiv  = pdiv;
                   best_div   = div;
               }
           }
       }
   }

   amhw_fsl_spi_div_cfg(p_hw_spi, best_pdiv, best_div);
}

/**
 * \brief SPI0�ӻ���ʼ����8bit���ݿ�� SPI_MODE1��
 */
static void __spi_slve_init (amhw_fsl_spi_t *p_hw_spi)
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
 * \brief SPI1�ӻ���ʼ����8bit���ݿ�� SPI_MODE1��
 */
static void __spi_master_init (amhw_fsl_spi_t *p_hw_spi, uint32_t spi_freq)
{
    /* ����SPIΪ���� */
    amhw_fsl_spi_workmode_cfg(p_hw_spi, AMHW_FSL_SPI_WMODE_MASTER);

    /* ����8bit���ݿ�� */
    amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_8BIT_WIDTH);

    /* ����ʱ����λ�ͼ��� */
    amhw_fsl_spi_mode_cfg(p_hw_spi, AMHW_FSL_SPI_MODE_1);
    
    /* ����CS����ΪƬѡ��� */
    amhw_fsl_spi_cs_cfg(p_hw_spi, AMHW_FSL_SPI_CS_SPI_OUT);

    /* ���ô����ٶ� */
    __spi_speed_cfg(p_hw_spi, 3000000, spi_freq);

    /* ʹ��SPIģ�� */
    amhw_fsl_spi_enable(p_hw_spi);
}


/**
 * \brief �������
 */
void demo_fsl_hw_spi_slave_irq_entry (amhw_fsl_spi_t *p_hw_spi0,
                                      amhw_fsl_spi_t *p_hw_spi1,
                                      int             slave_inum,
                                      uint32_t        spi_freq)
{
    uint8_t i;
    
    am_bool_t error_ocur = AM_FALSE;
    
    /* SPI��ʼ����SPI0Ϊ�ӻ���SPI1Ϊ���� */
    __spi_slve_init(p_hw_spi0);
    __spi_master_init(p_hw_spi1, spi_freq);


    /* ���췢�͵����� */
    for (i = 0; i < __NUM_COUNT; i++) {
        __g_spi0_slve_txbuf[i]   = i * 3;
        __g_spi1_master_txbuf[i] = i * 2;
    }
    
    /* SPI0�ӻ�ʹ���жϽ��պͷ������� */
    amhw_fsl_spi_int_enable(p_hw_spi0, AMHW_FSL_SPI_IRQ_R_MODDEF);
    amhw_fsl_spi_int_enable(p_hw_spi0, AMHW_FSL_SPI_IRQ_T);

    am_int_connect(slave_inum, __spi0_irq, (void*)p_hw_spi0);
    am_int_enable(slave_inum);
    
    /* SPI�����շ����� */
    for (i = 0; i < __NUM_COUNT; i++) {
        while((amhw_fsl_spi_stat_get(p_hw_spi1) & AMHW_FSL_SPI_STAT_T_EMPTY) == 0);
        amhw_fsl_spi_data8_wirte(p_hw_spi1,__g_spi1_master_txbuf[i]);
        
        while((amhw_fsl_spi_stat_get(p_hw_spi1) & AMHW_FSL_SPI_STAT_R_FULL) == 0);
        __g_spi1_master_rxbuf[i] = amhw_fsl_spi_data8_read(p_hw_spi1);
    }
   
    /* �ȴ��������ݷ������ */
    am_mdelay(1000);
    
    /* ���ݼ��� */
   for (i = 0; i < __NUM_COUNT; i++) {
        if (__g_spi0_slve_txbuf[i]   != __g_spi1_master_rxbuf[i] ||
            __g_spi1_master_txbuf[i] != __g_spi0_slve_rxbuf[i]) {
                
            error_ocur  = AM_TRUE;
            break;   
        }
        AM_DBG_INFO("spi0_tx = %d spi1_rx = %d\r\n",
                    __g_spi0_slve_txbuf[i],
                    __g_spi1_master_rxbuf[i]);
        AM_DBG_INFO("spi1_tx = %d spi0_rx = %d\r\n",
                    __g_spi1_master_txbuf[i],
                    __g_spi0_slve_rxbuf[i]);
    } 

    while (1) {
        
        /* ����У�����LED��˸���� */
        if(error_ocur) {
            am_led_on(LED1);
            am_mdelay(200);
            am_led_off(LED1);
            am_mdelay(200);
        
        /* LED�Ƴ��� */
        } else {
            am_led_on(LED1);
        }

    }
}

/** [src_fsl_hw_spi_slave_irq] */

/* end of file */
