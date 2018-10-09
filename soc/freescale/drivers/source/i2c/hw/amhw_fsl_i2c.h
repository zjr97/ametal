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
 * \brief I2C Ӳ�������ӿ�
 *
 * 1. 2��I2C�ӿڣ�
 * 2. �ɱ��ѡ��64������ʱ��Ƶ�ʣ�
 * 3. ֧�ֶ�������;��дӻ��Ķ�������
 * 4. ֧���ж����������ֽ����ݴ��䣻
 * 5. ͨ��������ã���֧��7bits��10bits��ַ���豸��
 * 6. ֧��ϵͳ�������ߣ�
 * 7. ����Ƭ��ʱ������ʱ�������ݺʹӻ���ַƥ�䣬���Խ��豸�ӵ���ģʽ�л��ѣ�
 * 8. ֧��DMA��
 * 9. �ɱ�̵��������˲���
 *
 * \internal
 * Modification History
 * - 1.00 16-09-19  ari, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_I2C_H
#define __AMHW_FSL_I2C_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
/**
 * @addtogroup amhw_fsl_if_i2c
 * @copydoc amhw_fsl_i2c.h
 * @{
 */

/**
 * \brief I2C �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_i2c {
    __IO uint8_t  address1;         /**< \brief I2C ��ַ�Ĵ���1  */
    __IO uint8_t  clkdiv;           /**< \brief I2C ʱ�ӷ�Ƶ�Ĵ���  */
    __IO uint8_t  control1;         /**< \brief I2C ���ƼĴ���1 */
    __IO uint8_t  status ;          /**< \brief I2C ״̬�Ĵ���     */
    __IO uint8_t  data;             /**< \brief I2C ����I/O�Ĵ���     */
    __IO uint8_t  control2;         /**< \brief I2C ���ƼĴ���2 */
    __IO uint8_t  glitch_filter;    /**< \brief I2C �ɱ�������˲��Ĵ���   */
    __IO uint8_t  range_address;    /**< \brief I2C ��Χ��ַ�Ĵ���  */
    __IO uint8_t  smbus;            /**< \brief I2C SMBUS������״̬�Ĵ���   */
    __IO uint8_t  address2;         /**< \brief I2C ��ַ�Ĵ���2 */
    __IO uint8_t  timeout_high;     /**< \brief I2C �͵�ƽ��ʱ��λ�Ĵ���   */
    __IO uint8_t  timeout_low;      /**< \brief I2C �͵�ƽ��ʱ��λ�Ĵ���   */
} amhw_fsl_i2c_t;

/**
 * \name I2C����ģʽ
 * \anchor grep_amhw_fsl_i2c_transmode
 * @{
 */

#define AMHW_FSL_I2C_TRANSMODE_RECV  0          /**< \brief I2C ����ģʽ         */
#define AMHW_FSL_I2C_TRANSMODE_SEND  AM_BIT(4)  /**< \brief I2C ����ģʽ         */

/** @} */

/**
 * \name I2C ����ģʽ
 * \anchor grep_amhw_fsl_i2c_workmode
 * @{
 */

#define AMHW_FSL_I2C_WORKMDOE_SLAVE      0        /**< \brief I2C �ӻ�ģʽ       */
#define AMHW_FSL_I2C_WORKMDOE_MASTER  AM_BIT(5)  /**< \brief I2C ����ģʽ        */

/** @} */

/**
 * \name I2C ״̬��־
 * \anchor grep_amhw_fsl_i2c_stat
 * @{
 */

#define AMHW_FSL_I2C_STAT_TCF    AM_BIT(7)     /**< \brief I2C ������ɱ�־      */
#define AMHW_FSL_I2C_STAT_IAAS   AM_BIT(6)     /**< \brief I2C ��Ϊ�ӻ���Ѱַ    */
#define AMHW_FSL_I2C_STAT_BUSY   AM_BIT(5)     /**< \brief I2C ����æ��־        */
#define AMHW_FSL_I2C_STAT_ARBL   AM_BIT(4)     /**< \brief I2C �����ٲö�ʧ��־  */
#define AMHW_FSL_I2C_STAT_RAM    AM_BIT(3)     /**< \brief I2C ��ַ��Χ�Ĵ���ƥ��  */
#define AMHW_FSL_I2C_STAT_SRW    AM_BIT(2)     /**< \brief I2C ���豸����״̬    */
#define AMHW_FSL_I2C_STAT_IICIF  AM_BIT(1)     /**< \brief I2C �жϱ�־          */
#define AMHW_FSL_I2C_STAT_RXAK   AM_BIT(0)     /**< \brief I2C �޻�Ӧ�ź�        */

/** @} */

/**
 * \name I2C ��ַģʽ
 * \anchor grep_amhw_fsl_i2c_addrmode
 * @{
 */

#define AMHW_FSL_I2C_ADDRMODE_BIT7        0        /**< \brief I2C 7λ��ַģʽ   */
#define AMHW_FSL_I2C_ADDRMODE_BIT10    AM_BIT(6)   /**< \brief I2C 10λ��ַģʽ  */

/** @} */

/**
 * \name I2C ����ģʽ
 * \anchor grep_amhw_fsl_i2c_drivemode
 * @{
 */

#define AMHW_FSL_I2C_DRIVEMODE_NORMAL  0         /**< \brief I2C ��������ģʽ   */
#define AMHW_FSL_I2C_DRIVEMODE_HIGH   AM_BIT(5)  /**< \brief I2C ��������ģʽ   */

/** @} */

/**
 * \name I2C �ӻ�ʱ��ģʽ
 * \anchor grep_amhw_fsl_i2c_s_clkmode
 * @{
 */

#define AMHW_FSL_I2C_S_CLKMODE_FALLOW_M    0      /**< \brief I2C �ӻ���������   */
#define AMHW_FSL_I2C_S_CLKMODE_ALONE   AM_BIT(4)  /**< \brief I2C �ӻ������ʶ��� */

/** @} */

/**
 * \name I2C ��ʱ��־
 * \anchor grep_amhw_fsl_i2c_tmout_flags
 * @{
 */

#define AMHW_FSL_I2C_TMOUT_FLAG_SCL_LOW    AM_BIT(3) /**< \brief SCL�ͳ�ʱ��־  */
#define AMHW_FSL_I2C_TMOUT_FLAG_IDEL       AM_BIT(2) /**< \brief ���г�ʱ       */
#define AMHW_FSL_I2C_TMOUT_FLAG_SDA_LOW    AM_BIT(1) /**< \brief SCL�߳�ʱ��־2 */

/** @} */

/**
 * \name I2C�ж�ѡ��
 * \anchor grep_amhw_fsl_i2c_int_option
 * \note ֻ��ʹ����ȫ���жϣ������жϲ���Ч
 *          - �ֽڴ�������ж�  ��IICIE(TCF)
 *          - ��ַƥ���ж�       : IICIE(IAAS)
 *          - �ٲö�ʧ�ж�      ��IICIE(ARBL)
 *          - ֹͣ�źŻ���ʼ�źż���ж�  ��IICIE & SSIE��STOPF | STARTF��I2Cx_FLT��4λ����
 *          - SCL�͵�ƽ��ʱ�ж� ��IICIE��SLTF��
 *          - SDA�͵�ƽ��ʱ�ж� ��IICIE & SHTF2IE��SHTF2��
 *          - �͹���ģʽ�����жϣ�IICIE & WUEN��IAAS��
 *
 * @{
 */

#define AMHW_FSL_I2C_INT_IICIE   AM_BIT(7)      /**< \brief I2Cȫ���ж�       */
#define AMHW_FSL_I2C_INT_STOPIE  AM_BIT(6)      /**< \brief ֹͣ�źż���ж�  */
/**< \brief ʵ����I2Cx_FLT�Ĵ�����6λ����ʼ�źź�ֹͣ�ź��жϣ��ֲ���û��д����KL03���ֲ���д�� */
#define AMHW_FSL_I2C_INT_SSIE    AM_BIT(6)      /**< \brief I2C Bus Stop or Start Interrupt Enable */
#define AMHW_FSL_I2C_INT_SHTF2IE AM_BIT(5)      /**< \brief SDA�͵�ƽ��ʱ�ж� */
#define AMHW_FSL_I2C_INT_WUEN    AM_BIT(4)      /**< \brief �����ж�          */

/** @} */

/** \brief ��ʱʱ������ʱ��ѡ�� */
typedef enum amhw_fsl_i2c_timeout_clk_sel {
    AMHW_FSL_I2C_MODULE_CLOCK_64 = 0,          /**< \brief I2Cģ��ʱ��64��Ƶ  */
    AMHW_FSL_I2C_MODULE_CLOCK_1  = AM_BIT(4)   /**< \brief I2Cģ��ʱ��        */
} amhw_fsl_i2c_timeout_clk_sel_t;

/**
 * \brief ʹ��I2Cģ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |=  AM_BIT(7);
}

/**
 * \brief ����I2Cģ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 &= ~AM_BIT(7);
}

/**
 * \brief ����һ����ʼ�ź�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_start_signal_send (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |=  AM_BIT(5);
}

/**
 * \brief ����һ��ֹͣ�ź�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_stop_signal_send (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 &= ~AM_BIT(5);
}

/**
 * \brief ����һ���ظ���ʼ�ź�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_restart_signal_send (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |= AM_BIT(2);
}

/**
 * \brief ���ô���ģʽ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] mode     : ����ģʽ���μ� grep_amhw_fsl_i2c_transmode
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_transmode_set (amhw_fsl_i2c_t *p_hw_i2c , uint8_t mode)
{
    p_hw_i2c->control1 &= ~AM_BIT(4);
    p_hw_i2c->control1 |=  mode;
}

/**
 * \brief ���ôӻ�1��ַ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] address  : �ӻ�1�ĵ�ַ
 * \param[in] mode     : ��ַģʽ
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr1_set (amhw_fsl_i2c_t *p_hw_i2c,
                                     uint16_t    address,
                                     uint8_t     mode)
{

    if (mode == AMHW_FSL_I2C_ADDRMODE_BIT10) {
        p_hw_i2c->control2 |= AM_BIT(6);
        p_hw_i2c->control2 &= ~AM_SBF(0x07, 0);
        p_hw_i2c->control2 |= (address >> 8) & 0x7;
    } else {
        p_hw_i2c->control2 &= ~AM_BIT(6);
        p_hw_i2c->address1 = (address << 1);
    }
}

/**
 * \brief ��ȡ�ӻ�1��ַ(��7λ)
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
uint8_t amhw_fsl_i2c_addr1_get (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->address1 >> 1);
}


/**
 * \brief ���÷�Ƶֵ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] div      : д��ķ�Ƶ����ϵ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_clk_div_set (amhw_fsl_i2c_t *p_hw_i2c, uint8_t div)
{
    p_hw_i2c->clkdiv = div;
}

/**
 * \brief ʹ��I2C�ж�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] irq_flag : �ж�ѡ��,�μ� grep_amhw_fsl_i2c_int_option
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_int_enable (amhw_fsl_i2c_t *p_hw_i2c, uint8_t irq_flag)
{
    if (irq_flag & AMHW_FSL_I2C_INT_IICIE) {
        p_hw_i2c->control1 |= AM_BIT(6);
    }
    if(irq_flag & AMHW_FSL_I2C_INT_SSIE) {
        p_hw_i2c->glitch_filter |= AM_BIT(5);
    }
    if (irq_flag & AMHW_FSL_I2C_INT_SHTF2IE) {
        p_hw_i2c->smbus |= AM_BIT(0);
    }
    if(irq_flag & AMHW_FSL_I2C_INT_WUEN) {
        p_hw_i2c->control1 |= AM_BIT(1);
    }
}

/**
 * \brief ����I2C�ж�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] irq_flag : �ж�ѡ��,�μ� grep_amhw_fsl_i2c_int_option
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_int_disable (amhw_fsl_i2c_t *p_hw_i2c, uint8_t irq_flag)
{
    if (irq_flag & AMHW_FSL_I2C_INT_IICIE) {
        p_hw_i2c->control1 &= ~AM_BIT(6);
    }
    if(irq_flag & AMHW_FSL_I2C_INT_SSIE) {
        p_hw_i2c->glitch_filter &= ~AM_BIT(5);
    }
    if (irq_flag & AMHW_FSL_I2C_INT_SHTF2IE) {
        p_hw_i2c->smbus &= ~AM_BIT(0);
    }
    if(irq_flag & AMHW_FSL_I2C_INT_WUEN) {
        p_hw_i2c->control1 &= ~AM_BIT(1);
    }
}

/**
 * \brief I2C ACKӦ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_ack_respond (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 &= ~AM_BIT(3);
}

/**
 * \brief I2C ��Ӧ��NAK��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_nak_respond (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |= AM_BIT(3);
}

/**
 * \brief I2C �ط�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 *
 * \note  �����ٲö�ʧ��ʱ����
 */
am_static_inline
void amhw_fsl_i2c_rsta (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |= AM_BIT(2);
}

/**
 * \brief I2C DMAģʽʹ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_dma_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 |= AM_BIT(0);
}

/**
 * \brief I2C DMAģʽ����
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_dma_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control1 &= ~AM_BIT(0);
}

/**
 * \brief ����״̬�Ĵ�����ֵ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ״̬��־���μ� grep_amhw_fsl_i2c_stat
 */
am_static_inline
uint8_t amhw_fsl_i2c_stat_get (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->status);
}

/**
 * \brief ���״̬�Ĵ�����־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] flags    : ״̬��־,�μ� grep_amhw_fsl_i2c_stat
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_stat_clr (amhw_fsl_i2c_t *p_hw_i2c , uint8_t flags)
{
    p_hw_i2c->status = flags;
}

/**
 * \brief д���ݵ����ݼĴ���
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] data     : д�������
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_data_write (amhw_fsl_i2c_t *p_hw_i2c , uint8_t data)
{
    p_hw_i2c->data = data;
}

/**
 * \brief ��ȡ���ݼĴ�����ֵ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
uint8_t amhw_fsl_i2c_data_read (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->data);
}

/**
 * \brief ʹ�ܳ��õ�ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_general_call_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control2 |= AM_BIT(7);
}

/**
 * \brief ���ܳ��õ�ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_general_call_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control2 &= ~AM_BIT(7);
}

/**
 * \brief ����I2C��ַģʽ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] mode     : ��ַģʽ���μ� grep_amhw_fsl_i2c_addrmode
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addrmode_set (amhw_fsl_i2c_t *p_hw_i2c , uint8_t mode)
{
    p_hw_i2c->control2 &= ~AM_BIT(6);
    p_hw_i2c->control2 |=  mode;
}

/**
 * \brief ��������ģʽ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] mode     : ����ģʽ���μ� grep_amhw_fsl_i2c_drivemode
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_drivemode_set (amhw_fsl_i2c_t *p_hw_i2c , uint8_t mode)
{
    p_hw_i2c->control2 &= ~AM_BIT(5);
    p_hw_i2c->control2 |=  mode;
}

/**
 * \brief I2C �ӻ���������Դ����
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] mode     : �ӻ�ʱ��ģʽ���μ� grep_amhw_fsl_i2c_s_clkmode
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_s_clkmode_set (amhw_fsl_i2c_t *p_hw_i2c , uint8_t mode)
{
    p_hw_i2c->control2 &= ~AM_BIT(4);
    p_hw_i2c->control2 |=  (mode);
}

/**
 * \brief ʹ�ܵ�ַ��Χƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr_range_match_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control2 |= AM_BIT(3);
}

/**
 * \brief ���ܵ�ַ��Χƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr_range_match_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->control2 &= ~AM_BIT(3);
}

/**
 * \brief ����I2C��Χ�Ĵ����ĵ�ַ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] addr     :д��ĵ�ַ
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr_range_set (amhw_fsl_i2c_t *p_hw_i2c, uint8_t addr)
{
    p_hw_i2c->range_address = (addr << 1);
}

/**
 * \brief ��ȡI2C��Χ�Ĵ����ĵ�ַ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��ַ
 */
am_static_inline
uint8_t amhw_fsl_i2c_addr_range_get (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->range_address >> 1);
}

/**
 * \brief ʹ��ֹͣģʽ�����ӳ�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 *
 * \note ʹ�ܺ����ݴ�����ɺ�Ż����ֹͣ�ź�
 */
am_static_inline
void amhw_fsl_i2c_stop_entry_delay_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->glitch_filter |= AM_BIT(7);
}

/**
 * \brief ����ֹͣģʽ�����ӳ�
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_stop_entry_delay_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->glitch_filter &= ~AM_BIT(7);
}

/**
 * \brief I2C ��ȡ����ֹͣ��־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
am_bool_t amhw_fsl_i2c_stop_is_dec (amhw_fsl_i2c_t *p_hw_i2c)
{
    return AM_BIT_ISSET(p_hw_i2c->glitch_filter, 6) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ���ֹͣ�źż���־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_stop_dec_clr (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->glitch_filter |= AM_BIT(6);
}

/**
 * \brief I2C ��ȡ���߿�ʼ��־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 *
 * \note FLT�Ĵ����е�4λΪ���߿�ʼ��ʶ������kl16��kl26���ֲ��϶�ûд
 */
am_static_inline
am_bool_t amhw_fsl_i2c_start_is_dec (amhw_fsl_i2c_t *p_hw_i2c)
{
    return AM_BIT_ISSET(p_hw_i2c->glitch_filter, 4) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief �����ʼ�źż���־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_start_dec_clr (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->glitch_filter |= AM_BIT(4);
}

/**
 * \brief �����˲�����
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_flt_fact (amhw_fsl_i2c_t *p_hw_i2c, uint8_t fact)
{
    if (fact > 15)
        fact = 15;
    
    p_hw_i2c->glitch_filter &= ~0x0f;
    p_hw_i2c->glitch_filter |= fact;
}

/**
 * \brief ʹ�ܿ���ACK
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 *
 * \note ʹ�ܿ���ACK��Ӧ�����öԵ�ǰ���յ�������Ч
 */
am_static_inline
void amhw_fsl_i2c_fast_ack_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus |= AM_BIT(7);
}

/**
 * \brief ���ܿ���ACK
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_fast_ack_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus &= ~AM_BIT(7);
}

/**
 * \brief ʹ�ܾ�����ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_alertaddr_match_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus |= AM_BIT(6);
}

/**
 * \brief ���ܾ�����ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_alertaddr_match_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus &= ~AM_BIT(6);
}

/**
 * \brief ����addr2�ĵ�ַ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] addr     : д��ĵ�ַ
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr2_set (amhw_fsl_i2c_t *p_hw_i2c, uint8_t addr)
{
    p_hw_i2c->address2 = (addr << 1);
}

/**
 * \brief ��ȡaddr2�ĵ�ַ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  addr2�ĵ�ַ
 */
am_static_inline
uint8_t amhw_fsl_i2c_addr2_get (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->address2 >> 1);
}

/**
 * \brief ʹ�ܵڶ���ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr2_match_enable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus |= AM_BIT(5);
}

/**
 * \brief ���ܵڶ���ַƥ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_addr2_match_disable (amhw_fsl_i2c_t *p_hw_i2c)
{
    p_hw_i2c->smbus &= ~AM_BIT(5);
}

/**
 * \brief ѡ��ʱ������ʱ��
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] clk      : ʱ��ѡ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_timeout_clk_sel (amhw_fsl_i2c_t                *p_hw_i2c,
                                  amhw_fsl_i2c_timeout_clk_sel_t clk)
{
    p_hw_i2c->smbus &= ~AM_BIT(4);
    p_hw_i2c->smbus |= clk;
}

/**
 * \brief ��ȡI2C��ʱ��־
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 *
 * \return ��ʱ��־,�μ� grep_amhw_fsl_i2c_tmout_flags
 */
am_static_inline
uint8_t amhw_fsl_i2c_tmout_flag_get (amhw_fsl_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->smbus & 0x0E);
}

/**
 * \brief I2C SCL��ʱ��־���
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ��
 * \param[in] flags    : ��ʱ��־�� �μ� grep_amhw_fsl_i2c_tmout_flags
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_tmout_flag_clr (amhw_fsl_i2c_t *p_hw_i2c , uint8_t flags)
{
    p_hw_i2c->smbus |= flags;
}

/**
 * \brief ����I2C��SCL�͵�ƽ��ʱֵ
 *
 * \param[in] p_hw_i2c : ָ��i2c�Ĵ������ָ
 * \param[in] value    : ���豸��ַ����
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2c_scl_timeout_val_set (amhw_fsl_i2c_t *p_hw_i2c , uint16_t value)
{
    p_hw_i2c->timeout_high = value >> 8;
    p_hw_i2c->timeout_low  = value;
}

/**
 * @} amhw_fsl_if_i2c
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_I2C_H */


/* end of file */
