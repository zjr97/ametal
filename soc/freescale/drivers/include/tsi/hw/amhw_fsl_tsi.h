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
 * \brief TSI Ӳ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-26  nwt, make some changes.
 * - 1.00 15-10-23  wxj, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_TSI_H
#define __AMHW_FSL_TSI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_fsl_if_tsi
 * \copydoc amhw_fsl_tsi.h
 * @{
 */

/**
 * \brief TSI �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_tsi {
    __IO uint32_t    gencs;         /**< \brief ���ơ�״̬�Ĵ��� */
    __IO uint32_t    data;          /**< \brief ���ݼĴ��� */
    __IO uint32_t    tshd;          /**< \brief ��ֵ�Ĵ���*/
} amhw_fsl_tsi_t;

/**
 * \anchor TSI INT MODE
 * \brief  TSI �ж�ģʽ����
 */
typedef enum amhw_fsl_tsi_irq_mode {
    AMHW_FSL_TSI_OUT_RANGE = 0,         /**< \brief ������ֵ�ж�ʹ�� */
    AMHW_FSL_TSI_END_SCAN,              /**< \brief ɨ������ж�ʹ�� */
}amhw_fsl_tsi_irq_mode_t;

/**
 * \anchor TSI MODE
 * \brief  TSI ģʽ����
 */
typedef enum amhw_fsl_tsi_mode {
    AMHW_FSL_TSI_CAP_SENSING       = 0, /**< \brief ���ݸ�Ӧģʽ����������� */
    AMHW_FSL_TSI_SINGLE_THR_FRQDIS = 4, /**< \brief ����ֵ�������ģʽ��Ƶ�����Ƶ�·����*/
    AMHW_FSL_TSI_SINGLE_THR_FRQEN  = 8, /**< \brief ����ֵ�������ģʽ��Ƶ�����Ƶ�·ʹ��*/
    AMHW_FSL_TSI_AUTOMATIC_NOISE   = 12, /**< \brief �Զ��������ģʽ */
}amhw_fsl_tsi_mode_t;

/**
 * \anchor TSI REFCHRG
 * \brief  TSI �ο������㶨����Դ����
 */
typedef enum amhw_fsl_tsi_refchrg {
    AMHW_FSL_TSI_REFCHRG_500NA     = 0, /**< \brief 500nA */
    AMHW_FSL_TSI_REFCHRG_1UA,           /**< \brief 1uA */
    AMHW_FSL_TSI_REFCHRG_2UA,           /**< \brief 2uA */
    AMHW_FSL_TSI_REFCHRG_4UA,           /**< \brief 4uA */
    AMHW_FSL_TSI_REFCHRG_8UA,           /**< \brief 8uA */
    AMHW_FSL_TSI_REFCHRG_16UA,          /**< \brief 16uA */
    AMHW_FSL_TSI_REFCHRG_32UA,          /**< \brief 32uA */
    AMHW_FSL_TSI_REFCHRG_64UA,          /**< \brief 64uA */
}amhw_fsl_tsi_refchrg_t;

/**
 * \anchor TSI EXTCHRG
 * \brief  TSI �缫�����㶨����Դ����
 */
typedef enum amhw_fsl_tsi_extchrg {
    AMHW_FSL_TSI_EXTCHRG_500NA     = 0, /**< \brief 500nA */
    AMHW_FSL_TSI_EXTCHRG_1UA,           /**< \brief 1uA */
    AMHW_FSL_TSI_EXTCHRG_2UA,           /**< \brief 2uA */
    AMHW_FSL_TSI_EXTCHRG_4UA,           /**< \brief 4uA */
    AMHW_FSL_TSI_EXTCHRG_8UA,           /**< \brief 8uA */
    AMHW_FSL_TSI_EXTCHRG_16UA,          /**< \brief 16uA */
    AMHW_FSL_TSI_EXTCHRG_32UA,          /**< \brief 32uA */
    AMHW_FSL_TSI_EXTCHRG_64UA,          /**< \brief 64uA */
}amhw_fsl_tsi_extchrg_t;

/**
 * \anchor TSI DVOLT
 * \brief  TSI ������ѹ����
 */
typedef enum amhw_fsl_tsi_dvolt {
    AMHW_FSL_TSI_DV103             = 0, /**< \brief DV = 1.03V */
    AMHW_FSL_TSI_DV073,                 /**< \brief DV = 0.73V */
    AMHW_FSL_TSI_DV043,                 /**< \brief DV = 0.43V */
    AMHW_FSL_TSI_DV029,                 /**< \brief DV = 0.29V */
}amhw_fsl_tsi_dvolt_t;

/**
 * \anchor TSI TSICH
 * \brief  TSI �������ͨ��
 */
typedef enum amhw_fsl_tsi_channel {
    AMHW_FSL_TSI_CHAN0             = 0, /**< \brief ͨ��0 */
    AMHW_FSL_TSI_CHAN1,                 /**< \brief ͨ��1 */
    AMHW_FSL_TSI_CHAN2,                 /**< \brief ͨ��2 */
    AMHW_FSL_TSI_CHAN3,                 /**< \brief ͨ��3 */
    AMHW_FSL_TSI_CHAN4,                 /**< \brief ͨ��4 */
    AMHW_FSL_TSI_CHAN5,                 /**< \brief ͨ��5 */
    AMHW_FSL_TSI_CHAN6,                 /**< \brief ͨ��6 */
    AMHW_FSL_TSI_CHAN7,                 /**< \brief ͨ��7 */
    AMHW_FSL_TSI_CHAN8,                 /**< \brief ͨ��8 */
    AMHW_FSL_TSI_CHAN9,                 /**< \brief ͨ��9 */
    AMHW_FSL_TSI_CHAN10,                /**< \brief ͨ��10 */
    AMHW_FSL_TSI_CHAN11,                /**< \brief ͨ��11 */
    AMHW_FSL_TSI_CHAN12,                /**< \brief ͨ��12 */
    AMHW_FSL_TSI_CHAN13,                /**< \brief ͨ��13 */
    AMHW_FSL_TSI_CHAN14,                /**< \brief ͨ��14 */
    AMHW_FSL_TSI_CHAN15,                /**< \brief ͨ��15 */
}amhw_fsl_tsi_channel_t;

/**
 * \anchor TSI FREQ_DIV
 * \brief  TSI �缫������Ƶ������
 */
typedef enum amhw_fsl_tsi_oscfreq_div {
    AMHW_FSL_TSI_OSCFRQ_DIV_1      = 0, /**< \brief 1��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_2,          /**< \brief 2��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_4,          /**< \brief 4��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_8,          /**< \brief 8��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_16,         /**< \brief 16��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_32,         /**< \brief 32��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_64,         /**< \brief 64��Ƶ */
    AMHW_FSL_TSI_OSCFRQ_DIV_128         /**< \brief 128��Ƶ */
}amhw_fsl_tsi_oscfreq_div_t;

/**
 * \anchor TSI scan tirgger mode
 * \brief  TSI ɨ�败��ģʽ����
 */
typedef enum amhw_fsl_tsi_trig_mode {
    AMHW_FSL_TSI_TRIG_SOFTWARE     = 0, /**< \brief ������� */
    AMHW_FSL_TSI_TRIG_HAEDWARE,         /**< \brief Ӳ������ */
}amhw_fsl_tsi_trig_mode_t;

/**
 * \name  TSI �Ĵ���λ����
 * @{
 */

#define AMHW_FSL_TSI_OUTRGF       (0x1UL << 31) /** \brief ���ݳ�����ֵ��־λ */
#define AMHW_FSL_TSI_ESOR         (0x1UL << 28) /** \brief �ж�ģʽѡ�� */
#define AMHW_FSL_TSI_TSIEN        (0x1UL << 7)  /** \brief TSIʹ�� */
#define AMHW_FSL_TSI_TSIIEN       (0x1UL << 6)  /** \brief �ж�ʹ�� */
#define AMHW_FSL_TSI_STPE         (0x1UL << 5)  /** \brief �͹���ģʽ��TSIʹ�� */
#define AMHW_FSL_TSI_STM          (0x1UL << 4)  /** \brief ɨ�败����ʽѡ�� */
#define AMHW_FSL_TSI_SCNIP        (0x1UL << 3)  /** \brief ������ɨ�� */
#define AMHW_FSL_TSI_EOSF         (0x1UL << 2)  /** \brief ɨ�������־ */
#define AMHW_FSL_TSI_CURSW        (0x1UL << 1)  /** \brief �����Խ��� */
#define AMHW_FSL_TSI_DMAEN        (0x1UL << 23) /** \brief DMA����ʹ�� */
#define AMHW_FSL_TSI_SWTS         (0x1UL << 22) /** \brief ͨ������������� */

/** @} */

/**
 * \brief ��ȡ TSI ���ݳ�����ֵ��־
 *
 * \param[in] p_hw_tsi   : ָ��TSI ����Ĵ������ָ��
 *
 * \retval 0 : ����û�г�����Χ
 * \retval 1 : ���ݳ�����Χ
 */
am_static_inline
int amhw_fsl_tsi_outrgf_get (amhw_fsl_tsi_t *p_hw_tsi)
{
    return (((p_hw_tsi->gencs & (1ul << 31)) !=0) ? 1 : 0);
}

/**
 * \brief ���� TSI ���ݳ�����ֵ��־
 *
 * \param[in] p_hw_tsi   : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_outrgf_clr (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs |= AMHW_FSL_TSI_OUTRGF;
}

/**
 * \brief TSI �ж�ģʽ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] irq       : �ж�ģʽ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_int_mode_set (amhw_fsl_tsi_t *p_hw_tsi, amhw_fsl_tsi_irq_mode_t irq)
{
    AM_BITS_SET(p_hw_tsi->gencs, 28, 1, irq);
}

/**
 * \brief TSI ����ģʽ����
 *
 * \param[in] p_hw_tsi  : ָ�� TSI ����Ĵ������ָ��
 * \param[in] mode      : Ҫ���õ�ģʽ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_mode_set (amhw_fsl_tsi_t *p_hw_tsi, amhw_fsl_tsi_mode_t mode)
{
    AM_BITS_SET(p_hw_tsi->gencs, 24, 4, mode);
}

/**
 * \brief TSI �ο���������Դ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] value     : ���õĵ���ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_refchrg_val_set (amhw_fsl_tsi_t *p_hw_tsi,
                               amhw_fsl_tsi_refchrg_t value)
{
    AM_BITS_SET(p_hw_tsi->gencs, 21, 3, value);
}

/**
 * \brief ������ѹ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] value     : ���õĵ�ѹֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_dvolt_set (amhw_fsl_tsi_t *p_hw_tsi,
                         amhw_fsl_tsi_dvolt_t value)
{
    AM_BITS_SET(p_hw_tsi->gencs, 19, 2, value);
}

/**
 * \brief TSI �缫��������Դ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] value     : ���õĵ���ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_extchrg_val_set (amhw_fsl_tsi_t *p_hw_tsi,
                               amhw_fsl_tsi_extchrg_t value)
{
    AM_BITS_SET(p_hw_tsi->gencs, 16, 3, value);
}

/**
 * \brief TSI �缫������Ƶ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] div_val   : ���õķ�Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_oscfreq_div_set (amhw_fsl_tsi_t *p_hw_tsi,
                               amhw_fsl_tsi_oscfreq_div_t div_val)
{
    AM_BITS_SET(p_hw_tsi->gencs, 13, 3, div_val);
}

/**
 * \brief TSI �缫ɨ���������
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] num       : ���õ�ɨ�����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_scan_num_set (amhw_fsl_tsi_t *p_hw_tsi, uint32_t num)
{
    AM_BITS_SET(p_hw_tsi->gencs, 8, 5, num);
}

/**
 * \brief TSI ģ��ʹ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_mode_enable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs |= AMHW_FSL_TSI_TSIEN;
}

/**
 * \brief TSI ģ�����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_mode_disable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs &= (~AMHW_FSL_TSI_TSIEN);
}

/**
 * \brief TSI �ж�ʹ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_int_enable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs |= AMHW_FSL_TSI_TSIIEN;
}

/**
 * \brief TSI �жϽ���
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_int_disable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs &= (~AMHW_FSL_TSI_TSIIEN);
}

/**
 * \brief TSI �͹���ģʽ�¹���ʹ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_lowpower_enable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs |= AMHW_FSL_TSI_STPE;
}

/**
 * \brief TSI �͹���ģʽ�¹�������
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_lowpower_disable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs &= (~AMHW_FSL_TSI_STPE);
}

/**
 * \brief TSI ɨ�败��ģʽ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] mode      : ��Ҫ���õ�ɨ��ģʽ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_scan_trig_set (amhw_fsl_tsi_t *p_hw_tsi,
                             amhw_fsl_tsi_trig_mode_t mode)
{
    AM_BITS_SET(p_hw_tsi->gencs, 4, 1, mode);
}

/**
 * \brief TSI ��ɨ�败��ģʽ
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \retval 0 : �������
 * \retval 1 : Ӳ������
 */
am_static_inline
int amhw_fsl_tsi_scan_trig_get (amhw_fsl_tsi_t *p_hw_tsi)
{
    return (((p_hw_tsi->gencs & AMHW_FSL_TSI_STM) !=0) ? 1 : 0);
}

/**
 * \brief TSI ɨ��״̬��ȡ
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \retval 0 : ������û��ɨ��
 * \retval 1 : ��������ɨ��
 */
am_static_inline
int amhw_fsl_tsi_scnip_get (amhw_fsl_tsi_t *p_hw_tsi)
{
    return (((p_hw_tsi->gencs & AMHW_FSL_TSI_SCNIP) != 0) ? 1 : 0);
}

/**
 * \brief TSI ��ɨ�������־
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \retval 0 : ɨ��û�н���
 * \retval 1 : ɨ�����
 */
am_static_inline
int amhw_fsl_tsi_eosf_get (amhw_fsl_tsi_t *p_hw_tsi)
{
    return (((p_hw_tsi->gencs & AMHW_FSL_TSI_EOSF) !=0) ? 1 : 0);
}

/**
 * \brief TSI ��ɨ�������־
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_eosf_clr (amhw_fsl_tsi_t *p_hw_tsi)
{
   p_hw_tsi->gencs |= AMHW_FSL_TSI_EOSF;
}

/**
 * \brief TSI �缫����������ο�������������ʹ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_cursw_enable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs |= AMHW_FSL_TSI_CURSW;
}

/**
 * \brief TSI �缫����������ο�����������������
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_cursw_disable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->gencs &= (~AMHW_FSL_TSI_CURSW);
}

/**
 * \brief TSI �������ͨ��ѡ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] chan      : ��Ҫѡ���ͨ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_chan_set (amhw_fsl_tsi_t *p_hw_tsi, amhw_fsl_tsi_channel_t chan)
{
    AM_BITS_SET(p_hw_tsi->data, 28, 4, chan);
}

/**
 * \brief TSI DMA��������ʹ��
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_dma_enable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->data |= AMHW_FSL_TSI_DMAEN;
}

/**
 * \brief TSI DMA�����������
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_dma_disable (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->data &= (~AMHW_FSL_TSI_DMAEN);
}

/**
 * \brief TSI ͨ�������������
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_soft_tirg_start (amhw_fsl_tsi_t *p_hw_tsi)
{
    p_hw_tsi->data |= AMHW_FSL_TSI_SWTS;
}

/**
 * \brief TSI ��ȡת�����ֵ
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ת�����ֵ
 */
am_static_inline
uint16_t amhw_fsl_tsi_convert_value_get (amhw_fsl_tsi_t *p_hw_tsi)
{
    return AM_BITS_GET(p_hw_tsi->data, 0, 16);
}

/**
 * \brief TSI дͨ����ֵ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] value     : ��ֵ����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_wake_chan_thresholdh_write (amhw_fsl_tsi_t *p_hw_tsi, uint32_t value)
{
    AM_BITS_SET(p_hw_tsi->tshd, 16, 16, value);
}

/**
 * \brief TSI ��ͨ����ֵ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ��ֵ����
 */
am_static_inline
uint16_t amhw_fsl_tsi_wake_chan_thresholdh_read (amhw_fsl_tsi_t *p_hw_tsi)
{
    return AM_BITS_GET(p_hw_tsi->tshd, 16, 16);
}

/**
 * \brief TSI дͨ�����޷�ֵ
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 * \param[in] value     : ��ֵ����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tsi_wake_chan_thresholdl_write (amhw_fsl_tsi_t *p_hw_tsi, uint32_t value)
{
    AM_BITS_SET(p_hw_tsi->tshd, 0, 16, value);
}

/**
 * \brief TSI ��ͨ����ֵ����
 *
 * \param[in] p_hw_tsi  : ָ��TSI ����Ĵ������ָ��
 *
 * \return ���޷�ֵ
 */
am_static_inline
uint16_t amhw_fsl_tsi_wake_chan_thresholdl_read (amhw_fsl_tsi_t *p_hw_tsi)
{
    return AM_BITS_GET(p_hw_tsi->tshd, 0, 16);
}

/**
 * @} amhw_fsl_if_tsi
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_TSI_H */

/* end of file */

