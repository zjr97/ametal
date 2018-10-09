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
 * \brief DMA �ӿ�ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-29  mem, modified.
 * - 1.00 15-07-12  win, first implementation.
 * \endinternal
 */

/*******************************************************************************
  includes
*******************************************************************************/
#include "ametal.h"
#include "am_int.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc82x_dma.h"
#include "hw/amhw_lpc82x_inmux.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/* DMAͨ��״̬�Ƿ��Ծ  */
#define __DMA_CHAN_IS_ACTIVE(p_hw_dma,chan) \
           (amhw_lpc82x_dma_chan_isactive((p_hw_dma), (chan))       || \
            amhw_lpc82x_dma_chan_iserror((p_hw_dma), (chan))        || \
            amhw_lpc82x_dma_chan_inta_isactive((p_hw_dma), (chan))  || \
            amhw_lpc82x_dma_chan_intb_isactive((p_hw_dma), (chan)))
                          
/* ͨ��������δʹ�ñ�־ */
#define __DMA_INVALID_MAP            0xFF

/* ������״̬���� */
#define __DMA_CTR_STAT_INIT          0  /* ��ʼ״̬��δ����       */
#define __DMA_CTR_STAT_SETUP         1  /* DMAͨ���ѽ���          */

/* EXT_INFO����λ���� */
#define __DMA_EXT_INFO_HWTRIG_POS    0  /* �����Ƿ�����Ӳ������   */
#define __DMA_EXT_INFO_REPEAT_POS    1  /* �����Ƿ��������ظ����� */
#define __DMA_EXT_INFO_PERIPH_REQ    2  /* �����Ƿ��������������� */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief ָ��DMA�豸��ָ�� */
am_lpc82x_dma_dev_t *__gp_dma_dev = NULL;


/*******************************************************************************
  ����ʵ��
*******************************************************************************/

/** \brief ��ȡͨ���Ĵ�������� */        
am_lpc82x_dma_controller_t* am_lpc82x_dma_controller_get (uint8_t  chan,
                                                          uint32_t opts)
{
    int     key;
    int     i;
    int     slot = -1;
    uint8_t                          trig_out;
    amhw_lpc82x_inmux_dma_trig_src_t trig_src;
    
    am_lpc82x_dma_controller_t      *p_ctr      = NULL;
    const am_lpc82x_dma_devinfo_t   *p_devinfo  = NULL;
    amhw_lpc82x_dma_t               *p_hw_dma   = NULL;
    amhw_lpc82x_inmux_t             *p_hw_inmux = NULL;
    
    if (__gp_dma_dev == NULL || chan > (AMHW_LPC82X_DMA_CHAN_CNT -1 )) {
        return NULL;
    }
    
    p_devinfo  = __gp_dma_dev->p_devinfo; 
    p_hw_dma   = (amhw_lpc82x_dma_t   *)p_devinfo->dma_regbase;
    p_hw_inmux = (amhw_lpc82x_inmux_t *)p_devinfo->inmux_regbase;
    
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    /* ͨ���������Ѿ������� */
    if (p_devinfo->p_controller_map[chan] != __DMA_INVALID_MAP) {
        
        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
        return NULL;
    }
    
    /* ���ҿ��п�������Դ */
    for (i = 0; i < p_devinfo->chan_count; i++) {
        if (p_devinfo->p_controller[i].state == __DMA_CTR_STAT_INIT) {
            slot = i;       /* �ҵ����һ��ͨ�������� */
            break;
        }
    }
    
    if (slot == -1) {

        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
        return NULL;
    }
    
    /* ��¼�ҵ����һ��DMA��������Ϣ */
    p_devinfo->p_controller_map[chan] = slot;
    p_ctr                             = &p_devinfo->p_controller[slot];
    
    p_ctr->chan          = chan;
    p_ctr->state         = __DMA_CTR_STAT_SETUP;
    p_ctr->ext_info      = 0;
    p_ctr->pfn_callback  = NULL;
    
    /* ��CPU�ж� */
    am_int_cpu_unlock(key);
    
    /* ������Ӳ������ */
    if ((opts & AMHW_LPC82X_DMA_CHAN_HWTRIG_EN) != 0 ) {
        
        /* ��¼������Ӳ������ */
        AM_BIT_SET(p_ctr->ext_info, __DMA_EXT_INFO_HWTRIG_POS);
        
        /* ����Ӳ������Դ */
        trig_src = (amhw_lpc82x_inmux_dma_trig_src_t)AM_BITS_GET(opts, 19, 4);
        amhw_lpc82x_inmux_dma_trig_set(p_hw_inmux, chan, trig_src);
        AM_BIT_CLR_MASK(opts, AM_SBF(0x0F, 19));
    }
    
    trig_out = (uint8_t)AM_BITS_GET(opts, 23, 2);
    
    /* ����DMA���triger���� */
    if (trig_out != 0) {
        amhw_lpc82x_inmux_dma_mux_set(p_hw_inmux, trig_out, chan);
        AM_BIT_CLR_MASK(opts, AM_SBF(0x03, 23));
    }
    
    if ((opts & AMHW_LPC82X_DMA_CHAN_PERIPH_REQ_EN) != 0) {

        /* ��¼�������������� */
        AM_BIT_SET(p_ctr->ext_info, __DMA_EXT_INFO_PERIPH_REQ);

        /*�������������ʹ�ܡ�*/
        AM_BIT_CLR_MASK(opts, 1);
    }

    /*�����������Ϣ */
    amhw_lpc82x_dma_chan_cfg_set(p_hw_dma, chan, opts);
    
    /* ʹ��ͨ����ͨ���ж�, ׼����ʼDMA���� */
    amhw_lpc82x_dma_chan_int_enable(p_hw_dma, chan);
    amhw_lpc82x_dma_chan_enable(p_hw_dma, chan);
    
    return p_ctr;
}

/**
 * \brief ��ֹ�������Ĵ��� 
 */
int am_lpc82x_dma_controller_abort (am_lpc82x_dma_controller_t *p_ctr)
{
    uint8_t            chan;
    amhw_lpc82x_dma_t *p_hw_dma = NULL;
    
    if (p_ctr == NULL || p_ctr->state == __DMA_CTR_STAT_INIT) {
        return -AM_EINVAL;
    }
    
    if (__gp_dma_dev == NULL) {
        return -AM_ENXIO;
    }
    
    chan     = p_ctr->chan;
    p_hw_dma = (amhw_lpc82x_dma_t*)__gp_dma_dev->p_devinfo->dma_regbase;
    
    amhw_lpc82x_dma_chan_int_disable(p_hw_dma, chan);
    amhw_lpc82x_dma_chan_disable(p_hw_dma, chan);

    /* �ȴ�ͨ������unbusy */
    while (amhw_lpc82x_dma_chan_isbusy(p_hw_dma, chan));

    /* ��ֹͨ������ */
    amhw_lpc82x_dma_chan_abort(p_hw_dma, chan);
    
    /* ���жϱ�־ */
    amhw_lpc82x_dma_chan_inta_clr(p_hw_dma, chan);
    amhw_lpc82x_dma_chan_intb_clr(p_hw_dma, chan);
    amhw_lpc82x_dma_chan_error_clr(p_hw_dma, chan);

    /* ʹ��ͨ����ͨ���ж� */
    amhw_lpc82x_dma_chan_int_enable(p_hw_dma, chan);
    amhw_lpc82x_dma_chan_enable(p_hw_dma, chan);
    
    p_ctr->pfn_callback = NULL;
    
    return AM_OK;
}

/**
 * \brief �ͷŴ�������� 
 */
int am_lpc82x_dma_controller_release (am_lpc82x_dma_controller_t *p_ctr)
{
    int key ;
    
    const am_lpc82x_dma_devinfo_t *p_devinfo  = NULL;
    amhw_lpc82x_dma_t             *p_hw_dma   = NULL;
    
    /* �ر�CPU�ж� */  
    key = am_int_cpu_lock();
    
    if (p_ctr == NULL || p_ctr->state == __DMA_CTR_STAT_INIT) {
        am_int_cpu_unlock(key);
        return -AM_EINVAL; 
    }
    
    p_devinfo = __gp_dma_dev->p_devinfo;
    p_hw_dma  = (amhw_lpc82x_dma_t*)p_devinfo->dma_regbase;
    
    /* DMA���ڹ����������ͷ� */
    if (__DMA_CHAN_IS_ACTIVE(p_hw_dma, p_ctr->chan)) {
        am_int_cpu_unlock(key);
        return -AM_EPERM;
    }
    
    p_devinfo->p_controller_map[p_ctr->chan]  = __DMA_INVALID_MAP;
    
    p_ctr->chan          = 0;
    p_ctr->state         = __DMA_CTR_STAT_INIT;
    p_ctr->ext_info      = 0;
    p_ctr->pfn_callback  = NULL;
    
    p_ctr                = NULL;

    /* ��CPU�ж� */ 
    am_int_cpu_unlock(key);
    
    return AM_OK;
}

/**
 * \brief ����transfer�ṹ�� 
 */
int am_lpc82x_dma_transfer_build (am_lpc82x_dma_transfer_t *p_trans,
                                  uint32_t                  src_addr,
                                  uint32_t                  dst_addr,
                                  uint16_t                  nbytes,
                                  uint16_t                  flags)
{
    uint8_t width_byte = (1 << AM_BITS_GET(flags, 0, 2));
    
    if (!AM_ALIGNED(src_addr, width_byte) ||
        !AM_ALIGNED(dst_addr, width_byte) ||
        !AM_ALIGNED(nbytes,   width_byte) ||
        nbytes == 0) {
        return -AM_EINVAL;
    }
    
    p_trans->src_addr = src_addr;
    p_trans->dst_addr = dst_addr;
    p_trans->nbytes   = nbytes;
    p_trans->flags    = flags;
    
    return AM_OK;
}

/**
 * \brief DMA���� 
 */
int am_lpc82x_dma_transfer (am_lpc82x_dma_controller_t *p_ctr,
                            am_lpc82x_dma_transfer_t   *p_trans,
                            am_lpc82x_dma_complete_cb_t pfn_callback,
                            void                       *p_arg)
{
    int         state;
    uint32_t    flags = 0;
    
    am_lpc82x_dma_xfer_desc_t xfer_desc;
    
    if (p_ctr == NULL || p_trans == NULL || p_trans->nbytes == 0) {
        return -AM_EINVAL;
    }

    /* width */
    flags |= AM_SBF(AM_BITS_GET(p_trans->flags, 0, 2), 8);
    
    /* src_inc */
    flags |= AM_SBF(AM_BITS_GET(p_trans->flags, 2, 2), 12);
    
    /* dst_inc */
    flags |= AM_SBF(AM_BITS_GET(p_trans->flags, 4, 2), 14);
    
    /* ʹ��A�жϺ����������ñ�־ */
    flags |= AM_LPC82X_DMA_XFER_SETINTA | AM_LPC82X_DMA_XFER_VALID;
    
    /* ���û��ʹ��Ӳ��������ʹ��������� */
    if (AM_BIT_GET(p_ctr->ext_info,
                   __DMA_EXT_INFO_HWTRIG_POS) == AM_FALSE) {

        flags |= AM_LPC82X_DMA_XFER_SWTRIG;
    }
    
    /* �ظ����䣬ʹ���Զ����أ������ӵ����� */
    if((p_trans->flags & AM_LPC82X_DMA_TRANS_REPEAT) != 0) {

        flags |= AM_LPC82X_DMA_XFER_RELOAD;
        AM_BIT_SET(p_ctr->ext_info, __DMA_EXT_INFO_REPEAT_POS);

    } else {
        
        /* ���δ��䣬������ɺ����triger��־ */
        flags |= AM_LPC82X_DMA_XFER_CLRTRIG;
    }
    
    /* ����ͨ�������� */
    state = am_lpc82x_dma_xfer_desc_build(&xfer_desc,        /* ͨ��������       */
                                          p_trans->src_addr, /* Դ�����ݻ�����   */
                                          p_trans->dst_addr, /* Ŀ������ݻ����� */
                                          p_trans->nbytes,   /* �����ֽ���       */
                                          flags);            /* ��������         */
    if (state != AM_OK) {
        return state;
    }
    
    return am_lpc82x_dma_xfer_desc_startup(p_ctr,
                                           &xfer_desc,
                                           pfn_callback,
                                           p_arg);
}

/**
 * \brief �������������� 
 */
int am_lpc82x_dma_xfer_desc_build (am_lpc82x_dma_xfer_desc_t *p_desc,
                                   uint32_t                  src_addr,
                                   uint32_t                  dst_addr,
                                   uint32_t                  nbytes,
                                   uint32_t                  flags)
{
    uint32_t xfer_cnt;
    uint32_t width_byte = (1 << AM_BITS_GET(flags, 8, 2));
    uint32_t src_inc    = AM_BITS_GET(flags, 12, 2);
    uint32_t dst_inc    = AM_BITS_GET(flags, 14, 2);
    
    /*
     * 32λ�������λҪΪ0(4�ֽڶ���)��16λ�����һλҪΪ0(2�ֽڶ���) 
     */
    if (!AM_ALIGNED(src_addr, width_byte) ||
        !AM_ALIGNED(dst_addr, width_byte) ||
        !AM_ALIGNED(nbytes,   width_byte) ||
        nbytes == 0) {
        return -AM_EINVAL;
    }

    xfer_cnt = nbytes / width_byte - 1;
    AM_BITS_SET(flags, 16, 10, xfer_cnt);

    p_desc->xfercfg = flags;

    p_desc->src_end_addr = (src_inc) ? (src_addr + nbytes - width_byte) :
                                        src_addr;
    p_desc->dst_end_addr = (dst_inc) ? (dst_addr + nbytes - width_byte) :
                                        dst_addr;
    p_desc->link = 0;

    return AM_OK;
}

/**
 * \brief ������������������ 
 */
int am_lpc82x_dma_xfer_desc_link (am_lpc82x_dma_xfer_desc_t *p_desc,
                                  am_lpc82x_dma_xfer_desc_t *p_next)
{   
    if (p_desc == NULL || 
        (p_next != 0 && !AM_ALIGNED(p_next, 16))) {  /* ����Ƿ�16�ֽڶ��� */
        return -AM_EINVAL;
    }
    
    p_desc->link = (uint32_t)p_next;
    return AM_OK;
}

/**
 * \brief ʹ��xfer_disc��ʽ��������
 */ 
int am_lpc82x_dma_xfer_desc_startup (am_lpc82x_dma_controller_t  *p_ctr,
                                     am_lpc82x_dma_xfer_desc_t   *p_desc,
                                     am_lpc82x_dma_complete_cb_t  pfn_callback,
                                     void                        *p_arg)
{
    uint8_t chan;
    
    int key;
    
    am_lpc82x_dma_xfer_desc_t   *p_desc_tmp   = NULL;
    amhw_lpc82x_dma_t           *p_hw_dma   = NULL;
    
    if (p_ctr        == NULL || 
        p_desc       == NULL || 
        p_ctr->state == __DMA_CTR_STAT_INIT) {
        return -AM_EINVAL;
    }
        
    if (__gp_dma_dev == NULL) {
        return -AM_ENXIO;
    }
    
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();
    
    chan       = p_ctr->chan;
    p_hw_dma   = (amhw_lpc82x_dma_t*)__gp_dma_dev->p_devinfo->dma_regbase;
    
    /* �жϵ�ǰͨ���Ƿ�ʹ������������,���ʹ�ܣ����Ƚ�����������, �����жϵ�ǰ��ͨ��״̬ */
    if (AM_BIT_GET(p_ctr->ext_info, __DMA_EXT_INFO_PERIPH_REQ) == AM_FALSE) {

    if(__DMA_CHAN_IS_ACTIVE(p_hw_dma, chan)){

      /* ��CPU�ж� */
      am_int_cpu_unlock(key);
      return -AM_EBUSY;
    }
    }

    /* �жϵ�ǰͨ���Ƿ���Ҫ������Ӧͨ����������*/
    if (AM_BIT_GET(p_ctr->ext_info, __DMA_EXT_INFO_PERIPH_REQ)) {

      if (amhw_lpc82x_dma_chan_periph_is_enable(p_hw_dma, p_ctr->chan) == AM_FALSE) {
          amhw_lpc82x_dma_chan_periph_enable(p_hw_dma, p_ctr->chan);
      }
    }
    
    p_desc_tmp = (am_lpc82x_dma_xfer_desc_t *)
                  amhw_lpc82x_dma_chan_desc_addr_get(p_hw_dma, chan);
    
    p_ctr->p_arg             = p_arg;
    p_ctr->pfn_callback      = pfn_callback;

    p_desc_tmp->xfercfg      = p_desc->xfercfg;
    p_desc_tmp->src_end_addr = p_desc->src_end_addr;
    p_desc_tmp->dst_end_addr = p_desc->dst_end_addr;
    p_desc_tmp->link         = p_desc->link;
    
    /* ʹ�����ظ����䣬���ӵ��Լ���transfer�������ò��и����� */
    if(AM_BIT_GET(p_ctr->ext_info, __DMA_EXT_INFO_REPEAT_POS)) {

        am_lpc82x_dma_xfer_desc_link(p_desc_tmp, p_desc_tmp);
        AM_BIT_CLR(p_ctr->ext_info, __DMA_EXT_INFO_REPEAT_POS);
    }
    
    amhw_lpc82x_dma_chan_xfercfg_set(p_hw_dma, chan, p_desc_tmp->xfercfg);
    
    /* ��CPU�ж� */
    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief DMA �жϴ����� 
 */
static void __dma_int_handler (void *p_arg)
{
    int      i;
    int      slot = -1;
    int      chan = -1;
    int      stat = 0;
    uint32_t inta, intb, error;
    
    am_lpc82x_dma_controller_t    *p_ctr     = NULL;
    const am_lpc82x_dma_devinfo_t *p_devinfo = __gp_dma_dev->p_devinfo;
    amhw_lpc82x_dma_t             *p_hw_dma  = (amhw_lpc82x_dma_t*)p_devinfo->dma_regbase;
    
    inta   = amhw_lpc82x_dma_inta_flags_get(p_hw_dma);
    intb   = amhw_lpc82x_dma_intb_flags_get(p_hw_dma);
    error  = amhw_lpc82x_dma_error_flags_get(p_hw_dma);

    /* �����־ */
    if ((error & 0x3FFFF) != 0) {
        for (i = 0; i < AMHW_LPC82X_DMA_CHAN_CNT; i++) {
            if (error & AM_BIT(i)) {
                chan = i;
                amhw_lpc82x_dma_chan_error_clr(p_hw_dma, chan);
                amhw_lpc82x_dma_chan_xfercfg_set(p_hw_dma, chan, 0);
                stat = AM_LPC82X_DMA_STAT_INTERR;
                break;
            }
        }
    } else if ((inta & 0x3FFFF) != 0) {
        for (i = 0; i < AMHW_LPC82X_DMA_CHAN_CNT; i++) {
            if (inta & AM_BIT(i)) {
                chan = i;
                amhw_lpc82x_dma_chan_inta_clr(p_hw_dma, chan);
                stat = AM_LPC82X_DMA_STAT_INTA;
                break;
            }
        } 
    } else if ((intb & 0x3FFFF) != 0) {
        for (i = 0; i < 18; i++) {
            if (intb & AM_BIT(i)) {
                chan = i;
                amhw_lpc82x_dma_chan_intb_clr(p_hw_dma, chan);
                stat = AM_LPC82X_DMA_STAT_INTB;
                break;
            }
        }
        
    }
    
    if (chan == -1) {
        return;
    }
    
    slot = p_devinfo->p_controller_map[chan];
    
    if (slot == __DMA_INVALID_MAP) {
        return;
    }
    
    p_ctr = &(p_devinfo->p_controller)[slot];
    
    if (p_ctr->pfn_callback) {
        p_ctr->pfn_callback(p_ctr->p_arg, stat);
    }
    
    /* ���DMAͨ�����У��ûص�����ΪNULL */
    if (!__DMA_CHAN_IS_ACTIVE(p_hw_dma, chan)) {
        p_ctr->pfn_callback = NULL;
    }
}

/**
 * \brief DMA ��ʼ�� 
 */
int am_lpc82x_dma_init (am_lpc82x_dma_dev_t     *p_dev,
                  const am_lpc82x_dma_devinfo_t *p_devinfo)
{
    int i;
    int state;
    amhw_lpc82x_dma_t *p_hw_dma  =  NULL;
    
    if (p_dev                       == NULL      || 
        p_devinfo                   == NULL      ||
        p_devinfo->p_controller_map == NULL      ||
        p_devinfo->p_controller     == NULL      ||
        p_devinfo->inmux_regbase    == 0         || 
        p_devinfo->dma_regbase      == 0         ||
        p_devinfo->chan_count       == 0         ||
        !AM_ALIGNED(p_devinfo->p_xfer_base, 512)) {
        return -AM_EINVAL;
    }
    
    /* �豸�Ѿ���ʼ�� */
    if (__gp_dma_dev != NULL) {
        return -AM_EPERM;
    }

    for (i = 0; i < AMHW_LPC82X_DMA_CHAN_CNT; i++) {
        p_devinfo->p_controller_map[i] = __DMA_INVALID_MAP;
    }
    
    for (i = 0; i < p_devinfo->chan_count; i++) {
        p_devinfo->p_controller[i].chan          = 0;
        p_devinfo->p_controller[i].state         = __DMA_CTR_STAT_INIT;
        p_devinfo->p_controller[i].ext_info      = 0;
        p_devinfo->p_controller[i].pfn_callback  = NULL;
    }
    
    state = am_int_connect(p_devinfo->inum, __dma_int_handler, (void *)0);
    if (state != AM_OK) {
       return  state;
    }

    state = am_int_enable(p_devinfo->inum);
    if (state != AM_OK) {
       return  state;
    }
    
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }
    
    p_dev->p_devinfo = p_devinfo;
    __gp_dma_dev     = p_dev;
    p_hw_dma         = (amhw_lpc82x_dma_t *)p_devinfo->dma_regbase;
    
    amhw_lpc82x_dma_enable(p_hw_dma);
    amhw_lpc82x_dma_sram_addr_set(p_hw_dma, (uint32_t)p_devinfo->p_xfer_base);
    
    return AM_OK;
}

/**
 * \brief DMA ȥ��ʼ�� 
 */
void am_lpc82x_dma_deinit (void)
{
    int i;
    const am_lpc82x_dma_devinfo_t *p_devinfo;
    
    if (__gp_dma_dev == NULL) {
        return;
    }
    
    p_devinfo = __gp_dma_dev->p_devinfo;
    
    for (i = 0; i < AMHW_LPC82X_DMA_CHAN_CNT; i++) {
        p_devinfo->p_controller_map[i] = __DMA_INVALID_MAP;
    }
    
    for (i = 0; i < p_devinfo->chan_count; i++) {
        p_devinfo->p_controller[i].chan          = 0;
        p_devinfo->p_controller[i].state         = __DMA_CTR_STAT_INIT;
        p_devinfo->p_controller[i].ext_info      = 0;
        p_devinfo->p_controller[i].pfn_callback  = NULL;
    }
    
    am_int_disconnect(p_devinfo->inum, __dma_int_handler, (void *)0);
    am_int_disable(p_devinfo->inum);
    amhw_lpc82x_dma_disable((amhw_lpc82x_dma_t *)p_devinfo->dma_regbase);
    
    if (p_devinfo->pfn_plfm_deinit) {
        p_devinfo->pfn_plfm_deinit();
    }
    
    __gp_dma_dev = NULL;
}

/* end of file */
