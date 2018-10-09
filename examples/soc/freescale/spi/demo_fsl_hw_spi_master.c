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
 * \brief SPI������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI��PIOC_6��PIOC_7����������ģ��ӻ��豸���ػ����ԣ�
 *
 * - ʵ������:
 *   1. ����ͨ��MOSI�������ݣ����������ݴ�MOSI���أ�
 *   2. �ȽϷ����Ͷ��ص����ݣ������ͬLED0һֱ����,������200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_kl26_hw_spi_master.c src_kl26_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 16-09-27  sdy, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_kl26_if_hw_spi_master
 * \copydoc demo_kl26_hw_spi_master.c
 */
 
/** [src_kl26_hw_spi_master] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "hw/amhw_fsl_spi.h"
#include "am_board.h"

/**
 * \name SPI����ṹ�����ò���
 */

#define SPI_CFG_LSB         AM_BIT(0)   /**< \brief ��λ���ȷ���         */
#define SPI_CFG_16BIT       AM_BIT(1)   /**< \brief �������ݿ��Ϊ16λ   */

#define SPI_CFG_MODE_0      (0)                     /**< \brief ģʽ0    */
#define SPI_CFG_MODE_1      (0         | AM_BIT(2)) /**< \brief ģʽ1    */
#define SPI_CFG_MODE_2      (AM_BIT(3) | 0)         /**< \brief ģʽ2    */
#define SPI_CFG_MODE_3      (AM_BIT(2) | AM_BIT(3)) /**< \brief ģʽ3    */

/** @} */

/** 
 * \brief SPI����ṹ��
 */
typedef struct spi_transfer {
    const void  *p_txbuf;           /**< \brief ָ�������ݻ����ָ��   */
    void        *p_rxbuf;           /**< \brief ָ��������ݻ����ָ��    */
    uint32_t     nbytes;            /**< \brief ���ݳ���                  */
    uint32_t     flags;             /**< \brief SPI������Ʊ�־λ         */
} spi_transfer_t;


/**
 * \brief SPI����ṹ���������
 *
 * \param[in] p_trans : ָ��SPI����ṹ��
 * \param[in] p_txbuf : ָ�������ݻ����ָ��
 * \param[in] p_rxbuf : ָ��������ݻ����ָ��
 * \param[in] nbytes  : ��ǰ�������ݳ���
 * \param[in] flags   : SPI������Ʊ�־λ
 *
 * \retval  AM_OK     : �������
 */
static int __spi_mktrans (spi_transfer_t *p_trans, 
                          const void     *p_txbuf,
                          void           *p_rxbuf,
                          uint32_t        nbytes,
                          uint16_t        flags)
                    
{
    if (p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->p_txbuf  = p_txbuf;
    p_trans->p_rxbuf  = p_rxbuf;
    p_trans->nbytes   = nbytes;
    p_trans->flags    = flags;

    return AM_OK;
}

/**
 * \brief SPI�ٶ�����
 *
 * \param[in] p_hw_spi     : ָ��SPI�Ĵ������ָ��
 * \param[in] target_speed : Ŀ���ٶ�
 * \param[in] spi_freq     : SPI����ʱ��Ƶ��
 *
 * \return  ��
 */
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

static void __spi_master_cfg (amhw_fsl_spi_t *p_hw_spi, uint32_t flags)
{
    if (flags & SPI_CFG_LSB) {
        amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_LSB);
    } else {
        amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_MSB);
    }

    if (flags & SPI_CFG_16BIT) {
        amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_16BIT_WIDTH);
    } else {
        amhw_fsl_spi_feature_cfg(p_hw_spi, AMHW_FSL_SPI_CFG_8BIT_WIDTH);
    }

    /* ����ʱ����λ�ͼ��� */
    amhw_fsl_spi_mode_cfg(p_hw_spi, flags);
}

/**
 * \brief SPIƬѡ����
 *
 * \param[in] p_hw_spi     : ָ��SPI�Ĵ������ָ��
 * \param[in] pin          : CS���ź�
 * \param[in] active_level : ������Ч״̬��ƽ
 * \param[in] state        : ״̬
 *
 * \return  ��
 */
static void __spi_master_cs_ctr (amhw_fsl_spi_t *p_hw_spi,
                                 int             pin,
                                 uint8_t         active_level,
                                 am_bool_t       state)
{
    /* Ƭѡ��Ч */
    if (state) {
        am_gpio_set(pin, active_level);
    
    /* Ƭѡ��Ч */
    } else {
        am_gpio_set(pin, !active_level);
    }
}

/**
 * \brief SPI�ػ��������
 */
static void __spi_loop_trans (amhw_fsl_spi_t  *p_hw_spi,
                              spi_transfer_t  *p_trans,
                              int              pin_cs)
{
    uint32_t pos = 0;

    am_bool_t  width_16bit  = (p_trans->flags & SPI_CFG_16BIT) ? AM_TRUE : AM_FALSE;
    
    __spi_master_cfg(p_hw_spi, p_trans->flags);

    __spi_master_cs_ctr(p_hw_spi, pin_cs, AM_GPIO_LEVEL_LOW, AM_TRUE);

    while(pos < p_trans->nbytes) {

        /* �ȴ����Է��� */
        while ((amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_T_EMPTY) == 0);

        if (width_16bit) {
            amhw_fsl_spi_data16_wirte(p_hw_spi, *(uint16_t*)((uint32_t)p_trans->p_txbuf + pos));
        } else {
            amhw_fsl_spi_data8_wirte(p_hw_spi, *(uint8_t*)((uint32_t)p_trans->p_txbuf + pos));
        }

        /* �ȴ����Խ��� */
        while ((amhw_fsl_spi_stat_get(p_hw_spi) & AMHW_FSL_SPI_STAT_R_FULL) == 0);

        if (width_16bit) {
            *(uint16_t*)((uint32_t)p_trans->p_rxbuf + pos) = amhw_fsl_spi_data16_read(p_hw_spi);
            pos +=2;
        } else {
            *(uint8_t*)((uint32_t)p_trans->p_rxbuf + pos) = amhw_fsl_spi_data8_read(p_hw_spi);
            pos += 1;
        }
    }
    
    /* ����Ƭѡ */
    __spi_master_cs_ctr(p_hw_spi, pin_cs, AM_GPIO_LEVEL_LOW, AM_FALSE);
}

/**
 * \brief �������
 */
void demo_fsl_hw_spi_master_entry (amhw_fsl_spi_t *p_hw_spi,
                                   int             pin_cs,
                                   uint32_t        spi_freq)
{
    spi_transfer_t spi0_transfer;     /* ����һ��SPI����ṹ��ʵ��          */

    const uint32_t length =32;
    uint16_t       spi_send_buf[16];
    uint16_t       spi_recv_buf[16];

    uint8_t i;

    am_bool_t error_ocur = AM_FALSE;

    amhw_fsl_spi_workmode_cfg(p_hw_spi, AMHW_FSL_SPI_WMODE_MASTER);
    __spi_speed_cfg(p_hw_spi, 3000000, spi_freq);
    amhw_fsl_spi_enable(p_hw_spi);

    /* �������� */
    for (i = 0; i < (length / 2); i++) {
        spi_send_buf[i] = i;
    }
    __spi_mktrans(&spi0_transfer,
                  &spi_send_buf,
                  &spi_recv_buf,
                  length,
                  (SPI_CFG_MODE_0 | SPI_CFG_16BIT));

    /* ���ݴ��� */
    __spi_loop_trans(p_hw_spi, &spi0_transfer, pin_cs);

    /* ���ݼ��� */
    for (i = 0; (i < length / 2); i++) {
        if (spi_recv_buf[i] != spi_send_buf[i]) {
            error_ocur = AM_TRUE;
            break;
        }
        am_kprintf("recv = %d\r\n", spi_recv_buf[i]);
    }

    while (1) {
        if (error_ocur) {
            am_led_on(LED0);
            am_mdelay(200);
            am_led_off(LED0);
            am_mdelay(200);
        } else {
            am_led_on(LED0);
        }
    }
}

/** [src_fsl_hw_spi_master] */

/* end of file */
