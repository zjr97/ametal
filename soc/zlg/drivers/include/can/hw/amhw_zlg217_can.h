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
 * \brief CAN hardware operation interface
 *
 * -note:�ڶ�ͬһ�Ĵ������ж�дʱ������Ӧ�Ĺ��ܲ�ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-05  zcb, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_CAN_H
#define __AMHW_ZLG217_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg217_if_can
 * \copydoc amhw_zlg217_can.h
 * @{
 */

/**
 * \brief ZLG217 CAN�Ĵ�����ṹ��
 */
typedef struct amhw_zlg217_can {

    union {
        __IO  uint32_t cr;              /**< \brief 0x00 basic ���ƼĴ��� */
        __IO  uint32_t mod;             /**< \brief 0x00 peli ģʽ�Ĵ��� */
    }mode;

    __IO  uint32_t cmr;                 /**< \brief 0x04 ����Ĵ��� */
    __IO  uint32_t sr;                  /**< \brief 0x08 ״̬�Ĵ��� */
    __I   uint32_t ir;                  /**< \brief 0x0c �жϼĴ��� */

    union {

        struct {
            __IO  uint32_t acr;         /**< \brief 0x10 ���մ���Ĵ��� */
            __IO  uint32_t amr;         /**< \brief 0x14 �������μĴ��� */
        }basic;

        struct {
            __IO  uint32_t ier;         /**< \brief 0x10 �ж�ʹ�ܼĴ��� */
                  uint32_t reserve0;
        }peli;

    }accept;

    __IO  uint32_t btr0;                /**< \brief 0x18 ���߶�ʱ��0 */
    __IO  uint32_t btr1;                /**< \brief 0x1c ���߶�ʱ��1 */

    union {

        struct {
                  uint32_t reserve1[2]; /**< \brief ���� */
            __IO  uint32_t txid0;       /**< \brief 0x28 id10 ~ 3 */
            __IO  uint32_t txid1;       /**< \brief 0x2c id2 ~ 0/rtr/dlc0-4 */
            __IO  uint32_t txdr[8];     /**< \brief 0x30 DATA1 - 8 */
            __IO  uint32_t rxid0;       /**< \brief 0x50 id10 ~ 3 */
            __IO  uint32_t rxid1;       /**< \brief 0x54 id2 ~ 0/rtr/dlc0-4 */
            __IO  uint32_t rxdr[8];     /**< \brief 0x58 DATA1 - 8 */
                  uint32_t reserve2;    /**< \brief 0x78 ���� */
        }basic;

        struct {
                  uint32_t reserve1[3]; /**< \brief ���� */
            __IO  uint32_t alc;         /**< \brief 0x2c �ܲö�ʧ��׽�Ĵ��� */
            __IO  uint32_t ecc;         /**< \brief 0x30 ������벶׽�Ĵ��� */
            __IO  uint32_t ewlr;        /**< \brief 0x34 ���󱨾����ƼĴ��� */
            __IO  uint32_t rxerr;       /**< \brief 0x38 RX��������Ĵ��� */
            __IO  uint32_t txerr;       /**< \brief 0x3c TX��������Ĵ��� */
            __IO  uint32_t sff;         /**< \brief 0x40 RX/TX֡��Ϣ�Ĵ��� */
            __IO  uint32_t id0;         /**< \brief 0x44 RX/TXʶ����1 */
            __IO  uint32_t id1;         /**< \brief 0x48 RX/TXʶ����2 */
            __IO  uint32_t data[10];    /**< \brief 0x4c RX/TX���� */
            __IO  uint32_t rmc;         /**< \brief 0x74 RX��Ϣ������ */
            __IO  uint32_t rbsa;        /**< \brief 0x78 RX��������ʼ��ַ */
        }peli;

    }info;

    __IO  uint32_t cdr;                 /**< \brief 0x7c ʱ�ӷ�Ƶ�� */

}amhw_zlg217_can_t;

/**
 * \brief CANģʽ����
 */
typedef enum amhw_zlg217_can_type {
    AMHW_ZLG217_CAN_BASIC_CAN = 0,        /**< \brief basic can */
    AMHW_ZLG217_CAN_PELI_CAN,             /**< \brief peli can */
}amhw_zlg217_can_type_t;

/**
 * \brief CAN���ܶ���
 *
 * \note basic canֻ֪�и�λģʽ������ģʽ��˯��ģʽ
 *
 */
typedef enum amhw_zlg217_can_mode_func {
    AMHW_ZLG217_CAN_MODE_RESET = 0,       /**< \brief ��λģʽ */
    AMHW_ZLG217_CAN_MODE_ONLY_LISTEN,     /**< \brief ֻ��ģʽ */
    AMHW_ZLG217_CAN_MODE_SELF_CHECK,      /**< \brief �Լ�ģʽ */
    AMHW_ZLG217_CAN_MODE_SLEEP = 4,       /**< \brief ˯��ģʽ */
    AMHW_ZLG217_CAN_MODE_RUN,             /**< \brief ����ģʽ */
}amhw_zlg217_can_mode_t;

/**
 * \brief CAN���ݽ��շ�ʽ
 */
typedef enum amhw_zlg217_can_recv_mode {
    AMHW_ZLG217_CAN_RECV_POLL = 0,        /**< \brief ��ѯ����ģʽ */
    AMHW_ZLG217_CAN_RECV_INT,             /**< \brief �жϽ���ģʽ */
}amhw_zlg217_can_recv_mode_t;

/**
 * \brief peli CAN�˲���ʽ
 */
typedef enum amhw_zlg217_can_peli_filter_mode {
    AMHW_ZLG217_CAN_PELI_SINGLE_FILTER,   /**< \brief peli can ���˲���ģʽ */
    AMHW_ZLG217_CAN_PELI_DOUBLE_FLITER,   /**< \brief peli can ˫�˲���ģʽ */
}amhw_zlg217_can_peli_filter_mode_t;

/******************************************************************************/

/**
 * \brief CAN�ж�
 *
 * \note basic canֻ֧��ǰ5���жϣ����л����ж�û��ʹ�ܺͽ���λ��ֻ��ʹ�ܻ��߽���ǰ4���ж�
 *
 * @{
 */

#define AMHW_ZLG217_CAN_INT_NUM              (8ul)

#define AMHW_ZLG217_CAN_INT_BUS_ERR          (0x1 << 7ul)  /**< \brief ���ߴ����ж� */
#define AMHW_ZLG217_CAN_INT_ARBITRATION_LOST (0x1 << 6ul)  /**< \brief �ٲö�ʧ�ж� */
#define AMHW_ZLG217_CAN_INT_ERR_PASSIVE      (0x1 << 5ul)  /**< \brief ���������ж� */
#define AMHW_ZLG217_CAN_INT_WAKEUP           (0x1 << 4ul)  /**< \brief �����ж� */
#define AMHW_ZLG217_CAN_INT_OVER             (0x1 << 3ul)  /**< \brief ��������ж� */
#define AMHW_ZLG217_CAN_INT_ERR              (0x1 << 2ul)  /**< \brief �����ж� */
#define AMHW_ZLG217_CAN_INT_TRAN             (0x1 << 1ul)  /**< \brief �����ж� */
#define AMHW_ZLG217_CAN_INT_RECV             (0x1 << 0ul)  /**< \brief �����ж� */

/**
 * @}
 */

/**
 * \brief can�ж�ʹ��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] type       : can���ͣ�ö��amhw_zlg217_can_mode_t����
 * \param[in] flag       : �жϱ�־���ο��궨��AMHW_ZLG217_CAN_INT_
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_int_enable (amhw_zlg217_can_t      *p_hw_can,
                                 amhw_zlg217_can_type_t  type,
                                 uint32_t                flag)
{
    if (type == AMHW_ZLG217_CAN_BASIC_CAN) {
        p_hw_can->mode.cr |= (flag << 1);
    } else if (type == AMHW_ZLG217_CAN_PELI_CAN) {
        p_hw_can->accept.peli.ier |= (flag);
    }
}

/**
 * \brief can�жϽ���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] type       : can���ͣ�ö��amhw_zlg217_can_mode_t����
 * \param[in] flag       : �жϱ�־���ο��궨��AMHW_ZLG217_CAN_INT_
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_int_disable (amhw_zlg217_can_t      *p_hw_can,
                                  amhw_zlg217_can_type_t  type,
                                  uint32_t                flag)
{
    if (type == AMHW_ZLG217_CAN_BASIC_CAN) {
        p_hw_can->mode.cr &= ~(flag << 1);
    } else if (type == AMHW_ZLG217_CAN_PELI_CAN) {
        p_hw_can->accept.peli.ier &= ~(flag);
    }
}

/**
 * \brief can�жϱ�־��ȡ���ж��жϴ���Դ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �����жϵ��ж�Դ
 */
am_static_inline
uint8_t amhw_zlg217_can_int_status_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->ir & 0xff);
}

/******************************************************************************/

/**
 * \brief can ģʽ����
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 * \param[in] type     canģʽ��ö��amhw_zlg217_can_type_t����
 * \param[in] p_now    ��ǰģʽ
 * \param[in] update   ������ģʽ
 *
 * \return ��
 *
 * \note basic canģʽֻ֧�ָ�λ���������С�˯������ģʽ
 *
 */
void amhw_zlg217_can_mode_set (amhw_zlg217_can_t      *p_hw_can,
                               amhw_zlg217_can_type_t  type,
                               amhw_zlg217_can_mode_t *p_now,
                               amhw_zlg217_can_mode_t  update);

/******************************************************************************/

/**
 * \brief ����Ĵ������λ����
 *
 * \note ����Ĵ�����basic can�ж���ȫΪ0xff,��peli can�ж���ȫΪ0x00
 *
 * @{
 */

#define AMHW_ZLG217_CAN_CMR_MASK     (0x1F)

#define AMHW_ZLG217_CAN_CMR_GTS      (4ul)  /**< \brief ˯��(basic) */
#define AMHW_ZLG217_CAN_CMR_SRR      (4ul)  /**< \brief �Խ�������(peli) */
#define AMHW_ZLG217_CAN_CMR_CDO      (3ul)  /**< \brief ���������� */
#define AMHW_ZLG217_CAN_CMR_RRB      (2ul)  /**< \brief �ͷŽ��ջ����� */
#define AMHW_ZLG217_CAN_CMR_AT       (1ul)  /**< \brief ��ֹ���� */
#define AMHW_ZLG217_CAN_CMR_TR       (0ul)  /**< \brief �������� */

/**
 * @}
 */

/**
 * \brief д��can����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] cmr        : ������غ궨�壬�ο�AMHW_ZLG217_CAN_CMR_
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_cmr_set (amhw_zlg217_can_t *p_hw_can, uint32_t cmr)
{
    p_hw_can->cmr |= (0x1 << cmr) & AMHW_ZLG217_CAN_CMR_MASK;
}

/**
 * \brief basic CAN����˯��ģʽ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_go_to_sleep (amhw_zlg217_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x1 << AMHW_ZLG217_CAN_CMR_GTS);
}

/**
 * \brief basic CAN����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_wake_up (amhw_zlg217_can_t *p_hw_can)
{
    p_hw_can->cmr &= ~(0x1 << AMHW_ZLG217_CAN_CMR_GTS);
}
/******************************************************************************/

/**
 * \brief ״̬�Ĵ������λ����
 * @{
 */

#define AMHW_ZLG217_CAN_SR_MASK         (0xFF)

#define AMHW_ZLG217_CAN_SR_BS           (0x1 << 7ul)  /**< \brief ����״̬λ */
#define AMHW_ZLG217_CAN_BUS_CLOSE       (1ul)         /**< \brief ���߹ر� */
#define AMHW_ZLG217_CAN_BUS_OPEN        (0ul)         /**< \brief ���߿��� */

#define AMHW_ZLG217_CAN_SR_ES           (0x1 << 6ul)  /**< \brief ����״̬λ */
#define AMHW_ZLG217_CAN_ERROR           (1ul)         /**< \brief ���� */
#define AMHW_ZLG217_CAN_OK              (0ul)         /**< \brief OK */

#define AMHW_ZLG217_CAN_SR_TS           (0x1 << 5ul)  /**< \brief ����״̬λ */
#define AMHW_ZLG217_CAN_TRANS_RUN       (1ul)         /**< \brief ���� */
#define AMHW_ZLG217_CAN_TRANS_IDLE      (0ul)         /**< \brief ���� */

#define AMHW_ZLG217_CAN_SR_RS           (0x1 << 4ul)  /**< \brief ����״̬λ */
#define AMHW_ZLG217_CAN_RECV_RUN        (1ul)         /**< \brief ���� */
#define AMHW_ZLG217_CAN_RECV_IDLE       (0ul)         /**< \brief ���� */

#define AMHW_ZLG217_CAN_SR_TCS          (0x1 << 3ul)  /**< \brief �������״̬λ */
#define AMHW_ZLG217_CAN_TRANS_FINISH    (1ul)         /**< \brief ������� */
#define AMHW_ZLG217_CAN_TRANS_FINISH_NO (0ul)         /**< \brief ����δ��� */

#define AMHW_ZLG217_CAN_SR_TBS          (0x1 << 2ul)  /**< \brief ���ͻ�����״̬λ */
#define AMHW_ZLG217_CAN_TX_BUF_UNLOCK   (1ul)         /**< \brief ���ͻ������ͷ� */
#define AMHW_ZLG217_CAN_TX_BUF_LOCK     (0ul)         /**< \brief ���ͻ��������� */

#define AMHW_ZLG217_CAN_SR_DOS          (0x1 << 1ul)  /**< \brief �������״̬λ */
#define AMHW_ZLG217_CAN_DATA_OVER       (1ul)         /**< \brief ������� */
#define AMHW_ZLG217_CAN_DATA_OVER_NO    (0ul)         /**< \brief ���������ȱ */

#define AMHW_ZLG217_CAN_SR_RBS          (0x1 << 0ul)  /**< \brief ���ջ�����״̬ */
#define AMHW_ZLG217_CAN_RX_BUF_FULL     (1ul)         /**< \brief �� */
#define AMHW_ZLG217_CAN_RX_BUF_EMPTY    (0ul)         /**< \brief �� */

/**
 * @}
 */

/**
 * \brief ��ȡCAN��״̬
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return CAN�����״̬
 */
am_static_inline
uint32_t amhw_zlg217_can_status_get (amhw_zlg217_can_t *p_hw_can)
{
    return (p_hw_can->sr & AMHW_ZLG217_CAN_SR_MASK);
}

/******************************************************************************/

/**
 * \brief ������Ԥ��ֵ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] brp        : ������Ԥ��ֵ��6bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_brp_set (amhw_zlg217_can_t *p_hw_can, uint8_t brp)
{
    p_hw_can->btr0 = (p_hw_can->btr0 & (~0x3f)) | (brp & 0x3f);
}

/**
 * \brief ��ȡ������Ԥ��ֵ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ������Ԥ��ֵ��6bit
 */
am_static_inline
uint8_t amhw_zlg217_can_brp_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->btr0 & 0x3f);
}

/**
 * \brief ͬ����ת�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] sjw        : ͬ����ת���ֵ��2bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_sjw_set (amhw_zlg217_can_t *p_hw_can, uint8_t sjw)
{
    p_hw_can->btr0 = (p_hw_can->btr0 & (~(0x3 << 6))) | ((sjw & 0x3) << 6);
}

/**
 * \brief ��ȡͬ����ת���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ͬ����ת��ȣ�2bit
 */
am_static_inline
uint8_t amhw_zlg217_can_sjw_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr0 >> 6) & 0x3);
}

/**
 * \brief ����ģʽ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] sam        : ����ģʽֵ��1bit��ȣ�1 ���߲�������
 *                                         0 ���߲���һ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_sam_set (amhw_zlg217_can_t *p_hw_can, uint8_t sam)
{
    p_hw_can->btr1 = (p_hw_can->btr1 & (~(0x1 << 7))) | ((sam & 0x1) << 7);
}

/**
 * \brief ��ȡ����ģʽ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \retval    0 ���߲���һ��
 *            1 ���߲�������
 */
am_static_inline
uint8_t amhw_zlg217_can_sam_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr1 >> 7) & 0x1);
}

/**
 * \brief ʱ���1����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] tseg1        : ����ģʽֵ��4bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_tseg1_set (amhw_zlg217_can_t *p_hw_can, uint8_t tseg1)
{
    p_hw_can->btr1 = (p_hw_can->btr1 & (~0xf)) | (tseg1 & 0xf);
}

/**
 * \brief ��ȡʱ���1
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ʱ���1��4bit
 */
am_static_inline
uint8_t amhw_zlg217_can_tseg1_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->btr1 & 0xf);
}

/**
 * \brief ʱ���2����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] tseg2        : ����ģʽֵ��3bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_can_tseg2_set (amhw_zlg217_can_t *p_hw_can, uint8_t tseg2)
{
    p_hw_can->btr1 = (p_hw_can->btr1 & (~(0x7 << 4))) | ((tseg2 & 0x7) << 4);
}

/**
 * \brief ʱ���2����
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg217_can_tseg2_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr1 >> 4) & 0x7);
}

/******************************************************************************/

/**
 * \brief basicCAN��λ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_reset_set (amhw_zlg217_can_t *p_hw_can)
{
    p_hw_can->mode.cr |= 0x1;
}

/**
 * \brief basicCAN��λ�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_reset_clr (amhw_zlg217_can_t *p_hw_can)
{
    p_hw_can->mode.cr &= ~0x1;
}

/**
 * \brief ��ȡbasicCAN��λ��־
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
am_bool_t amhw_zlg217_basic_can_reset_get (amhw_zlg217_can_t *p_hw_can)
{
    return ((p_hw_can->mode.cr & 0x1) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief basicCAN���մ�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] ac         : ���մ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_ac_set (amhw_zlg217_can_t *p_hw_can, uint8_t ac)
{
    p_hw_can->accept.basic.acr = ac;
}

/**
 * \brief ��ȡbasicCAN���մ���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ���մ���
 */
am_static_inline
uint8_t amhw_zlg217_basic_can_ac_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->accept.basic.acr & 0xff);
}

/**
 * \brief basicCAN��������ֵ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] am         : ��������ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_am_set (amhw_zlg217_can_t *p_hw_can, uint8_t am)
{
    p_hw_can->accept.basic.amr = am;
}

/**
 * \brief ��ȡbasicCAN��������ֵ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��������ֵ
 */
am_static_inline
uint8_t amhw_zlg217_basic_can_am_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->accept.basic.amr & 0xff);
}

/**
 * \brief basicCANд11λ���ͱ�ʶ��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] id         : ��ʶ��11bit
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_tx_id_write (amhw_zlg217_can_t *p_hw_can,
                                        uint16_t           id)
{
    p_hw_can->info.basic.txid0 = (id >> 3) & 0xff;
    p_hw_can->info.basic.txid1 = (p_hw_can->info.basic.txid1 &
                                              (~(0x7 << 5))) |
                                              ((id & 0x7) << 5);
}

/**
 * \brief basicCANԶ�̱�־λRTRд��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] rtr        : rtrֵ��0/1
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_tx_rtr_write (amhw_zlg217_can_t *p_hw_can,
                                         uint8_t            rtr)
{
    p_hw_can->info.basic.txid1 = (p_hw_can->info.basic.txid1 &
                                              (~(0x1 << 4))) |
                                              ((rtr & 0x1) << 4);
}

/**
 * \brief basicCANд�������ݳ���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] len        : ���ݳ���0-8bytes
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_tx_data_len_set (amhw_zlg217_can_t *p_hw_can,
                                            uint8_t            len)
{
    p_hw_can->info.basic.txid1 = (p_hw_can->info.basic.txid1 & (~0xf)) |
                                                           (len & 0xf) ;
}

/**
 * \brief basicCANд��������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] offset     : ����ƫ��0-8
 * \param[in] val        : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_basic_can_tx_data_write (amhw_zlg217_can_t *p_hw_can,
                                          uint8_t            offset,
                                          uint8_t            val)
{
    p_hw_can->info.basic.txdr[offset] = val & 0xff;
}

/**
 * \brief basicCAN��11λ���ձ�ʶ��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ��ʶ��
 */
am_static_inline
uint16_t amhw_zlg217_basic_can_rx_id_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint16_t)((p_hw_can->info.basic.rxid0 & 0xff) << 3) |
                     ((p_hw_can->info.basic.rxid1 & 0xff) >> 5) ;
}

/**
 * \brief basicCAN��Զ�̱�־λRTR
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return rtrֵ
 */
am_static_inline
uint8_t amhw_zlg217_basic_can_rx_rtr_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->info.basic.rxid1 >> 4) & 0x1);
}

/**
 * \brief basicCAN���������ݳ���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ���ݳ���0-8bytes
 */
am_static_inline
uint8_t amhw_zlg217_basic_can_rx_data_len_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.basic.rxid1 & 0xf);
}

/**
 * \brief basicCAN�����յ�����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] offset     : ����ƫ��0-8
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg217_basic_can_rx_data_read (amhw_zlg217_can_t *p_hw_can,
                                            uint8_t            offset)
{
    return (uint8_t)(p_hw_can->info.basic.rxdr[offset] & 0xff);
}

/******************************************************************************/

/**
 * \brief ģʽ�Ĵ������λ����
 * @{
 */

#define AMHW_ZLG217_CAN_PELI_MODE_SM       (4ul)  /**< \brief ˯��ģʽ */
#define AMHW_ZLG217_CAN_PELI_MODE_AFM      (3ul)  /**< \brief �����˲���ģʽ */
#define AMHW_ZLG217_CAN_PELI_MODE_STM      (2ul)  /**< \brief �Լ��ģʽ */
#define AMHW_ZLG217_CAN_PELI_MODE_LOM      (1ul)  /**< \brief ֻ��ģʽ */
#define AMHW_ZLG217_CAN_PELI_MODE_RM       (0ul)  /**< \brief ��λģʽ */

/**
 * @}
 */

/**
 * \brief peli CANģʽ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] flag       : �ο�AMHW_ZLG217_CAN_PELI_MODE_
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_mod_set (amhw_zlg217_can_t *p_hw_can,
                                   uint32_t           flag)
{
    p_hw_can->mode.mod |= (0x1 << flag);
}

/**
 * \brief peli CANģʽ���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] flag       : �ο�AMHW_ZLG217_CAN_PELI_MODE_
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_mod_clr (amhw_zlg217_can_t *p_hw_can,
                                   uint32_t           flag)
{
    p_hw_can->mode.mod &= ~(0x1 << flag);
}

/**
 * \brief peli CANģʽ��ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ģʽ
 */
am_static_inline
uint8_t amhw_zlg217_peli_can_mod_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->mode.mod & 0x1f) &
                            ~(0x1 << AMHW_ZLG217_CAN_PELI_MODE_AFM));
}

/**
 * \brief peli CAN�˲���ģʽ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] mode       : �ο�ö��amhw_zlg217_can_peli_filter_mode_t
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_filter_mod_set (amhw_zlg217_can_t *p_hw_can,
                           amhw_zlg217_can_peli_filter_mode_t mode)
{
    if (AMHW_ZLG217_CAN_PELI_SINGLE_FILTER == mode) {
        p_hw_can->mode.mod |= 0x1 << AMHW_ZLG217_CAN_PELI_MODE_AFM;
    } else if (AMHW_ZLG217_CAN_PELI_DOUBLE_FLITER == mode) {
        p_hw_can->mode.mod &= ~(0x1 << AMHW_ZLG217_CAN_PELI_MODE_AFM);
    }
}

/**
 * \brief ��ȡpeli CAN�˲���ģʽ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �ο�ö��amhw_zlg217_can_peli_filter_mode_t
 */
am_static_inline amhw_zlg217_can_peli_filter_mode_t
amhw_zlg217_peli_filter_mod_get (amhw_zlg217_can_t *p_hw_can)
{
    return (p_hw_can->mode.mod & (0x1 << AMHW_ZLG217_CAN_PELI_MODE_AFM) ?
                                     AMHW_ZLG217_CAN_PELI_SINGLE_FILTER :
                                     AMHW_ZLG217_CAN_PELI_DOUBLE_FLITER);
}

/**
 * \brief peli CAN �ٲö�ʧ��׽�Ĵ���ֵ��ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �Ĵ���ֵ,ֵ��Ӧ����
 *
 * \note 1. 0 - 11��ʾ�ٲö�ʧ��ʶ����bit1 - bit11
 *       2. 11��ʾ�ٲö�ʧ��SRTRλ
 *       3. 12��ʾ�ٲö�ʧ��IDEλ
 *       4. 13 - 30��ʾ�ٲö�ʧ��ʶ����bit12 - bit29
 *       5. 31��ʾ�ٲö�ʧ��RTRλ
 */
am_static_inline
uint8_t amhw_zlg217_peli_can_alc_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.peli.alc & 0x1f);
}

/**
 * \brief peli CAN�������
 * @{
 */

#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_MASK    (0x3)  /**< \brief ����������� */
#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_SHIFT   (6ul)  /**< \brief ���������ʼλ */
#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_BIT     (0ul)  /**< \brief λ���� */
#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_MODE    (1ul)  /**< \brief ��ʽ���� */
#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_FILL    (2ul)  /**< \brief ������ */
#define AMHW_ZLG217_CAN_PELI_ECC_ERRC_OTHER   (3ul)  /**< \brief �������� */

/** \brief 1:RX;0:TX */
#define AMHW_ZLG217_CAN_PELI_ECC_DIR_RX             (0x1 << 3ul)

#define AMHW_ZLG217_CAN_PELI_ECC_CODE_MASK          (0x1f)
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_SHIFT         (0ul)

/** \brief ID.28-ID.21 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ID28_21       (2ul)
/** \brief ֡��ʼ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_FRAME_STRAT   (3ul)
/** \brief SRTRλ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_SRTR          (4ul)
/** \brief IDEλ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_IDE           (5ul)
/** \brief ID.20-ID.18 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ID20_18       (6ul)
/** \brief ID.17-ID.13 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ID17_13       (7ul)
/** \brief CRC���� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_CRC_ARRAY     (8ul)
/** \brief ����λ0 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_RESERVE0      (9ul)
/** \brief ������ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_DATA          (10ul)
/** \brief ���ݳ��ȴ��� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_DATA_LEN      (11ul)
/** \brief RTRλ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_RTR           (12ul)
/** \brief ����λ1 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_RESERVR1      (13ul)
/** \brief ID.4-ID.0 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ID4_0         (14ul)
/** \brief ID.12-ID.5 */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ID12_5        (15ul)
/** \brief ������־ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ACTIVITY_ERR  (17ul)
/** \brief ��ֹ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_BREAK_OFF     (18ul)
/** \brief ֧�䣨���ƣ�λ��� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_CR_BIT        (19ul)
/** \brief ���������־ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_PASSIVE       (22ul)
/** \brief ������� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ERR           (23ul)
/** \brief CRC����� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_CRC           (24ul)
/** \brief Ӧ��ͨ�� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ACK_CH        (25ul)
/** \brief ֡���� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_FRAME_END     (26ul)
/** \brief Ӧ����� */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_ACK           (27ul)
/** \brief �����־ */
#define AMHW_ZLG217_CAN_PELI_ECC_CODE_OVERFLOW      (28ul)

/**
 * @}
 */

/**
 * \brief peli CAN ������벶׽�Ĵ���ֵ��ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �Ĵ���ֵ
 */
am_static_inline
uint8_t amhw_zlg217_peli_can_ecc_get (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.peli.ecc & 0xff);
}

/**
 * \brief peli CAN ���󱨾����ƼĴ���д��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] val        : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_ewlr_write (amhw_zlg217_can_t *p_hw_can,
                                      uint8_t            val)
{
    p_hw_can->info.peli.ewlr = val & 0xff;
}

/**
 * \brief peli CAN ���󱨾����ƼĴ�����ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t  amhw_zlg217_peli_can_ewlr_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.peli.ewlr & 0xff);
}

/**
 * \brief peli CAN RX��������Ĵ���д��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] init       : ��ʼֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_rxerr_write (amhw_zlg217_can_t *p_hw_can,
                                       uint8_t            init)
{
    p_hw_can->info.peli.rxerr = init & 0xff;
}

/**
 * \brief peli CAN RX��������Ĵ�����ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �����������ֵ
 */
am_static_inline
uint8_t  amhw_zlg217_peli_can_rxerr_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.peli.rxerr & 0xff);
}

/**
 * \brief peli CAN TX��������Ĵ���д��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] init       : ��ʼֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_txerr_write (amhw_zlg217_can_t *p_hw_can,
                                       uint8_t            init)
{
    p_hw_can->info.peli.txerr = init & 0xff;
}

/**
 * \brief peli CAN TX��������Ĵ�����ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �����������ֵ
 */
am_static_inline
uint8_t  amhw_zlg217_peli_can_txerr_read (amhw_zlg217_can_t *p_hw_can)
{
    return (uint8_t)(p_hw_can->info.peli.txerr & 0xff);
}

/**
 * \brief ff�Ĵ������λ����
 *
 * \note ff�Ĵ���ֻ��һ��ȫ��д�룬����һλһλд��
 *
 * @{
 */

#define AMHW_ZLG217_CAN_PELI_SFF_FF         (0x1 << 7)  /**< \brief Զ�̱�־λ */
#define AMHW_ZLG217_CAN_PELI_SFF_RTR        (0x1 << 6)  /**< \brief RTR��־ */

#define AMHW_ZLG217_CAN_PELI_SFF_DLC_SHIFT  (0ul)       /**< \brief DLC�ƶ�λ�� */
#define AMHW_ZLG217_CAN_PELI_SFF_DLC_MASK   (0xf)       /**< \brief DLC���� */

/**
 * @}
 */

/**
 * \brief peli CAN SFF����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] val        : ������ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_peli_can_sff_set (amhw_zlg217_can_t *p_hw_can,
                                   uint8_t            val)
{
    p_hw_can->info.peli.sff = val;
}

/**
 * \brief peli CAN SFF��ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return �Ĵ���ֵ
 */
am_static_inline
uint8_t amhw_zlg217_peli_can_sff_get (amhw_zlg217_can_t *p_hw_can)
{
    return (p_hw_can->info.peli.sff & 0xff);
}

/**
 * \brief peli CAN ID����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] is_extend  : AM_TRUE ��չ֡��AM_FALSE ��׼֡
 * \param[in] id         : id
 *
 * \return ��
 */
am_static_inline
void  amhw_zlg217_peli_can_id_set (amhw_zlg217_can_t *p_hw_can,
                                   am_bool_t          is_extend,
                                   uint32_t           id)
{
    if (AM_TRUE == is_extend) {
        p_hw_can->info.peli.data[1] = (id & 0x1f) << 3;
        p_hw_can->info.peli.data[0] = (id >> 5)  & 0xff;
        p_hw_can->info.peli.id1     = (id >> 13) & 0xff;
        p_hw_can->info.peli.id0     = (id >> 21) & 0xff;
    } else {
        p_hw_can->info.peli.id0 = (id >> 3) & 0xff;
        p_hw_can->info.peli.id1 = (id & 0x7) << 5;
    }
}

/**
 * \brief peli CAN ID��ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] is_extend  : AM_TRUE ��չ֡��AM_FALSE ��׼֡
 *
 * \return id
 */
am_static_inline
uint32_t amhw_zlg217_peli_can_id_get (amhw_zlg217_can_t *p_hw_can,
                                      am_bool_t          is_extend)
{
    uint32_t temp = 0;

    if (AM_TRUE == is_extend) {
        temp |= (p_hw_can->info.peli.id0 & 0xff) << 21;
        temp |= (p_hw_can->info.peli.id1 & 0xff) << 13;
        temp |= (p_hw_can->info.peli.data[0] & 0xff) << 5;
        temp |= (p_hw_can->info.peli.data[1] >> 3) & 0x1f;
    } else {
        temp |= (p_hw_can->info.peli.id0 & 0xff) << 3;
        temp |= (p_hw_can->info.peli.id1 >> 5) & 0x7;
    }

    return temp;
}

/**
 * \brief peli CAN ����д��
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] is_extend  : AM_TRUE ��չ֡��AM_FALSE ��׼֡
 * \param[in] offset     : ƫ��
 * \param[in] val        : ����
 *
 * \return ��
 */
am_static_inline
void  amhw_zlg217_peli_can_data_write (amhw_zlg217_can_t *p_hw_can,
                                       am_bool_t          is_extend,
                                       uint8_t            offset,
                                       uint8_t            val)
{
    if (AM_TRUE == is_extend) {
        p_hw_can->info.peli.data[offset + 2] = val;
    } else {
        p_hw_can->info.peli.data[offset] = val;
    }
}

/**
 * \brief peli CAN ���ݶ�ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] is_extend  : AM_TRUE ��չ֡��AM_FALSE ��׼֡
 * \param[in] offset     : ƫ��
 *
 * \return ����
 */
am_static_inline
uint8_t amhw_zlg217_peli_can_data_read (amhw_zlg217_can_t *p_hw_can,
                                        am_bool_t          is_extend,
                                        uint8_t            offset)
{
    if (AM_TRUE == is_extend) {
        return (uint8_t)(p_hw_can->info.peli.data[offset + 2] & 0xff);
    } else {
        return (uint8_t)(p_hw_can->info.peli.data[offset] & 0xff);
    }
}

/**
 * \brief peli CAN ���մ�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] ac         : �˲�ֵ
 *
 * \return ����
 */
am_static_inline
void amhw_zlg217_peli_can_ac_set (amhw_zlg217_can_t *p_hw_can,
                                  uint32_t           ac)
{
    p_hw_can->info.peli.data[0] = ac & 0xff;
    p_hw_can->info.peli.id1     = (ac >> 8) & 0xff;
    p_hw_can->info.peli.id0     = (ac >> 16) & 0xff;
    p_hw_can->info.peli.sff     = (ac >> 24) & 0xff;
}

/**
 * \brief peli CAN ���մ����ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ac
 */
am_static_inline
uint32_t amhw_zlg217_peli_can_ac_get (amhw_zlg217_can_t *p_hw_can)
{
    uint32_t temp = 0;

    temp |= (p_hw_can->info.peli.sff     & 0xff) << 24;
    temp |= (p_hw_can->info.peli.id0     & 0xff) << 16;
    temp |= (p_hw_can->info.peli.id1     & 0xff) << 8;
    temp |= (p_hw_can->info.peli.data[0] & 0xff);

    return temp;
}

/**
 * \brief peli CAN ���μĴ�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] am         : ����ֵ
 *
 * \return ����
 */
am_static_inline
void amhw_zlg217_peli_can_am_set (amhw_zlg217_can_t *p_hw_can,
                                  uint32_t           am)
{
    p_hw_can->info.peli.data[4] = am & 0xff;
    p_hw_can->info.peli.data[3] = (am >> 8) & 0xff;
    p_hw_can->info.peli.data[2] = (am >> 16) & 0xff;
    p_hw_can->info.peli.data[1] = (am >> 24) & 0xff;
}

/**
 * \brief peli CAN ���μĴ�����ȡ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return am
 */
am_static_inline
uint32_t amhw_zlg217_peli_can_am_get (amhw_zlg217_can_t *p_hw_can)
{
    uint32_t temp = 0;

    temp |= (p_hw_can->info.peli.data[1] & 0xff) << 24;
    temp |= (p_hw_can->info.peli.data[2] & 0xff) << 16;
    temp |= (p_hw_can->info.peli.data[3] & 0xff) << 8;
    temp |= (p_hw_can->info.peli.data[4] & 0xff);

    return temp;
}

/******************************************************************************/

/**
 * \brief CANģʽ���ã������ڸ�λ������д
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] type       : ö��amhw_zlg217_can_mode_t����
 *
 * \return wu
 */
am_static_inline
void amhw_zlg217_can_type_set (amhw_zlg217_can_t      *p_hw_can,
                               amhw_zlg217_can_type_t  type)
{
    if (type == AMHW_ZLG217_CAN_BASIC_CAN) {
        p_hw_can->cdr &= ~(0x1 << 7);
    } else if (type == AMHW_ZLG217_CAN_PELI_CAN) {
        p_hw_can->cdr |= (0x1 << 7);
    }
}

/**
 * @} amhw_zlg217_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG217_CAN_H */

/* end of file */
