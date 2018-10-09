/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 82X WKT Ӳ�������ӿ�����
 * 
 * 1. 32λ�ɼ��ؼ��������������ؼ���ֵʱ���������Զ���������ʱ�¼�������һ��
 *    �ж�/��������
 * 2. WKTλ��һ��������ʼ���ϵ�ĵ�Դ���У�
 * 3. WKT֧������ʱ��Դ��һ��ʱ��Դ��Դ��ʼ���ϵ�ĵ�Դ��
 * 4. WKT�����ڽ��������κε͹���ģʽ(������ȵ���ģʽ)�л��ѣ�Ҳ������ͨ�ö�ʱ��
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-02  sky, modified.
 * - 1.00 15-07-10  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC_WKT_H
#define __AMHW_LPC_WKT_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** 
 * \addtogroup amhw_lpc_if_wkt
 * \copydoc amhw_lpc_wkt.h
 * @{
 */

/** \brief ����ʱֵ��32λ�����ֵ */
#define AMHW_LPC_WKT_INVAL_MAX              (0xFFFFFFFFUL)

/** \brief IRCʱ�� 750kHz */
#define AMHW_LPC_WKT_IRC_CLOCK_FREQ          750000

/** \brief �͹���ʱ�� 10kHz */
#define AMHW_LPC_WKT_LOW_POWER_CLOCK_FREQ    10000

/** \brief �ⲿʱ�����û��Զ��� */
#define AMHW_LPC_WKT_EXT_CLOCK_FREQ          0

/**
  * \brief 82x WKT �Ĵ�����ṹ��
 */
typedef struct amhw_lpc_wkt {
    __IO uint32_t ctrl;          /**< \brief �Ի��Ѷ�ʱ�����ƼĴ��� (R/W) */
    __IO uint32_t reserved0[2];  /**< \brief ���� */
    __IO uint32_t count;         /**< \brief �������Ĵ��� (R/W) */
} amhw_lpc_wkt_t;

/** \brief WKT ѡ��ʱ��Դ */
typedef enum amhw_lpc_wkt_clksel_str {
    AMHW_LPC_WKT_IRC_CLOCK = 0,        /**< \brief ��ƵIRCʱ�� 750kHz */
    AMHW_LPC_WKT_LOW_POWER_CLOCK ,     /**< \brief �͹���ʱ�� ���10kHz */
    AMHW_LPC_WKT_EXT_CLOCK = AM_BIT(3) /**< \brief �ⲿʱ�� */
} amhw_lpc_wkt_clksel_str_t;


/**
 * \brief WKT CLKSEL ѡ���Ի��Ѷ�ʱ��ʱ��Դ
 *
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \param[in] value    : ���ò��� ֵΪ 0 ���� 1 (amhw_lpc_wkt_clksel_str_t)
 *                       ȡAMHW_LPC_WKT_IRC_CLOCK       (��ƵIRCʱ�� 750 kHz)
*                        ȡAMHW_LPC_WKT_LOW_POWER_CLOCK (�͹���ʱ�� 10 kHz)
 *                       ȡAMHW_LPC_WKT_EXT_CLOCK       (�ⲿʱ�� Ƶ���Զ���)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_wkt_clksel_cfg (amhw_lpc_wkt_t            *p_hw_wkt,
                              amhw_lpc_wkt_clksel_str_t  value)
{
     AM_BIT_CLR_MASK(p_hw_wkt->ctrl, AM_BIT(3) | AM_BIT(0));
     AM_BIT_SET_MASK(p_hw_wkt->ctrl, value);
}

/**
 * \brief WKT ALARMFLAG ��ȡ �Ի��Ѷ�ʱ��ʱ��Դ
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \retval =0 : IRCʱ��
 * \retval =1 : �͹���ʱ��
 * \retval >1 : �ⲿʱ��
 */
am_static_inline
int amhw_lpc_wkt_clksel_get (amhw_lpc_wkt_t *p_hw_wkt)
{
    return (p_hw_wkt->ctrl & (AM_BIT(3) | AM_BIT(0)));
}

/**
 * \brief WKT CLEARCTR �����Ի��Ѷ�ʱ��
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \return ��
 * \note ����������������������µļ���ֵ֮ǰ����ֹͣ
 */
am_static_inline
void amhw_lpc_wkt_clearctr_clr (amhw_lpc_wkt_t *p_hw_wkt)
{
     AM_BIT_SET(p_hw_wkt->ctrl, 2);
}

/**
 * \brief WKT ALARMFLAG ��ȡ���ѻ򾯱���ʱ��״̬
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \retval 0 : δ��ʱ
 * \retval 1 : ��ʱ
 */
am_static_inline
int amhw_lpc_wkt_alarmflag_get (amhw_lpc_wkt_t *p_hw_wkt)
{
    return (((p_hw_wkt->ctrl & (1UL << 1)) != 0) ? 1 : 0);
}

/**
 * \brief WKT ALARMFLAG д1������ѻ򾯱���ʱ��״̬
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc_wkt_alarmflag_clear (amhw_lpc_wkt_t *p_hw_wkt)
{
    AM_BIT_SET(p_hw_wkt->ctrl, 1);
}

/**
 * \brief ���õ�ǰ��ʱ���ļ���ֵ
 *
 * \param[in] p_hw_wkt   : ָ��WKT�Ĵ������ָ��
 * \param[in] value      : Ҫ���ö�ʱ���ļ���ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_wkt_count_set (amhw_lpc_wkt_t *p_hw_wkt, uint32_t value)
{
    p_hw_wkt->count = value;
}


/**
 * \brief �õ���ǰ��ʱ���ļ���ֵ
 * \param[in] p_hw_wkt : ָ��WKT�Ĵ������ָ��
 * \return ��ǰ��ʱ���ļ���ֵ
 */
am_static_inline
uint32_t amhw_lpc_wkt_count_get (amhw_lpc_wkt_t *p_hw_wkt)
{
    return p_hw_wkt->count;
}

/**
 * @} amhw_lpc_if_wkt
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC_WKT_H */

/* end of file */
