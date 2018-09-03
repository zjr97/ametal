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
 * \brief DMA ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-11  ari, first implementation
 * \endinternal
 */

#include "am_zlg_dma.h"
#include "am_int.h"
#include "am_vdebug.h"

/*******************************************************************************
  ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define __INT_NOT_CONNECTED      0xFF

/** \brief ͨ��δ���ӱ�ʶ */
#define __CHAN_NOT_CONNECTED     0xFF

/** \brief ����ָ��DMA�豸��Ϣ��ָ�� */
#define __DMA_DEVINFO_DECL(p_dma_devinfo, p_dev)  \
        const am_zlg_dma_devinfo_t *p_dma_devinfo = p_dev->p_devinfo

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief ָ��DMA�豸��ָ�� */
static am_zlg_dma_dev_t *__gp_dma_dev;

/** \brief DMA�жϻص�������Ϣ���� */
static struct am_zlg_dma_int_info __dma_int_info[AMHW_ZLG_DMA_CHAN_CNT];

/** \brief DMA�жϻص�������Ϣӳ�� */
static uint8_t __dma_int_map[AMHW_ZLG_DMA_CHAN_CNT];

/*******************************************************************************
  ��������
*******************************************************************************/

/* �������������� */
int am_zlg_dma_xfer_desc_build (amhw_zlg_dma_xfer_desc_t *p_desc,
                                uint32_t                  src_addr,
                                uint32_t                  dst_addr,
                                uint32_t                  nbytes,
                                uint32_t                  flags)
{
    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (nbytes > 0xFFFF) {
        return AM_ERROR;
    }

    p_desc->xfercfg  = flags;
    p_desc->src_addr = src_addr;
    p_desc->dst_addr = dst_addr;
    p_desc->nbytes   = nbytes;

    return AM_OK;
}

/* ��ʼDMA���� */
int am_zlg_dma_xfer_desc_chan_cfg (amhw_zlg_dma_xfer_desc_t      *p_desc,
                                   amhw_zlg_dma_transfer_type_t   type,
                                   uint8_t                        chan)
{
    uint32_t per_data_size = 8;
    uint32_t mem_data_size = 8;
    uint32_t trans_data_byte = 0;

    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (chan > AMHW_ZLG_DMA_CHAN_CNT) {
        return AM_ERROR;
    }

    mem_data_size = 1 << (((p_desc->xfercfg >> 8) & 0x3u) + 3);

    switch(type) {

    case AMHW_ZLG_DMA_PER_TO_MER:
        p_desc->xfercfg |= (AMHW_ZLG_DMA_CHAN_DIR_FROM_PER |
                            AMHW_ZLG_DMA_CHAN_MEM_TO_MEM_DISABLE);

        per_data_size   = 1 << (((p_desc->xfercfg >> 10) & 0x3u) + 3);
        trans_data_byte = p_desc->nbytes / (per_data_size / 8);

        amhw_zlg_dma_chan_per_address_set(p_hw_dma,
                                          p_desc->src_addr,
                                          chan);
        amhw_zlg_dma_chan_mem_address_set(p_hw_dma,
                                          p_desc->dst_addr,
                                          chan);
        break;

    case AMHW_ZLG_DMA_MER_TO_PER:
        p_desc->xfercfg |= (AMHW_ZLG_DMA_CHAN_DIR_FROM_MEM |
                            AMHW_ZLG_DMA_CHAN_MEM_TO_MEM_DISABLE);
        mem_data_size   = 1 << (((p_desc->xfercfg >> 10) & 0x3u) + 3);
        trans_data_byte = p_desc->nbytes / (mem_data_size / 8);

        amhw_zlg_dma_chan_per_address_set(p_hw_dma,
                                          p_desc->dst_addr,
                                          chan);
        amhw_zlg_dma_chan_mem_address_set(p_hw_dma,
                                          p_desc->src_addr,
                                          chan);
        break;

    case AMHW_ZLG_DMA_MER_TO_MER:
        p_desc->xfercfg |= (AMHW_ZLG_DMA_CHAN_DIR_FROM_MEM |
                            AMHW_ZLG_DMA_CHAN_MEM_TO_MEM_ENABLE);

        mem_data_size   = 1 << (((p_desc->xfercfg >> 10) & 0x3u) + 3);
        trans_data_byte = p_desc->nbytes / (mem_data_size / 8);

        amhw_zlg_dma_chan_per_address_set(p_hw_dma,
                                          p_desc->dst_addr,
                                          chan);
        amhw_zlg_dma_chan_mem_address_set(p_hw_dma,
                                          p_desc->src_addr,
                                          chan);
        break;

    default:
        break;
    }

    amhw_zlg_dma_chan_tran_data_size(p_hw_dma,
                                     trans_data_byte,
                                     chan);

    amhw_zlg_dma_chan_config_set(p_hw_dma,
                                 p_desc->xfercfg,
                                 chan);

    return AM_OK;
}

/* ֹͣͨ������ */
int am_zlg_dma_chan_start (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg_dma_chan_int_enable(p_hw_dma,
                                 AMHW_ZLG_DMA_CHAN_INT_TX_CMP_MASK,
                                 chan);
    amhw_zlg_dma_chan_enable(p_hw_dma, chan, AM_TRUE);

    return AM_OK;
}

/* ֹͣͨ������ */
int am_zlg_dma_chan_stop (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg_dma_chan_int_disable(p_hw_dma,
                                  AMHW_ZLG_DMA_CHAN_INT_TX_CMP_MASK,
                                  chan);
    amhw_zlg_dma_chan_enable(p_hw_dma, chan, AM_FALSE);

    return AM_OK;
}

/* DMA�жϴ����� */
static void __dma_int_handler (void *p_arg)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    int      i;
    int      chan = 0xFF;
    uint8_t  flag = 0xFF;

    am_zlg_pfn_dma_isr_t  pfn_isr;
    void                  *p_isr_arg;

    for (i = 0 ; i < AMHW_ZLG_DMA_CHAN_CNT ; i++) {
        if (amhw_zlg_dma_chan_stat_check(p_hw_dma , AMHW_ZLG_DMA_CHAN_TX_COMP_FLAG(i))) {
            if (amhw_zlg_dma_chan_stat_check(p_hw_dma , AMHW_ZLG_DMA_CHAN_TX_HALF_FLAG(i))) {
                amhw_zlg_dma_chan_flag_clear(p_hw_dma, AMHW_ZLG_DMA_CHAN_TX_HALF_FLAG(i));
            }
            chan = i;
            if(amhw_zlg_dma_chan_stat_check(p_hw_dma , AMHW_ZLG_DMA_CHAN_TX_ERR_FLAG(i)))  {
                flag = AM_ZLG_DMA_INT_ERROR ;
                amhw_zlg_dma_chan_flag_clear(p_hw_dma, AMHW_ZLG_DMA_CHAN_TX_ERR_FLAG(i));
            } else {
                flag = AM_ZLG_DMA_INT_NORMAL ;
            }
            amhw_zlg_dma_chan_flag_clear(p_hw_dma, AMHW_ZLG_DMA_CHAN_TX_COMP_FLAG(i));
            break;
        }
    }

    if (0xFF != chan) {

        pfn_isr   = __dma_int_info[chan].pfn_isr;
        p_isr_arg = __dma_int_info[chan].p_arg;

        if (pfn_isr) {
            pfn_isr(p_isr_arg , flag);
        }
    }
}

/* ����DMA�жϷ����� */
int am_zlg_dma_isr_connect (int                     chan,
                            am_zlg_pfn_dma_isr_t    pfn_isr,
                            void                   *p_arg)
{
    if (__dma_int_map[chan] == __INT_NOT_CONNECTED) {
        __dma_int_info[chan].pfn_isr = pfn_isr;
        __dma_int_info[chan].p_arg   = p_arg;
        __dma_int_map[chan]          = chan;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/* ɾ��DMA�жϷ��������� */
int am_zlg_dma_isr_disconnect (int                     chan,
                               am_zlg_pfn_dma_isr_t    pfn_isr,
                               void                   *p_arg)
{
    if (__dma_int_map[chan] == chan) {
        __dma_int_info[chan].pfn_isr = NULL;
        __dma_int_map[chan]          = __INT_NOT_CONNECTED;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/**
 * \breif ��ȡĳͨ����ǰ����ʣ����ֽ���
 */
uint16_t am_zlg_dma_tran_data_get (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    return amhw_zlg_dma_chan_tran_data_get(p_hw_dma, chan);
}

/**
 * \brief ���ô�����ֽ���
 */
void am_zlg_dma_tran_data_size (int chan, uint32_t trans_data_byte)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg_dma_t *p_hw_dma = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg_dma_chan_tran_data_size(p_hw_dma,
                                        trans_data_byte,
                                        chan);
}

/* DMA��ʼ�� */
int am_zlg_dma_init (am_zlg_dma_dev_t           *p_dev,
                     const am_zlg_dma_devinfo_t *p_devinfo)
{
    uint32_t i = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return AM_ERROR;
    }

    p_dev->p_devinfo = p_devinfo;
    __gp_dma_dev     = p_dev;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    for (i = 0; i < AMHW_ZLG_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = __INT_NOT_CONNECTED;
    }

    for (i = p_devinfo->inum_start; i <= p_devinfo->inum_end; i++) {
        am_int_connect(i, __dma_int_handler, (void *)0);
        am_int_enable(i);
    }

    return AM_OK;
}

/* DMAȥ��ʼ�� */
void am_zlg_dma_deinit (void)
{
    am_zlg_dma_devinfo_t *p_dma_devinfo = NULL;
    amhw_zlg_dma_t       *p_hw_dma;
    
    int i = 0;

    if (NULL == __gp_dma_dev) {
        return;
    }

    p_dma_devinfo = (am_zlg_dma_devinfo_t *)__gp_dma_dev->p_devinfo;
    p_hw_dma      = (amhw_zlg_dma_t *)p_dma_devinfo->dma_reg_base;

    for (i = 0; i < AMHW_ZLG_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = 0;
        amhw_zlg_dma_chan_enable(p_hw_dma , i, AM_FALSE);
    }

    for (i = p_dma_devinfo->inum_start; i <= p_dma_devinfo->inum_end; i++) {
        am_int_disconnect(i,
                          __dma_int_handler,
                          (void *)0);

        am_int_disable(i);
    }

    if (p_dma_devinfo->pfn_plfm_deinit) {
        p_dma_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
