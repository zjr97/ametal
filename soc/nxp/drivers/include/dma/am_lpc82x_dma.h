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
 * \brief LPC82x DMA �����ӿ�
 *
 * DMA ���������ͨ�����ֽṹ������
 * - #am_lpc82x_dma_transfer_t  ���Խ��м򵥵��ڴ浽�ڴ棬�ڴ浽���裬���赽�ڴ洫�䣻
 * - #am_lpc82x_dma_xfer_desc_t ��������������ʽ���䣬��pingpongģʽ���䡣
 * 
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified.
 * - 1.00 15-07-12  win, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC82X_DMA_H
#define __AM_LPC82X_DMA_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc82x_if_dma
 * \copydoc am_lpc82x_dma.h
 * @{
 */

/**
 * \name DMA transfer�ṹ�崫����Ʋ���
 * \anchor grp_dma_trans_flags
 *
 *  �������ýṹ�� #am_lpc82x_dma_transfer_t ��flags����
 * @{
 */

/** \brief �������ݿ��Ϊ8 bit */
#define AM_LPC82X_DMA_TRANS_WIDTH_8BIT   AM_SBF(0, 0)

/** \brief �������ݿ��Ϊ16 bit */
#define AM_LPC82X_DMA_TRANS_WIDTH_16BIT  AM_SBF(1, 0)

/** \brief �������ݿ��Ϊ32 bit */
#define AM_LPC82X_DMA_TRANS_WIDTH_32BIT  AM_SBF(2, 0)

/** \brief Դ��ַ������ */
#define AM_LPC82X_DMA_TRANS_SRCINC_NOINC AM_SBF(0, 2)

/** \brief Դ��ַ����Ϊ1�����ݿ�� */
#define AM_LPC82X_DMA_TRANS_SRCINC_1X    AM_SBF(1, 2)

/** \brief Դ��ַ����Ϊ2�����ݿ��*/
#define AM_LPC82X_DMA_TRANS_SRCINC_2X    AM_SBF(2, 2)

/** \brief Դ��ַ����Ϊ4�����ݿ�� */
#define AM_LPC82X_DMA_TRANS_SRCINC_4X    AM_SBF(3, 2)

/** \brief Ŀ���ַ���� */
#define AM_LPC82X_DMA_TRANS_DSTINC_NOINC AM_SBF(0, 4)

/** \brief Ŀ���ַ����Ϊ1�����ݿ�� */
#define AM_LPC82X_DMA_TRANS_DSTINC_1X    AM_SBF(1, 4)

/** \brief Ŀ���ַ����Ϊ2�����ݿ�� */
#define AM_LPC82X_DMA_TRANS_DSTINC_2X    AM_SBF(2, 4)

/** \brief Ŀ���ַ����Ϊ4�����ݿ�� */
#define AM_LPC82X_DMA_TRANS_DSTINC_4X    AM_SBF(3, 4)

/** \brief ������ɺ��ظ����� */
#define AM_LPC82X_DMA_TRANS_REPEAT       AM_BIT( 6 )

/** @} */

/** \brief DMA transfer�ṹ�� */
typedef struct am_lpc82x_dma_transfer {
    uint32_t src_addr;            /**< \brief Դ��ַ              */
    uint32_t dst_addr;            /**< \brief Ŀ���ַ            */
    uint16_t nbytes;              /**< \brief �ܹ�������ֽ���    */
    uint16_t flags;               /**< \brief ������Ʊ�־        */
} am_lpc82x_dma_transfer_t;

/**
 * \name DMA xfer_desc�ṹ�崫����Ʋ���
 * \anchor grp_am_lpc82x_dma_xfer_flags
 *
 * �������� #am_lpc82x_dma_xfer_desc_t �е�xfercfg����
 *
 * @{
 */

/** \brief ������������Ч */
#define AM_LPC82X_DMA_XFER_VALID           AM_BIT(0)

/** \brief �������������ʱ���Զ������µ�ͨ�������� */
#define AM_LPC82X_DMA_XFER_RELOAD           AM_BIT(1)

/** \brief ��������DMA�������� */
#define AM_LPC82X_DMA_XFER_SWTRIG           AM_BIT(2)

/** \brief �������������ʱ�����������־ */
#define AM_LPC82X_DMA_XFER_CLRTRIG          AM_BIT(3)

/** \brief �������������ʱ������A�ж� */
#define AM_LPC82X_DMA_XFER_SETINTA          AM_BIT(4)

/** \brief �������������ʱ������B�ж� */
#define AM_LPC82X_DMA_XFER_SETINTB          AM_BIT(5)

/** \brief Դ��ַ������ */
#define AM_LPC82X_DMA_XFER_WIDTH_8BIT       AM_SBF(0, 8)

/** \brief �������ݿ��Ϊ16 bit */
#define AM_LPC82X_DMA_XFER_WIDTH_16BIT      AM_SBF(1, 8)

/** \brief �������ݿ��Ϊ32 bit */
#define AM_LPC82X_DMA_XFER_WIDTH_32BIT      AM_SBF(2, 8)

/** \brief ÿ�δ���Դ��ַ������  */
#define AM_LPC82X_DMA_XFER_SRCINC_NOINC    AM_SBF(0, 12)

/** \brief Դ��ַ����Ϊ1�����ݿ�� */
#define AM_LPC82X_DMA_XFER_SRCINC_1X        AM_SBF(1, 12)

/** \brief Դ��ַ����Ϊ2�����ݿ�� */
#define AM_LPC82X_DMA_XFER_SRCINC_2X        AM_SBF(2, 12)

/** \brief Դ��ַ����Ϊ4�����ݿ�� */
#define AM_LPC82X_DMA_XFER_SRCINC_4X        AM_SBF(3, 12)

/** \brief Ŀ���ַ���� */
#define AM_LPC82X_DMA_XFER_DSTINC_NOINC     AM_SBF(0, 14)

/** \brief Ŀ���ַ����Ϊ1�����ݿ�� */
#define AM_LPC82X_DMA_XFER_DSTINC_1X        AM_SBF(1, 14)

/** \brief Ŀ���ַ����Ϊ2�����ݿ�� */
#define AM_LPC82X_DMA_XFER_DSTINC_2X        AM_SBF(2, 14)

/** \brief Ŀ���ַ����Ϊ3�����ݿ�� */
#define AM_LPC82X_DMA_XFER_DSTINC_4X        AM_SBF(3, 14)

/**
 * \brief DMA xfer_desc�ṹ��
 * \attention xfer_desc�ĵ�ַ������16�ֽڶ���
 */
typedef struct am_lpc82x_dma_xfer_desc {
    volatile uint32_t xfercfg;           /**< \brief ��������         */
    volatile uint32_t src_end_addr;      /**< \brief Դ����ĩ��ַ     */
    volatile uint32_t dst_end_addr;      /**< \brief Ŀ������ĩ��ַ   */
    volatile uint32_t link;              /**< \brief ָ����һ�������� */
} am_lpc82x_dma_xfer_desc_t;

/**
 * \name DMA �������״̬��־
 * \anchor am_lpc82x_dma_complete_cb_stat
 *
 *  ����DMA�������ʱ������ص������е�stat���� 
 * @{
 */

#define AM_LPC82X_DMA_STAT_INTA   AM_BIT(0) /**< \brief �ж�A����     */
#define AM_LPC82X_DMA_STAT_INTB   AM_BIT(1) /**< \brief �ж�B����     */
#define AM_LPC82X_DMA_STAT_INTERR AM_BIT(2) /**< \brief �����жϷ���  */

/** @} */

/**
 * \brief DMA��������ص���������
 *
 * \param[in] p_arg : ����ṹ�崫��Ļص���������
 * \param[in] stat  : ���������״̬
 *      \arg AM_LPC82X_DMA_STAT_INTA   : �ж�A����
 *      \arg AM_LPC82X_DMA_STAT_INTB   : �ж�B����
 *      \arg AM_LPC82X_DMA_STAT_INTERR : �����жϷ���
 * 
 * \return ��
 *
 * \note #am_lpc82x_dma_transfer() �������ݲ������AM_LPC82X_DMA_STAT_INTB�ж�
 */
typedef void (*am_lpc82x_dma_complete_cb_t)(void *p_arg, int stat);


/** \brief DMAͨ��������
 *
 * ���д�����ڿ����� \n
 * ͨ�� #am_lpc82x_dma_controller_get()     ��ʼ��ͨ���ͻ�ȡ������
 * ͨ�� #am_lpc82x_dma_controller_abort()   ��ֹ���������ݴ���
 * ͨ�� #am_lpc82x_dma_controller_release() �ͷſ�����
 */
typedef struct am_lpc82x_dma_controller {
    uint8_t                      chan;         /**< \brief ͨ��               */
    uint8_t                      state;        /**< \brief ������״̬         */
    uint16_t                     ext_info;     /**< \brief ������Ϣ���ڲ�ʹ�� */
    am_lpc82x_dma_complete_cb_t  pfn_callback; /**< \brief �ص�����           */
    void                        *p_arg;        /**< \brief �ص�������         */
} am_lpc82x_dma_controller_t;

/** \brief DMA�豸��Ϣ */
typedef struct am_lpc82x_dma_devinfo {
    
    /** \brief DMA�Ĵ������ַ */
    uint32_t    dma_regbase;
    
    /** \brief INMUX�Ĵ������ַ */
    uint32_t    inmux_regbase;
    
    /** \brief ָ��������ڴ�ӳ���ָ�� */
    uint8_t     *p_controller_map;

    /** \brief ָ��������ڴ��ָ�� */
    am_lpc82x_dma_controller_t *p_controller;
    
    /** \brief ָ��������������ַ��ָ�룬������512�ֽڶ��� */
    am_lpc82x_dma_xfer_desc_t  *p_xfer_base;
    
    /** \brief ʹ�õ�ͨ������   */
    uint8_t     chan_count;
    
    /** \brief DMA�жϺ� */
    uint8_t     inum;
    
    /** \brief ƽ̨��ʼ������ */
    void      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void      (*pfn_plfm_deinit)(void);
    
} am_lpc82x_dma_devinfo_t;

/**
 * \brief DMA�豸
 */
typedef struct am_lpc82x_dma_dev {
    
    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const am_lpc82x_dma_devinfo_t *p_devinfo;
    
} am_lpc82x_dma_dev_t;


/**
 * \brief ��ȡͨ�������� 
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] opts : ���ò�����DMA_CHAN_OPT_*����� \n   
*                    \ref grp_dma_chan_opt_prio               : ���ȼ� \n
 *                   \ref grp_dma_chan_opt_periph_req_en      : ��������ʹ�� \n
 *                   \ref grp_dma_chan_opt_hwtrig_mode        : Ӳ���������� \n
 *                   \ref grp_dma_chan_opt_hwtrig_src         : Ӳ������Դ \n
 *                   \ref grp_dma_chan_opt_hwtrig_burst_en    : ͻ��ģʽʹ�� \n
 *                   \ref grp_dma_chan_opt_hwtrig_burst_wrap  : ͻ��ģʽ��ַ���� \n
 *                   \ref grp_dma_chan_opt_hwtrig_burst_count : ͻ�������С \n
 *                   \ref grp_dma_chan_opt_trig_out           : ������� \n
 *                   \see lpc82x_dma_chan.h
 * 
 * \return ָ��ͨ����������ָ��
 *
 * \note ���ͨ���Ѿ���ʹ����û���ͷţ���û���㹻����Դʹ�ã���������NULL
 */
am_lpc82x_dma_controller_t* am_lpc82x_dma_controller_get (uint8_t  chan,
                                                          uint32_t opts);

/**
 * \brief ��ֹ���������ݴ��� 
 *
 * \param[in] p_ctr : ָ��ͨ����������ָ��
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 * \retval -AM_ENXIO  : �豸������
 */
int am_lpc82x_dma_controller_abort (am_lpc82x_dma_controller_t *p_ctr);

/**
 * \brief �ͷſ����� 
 *
 * \param[in] p_ctr   : ָ��ͨ����������ָ��
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 * \retval -AM_EPERM  : ����������(���ڴ���)
 * \retval -AM_ENXIO  : �豸������
 */
int am_lpc82x_dma_controller_release (am_lpc82x_dma_controller_t *p_ctr);

/**
 * \brief ����transfer�ṹ�� 
 * 
 * \param[in] p_trans  : ָ����ṹ���ָ�� 
 * \param[in] src_addr : Դ���׵�ַ
 * \param[in] dst_addr : Ŀ����׵�ַ
 * \param[in] nbytes   : �����ֽ�����ע��Ҫ�롰flags���Ŀ�ȶ�Ӧ
 * \param[in] flags    : ������� �μ���\ref grp_dma_trans_flags
 *
 * \retval  AM_OK      : �����ɹ� 
 * \retval -AM_EINVAL  : ������Ч
 */
int am_lpc82x_dma_transfer_build (am_lpc82x_dma_transfer_t *p_trans,
                                  uint32_t                  src_addr,
                                  uint32_t                  dst_addr,
                                  uint16_t                  nbytes,
                                  uint16_t                  flags);

/**
 * \brief ʹ��transfer��ʽ��������
 *
 * �ú���������һ��DMA���䣬����p_transָ��ṹ������������
 *
 * \param[in] p_ctr        : ָ��ͨ����������ָ��
 * \param[in] p_trans      : ָ����ṹ���ָ��
 * \param[in] pfn_callback : ��������ص�����
 * \param[in] p_arg        : �ص���������
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 * \retval -AM_ENXIO  : �豸������
 * \retval -AM_RBUSY  : �豸æ
 */
int am_lpc82x_dma_transfer (am_lpc82x_dma_controller_t  *p_ctr,
                            am_lpc82x_dma_transfer_t    *p_trans,
                            am_lpc82x_dma_complete_cb_t  pfn_callback,
                            void                        *p_arg);

/**
 * \brief ����xfer_desc�ṹ�� 
 *
 * \attention ��ʹ��������Ҫ�Զ����أ������������ĵ�ַӦ��16�ֽڶ���  
 * 
 * \param[in] p_desc   : ָ��DMA������������ָ�� 
 * \param[in] src_addr : Դ���׵�ַ 
 * \param[in] dst_addr : Ŀ����׵�ַ 
 * \param[in] nbytes   : �����ֽ�����ע��Ҫ�롰flags���Ŀ�ȶ�Ӧ 
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_am_lpc82x_dma_xfer_flags
 *
 * \retval  AM_OK      : �����ɹ� 
 * \retval -AM_EINVAL  : ������Ч
 */
int am_lpc82x_dma_xfer_desc_build (am_lpc82x_dma_xfer_desc_t *p_desc,
                                   uint32_t                   src_addr,
                                   uint32_t                   dst_addr,
                                   uint32_t                   nbytes,
                                   uint32_t                   flags);
                                   
/**
 * \brief ��������xfer_desc���������� 
 *
 * \param[in] p_desc : ָ��ǰ������������ָ��
 * \param[in] p_next : ָ����һ��������������ָ�룬����16�ֽڶ��� 
 *
 * \retval  AM_OK    : ���ӳɹ� 
 * \retval -AM_EINVL : ������Ч 
 */
int am_lpc82x_dma_xfer_desc_link (am_lpc82x_dma_xfer_desc_t *p_desc,
                                  am_lpc82x_dma_xfer_desc_t *p_next);

/**
 * \brief ʹ��xfer_describe��ʽ��������
 *
 * �ú���������һ��DMA���䣬����p_descָ��ṹ�����������ݣ����p_descָ��һ������
 * DMA���Զ����������еĴ���������
 *
 * \param[in] p_ctr        : ָ��ͨ����������ָ��
 * \param[in] p_desc       : ָ���һ��������������ָ��
 * \param[in] pfn_callback : ��������ص�����
 * \param[in] p_arg        : �ص���������
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 * \retval -AM_ENXIO  : �豸������
 * \retval -AM_RBUSY  : �豸æ
 */
int am_lpc82x_dma_xfer_desc_startup (am_lpc82x_dma_controller_t  *p_ctr,
                                     am_lpc82x_dma_xfer_desc_t   *p_desc,
                                     am_lpc82x_dma_complete_cb_t  pfn_callback,
                                     void                        *p_arg);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev     : ָ��DMA�豸��ָ�� 
 * \param[in] p_devinfo : ָ��DMA�豸��Ϣ��ָ�� 
 *
 * \retval  AM_OK        : ��ʼ���ɹ� 
 * \retval -AM_EINVLA    : ������Ч
 * \retval -AM_EPERM     : ����������(�豸�Ѿ���ʼ��) 
 */
int am_lpc82x_dma_init (am_lpc82x_dma_dev_t           *p_dev,
                        const am_lpc82x_dma_devinfo_t *p_devinfo);


/**
 * \brief DMAȥ��ʼ�� 
 * \return  ��
 */
void am_lpc82x_dma_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_LPC82X_DMA_H */

/* end of file */
