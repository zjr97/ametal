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
 * \brief ���ڣ�UART�������ӿ�
 *
 * 1. ȫ˫����������׼������(NRZ)��ʽ
 * 2. ���ж���ʹ�ܵ�˫����ɷ���ķ��ͽ������ͽ�����
 * 3. �����ʿɱ�̣� 13 λģ����Ƶ����
 * 4. �ж���������ѯ����
 * 1. �������ݼĴ����ղ��ҷ������
 * 2. �������ݼĴ�����
 * 3. ���չ��ء���ż�������֡�������������
 * 4. ���н��������
 * 5. �����������л��
 * 6. ֧�� LIN ���жϼ��
 * 5. Ӳ����żУ�����ɺͼ��
 * 6. �ɱ�̵� 8 λ��ר 9 λ�ַ�����
 * 7. �ɱ�̵� 1 λ�� 2 λֹͣλ
 * 8. �����߻��ַ��־���ѽ�������
 * 9. ��ѡ�� 13 λ��ֹ������/11 λ��ֹ�����
 * 10. ��ѡ�ķ������������
 * 11. 5 ͨ�� DMA �ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-14  nwt, make some changes about Macro definition.
 * - 1.00 15-07-03  xiongyanming, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_UART_H
#define __AMHW_FSL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
//#include "amhw_kl26_periph_map.h"
//#include "kl26_inum.h"
/**
 * \addtogroup amhw_fsl_if_uart
 * \copydoc amhw_fsl_uart.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * \brief uart �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_uart {
     __IO uint8_t bdh;                    /**< \brief UART �����ʸ�λ�Ĵ���  */
     __IO uint8_t bdl;                    /**< \brief UART �����ʵ�λ�Ĵ���  */
     __IO uint8_t c1;                     /**< \brief UART ���ƼĴ���        */
     __IO uint8_t c2;                     /**< \brief UART ���ƼĴ���        */
     __IO uint8_t stat1;                  /**< \brief UART ״̬�Ĵ���1       */
     __IO uint8_t stat2;                  /**< \brief UART ״̬�Ĵ���2       */
     __IO uint8_t c3;                     /**< \brief UART ���ƼĴ���        */
     __IO uint8_t data;                   /**< \brief UART ���ݼĴ���        */
     union {                                                                 
          struct {                                                           
              __IO uint8_t uart0_ma1;     /**< \brief UART0 ƥ���ַ�Ĵ���   */
              __IO uint8_t uart0_ma2;     /**< \brief UART0 ƥ���ַ�Ĵ���   */
              __IO uint8_t uart0_c4;      /**< \brief UART0 ���ƼĴ���       */
              __IO uint8_t uart0_c5;      /**< \brief UART0 ���ƼĴ���       */
          };                                                                 
          __IO uint8_t uart1_2_c4;        /**< \brief UART1/2 ���ƼĴ���     */
      };
} amhw_fsl_uart_t;


/**
 * \name �������ݼĴ�����ַ���壬(������DMA�õ�)
 * @{
 */
/** \brief UART0 �������ݼĴ�����ַ  */
#define AMHW_FSL_UART0_DAT_ADDR  (&(AMHW_FSL_UART0->data))
/** \brief UART1 �������ݼĴ�����ַ  */
#define AMHW_FSL_UART1_DAT_ADDR  (&(AMHW_FSL_UART1->data))
/** \brief UART2 �������ݼĴ�����ַ  */
#define AMHW_FSL_UART2_DAT_ADDR  (&(AMHW_FSL_UART2->data))

/** @} */

/**
 * \name uart �����ʷ�Ƶ��������λ�궨��
 * @{
 */
/** \brief �����ʷ�Ƶ���Ӹ�λ����                                            */
#define AMHW_FSL_UART_BDH_SBR_MASK     0x1Fu
#define AMHW_FSL_UART_BDH_SBR(x)       (((uint8_t)(((uint8_t)(x))<<0))&0x1Fu)
/** \brief �����ʷ�Ƶ���ӵ�λ����                                            */
#define AMHW_FSL_UART_BDL_SBR_MASK     0xFFu
#define AMHW_FSL_UART_BDL_SBR(x)       (((uint8_t)(((uint8_t)(x))<<0))&0xFFu)

/** @} */

/**
 * \name uart ������/������ʹ��λ�궨��
 * @{
 */
#define AMHW_FSL_UART_C2_TE_EN         ((uint8_t)(1<<3)) /**< \brief ������ʹ��  */
#define AMHW_FSL_UART_C2_RE_EN         ((uint8_t)(1<<2)) /**< \brief ������ʹ��  */

/** @} */

/**
 * \name uart ����OSRֵ�궨��
 * @{
 */
#define AMHW_FSL_UART_C4_OSR_MASK     ((uint8_t)0x1Fu)
#define AMHW_FSL_UART_C4_OSR(x)       (((uint8_t)(((uint8_t)(x))<<0))&0x1Fu)

/** @} */

/**
 * \name uart ״̬�Ĵ���1����λ�궨��
 * @{
 */
/** \brief �������ݿ�ʱ���������Լ�������                                    */
#define AMHW_FSL_UART_S1_TDRE_MASK     0x80u

/** \brief �ӷ�����ɱ�־����λ                                                      */
#define AMHW_FSL_UART_S1_TC_MASK       0x40u

/** \brief ��������Ϊ��ʱ���������Զ�ȡ����                                  */
#define AMHW_FSL_UART_S1_RDRF_MASK     0x20u

/** \brief У�����λ������ */
#define AMHW_FSL_UART_S1_PF_MASK       0x01u

/** @} */

/**
 * \brief ʹ��˫���ز���λ�궨��
 */
#define AMHW_FSL_UART0_C5_BOTHEDGE_EN  ((uint8_t)(1<<1))

/**
 * \name uart C1 ���ƼĴ���1
 * @{
 */

/** \brief �ػ�ģʽ����ģʽ */
#define AMHW_FSL_UART_C1_LOOPS         ((uint8_t)(1 << 7))

/** \brief ����Դѡ��[LOOPS = 1]��λ��Ϊ0ʱLOOPģʽ��Ϊ1ʱSingle-Wireģʽ */
#define AMHW_FSL_UART_C1_RSRC          ((uint8_t)(1 << 5))

#define AMHW_FSL_UART_C1_M_8BIT        ((uint8_t)(0 << 4)) /**< \brief 8λ���ݳ���*/
#define AMHW_FSL_UART_C1_M_9BIT        ((uint8_t)(1 << 4)) /**< \brief 9λ���ݳ���*/

#define AMHW_FSL_UART_C1_PARITY_NO     ((uint8_t)(0 << 1)) /**< \brief ��ʹ��У�� */
#define AMHW_FSL_UART_C1_PARITY_EVEN   ((uint8_t)(2 << 0)) /**< \brief żУ��     */
#define AMHW_FSL_UART_C1_PARITY_ODD    ((uint8_t)(3 << 0)) /**< \brief ��У��     */

/** @} */

/**
 * \name uart C1 ֹͣλλ�궨��
 * @{
 */
#define AMHW_FSL_UART_BDH_SBNS_STOP_1   (0UL << 5)         /**< \brief 1λֹͣλ  */
#define AMHW_FSL_UART_BDH_SBNS_STOP_2   (1UL << 5)         /**< \brief 2λֹͣλ  */

/** @} */

/**
 * \name uart C3 ���ƼĴ���3
 * @{
 */

/** \brief ���õ���ģʽ��IO���ŵ�����������򣬸�λ��0��ʾ���룬��λ��1��ʾ��� */
#define AMHW_FSL_UART_C3_TXDIR          (1U << 5)

/** \brief ����ģʽ��Tx����Ϊ���뷽���� #AMHW_FSL_UART_C3_TXDIR λ����� */
#define AMHW_FSL_UART_SINGLE_WIRE_INPUT  0

/** \brief ����ģʽ��Tx����Ϊ��������� #AMHW_FSL_UART_C3_TXDIR λ����� */
#define AMHW_FSL_UART_SINGLE_WIRE_OUTPUT 1

/** @} */

/**
 * \name �����ж�Դ����,��ͨ��amhw_fsl_uart_int_enableʹ�ܻ�amhw_fsl_uart_int_disable����
 * @{
 */
#define AMHW_FSL_UART_INT_BDH_LBKDIE  (1UL << 9) /**< \brief LIN�ϵ����ж�      */
#define AMHW_FSL_UART_INT_BDH_RXEDGIE (1UL << 8) /**< \brief RxD������Ч�����ж�  */
#define AMHW_FSL_UART_INT_C2_TIE      (1UL << 7) /**< \brief TDRE����׼�������ж� */
#define AMHW_FSL_UART_INT_C2_TCIE     (1UL << 6) /**< \brief TC��������ж�       */
#define AMHW_FSL_UART_INT_C2_IRIE     (1UL << 5) /**< \brief RDRF����׼�������ж� */
#define AMHW_FSL_UART_INT_C2_ILIE     (1UL << 4) /**< \brief IDLE������·�ж�ʹ�� */
#define AMHW_FSL_UART_INT_C3_OVR      (1UL << 3) /**< \brief ����ж�             */
#define AMHW_FSL_UART_INT_C3_NEIE     (1UL << 2) /**< \brief ���������ж�         */
#define AMHW_FSL_UART_INT_C3_IFRMERR  (1UL << 1) /**< \brief ֡�����ж�           */
#define AMHW_FSL_UART_INT_C3_PARERR   (1UL << 0) /**< \brief ��żУ������ж�     */
#define AMHW_FSL_UART_INT_ALL         (0x3FF)    /**< \brief �����ж�             */

/** @} */

/**
 * \name UART�����ж�״̬��־������ͨ������amhw_fsl_uart_intstat_get()��ȡ�ж�״̬
 * @{
 */
#define AMHW_FSL_UART_INTSTAT_S2_LBKDIF  (1UL << 15) /**< \brief LIN�ϵ����־   */
#define AMHW_FSL_UART_INTSTAT_S2_RXEDGIF (1UL << 14) /**< \brief RxD������Ч�ر�־ */
#define AMHW_FSL_UART_INTSTAT_S1_TDRE    (1UL << 7)  /**< \brief TDRE���;�����־  */
#define AMHW_FSL_UART_INTSTAT_S1_TC      (1UL << 6)  /**< \brief TC������ɱ�־    */
#define AMHW_FSL_UART_INTSTAT_S1_RDRF    (1UL << 5)  /**< \brief RDRF���վ�����־  */
#define AMHW_FSL_UART_INTSTAT_S1_IDLE    (1UL << 4)  /**< \brief IDLE���б�־      */
#define AMHW_FSL_UART_INTSTAT_S1_OVR     (1UL << 3)  /**< \brief �����־          */
#define AMHW_FSL_UART_INTSTAT_S1_NF      (1UL << 2)  /**< \brief ���������־      */
#define AMHW_FSL_UART_INTSTAT_S1_FE      (1UL << 1)  /**< \brief ֡�����־        */
#define AMHW_FSL_UART_INTSTAT_S1_PF      (1UL << 0)  /**< \brief ��żУ������־  */

/** @} interrupt state */


/**
 * \name uart ������/������DMAʹ��λ�궨��
 * @{
 */

#define AMHW_FSL_UART_DMA_RX_EN         ((uint8_t)(1<<5)) /**< \brief ������DMAʹ��  */
#define AMHW_FSL_UART_DMA_TX_EN         ((uint8_t)(1<<7)) /**< \brief ������DMAʹ��  */

/** @} */


/**
 * \name �������⹤��ģʽ
 * \anchor amhw_fsl_uart_spec_mode
 * @{
 */

/** \brief �ػ�ģʽ */
#define AMHW_FSL_UART_SPEC_MODE_LOOP            0

/** \brief ����ģʽ */
#define AMHW_FSL_UART_SPEC_MODE_SINGLE_WIRE     1

/** @} */


/**
 * \brief ���ڲ����ʷ�Ƶ���Ӹ�λ���ú���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] sbr_val   : �����ʷ�Ƶ���Ӹ�λֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_bdh_sbr_set (amhw_fsl_uart_t *p_hw_uart, uint8_t sbr_val)
{
    p_hw_uart->bdh &= ~AMHW_FSL_UART_BDH_SBR_MASK;
    p_hw_uart->bdh |= AMHW_FSL_UART_BDH_SBR(sbr_val);
}
/**
 * \brief ���ڲ����ʷ�Ƶ���ӵ�λ���ú���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] sbr_val   : �����ʷ�Ƶ���ӵ�λֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_bdl_sbr_set (amhw_fsl_uart_t *p_hw_uart, uint8_t sbr_val)
{
    p_hw_uart->bdl &= ~AMHW_FSL_UART_BDL_SBR_MASK;
    p_hw_uart->bdl |= AMHW_FSL_UART_BDL_SBR(sbr_val);

}

/**
 * \brief ������ʹ�ܺ���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_c2_tx_enable (amhw_fsl_uart_t *p_hw_uart)
{
    p_hw_uart->c2 |= AMHW_FSL_UART_C2_TE_EN;
}
/**
 * \brief ���������ܺ���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_c2_tx_disable (amhw_fsl_uart_t *p_hw_uart)
{
    p_hw_uart->c2 &= ~AMHW_FSL_UART_C2_TE_EN;
}

/**
 * \brief ������ʹ�ܺ���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_c2_rx_enable (amhw_fsl_uart_t *p_hw_uart)
{
    p_hw_uart->c2 |= AMHW_FSL_UART_C2_RE_EN;
}

/**
 * \brief ���������ܺ���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_c2_rx_disable (amhw_fsl_uart_t *p_hw_uart)
{
    p_hw_uart->c2 &= ~AMHW_FSL_UART_C2_RE_EN;
}
/**
 * \brief ʹ�ܴ���
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_enable (amhw_fsl_uart_t *p_hw_uart)
{
    amhw_fsl_uart_c2_rx_enable(p_hw_uart);
    amhw_fsl_uart_c2_tx_enable(p_hw_uart);
}

/**
 * \brief ���ܴ���
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_disable (amhw_fsl_uart_t *p_hw_uart)
{
    amhw_fsl_uart_c2_rx_disable(p_hw_uart);
    amhw_fsl_uart_c2_tx_disable(p_hw_uart);
}

/**
 * \brief ��������OSRֵ���ú���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] osr_val   : �����ʷ�Ƶ���Ӹ�λֵ
 *
 * \note ��������ֻ���ڴ���0
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_c4_osr_set (amhw_fsl_uart_t *p_hw_uart, uint8_t osr_val)
{
    uint8_t temp=0;
    temp = p_hw_uart->uart0_c4 ;
    temp &= ~AMHW_FSL_UART_C4_OSR_MASK;
    temp|= AMHW_FSL_UART_C4_OSR(osr_val);
    p_hw_uart->uart0_c4 =temp;
}

/**
 * \brief д���ڷ��ͼĴ���ֵ������һ�����ݣ�
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] data      : ���͵�����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_txdata_write (amhw_fsl_uart_t *p_hw_uart, uint8_t data)
{
    p_hw_uart->data = data;
}

/**
 * \brief ��ȡ���ڽ�������
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \return ���ڽ��յ�������
 */
am_static_inline
uint8_t amhw_fsl_uart_rxdata_read (amhw_fsl_uart_t *p_hw_uart)
{
     return p_hw_uart->data;
}


/**
 * \brief �õ����ڷ���״̬
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��S1_TDREλֵ��1ʱ�������Լ�����������
 */
am_static_inline
uint8_t amhw_fsl_uart_stat1_tdre_get (amhw_fsl_uart_t *p_hw_uart)
{

   return (((uint8_t)(p_hw_uart->stat1 & AMHW_FSL_UART_S1_TDRE_MASK)) >> 7);
}

/**
 * \brief �õ����ڷ�����ɱ�־
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��S1_TCλֵ��1ʱ����������ɣ�0��ʾ���ڴ���
 */
am_static_inline
uint8_t amhw_fsl_uart_stat1_tc_get (amhw_fsl_uart_t *p_hw_uart)
{
   return (((uint8_t)(p_hw_uart->stat1 & AMHW_FSL_UART_S1_TC_MASK)) >> 6);
}

/**
 * \brief �õ����ڽ���״̬
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��S1_RDRFλֵ��1ʱ�������Լ�����������
 */
am_static_inline
uint8_t amhw_fsl_uart_stat1_rdre_get (amhw_fsl_uart_t *p_hw_uart)
{
   return (((uint8_t)(p_hw_uart->stat1 & AMHW_FSL_UART_S1_RDRF_MASK)) >> 5);
}

/**
 * \brief �õ�У��״̬
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 *
 * \return PFλ��ֵ��1��ʾ��ǰ�������ݳ���У�����
 */
am_static_inline
uint8_t amhw_fsl_uart_stat1_pf_get (amhw_fsl_uart_t *p_hw_uart)
{
    return (p_hw_uart->stat1 & AMHW_FSL_UART_S1_PF_MASK);
}


/**
 * \brief UART����ģʽλ����
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] datamode  : ����ģʽ
                          AMHW_FSL_UART_C1_M_*��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_data_mode_set (amhw_fsl_uart_t *p_hw_uart, uint8_t datamode)
{
    p_hw_uart->c1 &= ~(1<<4);
    p_hw_uart->c1|= datamode;
}

/**
 * \brief UART��żУ������
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] parity    : ����ģʽ
                          AMHW_FSL_UART_C1_PARITY_*��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_parity_set (amhw_fsl_uart_t *p_hw_uart, uint8_t parity)
{

    p_hw_uart->c1 &= ~(3<<0);
    p_hw_uart->c1 |= parity;

}

/**
 * \brief UARTֹͣλ���ú���
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] stop_bit  : ֹͣģʽλ��
                          AMHW_FSL_UART_BDH_SBNS_STOP_*��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_stop_bit_set (amhw_fsl_uart_t *p_hw_uart, uint8_t stop_bit)
{
    p_hw_uart->bdh &= ~(1<<5);
    p_hw_uart->bdh |= stop_bit;
}

/**
 * \brief ʹ��ָ���Ĵ����ж�
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_enable : AMHW_FSL_UART_INT_* ��ֵ����AMHW_FSL_UART_INT_*��Ļ�ֵ
 *                         (#AMHW_FSL_UART_INT_BDH_LBKDIE)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_int_enable (amhw_fsl_uart_t *p_hw_uart, uint32_t int_enable)
{
     p_hw_uart->bdh |= ((uint8_t)((int_enable&0x300)>>2));
     p_hw_uart->c2  |= ((uint8_t)(int_enable&0xf0));
     p_hw_uart->c3  |= ((uint8_t)(int_enable&0x0f));
}

/**
 * \brief ����ָ���Ĵ����ж�
 *
 * \param[in] p_hw_uart   : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_disable : AMHW_FSL_UART_INT_* ��ֵ����AMHW_FSL_UART_INT_*��Ļ�ֵ
 *                          (#AMHW_FSL_UART_INT_BDH_LBKDIE)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_int_disable (amhw_fsl_uart_t *p_hw_uart, uint32_t int_disable)
{
    p_hw_uart->bdh &= ~((uint8_t)((int_disable&0x300)>>2));
    p_hw_uart->c2  &= ~((uint8_t)(int_disable&0xf0));
    p_hw_uart->c3  &= ~((uint8_t)(int_disable&0x0f));
}

/**
 * \brief �õ�ver0 �����ж�״̬
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \return AMHW_FSL_UART_INTSTAT_*��ֵ����AMHW_FSL_UART_INTSTAT_*��Ļ�ֵ
 *         (#AMHW_FSL_UART_INTSTAT_S2_LBKDIF)
 */
am_static_inline
uint32_t amhw_fsl_uart_ver0_intstat_get (amhw_fsl_uart_t *p_hw_uart)
{
    uint32_t intstat = 0;
    intstat = ((p_hw_uart->stat2 & 0xc0) << 8)|
               (p_hw_uart->stat1 & 0xff);
               
    /* if UART0, w1c s1 */

	p_hw_uart->stat1 |= 0x1F;

    return intstat;
}
/**
 * \brief �õ�ver1 �����ж�״̬
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \return AMHW_FSL_UART_INTSTAT_*��ֵ����AMHW_FSL_UART_INTSTAT_*��Ļ�ֵ
 *         (#AMHW_FSL_UART_INTSTAT_S2_LBKDIF)
 */
am_static_inline
uint32_t amhw_fsl_uart_ver1_intstat_get (amhw_fsl_uart_t *p_hw_uart)
{
    uint32_t intstat = 0;
    intstat = ((p_hw_uart->stat2 & 0xc0) << 8)|
               (p_hw_uart->stat1 & 0xff);
    
    return intstat;
}

/**
 * \brief ����ģʽ��Tx���ŵ����������������
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] dir       : ����������� #AMHW_FSL_UART_SINGLE_WIRE_INPUT ����
 *                        #AMHW_FSL_UART_SINGLE_WIRE_OUTPUT
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_single_wire_dir_set (amhw_fsl_uart_t *p_hw_uart, uint8_t dir)
{
    p_hw_uart->c3 = ((p_hw_uart->c3 & (~AMHW_FSL_UART_C3_TXDIR)) | (dir << 5));
}


/**
 * \brief ʹ��ָ����ver0 ����MDA���մ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver0_dma_rx_enable (amhw_fsl_uart_t *p_hw_uart)
{
	p_hw_uart->uart0_c5 |= AMHW_FSL_UART_DMA_RX_EN;
}
/**
 * \brief ʹ��ָ����ver0 ����MDA���մ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver1_dma_rx_enable (amhw_fsl_uart_t *p_hw_uart)
{
	p_hw_uart->uart1_2_c4 |= AMHW_FSL_UART_DMA_RX_EN;
}

/**
 * \brief ����ָ����ver0 ����MDA���մ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver0_dma_rx_disable (amhw_fsl_uart_t *p_hw_uart)
{
	p_hw_uart->uart0_c5 &= ~AMHW_FSL_UART_DMA_RX_EN;
}

/**
 * \brief ����ָ����ver1 ����MDA���մ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver1_dma_rx_disable (amhw_fsl_uart_t *p_hw_uart)
{
	p_hw_uart->uart1_2_c4 &= ~AMHW_FSL_UART_DMA_RX_EN;
}

/**
 * \brief ʹ��ָ����ver0 ����DMA���ʹ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver0_dma_tx_enable (amhw_fsl_uart_t *p_hw_uart)
{

	p_hw_uart->uart0_c5 |= AMHW_FSL_UART_DMA_TX_EN;

}

/**
 * \brief ʹ��ָ����ver1 ����DMA���ʹ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver1_dma_tx_enable (amhw_fsl_uart_t *p_hw_uart)
{

	p_hw_uart->uart1_2_c4 |= AMHW_FSL_UART_DMA_TX_EN;

}
/**
 * \brief ����ָ����ver0 ����MDA���ʹ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver0_dma_tx_disable (amhw_fsl_uart_t *p_hw_uart)
{

	p_hw_uart->uart0_c5 &= ~AMHW_FSL_UART_DMA_TX_EN;

}

/**
 * \brief ����ָ����ver1 ����MDA���ʹ���
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_uart_ver1_dma_tx_disable (amhw_fsl_uart_t *p_hw_uart)
{

	p_hw_uart->uart1_2_c4 &= ~AMHW_FSL_UART_DMA_TX_EN;

}


/**
 * \brief UART���⹦��ģʽ����(�ػ�ģʽ�� ����ģʽ)
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] mode      : ����ģʽ
 *
 * \return ��
 *
 * \note ��ͨ�Ĵ���ģʽ����Ҫʹ�õ��ú�����������
 */
void amhw_fsl_uart_special_mode_set (amhw_fsl_uart_t *p_hw_uart, uint8_t mode);


/**
 * \brief UART���ݷ���(��ѯģʽ)
 *
 * \param[in] p_hw_uart : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_txbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����͵����ݸ���
 */
uint32_t amhw_fsl_uart_poll_send (amhw_fsl_uart_t  *p_hw_uart,
                                   const uint8_t *p_txbuf,
                                   uint32_t       nbytes);

/**
 * \brief UART���ݽ���(��ѯģʽ)
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_rxbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����յ����ݸ���
 */
uint32_t amhw_fsl_uart_poll_receive (amhw_fsl_uart_t *p_hw_uart,
                                      uint8_t      *p_rxbuf,
                                      uint32_t      nbytes);

/**
 * \brief VER0 ���ڲ���������
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] sysclk     : ���ڵ�����ʱ��Ƶ��
 * \param[in] baud       : �������õĴ��ڲ�����
 *
 * \return ����0��ʾʵ�ʵĲ����ʣ�С��0��������ʧ�ܡ�
 */
int amhw_fsl_uart_ver0_baudrate_set (amhw_fsl_uart_t *p_hw_uart, uint32_t sysclk, int baud);

/**
 * \brief VER1 ���ڲ���������
 *
 * \param[in] p_hw_uart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] sysclk     : ���ڵ�����ʱ��Ƶ��
 * \param[in] baud       : �������õĴ��ڲ�����
 *
 * \return ����0��ʾʵ�ʵĲ����ʣ�С��0��������ʧ�ܡ�
 */
int amhw_fsl_uart_ver1_baudrate_set (amhw_fsl_uart_t *p_hw_uart, uint32_t sysclk, int baud);

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * @} amhw_fsl_if_uart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_UART_H */

/* end of file */
