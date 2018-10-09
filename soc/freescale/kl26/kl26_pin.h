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
 * \brief KL26 GPIO �������ò�������
 *
 * \internal
 * \par Modification History
 *
 * \note: 
 *  1. ��KL16��ȣ�KL26��GPIO�ܽ�����PIOE_16��PIOE_17��PIOE_18��PIOE_19
 *  2. ���м������ž��������������ã��⼸�����Ž���ʹ�ø���������������GPIOģʽ��IO������������
 *
 * - 1.00 17-04-07  nwt, adapt gpio difference kl16, kl26.
 * - 1.00 15-10-17  wxj, first implementation.
 * \endinternal
 */

#ifndef __KL26_PIN_H
#define __KL26_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_kl26_gpio_util.h"

 /**
 * \addtogroup kl26_if_pin
 * \copydoc kl26_pin.h
 * @{
 */

/**
 * \name оƬ�ͺ�ʹ��ѡ��
 * @{
 */
#if defined(KL16) || defined(KL26)
#else
#define KL26
#endif

/** @} */

/**
 * \name KL26 GPIO ���ű��
 * @{
 */

#define PIOA_0          0         /**< \brief PIOA_0 ���ź�  */
#define PIOA_1          1         /**< \brief PIOA_1 ���ź�  */
#define PIOA_2          2         /**< \brief PIOA_2 ���ź�  */
#define PIOA_3          3         /**< \brief PIOA_3 ���ź�  */
#define PIOA_4          4         /**< \brief PIOA_4 ���ź�  */
#define PIOA_5          5         /**< \brief PIOA_5 ���ź�  */

#define PIOA_12         12        /**< \brief PIOA_12���ź�  */
#define PIOA_13         13        /**< \brief PIOA_13���ź�  */

#define PIOA_18         18        /**< \brief PIOA_18���ź�  */
#define PIOA_19         19        /**< \brief PIOA_19���ź�  */
#define PIOA_20         20        /**< \brief PIOA_20���ź� */

#define PIOB_0          32       /**< \brief PIOB_0 ���ź� */
#define PIOB_1          33       /**< \brief PIOB_1 ���ź� */
#define PIOB_2          34       /**< \brief PIOB_2 ���ź� */
#define PIOB_3          35       /**< \brief PIOB_3 ���ź� */

#define PIOB_16         48       /**< \brief PIOB_16���ź� */
#define PIOB_17         49       /**< \brief PIOB_17���ź� */
#define PIOB_18         50       /**< \brief PIOB_18���ź� */
#define PIOB_19         51       /**< \brief PIOB_19���ź� */

#define PIOC_0          64       /**< \brief PIOC_0 ���ź� */
#define PIOC_1          65       /**< \brief PIOC_1 ���ź� */
#define PIOC_2          66       /**< \brief PIOC_2 ���ź� */
#define PIOC_3          67       /**< \brief PIOC_3 ���ź� */
#define PIOC_4          68       /**< \brief PIOC_4 ���ź� */
#define PIOC_5          69       /**< \brief PIOC_5 ���ź� */
#define PIOC_6          70       /**< \brief PIOC_6 ���ź� */
#define PIOC_7          71       /**< \brief PIOC_7 ���ź� */
#define PIOC_8          72       /**< \brief PIOC_8 ���ź� */
#define PIOC_9          73       /**< \brief PIOC_9 ���ź� */
#define PIOC_10         74       /**< \brief PIOC_10���ź� */
#define PIOC_11         75       /**< \brief PIOC_11���ź� */

#define PIOD_0          96       /**< \brief PIOD_0 ���ź� */
#define PIOD_1          97       /**< \brief PIOD_1 ���ź� */
#define PIOD_2          98       /**< \brief PIOD_2 ���ź� */
#define PIOD_3          99       /**< \brief PIOD_3 ���ź� */
#define PIOD_4          100       /**< \brief PIOD_4 ���ź� */
#define PIOD_5          101       /**< \brief PIOD_5 ���ź� */
#define PIOD_6          102       /**< \brief PIOD_6 ���ź� */
#define PIOD_7          103       /**< \brief PIOD_7 ���ź� */

#define PIOE_0          128       /**< \brief PIOE_0 ���ź� */
#define PIOE_1          129       /**< \brief PIOE_1 ���ź� */

#ifdef KL16
#define PIOE_16         144       /**< \brief PIOE_16���ź� */
#define PIOE_17         145       /**< \brief PIOE_17���ź� */
#define PIOE_18         146       /**< \brief PIOE_18���ź� */
#define PIOE_19         147       /**< \brief PIOE_19���ź� */
#endif /* KL16 */

#define PIOE_20         148       /**< \brief PIOE_20���ź� */
#define PIOE_21         149       /**< \brief PIOE_21���ź� */
#define PIOE_22         150       /**< \brief PIOE_22���ź� */
#define PIOE_23         151       /**< \brief PIOE_23���ź� */
#define PIOE_24         152       /**< \brief PIOE_24���ź� */
#define PIOE_25         153       /**< \brief PIOE_25���ź� */

#define PIOE_29         157       /**< \brief PIOE_29���ź� */
#define PIOE_30         158       /**< \brief PIOE_30���ź� */
#define PIOE_31         159       /**< \brief PIOE_31���ź� */

/** @} */

/**
 * \brief ������Ŀ, KL26������ĿΪ50����KL16��������ĿΪ54
 */
#ifdef KL26
#define PIN_NUM         50
#endif

#ifdef KL16
#define PIN_NUM         54
#endif

/**
 * \brief ֧����������ж�����96
 */
#define PIN_INT_MAX     96

/**
 * \name KL26 ��ת�ƹ��ܶ���(ÿ�����Ŷ��������¶���)
 * @{
 */

/******************************************************************************/

/**
 * \name PIOA_0���Ź���
 * @{
 */

#define PIOA_0_TSI0_CH1     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH1 */
#define PIOA_0_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_0_TPM0_CH5     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH5 */
#define PIOA_0_SWD_CLK      AM_KL26_GPIO_FUNC_CODE(0x7)   /**< \brief SWD_CLK  */

/** @} */

/**
 * \name PIOA_0����ģʽ
 * @{
 */

#define PIOA_0_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief (������/����)*/
#define PIOA_0_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_0_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_0 ������ת����
 * @{
 */

#define PIOA_0_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_0_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* �ùܽ�û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_1���Ź���
 * @{
 */

#define PIOA_1_TSI0_CH2     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH1 */
#define PIOA_1_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_1_UART0_RX     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief UART0_RX */
#define PIOA_1_TPM2_CH0     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH0 */

/** @} */

/**
 * \name PIOA_1����ģʽ
 * @{
 */

#define PIOA_1_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief (������/����)*/
#define PIOA_1_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_1_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_1 ������ת����
 * @{
 */

#define PIOA_1_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_1_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_2���Ź���
 * @{
 */

#define PIOA_2_TSI0_CH3     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH3 */
#define PIOA_2_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_2_UART0_TX     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief UART0_TX */
#define PIOA_2_TPM2_CH1     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH1 */

/** @} */

/**
 * \name PIOA_2����ģʽ
 * @{
 */

#define PIOA_2_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief(������/����)*/
#define PIOA_2_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_2_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_2 ������ת����
 * @{
 */

#define PIOA_2_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_2_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_3���Ź���
 * @{
 */

#define PIOA_3_TSI0_CH4     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH4 */
#define PIOA_3_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_3_I2C1_SCL     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C_SCL  */
#define PIOA_3_TPM0_CH0     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH0 */
#define PIOA_3_SWD_DIO      AM_KL26_GPIO_FUNC_CODE(0x7)   /**< \brief SWD_DIO  */

/** @} */

/**
 * \name PIOA_3����ģʽ
 * @{
 */

#define PIOA_3_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/����)*/
#define PIOA_3_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_3_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_3 ������ת����
 * @{
 */

#define PIOA_3_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_3_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_4���Ź���
 * @{
 */

#define PIOA_4_TSI0_CH5     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH5 */
#define PIOA_4_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_4_I2C1_SDA     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C_SDA  */
#define PIOA_4_TPM0_CH1     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH1 */
#define PIOA_4_NMI_B        AM_KL26_GPIO_FUNC_CODE(0x7)   /**< \brief NMI_B    */

/** @} */

/**
 * \name PIOA_4����ģʽ
 * @{
 */

#define PIOA_4_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_4_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_4_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_4 ������ת����
 * @{
 */

#define PIOA_4_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_4_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_4 ��������˲�(��Դ�˲���)
 * @{
 */

#define PIOA_4_FILT_DIS     AM_KL26_GPIO_PFE_CODE(0x0)    /**< \brief �˲����� */
#define PIOA_4_FILT_EN      AM_KL26_GPIO_PFE_CODE(0x1)    /**< \brief �˲�ʹ�� */

/** @} */

/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_5���Ź���
 * @{
 */

#define PIOA_5_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO      */
#define PIOA_5_USB_CLKIN    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief USB_CLKIN */
#define PIOA_5_TPM0_CH2     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH2  */
#define PIOA_5_I2S0_TX_BCLK AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TX_BCLK */

/** @} */

/**
 * \name PIOA_5����ģʽ
 * @{
 */

#define PIOA_5_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_5_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_5_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_5 ������ת����
 * @{
 */

#define PIOA_5_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_5_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_12���Ź���
 * @{
 */

#define PIOA_12_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO      */
#define PIOA_12_TPM1_CH0    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH0  */
#define PIOA_12_I2S0_TXD0   AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TXD0 */

/** @} */

/**
 * \name PIOA_12����ģʽ
 * @{
 */

#define PIOA_12_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_12_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_12_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_12 ������ת����
 * @{
 */

#define PIOA_12_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_12_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_13���Ź���
 * @{
 */

#define PIOA_13_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_13_TPM1_CH1    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH1 */
#define PIOA_13_I2S0_TX_FS  AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TX_FS */

/** @} */

/**
 * \name PIOA_13����ģʽ
 * @{
 */

#define PIOA_13_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_13_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_13_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_13 ������ת����
 * @{
 */

#define PIOA_13_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_13_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_18���Ź���
 * @{
 */

#define PIOA_18_EXTAL0      AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief EXTAL0   */
#define PIOA_18_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOA_18_UART1_RX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_RX */
#define PIOA_18_TPM_CLKIN0  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN0 */

/** @} */

/**
 * \name PIOA_18����ģʽ
 * @{
 */

#define PIOA_18_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_18_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_18_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_18 ������ת����
 * @{
 */

#define PIOA_18_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_18_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_19���Ź���
 * @{
 */

#define PIOA_19_XTAL0       AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief XTAL0 */
#define PIOA_19_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO  */
#define PIOA_19_UART1_TX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_TX */
#define PIOA_19_TPM_CLKIN1  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN1 */
#define PIOA_19_LPTMR0_ALT1 AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief LPTMR_ALT1 */
/** @} */

/**
 * \name PIOA_19����ģʽ
 * @{
 */

#define PIOA_19_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_19_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_19_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_19 ������ת����
 * @{
 */

#define PIOA_19_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_19_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOA_20���Ź���
 * @{
 */

#define PIOA_20_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOA_20_REST_B      AM_KL26_GPIO_FUNC_CODE(0x7)   /**< \brief REST_B */

/** @} */

/**
 * \name PIOA_20����ģʽ
 * @{
 */

#define PIOA_20_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOA_20_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOA_20_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOA_20 ������ת����
 * @{
 */

#define PIOA_20_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOA_20_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOB_0���Ź���
 * @{
 */

#define PIOB_0_ADC0_SE8     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE8 */
#define PIOB_0_TSI0_CH0     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH0 */
#define PIOB_0_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_0_LLWU_P5      AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P5 */
#define PIOB_0_I2C0_SCL     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SCL */
#define PIOB_0_TPM1_CH0     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH0 */

/** @} */

/**
 * \name PIOB_0����ģʽ
 * @{
 */

#define PIOB_0_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_0_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_0_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_0 ������ת����
 * @{
 */

#define PIOB_0_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_0_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_0 �ܽ���������
 * @{
 */

#define PIOB_0_DRIVE_NORMAL AM_KL26_GPIO_DSE_CODE(0x0)    /**< \brief ��ͨ������ */
#define PIOB_0_DRIVE_HIGH   AM_KL26_GPIO_DSE_CODE(0x1)    /**< \brief ǿ������*/

/* �ùܽ�û�����ùܽ��˲����� */

/******************************************************************************/

/**
 * \name PIOB_1���Ź���
 * @{
 */

#define PIOB_1_ADC0_SE9     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE9 */
#define PIOB_1_TSI0_CH6     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH6 */
#define PIOB_1_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_1_I2C0_SDA     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SDA */
#define PIOB_1_TPM1_CH1     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH1 */

/** @} */

/**
 * \name PIOB_1����ģʽ
 * @{
 */

#define PIOB_1_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_1_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_1_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_1 ������ת����
 * @{
 */

#define PIOB_1_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_1_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_1 �ܽ���������
 * @{
 */

#define PIOB_1_DRIVE_NORMAL AM_KL26_GPIO_DSE_CODE(0x0)    /**< \brief ��ͨ������ */
#define PIOB_1_DRIVE_HIGH   AM_KL26_GPIO_DSE_CODE(0x1)    /**< \brief ǿ������*/

/* �ùܽ�û�����ùܽ��˲����� */

/******************************************************************************/

/**
 * \name PIOB_2���Ź���
 * @{
 */

#define PIOB_2_ADC0_SE12    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE12 */
#define PIOB_2_TSI0_CH7     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH7 */
#define PIOB_2_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_2_I2C0_SCL     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SCL */
#define PIOB_2_TPM2_CH0     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH0 */

/** @} */

/**
 * \name PIOB_2����ģʽ
 * @{
 */

#define PIOB_2_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_2_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_2_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_2 ������ת����
 * @{
 */

#define PIOB_2_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_2_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOB_3���Ź���
 * @{
 */

#define PIOB_3_ADC0_SE13    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE13 */
#define PIOB_3_TSI0_CH8     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH8 */
#define PIOB_3_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_3_I2C0_SDA     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SDA */
#define PIOB_3_TPM2_CH1     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH1 */

/** @} */

/**
 * \name PIOB_3����ģʽ
 * @{
 */

#define PIOB_3_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_3_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_3_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_3 ������ת����
 * @{
 */

#define PIOB_3_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_3_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOB_16���Ź���
 * @{
 */

#define PIOB_16_TSI0_CH9    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH9 */
#define PIOB_16_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_16_SPI1_MOSI   AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MOSI */
#define PIOB_16_UART0_RX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART0_RX */
#define PIOB_16_TPM_CLKIN0  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN0 */
#define PIOB_16_SPI1_MISO   AM_KL26_GPIO_FUNC_CODE(0x5)    /**< \brief SPI1_MISO */

/** @} */

/**
 * \name PIOB_16����ģʽ
 * @{
 */

#define PIOB_16_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_16_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_16_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_16 ������ת����
 * @{
 */

#define PIOB_16_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_16_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOB_17���Ź���
 * @{
 */

#define PIOB_17_TSI0_CH10   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH10 */
#define PIOB_17_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_17_SPI1_MISO   AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MISO */
#define PIOB_17_UART0_TX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART0_TX */
#define PIOB_17_TPM_CLKIN1  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN1 */
#define PIOB_17_SPI1_MOSI   AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI1_MOSI */

/** @} */

/**
 * \name PIOB_17����ģʽ
 * @{
 */

#define PIOB_17_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_17_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_17_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_17 ������ת����
 * @{
 */

#define PIOB_17_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_17_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOB_18���Ź���
 * @{
 */

#define PIOB_18_TSI0_CH11   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH11 */
#define PIOB_18_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_18_TPM2_CH0    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH0 */
#define PIOB_18_I2S_TX_BCLK AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S_TX_BCLK */

/** @} */

/**
 * \name PIOB_18����ģʽ
 * @{
 */

#define PIOB_18_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_18_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_18_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_18 ������ת����
 * @{
 */

#define PIOB_18_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_18_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOB_19���Ź���
 * @{
 */

#define PIOB_19_TSI0_CH12   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH12 */
#define PIOB_19_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOB_19_TPM2_CH1    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH1 */
#define PIOB_19_I2S_TX_FS   AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S_TX_FS */

/** @} */

/**
 * \name PIOB_19����ģʽ
 * @{
 */

#define PIOB_19_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOB_19_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOB_19_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOB_19 ������ת����
 * @{
 */

#define PIOB_19_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOB_19_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_0���Ź���
 * @{
 */

#define PIOC_0_TSI0_CH13    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH13 */
#define PIOC_0_ADC0_SE14    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE14 */
#define PIOC_0_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_0_EXTRG_IN     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief EXTRG_IN */
#define PIOC_0_USB_SOF_OUT  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief AUDIOUSB_SOF */
#define PIOC_0_CMP0_OUT     AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief CMP0_OUT */
#define PIOC_0_I2S0_TXD0    AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TXD0 */

/** @} */

/**
 * \name PIOC_0����ģʽ
 * @{
 */

#define PIOC_0_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_0_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_0_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_0 ������ת����
 * @{
 */

#define PIOC_0_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_0_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_1���Ź���
 * @{
 */

#define PIOC_1_TSI0_CH14    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH14 */
#define PIOC_1_ADC0_SE15    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE15 */
#define PIOC_1_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_1_LLWU_P6      AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P6 */
#define PIOC_1_RTC_CLKIN    AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief RTC_CLKIN */
#define PIOC_1_I2C1_SCL     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief EXTRG_IN */
#define PIOC_1_TPM0_CH0     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief EXTRG_IN */
#define PIOC_1_I2S0_TXD0    AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TXD0 */

/** @} */

/**
 * \name PIOC_1����ģʽ
 * @{
 */

#define PIOC_1_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_1_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_1_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_1 ������ת����
 * @{
 */

#define PIOC_1_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_1_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_2���Ź���
 * @{
 */

#define PIOC_2_TSI0_CH15    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief TSI0_CH15 */
#define PIOC_2_ADC0_SE11    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE11 */
#define PIOC_2_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_2_I2C1_SDA     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C1_SDA */
#define PIOC_2_TPM0_CH1     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH1 */
#define PIOC_2_I2S0_TX_FS   AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TX_FS */

/** @} */

/**
 * \name PIOC_2����ģʽ
 * @{
 */

#define PIOC_2_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_2_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_2_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_2 ������ת����
 * @{
 */

#define PIOC_2_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_2_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_3���Ź���
 * @{
 */

#define PIOC_3_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_3_LLWU_P7      AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P7 */
#define PIOC_3_UART1_RX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_RX */
#define PIOC_3_TPM0_CH2     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH2 */
#define PIOC_3_CLKOUT       AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief CLKOUT */
#define PIOC_3_I2S0_TX_BCLK AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_TX_BCLK */

/** @} */

/**
 * \name PIOC_3����ģʽ
 * @{
 */

#define PIOC_3_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_3_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_3_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_3 ������ת����
 * @{
 */

#define PIOC_3_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_3_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_4���Ź���
 * @{
 */

#define PIOC_4_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_4_LLWU_P8      AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P8 */
#define PIOC_4_SPI0_PCS0    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_PCS0 */
#define PIOC_4_UART1_TX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_TX */
#define PIOC_4_TPM0_CH3     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH3 */
#define PIOC_4_I2S0_MCLK    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief I2S0_MCLK */

/** @} */

/**
 * \name PIOC_4����ģʽ
 * @{
 */

#define PIOC_4_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_4_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_4_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_4 ������ת����
 * @{
 */

#define PIOC_4_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_4_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_5���Ź���
 * @{
 */

#define PIOC_5_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_5_LLWU_P9      AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P9 */
#define PIOC_5_SPI0_SCK     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_SCK */
#define PIOC_5_LPTMR0_ALT2  AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief LPTMR0_ALT2 */
#define PIOC_5_I2S0_RXD0    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RXD0 */
#define PIOC_5_CMP0_OUT     AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief CMP0_OUT */

/** @} */

/**
 * \name PIOC_5����ģʽ
 * @{
 */

#define PIOC_5_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_5_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_5_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_5 ������ת����
 * @{
 */

#define PIOC_5_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_5_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_6���Ź���
 * @{
 */

#define PIOC_6_CMP0_IN0     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief CMP0_IN0 */
#define PIOC_6_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_6_LLWU_P10     AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P10 */
#define PIOC_6_SPI0_MOSI    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MOSI */
#define PIOC_6_EXTRG_IN     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief EXTRG_IN */
#define PIOC_6_I2S0_RX_BCLK AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RX_BCLK */
#define PIOC_6_SPI0_MISO    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MISO */
#define PIOC_6_I2S0_MCLK    AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2S0_MCLK */

/** @} */

/**
 * \name PIOC_6����ģʽ
 * @{
 */

#define PIOC_6_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_6_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_6_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_6 ������ת����
 * @{
 */

#define PIOC_6_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_6_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_7���Ź���
 * @{
 */

#define PIOC_7_CMP0_IN1     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief CMP0_IN1  */
#define PIOC_7_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO      */
#define PIOC_7_SPI0_MISO    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MISO */
#define PIOC_7_USB_SOF_OUT  AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief AUDIOUSB_SOF */
#define PIOC_7_I2S0_RX_FS   AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RX_FS   */
#define PIOC_7_SPI0_MOSI    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MOSI    */

/** @} */

/**
 * \name PIOC_7����ģʽ
 * @{
 */

#define PIOC_7_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_7_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_7_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_7 ������ת����
 * @{
 */

#define PIOC_7_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_7_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_8���Ź���
 * @{
 */

#define PIOC_8_CMP0_IN2     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief CMP0_IN2 */
#define PIOC_8_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_8_I2C0_SCL     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SCL */
#define PIOC_8_TPM0_CH4     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH4 */
#define PIOC_8_I2S0_MCLK    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_MCLK */

/** @} */

/**
 * \name PIOC_8����ģʽ
 * @{
 */

#define PIOC_8_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_8_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_8_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_8 ������ת����
 * @{
 */

#define PIOC_8_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_8_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_9���Ź���
 * @{
 */

#define PIOC_9_CMP0_IN3     AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief CMP0_IN3 */
#define PIOC_9_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_9_I2C0_SDA     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C0_SDA */
#define PIOC_9_TPM0_CH5     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH5 */
#define PIOC_9_I2S0_RX_BCLK AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RX_BCLK */

/** @} */

/**
 * \name PIOC_9����ģʽ
 * @{
 */

#define PIOC_9_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_9_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_9_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_9 ������ת����
 * @{
 */

#define PIOC_9_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_9_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_10���Ź���
 * @{
 */

#define PIOC_10_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_10_I2C1_SCL    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C1_SCL */
#define PIOC_10_I2S0_RX_FS  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RX_FS */

/** @} */

/**
 * \name PIOC_10����ģʽ
 * @{
 */

#define PIOC_10_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_10_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_10_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_10 ������ת����
 * @{
 */

#define PIOC_10_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_10_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOC_11���Ź���
 * @{
 */

#define PIOC_11_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOC_11_I2C1_SDA    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief I2C1_SDA */
#define PIOC_11_I2S0_RXD0   AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2S0_RXD0 */

/** @} */

/**
 * \name PIOC_11����ģʽ
 * @{
 */

#define PIOC_11_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOC_11_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOC_11_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOC_11 ������ת����
 * @{
 */

#define PIOC_11_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOC_11_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_0���Ź���
 * @{
 */

#define PIOD_0_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_0_SPI0_PCS0    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_PCS0 */
#define PIOD_0_TPM0_CH0     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH0 */

/** @} */

/**
 * \name PIOD_0����ģʽ
 * @{
 */

#define PIOD_0_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_0_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_0_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_0 ������ת����
 * @{
 */

#define PIOD_0_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_0_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_1���Ź���
 * @{
 */

#define PIOD_1_ADC0_SE5B    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE5B */
#define PIOD_1_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_1_SPI0_SCK     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_SCK */
#define PIOD_1_TPM0_CH1     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH1 */

/** @} */

/**
 * \name PIOD_1����ģʽ
 * @{
 */

#define PIOD_1_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_1_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_1_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_1 ������ת����
 * @{
 */

#define PIOD_1_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_1_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_2���Ź���
 * @{
 */

#define PIOD_2_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_2_SPI0_MOSI    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MOSI */
#define PIOD_2_UART2_RX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_RX */
#define PIOD_2_TPM0_CH2     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH2 */
#define PIOD_2_SPI0_MISO    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MISO */

/** @} */

/**
 * \name PIOD_2����ģʽ
 * @{
 */

#define PIOD_2_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_2_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_2_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_2 ������ת����
 * @{
 */

#define PIOD_2_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_2_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_3���Ź���
 * @{
 */

#define PIOD_3_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_3_SPI0_MISO    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MISO */
#define PIOD_3_UART2_TX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_TX */
#define PIOD_3_TPM0_CH3     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH3 */
#define PIOD_3_SPI0_MOSI    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MOSI */

/** @} */

/**
 * \name PIOD_3����ģʽ
 * @{
 */

#define PIOD_3_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_3_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_3_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_3 ������ת����
 * @{
 */

#define PIOD_3_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_3_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_4���Ź���
 * @{
 */

#define PIOD_4_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_4_LLWU_P14     AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P14 */
#define PIOD_4_SPI1_PCS0    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_PCS0 */
#define PIOD_4_UART2_RX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_RX */
#define PIOD_4_TPM0_CH4     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH4 */

/** @} */

/**
 * \name PIOD_4����ģʽ
 * @{
 */

#define PIOD_4_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_4_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_4_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_4 ������ת����
 * @{
 */

#define PIOD_4_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_4_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_5���Ź���
 * @{
 */

#define PIOD_5_ADC0_SE6B    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE6B */
#define PIOD_5_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_5_SPI1_SCK     AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_SCK */
#define PIOD_5_UART2_TX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_TX */
#define PIOD_5_TPM0_CH5     AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM0_CH5 */

/** @} */

/**
 * \name PIOD_5����ģʽ
 * @{
 */

#define PIOD_5_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_5_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_5_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_5 ������ת����
 * @{
 */

#define PIOD_5_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_5_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
/******************************************************************************/

/**
 * \name PIOD_6���Ź���
 * @{
 */

#define PIOD_6_ADC0_SE7B    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE7B */
#define PIOD_6_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_6_LLWU_P15     AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief LLWU_P15 */
#define PIOD_6_SPI1_MOSI    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MOSI */
#define PIOD_6_UART0_RX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART0_RX */
#define PIOD_6_SPI1_MISO    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI1_MISO */

/** @} */

/**
 * \name PIOD_6����ģʽ
 * @{
 */

#define PIOD_6_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_6_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_6_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_6 ������ת����
 * @{
 */

#define PIOD_6_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_6_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/**
 * \name PIOD_6 �ܽ���������
 * @{
 */

#define PIOD_6_DRIVE_NORMAL  AM_KL26_GPIO_DSE_CODE(0x0)    /**< \brief ��ͨ������ */
#define PIOD_6_DRIVE_HIGH    AM_KL26_GPIO_DSE_CODE(0x1)    /**< \brief ǿ������*/

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */

/******************************************************************************/

/**
 * \name PIOD_7���Ź���
 * @{
 */

#define PIOD_7_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOD_7_SPI1_MISO    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MISO */
#define PIOD_7_UART0_TX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART0_TX */
#define PIOD_7_SPI1_MOSI    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI1_MOSI */

/** @} */

/**
 * \name PIOD_7����ģʽ
 * @{
 */

#define PIOD_7_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOD_7_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOD_7_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOD_7 ������ת����
 * @{
 */

#define PIOD_7_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOD_7_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/**
 * \name PIOD_7 �ܽ���������
 * @{
 */

#define PIOD_7_DRIVE_NORMAL AM_KL26_GPIO_DSE_CODE(0x0)    /**< \brief ��ͨ������ */
#define PIOD_7_DRIVE_HIGH   AM_KL26_GPIO_DSE_CODE(0x1)    /**< \brief ǿ������*/

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */

/******************************************************************************/

/**
 * \name PIOE_0���Ź���
 * @{
 */

#define PIOE_0_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_0_SPI1_MISO    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MISO */
#define PIOE_0_UART1_TX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_TX */
#define PIOE_0_RTC_CLKOUT   AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief RTC_CLKOUT */
#define PIOE_0_CMP0_OUT     AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief CMP0_OUT */
#define PIOE_0_I2C1_SDA     AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2C1_SDA */

/** @} */

/**
 * \name PIOE_0����ģʽ
 * @{
 */

#define PIOE_0_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_0_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_0_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_0 ������ת����
 * @{
 */

#define PIOE_0_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_0_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_1���Ź���
 * @{
 */

#define PIOE_1_GPIO         AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_1_SPI1_MOSI    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI1_MOSI */
#define PIOE_1_UART1_RX     AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART1_RX */
#define PIOE_1_SPI1_MISO    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI1_MISO */
#define PIOE_1_I2C1_SCL     AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief I2C1_SCL */

/** @} */

/**
 * \name PIOE_1����ģʽ
 * @{
 */

#define PIOE_1_INACTIVE     AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_1_PULLDOWN     AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_1_PULLUP       AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_1 ������ת����
 * @{
 */

#define PIOE_1_SLEW_FAST    AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_1_SLEW_SLOW    AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/
#ifdef KL16
/**
 * \name PIOE_16���Ź���
 * @{
 */
#define PIOE_16_ADC0_DP1    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DP1 */
#define PIOE_16_ADC0_SE1    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE1 */
#define PIOE_16_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_16_SPI0_PCS0   AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_PCS0 */
#define PIOE_16_UART2_TX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_TX */
#define PIOE_16_TPM_CLKIN0  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN0 */

/** @} */

/**
 * \name PIOE_16����ģʽ
 * @{
 */

#define PIOE_16_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_16_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_16_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_16 ������ת����
 * @{
 */

#define PIOE_16_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_16_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_17���Ź���
 * @{
 */
#define PIOE_17_ADC0_DM1    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DM1 */
#define PIOE_17_ADC0_SE5A   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE5A */
#define PIOE_17_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_17_SPI0_SCK    AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_SCK */
#define PIOE_17_UART2_RX    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief UART2_RX */
#define PIOE_17_TPM_CLKIN1  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN1 */
#define PIOE_17_LPTMR0_ALT3 AM_KL26_GPIO_FUNC_CODE(0x6)   /**< \brief LPTMR0_ALT3 */

/** @} */

/**
 * \name PIOE_17����ģʽ
 * @{
 */

#define PIOE_17_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_17_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_17_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_17 ������ת����
 * @{
 */

#define PIOE_17_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_17_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_18���Ź���
 * @{
 */
#define PIOE_18_ADC0_DP2    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DP2 */
#define PIOE_18_ADC0_SE2    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE2 */
#define PIOE_18_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_18_SPI0_MOSI   AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MOSI */
#define PIOE_18_I2C0_SDA    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2C0_SDA */
#define PIOE_18_SPI0_MISO   AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MISO */

/** @} */

/**
 * \name PIOE_18����ģʽ
 * @{
 */

#define PIOE_18_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_18_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_18_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_18 ������ת����
 * @{
 */

#define PIOE_18_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_18_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_19���Ź���
 * @{
 */
#define PIOE_19_ADC0_DM2    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DM2 */
#define PIOE_19_ADC0_SE6A   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE6A */
#define PIOE_19_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO */
#define PIOE_19_SPI0_MISO   AM_KL26_GPIO_FUNC_CODE(0x2)   /**< \brief SPI0_MISO */
#define PIOE_19_I2C0_SCL    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief I2C0_SCL */
#define PIOE_19_SPI0_MOSI   AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief SPI0_MOSI */

/** @} */

/**
 * \name PIOE_19����ģʽ
 * @{
 */

#define PIOE_19_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_19_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_19_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_19 ������ת����
 * @{
 */

#define PIOE_19_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_19_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */
/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */
#endif

/******************************************************************************/

/**
 * \name PIOE_20���Ź���
 * @{
 */
#define PIOE_20_ADC0_DP0    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DP0 */
#define PIOE_20_ADC0_SE0    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE0 */
#define PIOE_20_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOE_20_TPM1_CH0    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH0 */
#define PIOE_20_UART0_TX    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief UART0_TX */

/** @} */

/**
 * \name PIOE_20����ģʽ
 * @{
 */

#define PIOE_20_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_20_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_20_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_20 ������ת����
 * @{
 */

#define PIOE_20_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_20_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_21���Ź���
 * @{
 */
#define PIOE_21_ADC0_DM0    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DM0  */
#define PIOE_21_ADC0_SE4A   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE4A */
#define PIOE_21_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO      */
#define PIOE_21_TPM1_CH1    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM1_CH1  */
#define PIOE_21_UART0_RX    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief UART0_RX  */

/** @} */

/**
 * \name PIOE_21����ģʽ
 * @{
 */

#define PIOE_21_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_21_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_21_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_21 ������ת����
 * @{
 */

#define PIOE_21_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_21_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_22���Ź���
 * @{
 */
#define PIOE_22_ADC0_DP3    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DP3 */
#define PIOE_22_ADC0_SE3    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE3 */
#define PIOE_22_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOE_22_TPM2_CH0    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH0 */
#define PIOE_22_UART2_TX    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief UART2_TX */

/** @} */

/**
 * \name PIOE_22����ģʽ
 * @{
 */

#define PIOE_22_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ��������/���� */
#define PIOE_22_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_22_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_22 ������ת����
 * @{
 */

#define PIOE_22_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_22_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_23���Ź���
 * @{
 */
#define PIOE_23_ADC0_DM3    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_DM3  */
#define PIOE_23_ADC0_SE7A   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE7A */
#define PIOE_23_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO      */
#define PIOE_23_TPM2_CH1    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM2_CH1  */
#define PIOE_23_UART2_RX    AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief UART2_RX  */

/** @} */

/**
 * \name PIOE_23����ģʽ
 * @{
 */

#define PIOE_23_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_23_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_23_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_23 ������ת����
 * @{
 */

#define PIOE_23_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_23_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_24���Ź���
 * @{
 */

#define PIOE_24_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOE_24_TPM0_CH0    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH0 */
#define PIOE_24_I2C0_SCL    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief I2C0_SCL */

/** @} */

/**
 * \name PIOE_24����ģʽ
 * @{
 */

#define PIOE_24_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_24_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_24_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_24 ������ת����
 * @{
 */

#define PIOE_24_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_24_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_25���Ź���
 * @{
 */

#define PIOE_25_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOE_25_TPM0_CH1    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH1 */
#define PIOE_25_I2C0_SDA    AM_KL26_GPIO_FUNC_CODE(0x5)   /**< \brief I2C0_SDA */

/** @} */

/**
 * \name PIOE_25����ģʽ
 * @{
 */

#define PIOE_25_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_25_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_25_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_25 ������ת����
 * @{
 */

#define PIOE_25_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_25_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_29���Ź���
 * @{
 */
#define PIOE_29_CMP0_IN5    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief CMP0_IN5   */
#define PIOE_29_ADC0_SE4B   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE4B  */
#define PIOE_29_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO       */
#define PIOE_29_TPM0_CH2    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH2   */
#define PIOE_29_TPM_CLKIN0  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN0 */

/** @} */

/**
 * \name PIOE_29����ģʽ
 * @{
 */

#define PIOE_29_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_29_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_29_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_29 ������ת����
 * @{
 */

#define PIOE_29_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_29_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_30���Ź���
 * @{
 */
#define PIOE_30_DAC0_OUT    AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief DAC0_OUT   */
#define PIOE_30_ADC0_SE23   AM_KL26_GPIO_FUNC_CODE(0x0)   /**< \brief ADC0_SE23  */
#define PIOE_30_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO       */
#define PIOE_30_TPM0_CH3    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH3   */
#define PIOE_30_TPM_CLKIN1  AM_KL26_GPIO_FUNC_CODE(0x4)   /**< \brief TPM_CLKIN1 */

/** @} */

/**
 * \name PIOE_30����ģʽ
 * @{
 */

#define PIOE_30_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_30_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_30_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_30 ������ת����
 * @{
 */

#define PIOE_30_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_30_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * \name PIOE_31���Ź���
 * @{
 */

#define PIOE_31_GPIO        AM_KL26_GPIO_FUNC_CODE(0x1)   /**< \brief GPIO     */
#define PIOE_31_TPM0_CH4    AM_KL26_GPIO_FUNC_CODE(0x3)   /**< \brief TPM0_CH4 */

/** @} */

/**
 * \name PIOE_31����ģʽ
 * @{
 */

#define PIOE_31_INACTIVE    AM_KL26_GPIO_PE_CODE(0x0)     /**< \brief ������/���� */
#define PIOE_31_PULLDOWN    AM_KL26_GPIO_PULL_CODE(0x0)   /**< \brief ����ģʽ */
#define PIOE_31_PULLUP      AM_KL26_GPIO_PULL_CODE(0x1)   /**< \brief ����ģʽ */

/** @} */

/**
 * \name PIOE_31 ������ת����
 * @{
 */

#define PIOE_31_SLEW_FAST   AM_KL26_GPIO_SRE_CODE(0x0)    /**< \brief ����ģʽ */
#define PIOE_31_SLEW_SLOW   AM_KL26_GPIO_SRE_CODE(0x1)    /**< \brief ����ģʽ */

/** @} */

/* �ùܽ�û�����ùܽ��˲����� */
/* û�����ùܽ����������� */

/******************************************************************************/

/**
 * @} kl26_if_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __KL26_PIN_H */

/* end of file */
