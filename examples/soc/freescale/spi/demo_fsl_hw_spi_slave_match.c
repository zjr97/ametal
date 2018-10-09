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
 * \brief SPI�ӻ�ƥ���ж���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӻ��ӿں������ӿڶ�Ӧ��������(PIOC_4 == PIOD_4, PIOC_5 == PIOD_5,
 *      PIOC_6 == PIOD_6, PIOC_7 == PIOD_7)����
 *
 * - ʵ������:
 *   1. SPI0�ӻ�����SPI1�������ݣ�������ݱ�ƥ�䣬���ʹӻ��������������
 *   2. SPI1���������յ����������Ƿ���ȷ�������ȷ����LED������LED��˸������
 *
 * \par Դ����
 * \snippet demo_fsl_hw_spi_slave_match.c src_fsl_hw_spi_slave_match
 *
 * \internal
 * \par History
 * - 1.00 15-10-30  liqing, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_spi_slave_match
 * \copydoc demo_fsl_hw_spi_slave_match.c
 */
 
/** [src_fsl_hw_spi_slave_match] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_fsl_spi.h"
#include "am_board.h"
#include "am_arm_nvic.h"

#define __SLAVE_MATCH_DATA    0x55            /**< \brief ƥ������      */
#define __DATA_LENGTH         0x5             /**< \brief �����볤��    */

/** \brief �ӻ�������    */
const uint8_t __g_slv_data[__DATA_LENGTH] = {
   1, 2, 1, 3, 5
};

/**
 * \brief SPI�жϴ�����
 */
void __spi_irq_handle (void *p_arg)
{
    static volatile uint8_t pos = 0;               /* ����λ��          */
    static volatile am_bool_t  match_irq  = AM_TRUE;     /* ƥ���жϴ򿪱�־   */
    static volatile am_bool_t  send_irq   = AM_FALSE;    /* �����жϴ򿪱�־   */

    amhw_fsl_spi_t *p_hw_spi = (amhw_fsl_spi_t*)p_arg;

    /* ƥ���ж� */
    if (match_irq && ((amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_MATCH) != 0 )) {
        
        /* ��ʼ�������������� */
        p_hw_spi->s = 0x40;
        pos = 0;
        
        amhw_fsl_spi_int_disable(p_hw_spi, AMHW_FSL_SPI_IRQ_MATCH); /* �ر�ƥ���ж� */
        match_irq = AM_FALSE;
        
        amhw_fsl_spi_int_enable(p_hw_spi, AMHW_FSL_SPI_IRQ_T);      /* ���������ж� */
        send_irq  = AM_TRUE;
    }

    /* �����ж� */
    if (send_irq && (amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_T_EMPTY) != 0 ) {
        
        /* �������� */
        if (pos < __DATA_LENGTH) {
            amhw_fsl_spi_data8_read(p_hw_spi);
            amhw_fsl_spi_data8_wirte(p_hw_spi, __g_slv_data[pos++]);
            
        /* �ص����״̬ */
        } else {
            p_hw_spi->s = 0x40;
            amhw_fsl_spi_matchdata16_wirte(p_hw_spi, 0x55);
            
            amhw_fsl_spi_int_enable(p_hw_spi, AMHW_FSL_SPI_IRQ_MATCH);
            match_irq = AM_TRUE;
            
            amhw_fsl_spi_int_disable(p_hw_spi, AMHW_FSL_SPI_IRQ_T);
            send_irq  = AM_FALSE;
        }
    }
}

static void __spi_speed_cfg (amhw_fsl_spi_t *p_hw_spi,
                             uint32_t        target_speed,
                             uint32_t        spi_freq)
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
    /* ����SPIΪ�ӻ� */
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
void demo_fsl_hw_spi_slave_match_entry (amhw_fsl_spi_t *p_hw_spi0,
                                        amhw_fsl_spi_t *p_hw_spi1,
                                        int             slave_inum,
                                        uint32_t        spi_freq)
{
    uint8_t i;
    /** \brief �������ͻ����� */
    uint8_t master_tx_buf[6] = {__SLAVE_MATCH_DATA, 0, 0, 0, 0, 0};
    /** \brief �������ջ����� */
    uint8_t master_rx_buf[6] = {0};
    am_bool_t error_ocur = AM_FALSE;

    /* SPI �ӻ���ʼ�� */
    __spi_slve_init(p_hw_spi0);
    __spi_master_init(p_hw_spi1, spi_freq);

    /* ����ƥ������(���������8bit������ֻ�е�8λ��Ч ) */
    amhw_fsl_spi_matchdata16_wirte(p_hw_spi0, __SLAVE_MATCH_DATA);

    /* ���ƥ���־ */
    p_hw_spi0->s = 0x40;

    /* ����ƥ���ж� */
    amhw_fsl_spi_int_enable(p_hw_spi0, AMHW_FSL_SPI_IRQ_MATCH);
    am_int_connect(slave_inum, __spi_irq_handle, (void*)p_hw_spi0);
    am_int_enable(slave_inum);

    /* �������������룬������������ */
    for (i = 0; i < (__DATA_LENGTH + 1); i++) {
        while((amhw_fsl_spi_stat_get(p_hw_spi1) & AMHW_FSL_SPI_STAT_T_EMPTY) == 0);
        amhw_fsl_spi_data8_wirte(p_hw_spi1,master_tx_buf[i]);
        
        while((amhw_fsl_spi_stat_get(p_hw_spi1) & AMHW_FSL_SPI_STAT_R_FULL) == 0);
        master_rx_buf[i] = amhw_fsl_spi_data8_read(p_hw_spi1);
    }
    
    am_mdelay(1000);
    
    /* �����յ��������� */
    for (i = 0; i < __DATA_LENGTH ; i++) {
        if (master_rx_buf[i+1] != __g_slv_data[i]) {
            error_ocur = AM_TRUE;
            break;
        }
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

/** [src_fsl_hw_spi_slave_match] */

/* end of file */
