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
 * \brief DMA����������DMA�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-23  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DMA_H
#define __AMDR_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_kl26_dma.h"
#include "../../../kl26/kl26_dmamux_chan.h"

/**
 * \addtogroup am_kl26_if_dma
 * \copydoc am_kl26_dma.h
 * @{
 */

/**
 * \name ͨ�������жϱ�־
 * \anchor am_kl26_dma_chan_cfg_flags
 * @{
 */

/** \brief ����жϱ�ʶ */
#define AM_KL26_DMA_INT_NORMAL         0

/** \brief �����жϱ�ʶ */
#define AM_KL26_DMA_INT_ERROR          1

/** @} */

/** \brief DMA�жϻص��������� */
typedef void (*am_kl26_pfn_dma_isr_t)(void *p_arg, uint8_t flag);

/** \brief DMA�жϻص�������Ϣ */
struct am_kl26_dma_int_info {

    /** \brief DMA�����ص����� */
    am_kl26_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                  *p_arg;
};

/** \brief DMA�豸��Ϣ */
typedef struct am_kl26_dma_devinfo {

    /** \brief ָ��DMAMUX�Ĵ������ָ�� */
    amhw_kl26_dmamux_t  *p_hw_dmamux;

    /** \brief ָ��DMA�Ĵ������ָ�� */
    amhw_kl26_dma_t     *p_hw_dma;

    /** \brief DMA�жϺ� */
    uint8_t         inum;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_kl26_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct am_kl26_dma_dev {

    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const am_kl26_dma_devinfo_t *p_devinfo;

}am_kl26_dma_dev_t;

/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan  : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags : ����ʹ��λ�Լ���Ӧͨ��������Դ����
 *                    �ж�Ӧ�ĺ궨��
 *
 * \retval AM_OK    : ���óɹ�
 * \retval AM_ERROR : ���ô��󣬸�ͨ��֮ǰ���ù�
 */
int am_kl26_dma_chan_cfg(int chan, uint8_t flags);

/**
 * \brief ֹͣͨ������
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) ��
 *
 * \retval AM_OK   : �����ɹ�
 */
int am_kl26_dma_chan_stop(int chan);

/**
 * \brief ��������������
 *
 * \param[in] p_desc   : ָ��DMA������������ָ��
 * \param[in] src_addr : Դ���׵�ַ
 * \param[in] dst_addr : Ŀ����׵�ַ
 * \param[in] nbytes   : �����ֽ���
 * \param[in] flags    : ���ò���
 *
 * \retval  AM_OK      : �����ɹ�
 * \retval -AM_EINVAL  : δ���룬��Ч����
 */
int am_kl26_dma_xfer_desc_build (amhw_kl26_dma_xfer_desc_t *p_desc,
                                 uint32_t                   src_addr,
                                 uint32_t                   dst_addr,
                                 uint32_t                   nbytes,
                                 uint32_t                   flags);

/**
 * \brief ����Ŀ�ĵ�ַ��������С
 *
 * \param[in] size     : ö���嶨�� ����������С����
 * \param[in] chan     : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \return ��
 */
void am_kl26_dma_xfer_desc_buffer_set (amhw_kl26_dma_buffer_size_set_t size,
                                       uint8_t                         chan);

/**
 * \brief ����Դ��ַ��������С
 *
 * \param[in] size     : ö���嶨�� ����������С����
 * \param[in] chan     : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \return ��
 */
void am_kl26_dma_xfer_source_buffer_set (amhw_kl26_dma_buffer_size_set_t size,
                                         uint8_t                         chan);

/**
 * \brief ��ʼDMA����
 *
 * \param[in] p_desc  : ָ��DMA������������ָ��
 * \param[in] type    : DMA����ģʽ���� ���ж�Ӧ��ö����dma_transfer_type_t
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
int am_kl26_dma_chan_start (amhw_kl26_dma_xfer_desc_t    *p_desc,
                            amhw_kl26_dma_transfer_type_t type,
                            uint8_t                       chan);

/**
 * \brief ����DMA�ص�����
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_KL26_DMA_INT*
 *            (#AM_KL26_DMA_INT_ERROR)��(#AM_KL26_DMA_INT_NORMAL)
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) ��
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� �������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_kl26_dma_isr_connect(int                    chan,
                            am_kl26_pfn_dma_isr_t  pfn_isr,
                            void                  *p_arg);

/**
 * \brief ɾ��DMA�ص�����������
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_KL26_DMA_INT*
 *            (#AM_KL26_DMA_INT_ERROR)��(#AM_KL26_DMA_INT_NORMAL)
 *            �ûص������ĵ����������ǲ����жϵ�ͨ������ȡֵ��Χ��DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) ��
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ����������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ɾ���ɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_kl26_dma_isr_disconnect(int                    chan,
                               am_kl26_pfn_dma_isr_t  pfn_isr,
                               void                  *p_arg);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev         : ָ��DMA�豸��ָ��
 * \param[in] p_dma_devinfo : ָ��DMA�豸��Ϣ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 */
int am_kl26_dma_init(am_kl26_dma_dev_t           *p_dev,
                     const am_kl26_dma_devinfo_t *p_dma_devinfo);


/**
 * \brief DMAȥ��ʼ��
 *
 * \return  ��
 */
void am_kl26_dma_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_KL26_DMA_H */

/* end of file */
