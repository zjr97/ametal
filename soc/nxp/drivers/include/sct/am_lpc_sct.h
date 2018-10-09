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
 * \brief SCT����
 *
 * 1. SCT��״̬�����ö�ʱ������һ���Լ�����Ϊ���������¼�Ϊ���ģ�״̬״̬�����õĶ�ʱ��
 * 2. SCT������
 *    - һ�����32λ�����ļ�������
 *    - ��ʵ�ֵ��������������˫�������
 *    - �ɱ�SCT�¼�Ӳ�����Զ����ƣ���������������ֹͣ����������ֹ��
 *    - �ɱ�SCT�¼�Ӳ�����Զ������趨��ƥ��ֵ���ж��Ƿ�ƥ�䣻
 *    - �ɱ�SCT�¼�Ӳ�����Զ���ȡ����ֵ���Ա�ʵ�ֲ����߼���
 * 3. SCT�¼�
 *    - �¼��໥�������¼���Ŀ�ߴ�13����
 *    - ����������¼�����������������������IO������ƥ��������������������IO��ƥ��������ϣ�
 *    - ����������¼�����ЩSCT״̬�¿��Բ����ģ�
 *    - ����������¼�����ʱ���Լ������Ĳ����������ƣ���������������ֹͣ����������ֹ��
 *    - ����������¼�����ʱ���Ƿ񴥷�DMA��������֧������DMA����ͨ����
 *    - ����������¼�����ʱ�������IOͨ�����п��ƣ�
 *    - ����������¼�����ʱ������SCT�¼��жϣ�
 *    - ����������¼������󣬶�SCT״̬��Ӱ�졣
 * 4. SCT״̬
 *    - SCT�ṩ��13��״̬
 *    - ��������SCT�����ĸ�״̬��
 *    - ״̬֮���ͨ��SCT�¼������Զ��л���
 * 5. SCT ����IOͨ��
 *    - �ṩ��8������IOͨ����
 *    - ÿ��ͨ������������ΪSCT�¼�������IO�������߲�������״̬�����룻
 * 6. SCT ���IOͨ��
 *    - �ṩ��8������IOͨ����
 *    - ÿ��ͨ������������ΪSCT�¼�������IO���������¼�����ʱ�������Ƶ����IOͨ����
 *    - ���IOͨ��3�������ڴ���ADCת����������ͨ���޴˹��ܣ�
 *    - ������¼�ͬʱ����ͬһ�����ͨ��ʱ���ҷ����˵�ƽ��ͻ��������������ֳ�ͻ�Ľ��������
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-30  hgo, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_SCT_H
#define __AM_LPC_SCT_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc_if_sct
 * \copydoc am_lpc_sct.h
 * @{
 */

/** \brief SCT�¼��ж���Ϣ */
struct am_lpc_sct_evt_isr_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_isr;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};


/**
 * \brief SCT��ʱ������ص��豸��Ϣ
 */
typedef struct am_lpc_sct_devinfo {

    /** \brief SCT�Ĵ�����Ļ���ַ*/
    uint32_t                           sct_regbase;

    /** \brief SCT�жϺ� */
    uint8_t                            inum;

    /** \brief SCTʱ�ӱ�� */
    uint32_t                           clk_id;

    /** \brief ���¼��ж����� */
    int                                evt_isr_cnt;

    /** \brief ISR��Ϣӳ��(��С�� evt_isr_cnt һ��) */
    uint8_t                           *p_isrmap;

    /** \brief ISR��Ϣ���� */
    int                                isrinfo_cnt;


    /** \brief ISR��Ϣӳ���ڴ�(��С�� isrinfo_cnt һ��) */
    struct am_lpc_sct_evt_isr_info *p_isrinfo;

    /** \brief ���ͨ������ */
    int                                 sct_out_num;

    /** \brief DMA����ͨ������  */
    int                                 sct_dma_req_num;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
} am_lpc_sct_devinfo_t;

/**
 * \brief SCT��ʱ�����豸
 */
typedef struct am_lpc_sct_dev {

    /** \brief ָ��SCT(��ʱ����)�豸��Ϣ������ָ�� */
    const am_lpc_sct_devinfo_t  *p_devinfo;

    /** \brief �����¼���״̬
     *  bit0 = event0, bit1 = event1...
     *  ��bit0 = 1ʱ���¼�0�ѱ�ʹ��
     *  ��bit0 = 0ʱ���¼�0δʹ��
     */
    uint8_t                         evt_stat;

    /** \brief ������Ч��־ */
    am_bool_t                       valid_flg;
} am_lpc_sct_dev_t;

/** \brief SCT�������������Ͷ��� */
typedef am_lpc_sct_dev_t *am_lpc_sct_handle_t;

/**
 * \brief SCT�¼�
 */
typedef struct am_lpc_sct_evt {
    uint64_t    cond_flags;          /**< \brief �¼�����������������        */
    uint8_t     stat_en_flags;       /**< \brief �¼�����ЩSCT״̬����Ч������     */
    uint8_t     out_stat_flag;       /**< \brief �¼�����ʱSCT״̬������������� */
    uint8_t     out_cnt_flags;      /**< \brief �¼�����ʱ���Ƽ�������������   */
    uint8_t     out_dma_flags;       /**< \brief �¼�����ʱ����DMA����������   */
    uint16_t    out_io_flags;        /**< \brief �¼�����ʱ����IO��������        */
    uint64_t    out_int_flag;        /**< \brief �¼�����ʱ�ж�������        */
} am_lpc_sct_evt_t;


/**
 * \name �¼�����cond_flags bit[63:0]������λ����
 * @{
 */
#define AM_LPC_SCT_ISOUT_BITS_START        0   /**< \brief IO����ѡ����ʼλ��  */
#define AM_LPC_SCT_IOSEL_CH_BITS_START     1   /**< \brief IOͨ����ʼλ��  */
#define AM_LPC_SCT_IOCOND_BITS_START       5   /**< \brief IO������ʼλ��  */
#define AM_LPC_SCT_COND_OPR_BITS_START     7   /**< \brief ����������ʼλ��  */
#define AM_LPC_SCT_MATCAP_CH_BITS_START    16  /**< \brief ƥ��ͨ����ʼλ��  */
#define AM_LPC_SCT_MATCAP_ISCAP_BITS_START 24  /**< \brief �Ƿ�����ƥ��   */
#define AM_LPC_SCT_MATCAP_ISSET_BITS_START 25  /**< \brief �Ƿ�ƥ�书��   */
#define AM_LPC_SCT_MAT_VAL_BITS_START      32  /**< \brief ƥ��ֵλ����ʼλ��*/
#define AM_LPC_SCT_MATCAP_CH_BITS_LEN      4   /**< \brief ƥ��ͨ��λ�򳤶�   */
/** @} */

/**
 * \name �¼�����״̬�仯����out_stat_flag bit[7:0]������λ����
 * @{
 */
#define AM_LPC_SCT_ISRELOAD_BITS_START    0  /**< \brief �Ƿ���װ״̬��ʼλ��  */
#define AM_LPC_SCT_STAT_VAL_BITS_START    1  /**< \brief ״ֵ̬��ʼλ��  */
/** @} */

/**
 * \name �¼����Ƽ���������out_cnt_flags bit[8:0]������λ����
 * @{
 */
#define AM_LPC_SCT_LIMIT_BITS_START   0   /**< \brief ���ƶ�ʱ����ʼλ��  */
#define AM_LPC_SCT_STOP_BITS_START    1   /**< \brief ֹͣ��ʱ����ʼλ��  */
#define AM_LPC_SCT_START_BITS_START   2   /**< \brief ������ʱ����ʼλ��  */
#define AM_LPC_SCT_HALT_BITS_START    3   /**< \brief ��ֹ��ʱ����ʼλ��  */
/** @} */

/**
 * \name �¼�����IO�������out_io_flags bit[15:0]������λ����
 * @{
 */
#define AM_LPC_SCT_IOSET_CH_BITS_START    0   /**< \brief ��λIOͨ����ʼλ��  */
#define AM_LPC_SCT_IOCLR_CH_BITS_START    8   /**< \brief ����IOͨ����ʼλ��  */
/** @} */

/**
 * \name �¼������ж�����out_int_flag bit[63:0]������λ����
 * @{
 */
#define AM_LPC_SCT_CALLBACK_BITS_START    0  /**< \brief �ص�������ʼλ��  */
#define AM_LPC_SCT_CBPARAM_BITS_START     32 /**< \brief �ص�����������ʼλ��  */
#define AM_LPC_SCT_CALLBACK_BITS_LEN      32  /**< \brief �ص���������  */
#define AM_LPC_SCT_CBPARAM_BITS_LEN       32  /**< \brief �ص�������������  */
/** @} */

/**
 * \name �¼�����DMA��������out_dma_flags bit[7:0]������λ����
 * @{
 */
#define AM_LPC_SCT_DMA_REQ_CH_BITS_START    0 /**< \brief DMA����ͨ����ʼλ��  */
/** @} */

/**
 * \name SCT���е����IOͨ�����
 * \anchor grp_am_lpc_sct_io_chan_out
 * @{
 */
#define    AM_LPC_SCT_IO_CHAN_OUT0   0   /**< \brief SCT���ͨ��0     */
#define    AM_LPC_SCT_IO_CHAN_OUT1   1   /**< \brief SCT���ͨ��1     */
#define    AM_LPC_SCT_IO_CHAN_OUT2   2   /**< \brief SCT���ͨ��2     */
#define    AM_LPC_SCT_IO_CHAN_OUT3   3   /**< \brief SCT���ͨ��3     */
#define    AM_LPC_SCT_IO_CHAN_OUT4   4   /**< \brief SCT���ͨ��4     */
#define    AM_LPC_SCT_IO_CHAN_OUT5   5   /**< \brief SCT���ͨ��5     */
#define    AM_LPC_SCT_IO_CHAN_OUT6   6   /**< \brief SCT���ͨ��6     */
#define    AM_LPC_SCT_IO_CHAN_OUT7   7   /**< \brief SCT���ͨ��7     */

/** @} */

/**
 * \name SCT���е�����IOͨ�����
 * \anchor grp_am_lpc_sct_io_chan_in
 * @{
 */
#define    AM_LPC_SCT_IO_CHAN_IN0    0    /**< \brief SCT����ͨ��0 */
#define    AM_LPC_SCT_IO_CHAN_IN1    1    /**< \brief SCT����ͨ��1 */
#define    AM_LPC_SCT_IO_CHAN_IN2    2    /**< \brief SCT����ͨ��2 */
#define    AM_LPC_SCT_IO_CHAN_IN3    3    /**< \brief SCT����ͨ��3 */
#define    AM_LPC_SCT_IO_CHAN_IN4    4    /**< \brief SCT����ͨ��4 */
#define    AM_LPC_SCT_IO_CHAN_IN5    5    /**< \brief SCT����ͨ��5 */
#define    AM_LPC_SCT_IO_CHAN_IN6    6    /**< \brief SCT����ͨ��6 */
#define    AM_LPC_SCT_IO_CHAN_IN7    7    /**< \brief SCT����ͨ��7 */

/** @} */

/**
 * \name SCT���пɹ�����IO����
 * \anchor grp_am_lpc_sct_io_cond
 * @{
 */
#define    AM_LPC_SCT_IO_COND_LOW     0    /**< \brief �͵�ƽ���     */
#define    AM_LPC_SCT_IO_COND_RISE    1    /**< \brief �����ؼ��     */
#define    AM_LPC_SCT_IO_COND_FALL    2    /**< \brief �½��ؼ��     */
#define    AM_LPC_SCT_IO_COND_HIGH    3    /**< \brief �ߵ�ƽ���     */
/** @} */


/**
 * \name SCT�¼��������ú�
 *
 * \note �ض���IO���ػ��ƽ��ָ���Ĳ����ƽ����ĳ��ƥ��ֵ���ɴ���SCT�¼�������
 * - #AM_LPC_SCT_EVT_COND_MAT ���Ը� #AM_LPC_SCT_EVT_COND_IO_OUT ��
 *   #AM_LPC_SCT_EVT_COND_IO_IN ����һ�����С��򡯻��롯���㣬��ɵ�ֵ��Ϊ���������
 * - #AM_LPC_SCT_EVT_COND_IO_OUT �� #AM_LPC_SCT_EVT_COND_IO_IN
 *   ����ͬʱ��������������
 * - ʹ�� #AM_LPC_SCT_EVT_COND_CAP ����������ʱ�������������껥�⣬
 *   �����겻����ú���л�����������������
 * \anchor grp_am_lpc_sct_evt_cond_flags
 * @{
 */

/**
 *  \brief ƥ��������(��SCT���������ڸ�ƥ��ֵʱ���¼�����)
 *         mat_chΪָ����ƥ��Ĵ�������ţ���ΧΪ0~7
 *         mat_valΪƥ��ֵ��ȡֵ��ΧΪ0~0xFFFFFFFF
 */
#define AM_LPC_SCT_EVT_COND_MAT(mat_ch, mat_val)  \
                  (AM_BIT(AM_LPC_SCT_MATCAP_ISSET_BITS_START) | \
                   AM_SBF(mat_ch, AM_LPC_SCT_MATCAP_CH_BITS_START) | \
                   AM_SBF((uint64_t)mat_val, AM_LPC_SCT_MAT_VAL_BITS_START))

/**
 * \brief ���IO�����꣨��ָ��IOͨ�����ض���������⵽ʱ���¼�������
 *        io_ch_outΪ���IOͨ����ţ��μ�\ref grp_am_lpc_sct_io_chan_out,
 *        io_condΪָ������IO�������μ�\ref grp_am_lpc_sct_io_cond
 */
#define AM_LPC_SCT_EVT_COND_IO_OUT(io_ch_out, io_cond)  \
                    (AM_BIT(AM_LPC_SCT_ISOUT_BITS_START) | \
                     AM_SBF(io_ch_output, AM_LPC_SCT_IOSEL_CH_BITS_START) | \
                     AM_SBF(io_cond, AM_LPC_SCT_IOCOND_BITS_START))

/**
 * \brief ����IO�����꣨��ָ��IOͨ�����ض���������⵽ʱ���¼�������
 *        io_ch_inΪ����IOͨ����ţ��μ�\ref grp_am_lpc_sct_io_chan_in
 *        io_condΪָ������IO�������μ�\ref grp_am_lpc_sct_io_cond
 */
#define AM_LPC_SCT_EVT_COND_IO_IN(io_ch_in, io_cond) \
                      (AM_SBF(io_ch_input, AM_LPC_SCT_IOSEL_CH_BITS_START) |\
                       AM_SBF(io_cond, AM_LPC_SCT_IOCOND_BITS_START))
/**
 * \brief ���������꣨��ָ������IOͨ�����ض���������⵽ʱ���¼�������
 *        cap_chΪ����ͨ����ţ���ΧΪ0~7
 *        io_ch_inΪ����IOͨ����ţ��μ�\ref grp_am_lpc_sct_io_chan_in
 *        io_condΪָ�������IO�������μ�\ref grp_am_lpc_sct_io_cond
 */
#define AM_LPC_SCT_EVT_COND_CAP(cap_ch, io_ch_in, io_cond) \
                      (AM_BIT(AM_LPC_SCT_MATCAP_ISSET_BITS_START) | \
                       AM_BIT(AM_LPC_SCT_MATCAP_ISCAP_BITS_START) | \
                       AM_SBF(mat_ch, AM_LPC_SCT_MATCAP_CH_BITS_START) |  \
                       AM_LPC_SCT_COND_IO_IN(io_ch_input, io_cond))


/** \brief ���������㣬ָ��ƥ��������IO�����������һ������ʱ���¼����� */
#define AM_LPC_SCT_EVT_COND_OPR_OR      \
                                    AM_SBF(0, AM_LPC_SCT_COND_OPR_BITS_START)

/** \brief ֻ���ƥ������������IO���������ָ��ƥ����������ʱ���¼�����*/
#define AM_LPC_SCT_EVT_COND_OPR_MATCH   \
                                    AM_SBF(1, AM_LPC_SCT_COND_OPR_BITS_START)

/** \brief ֻ���ƥ������������IO���������ָ��IO��������ʱ���¼�����*/
#define AM_LPC_SCT_EVT_COND_OPR_IO      \
                                    AM_SBF(2, AM_LPC_SCT_COND_OPR_BITS_START)

/** \brief ���������㣬ָ��ƥ��������IO�������ͬʱ����ʱ���¼�����*/
#define AM_LPC_SCT_EVT_COND_OPR_AND     \
                                    AM_SBF(3, AM_LPC_SCT_COND_OPR_BITS_START)
/** @} */

/**
 * \name SCT�¼�״̬ʹ�����ú�
 *
 * \note һ��SCT״̬���Բ������SCT�¼���һ���¼������ڲ�ͬSCT״̬�²���
 *
 * \anchor grp_am_lpc_sct_evt_stat_en_flags
 * @{
 */

/** \brief �¼���ָ��״̬���Բ�����stat_numȡֵΪ0~7 */
#define AM_LPC_SCT_EVT_STAT_EN(stat_num)         AM_SBF(1, stat_num)

/** \brief �¼���ָ��״̬��Χ�¿��Բ���
 *         stat_mask��bit0����״̬0��bit0=1ʱ���¼���״̬0ʹ�ܣ�
 *                                 bit1=1ʱ���¼���״̬1ʹ�ܣ�����λ������
 */
#define AM_LPC_SCT_EVT_STAT_EN_MASK(stat_mask)   (stat_mask)
/** @} */


/**
 * \name SCT�¼�����״̬���ú�
 *
 * \note �¼�����������SCT��״̬�仯��
 *       ���ǽ������¼��ǵ�ǰ״̬�����������¼����¼������ʱ���Ű������øı�SCT״̬
 * \anchor grp_am_lpc_sct_evt_out_stat_flags
 * @{
 */

/** \brief �¼���������װ״ֵ̬��SCT״̬��Ϊstat��statȡֵΪ0~7 */
#define AM_LPC_SCT_EVT_OUT_STAT_RELOAD(stat)   \
                              (AM_BIT(AM_LPC_SCT_ISRELOAD_BITS_START) |\
                               AM_SBF(stat, AM_LPC_SCT_STAT_VAL_BITS_START))

/** \brief �¼������󣬵���״ֵ̬��SCT״̬��Ϊ(old_state + stat)��statȡֵΪ0~7 */
#define AM_LPC_SCT_EVT_OUT_STAT_ADD(stat)      \
                               AM_SBF(stat, AM_LPC_SCT_STAT_VAL_BITS_START)
/** @} */

/**
 * \name SCT�¼����Ƽ��������ú�
 *
 * \note һ��SCT�¼�����ͬʱ���Ƽ��������ơ�ֹͣ����������ֹ��
 *       - ���Ƽ�������ָ������������߷��������ȡ����SCT�����������ã�
 *       - ֹͣ��������ָ������ֹͣ������������IO��ص�������������Ч��ֻ��ƥ��Ͳ���ʧЧ��
 *                                 ����Ӳ������������
 *       - ������������ָ��������ʼ������������ֹͣ״̬�µļ���������������������
 *       - ��ֹ�������ǹر�SCT����ʱ����ֹͣ�������������Ǵ�ʱIO��ض���ҲʧЧ��
 *                                 ����Ӳ���޷����ѣ�����ʹ������������������SCT��
 * \anchor grp_am_lpc_sct_evt_out_cnt_flags
 * @{
 */
/** \brief �¼�����ʱ�����Ƽ���������   */
#define AM_LPC_SCT_EVT_OUT_CNT_LIMIT  AM_BIT(AM_LPC_SCT_LIMIT_BITS_START)

/** \brief �¼�����ʱ��ֹͣ����������   */
#define AM_LPC_SCT_EVT_OUT_CNT_STOP   AM_BIT(AM_LPC_SCT_STOP_BITS_START)

/** \brief �¼�����ʱ����������������   */
#define AM_LPC_SCT_EVT_OUT_CNT_START  AM_BIT(AM_LPC_SCT_START_BITS_START)

/** \brief �¼�����ʱ����ֹ����������   */
#define AM_LPC_SCT_EVT_OUT_CNT_HALT   AM_BIT(AM_LPC_SCT_HALT_BITS_START)
/** @} */

/**
 * \name SCT�¼�����DMA�������ú�
 *
 * \note SCT�¼���ͬʱ����DMA�������0��DMA�������1
 * \anchor grp_am_lpc_sct_evt_out_dma_flags
 * @{
 */
/**
 * \brief �¼�����ʱ������DMA����
 *
 *        dma_req_outΪDMA�������ͨ����ţ�ֵΪ0��1
 */
#define AM_LPC_SCT_EVT_OUT_DMA(dma_req_out) AM_BIT(dma_req_out)
/** @} */

/**
 * \name SCT�¼�����IO������ú�
 *
 * \note SCT�¼�����ͬʱ���ƶ��IO���ͨ����λ������
 * \anchor grp_am_lpc_sct_evt_out_io_flags
 * @{
 */
/**
 * \brief �¼�����ʱ����ĳ���IOͨ��������λ
 *        io_ch_outΪ���IOͨ����ţ��μ�\ref grp_am_lpc_sct_io_chan_out,
 */
#define AM_LPC_SCT_EVT_OUT_IO_SET(io_ch_out) AM_BIT(io_ch_out)

/**
 * \brief �¼�����ʱ����ĳ���IOͨ����������
 *        io_ch_outΪ���IOͨ����ţ��μ�\ref grp_am_lpc_sct_io_chan_out,
 */
#define AM_LPC_SCT_EVT_OUT_IO_CLR(io_ch_out)  \
                           AM_BIT(io_ch_out + AM_LPC_SCT_IOCLR_CH_BITS_START)
/** @} */


/**
 * \name SCT�¼��ж����ú�
 *
 * \note SCT�¼����ֻ��������һ���жϻص�����
 * \anchor grp_am_lpc_sct_evt_out_int_flags
 * @{
 */
/**
 * \brief �¼�����ʱ�������ж�
 *        callbackΪ�ص�������p_argΪ�ص������Ĳ���
 */
#define AM_LPC_SCT_EVT_OUT_INT(callback, p_arg)    \
                       (AM_SBF((uint64_t)((uint32_t)p_arg), \
                               AM_LPC_SCT_CBPARAM_BITS_START) |\
                              ((uint32_t)callback))
/** @} */


/**
 * \brief ��ʼ��SCT
 *
 * \param[in] p_dev     : ָ��SCT�豸��ָ��
 * \param[in] p_devinfo : ָ��SCT�豸��Ϣ������ָ��
 *
 * \return SCT������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_lpc_sct_handle_t am_lpc_sct_init (am_lpc_sct_dev_t      *p_dev,
                                     const am_lpc_sct_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��SCT�����ʼ��SCT���ͷ������Դ
 *
 * \param[in] handle : am_lpc_sct_init() ��ʼ��������õ�SCT������
 *
 * \return ��
 */
void am_lpc_sct_deinit (am_lpc_sct_handle_t handle);

/**
 * \brief ��ʼ��SCT�¼�����
 *
 * \param[in] p_evt : ָ��Ҫ��ʼ�����¼�
 *
 */
am_static_inline
void am_lpc_sct_evt_init (am_lpc_sct_evt_t *p_evt)
{

    p_evt->cond_flags     = 0;
    p_evt->stat_en_flags  = 0;
    p_evt->out_stat_flag  = 0;
    p_evt->out_cnt_flags  = 0;
    p_evt->out_dma_flags  = 0;
    p_evt->out_io_flags   = 0;
    p_evt->out_int_flag   = 0;
}

/** \brief ĳSCT�¼����ܲ�ʹ�����ú� */
#define AM_LPC_SCT_EVT_FUNCS_NOT_USE   0

/**
 * \brief ����SCT�¼�
 *
 * \param[in] p_evt          : ָ��Ҫ�������¼�
 *
 * \param[in] cond_flags     : �����¼�����������
 *                             �μ�\ref grp_am_lpc_sct_evt_cond_flags
 *
 * \param[in] stat_en_flags  : �¼�����ЩSCT״̬����Ч����
 *                             �μ�\ref grp_am_lpc_sct_evt_stat_en_flags
 *
 * \param[in] out_stat_flag  : �¼�����ʱSCT״̬�����������
 *                             �μ�\ref grp_am_lpc_sct_evt_out_stat_flags
 *
 * \param[in] out_cnt_flags  : �¼�����ʱ���Ƽ�����������
 *                             �μ�\ref grp_am_lpc_sct_evt_out_cnt_flags
 *
 * \param[in] out_dma_flags  : �¼�����ʱDMA�����������
 *                             �μ�\ref grp_am_lpc_sct_evt_out_dma_flags
 *
 * \param[in] out_io_flags   : �¼�����ʱ����IO������
 *                             �μ�\ref grp_am_lpc_sct_evt_out_io_flags
 *
 * \param[in] out_int_flag   : �¼�����ʱ�ж�����
 *                             �μ�\ref grp_am_lpc_sct_evt_out_int_flags
 * \return ��
 *
 * \note ����ʹ��ĳ�������ʱ�������ú� #AM_LPC_SCT_EVT_FUNCS_NOT_USE ָ����
 */
am_static_inline
void am_lpc_sct_evt_build (am_lpc_sct_evt_t *p_evt,
                              uint64_t             cond_flags,
                              uint8_t              stat_en_flags,
                              uint16_t             out_stat_flag,
                              uint8_t              out_cnt_flags,
                              uint8_t              out_dma_flags,
                              uint16_t             out_io_flags,
                              uint64_t             out_int_flag)
{
    p_evt->cond_flags     = cond_flags;
    p_evt->stat_en_flags  = stat_en_flags;
    p_evt->out_stat_flag  = out_stat_flag;
    p_evt->out_cnt_flags  = out_cnt_flags;
    p_evt->out_dma_flags  = out_dma_flags;
    p_evt->out_io_flags   = out_io_flags;
    p_evt->out_int_flag   = out_int_flag;
}

/**
 * \brief ���SCT�¼�
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] evt_num    : �¼��ţ�ȡֵ��Χ0~7
 * \param[in] p_evt      : ָ��Ҫ��ӵ��¼�
 *
 * \retval  AM_OK        : ��ӳɹ�
 * \retval -AM_EINVAL    : ���ʧ��, ��������
 * \retval -AM_EPERM     : û�пյ��ڴ�ӳ�䣬�ص����������趨������
 *
 */
int am_lpc_sct_evt_add (am_lpc_sct_handle_t   sct_handle,
                           uint8_t                  evt_num,
                           am_lpc_sct_evt_t     *p_evt);

/**
 * \brief ɾ��SCT�¼�
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] evt_num    : �¼��ţ�ȡֵ��Χ0~7
 *
 * \retval  AM_OK        : ɾ���ɹ�
 * \retval -AM_EINVAL    : ɾ��ʧ��, ��������
 *
 */
int am_lpc_sct_evt_del (am_lpc_sct_handle_t   sct_handle,
                           uint8_t                  evt_num);


/**
 * \brief ����SCT
 *
 * \param[in] sct_handle : SCT����������
 *
 * \retval  AM_OK        : �����ɹ�
 * \retval -AM_EINVAL    : ����ʧ��, ��������
 *
 */
int am_lpc_sct_start (am_lpc_sct_handle_t   sct_handle);

/**
 * \brief ֹͣSCT
 *
 * \param[in] sct_handle : SCT����������
 *
 * \retval  AM_OK        : ֹͣ�ɹ�
 * \retval -AM_EINVAL    : ֹͣʧ��, ��������
 *
 */
int am_lpc_sct_stop (am_lpc_sct_handle_t   sct_handle);

/**
 * \brief ��ֹSCT
 *
 * \param[in] sct_handle : SCT����������
 *
 * \retval  AM_OK        : ��ֹ�ɹ�
 * \retval -AM_EINVAL    : ��ֹʧ��, ��������
 *
 */
int am_lpc_sct_halt (am_lpc_sct_handle_t   sct_handle);


/**
 * \name SCT���ͨ����ƽ��ͻ�Ľ���������ú�
 * \anchor grp_am_lpc_sct_res_flags
 * @{
 */
#define AM_LPC_SCT_RES_OUT_NOCHANGE     (0)    /**< \brief ��ͻʱ�ޱ仯     */
#define AM_LPC_SCT_RES_OUT_SET          (1)    /**< \brief ��ͻʱ��λ���   */
#define AM_LPC_SCT_RES_OUT_CLR          (2)    /**< \brief ��ͻʱ�������   */
#define AM_LPC_SCT_RES_OUT_TOG          (3)    /**< \brief ��ͻʱ��ת���   */
/**
 * @}
 */

/**
 * \brief �������ͨ����ƽ��ͻʱ�Ľ������
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] output_num : ���ͨ���ţ�0 ~ 5
 * \param[in] value      : ��ͻ�����ʽ��\ref grp_am_lpc_sct_res_flags
 *                          - #AM_LPC_SCT_RES_OUT_NOCHANGE : ����ޱ仯
 *                          - #AM_LPC_SCT_RES_OUT_SET      : ����ߵ�ƽ
 *                          - #AM_LPC_SCT_RES_OUT_CLR      : ����͵�ƽ
 *                          - #AM_LPC_SCT_RES_OUT_TOG      : ��ת�����ƽ
 *
 * \retval  AM_OK        : ���óɹ�
 * \retval -AM_EINVAL    : ����ʧ��, ��������
 */
int am_lpc_sct_conflict_res_config (am_lpc_sct_handle_t sct_handle,
                                       uint8_t                output_num,
                                       uint8_t                value);

/**
 * \brief ����SCT״ֵ̬
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] state    : ״ֵ̬
 *
 * \note ����״ֵ̬ʱ������ȷ����Ӧ�ļ�����������ֹ(HALT)״̬�������趨ʧ��
 *
 * \retval  AM_OK        : ���óɹ�
 * \retval -AM_EINVAL    : ����ʧ��, ��������
 * \retval -AM_EPERM     : δ����HALT״̬������ʧ��
 */
int am_lpc_sct_state_set (am_lpc_sct_handle_t sct_handle,
                             uint16_t               state);

/**
 * \brief ͨ��ʱ���ȡ��Ҫ�趨��ƥ��ֵ
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] period_ns  : ���ڣ���λns
 *
 * \return ƥ��ֵ
 *
 * \note ����ﵽ�����õļ��ޣ���ƥ�����ڹ�С�������ô����Զ�����Ϊ1�����ڹ�С��
 *       ��4294967295�����ڹ��󣩡�
 */
uint32_t am_lpc_sct_time_to_match(am_lpc_sct_handle_t sct_handle,
                                     uint32_t               period_ns);

/**
 * \brief ��ָ�������ͨ�����������ƽ
 *
 * \param[in] sct_handle : SCT����������
 * \param[in] output_num : ���ͨ���ţ�0 ~ 5
 * \param[in] value      : ����״̬���μ� \ref grp_am_gpio_pin_level
 *
 * \note дSCT����Ĵ�������ȷ�����еļ�����������ֹ(HALT)״̬�������趨ʧ��
 *
 * \retval  AM_OK        : ���óɹ�
 * \retval -AM_EINVAL    : ����ʧ��, ��������
 * \retval -AM_EPERM     : δ����HALT״̬������ʧ��
 */

int am_lpc_sct_out_state_set (am_lpc_sct_handle_t sct_handle,
                              uint8_t             output_num,
                              uint8_t             value);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_SCT_H */

/* end of file */
