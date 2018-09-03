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
 * \brief �ж��ӳٴ����׼�ӿ�
 *
 *     ʵ��Ӧ���У�����ϣ��Ӳ���жϺ��������ܿ�Ľ�������ˣ��������ж�ʵ����Ҫ���
 * �ıȽϺ�ʱ�Ĺ����ŵ��ж��ӳ��д���
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "am_isr_defer.h"
 * \endcode
 *
 * \attention ��isr_deferʵ�ֿ���֧�� Cortex-Mxϵ�� MCU��ʹ��PendSV�����ӳ���ҵ
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-23  tee, first implementation
 * \endinternal
 */
 
#include "ametal.h"
#include "am_isr_defer.h"
 
/*******************************************************************************
  Locals
*******************************************************************************/
static am_jobq_handle_t           __g_isr_defer_handle = NULL;
static am_isr_defer_add_cb_t      __gpfn_trigger_cb    = NULL;
static void                      *__gp_cb_arg          = NULL;

/*******************************************************************************
  Public functions
*******************************************************************************/
void am_isr_defer_init (am_isr_defer_add_cb_t pfn_cb, void *p_arg)
{
    extern struct am_isr_defer_info *gp_isr_defer_info;
    
    __gp_cb_arg       = p_arg;
    __gpfn_trigger_cb = pfn_cb;
    
    __g_isr_defer_handle = am_jobq_queue_init(&gp_isr_defer_info->jobq_queue,
                                               gp_isr_defer_info->priority_num,
                                               gp_isr_defer_info->pri_heads,
                                               gp_isr_defer_info->p_bitmap_job);
} 

/******************************************************************************/
void am_isr_defer_job_init (am_isr_defer_job_t  *p_job,
                            am_pfnvoid_t         func,
                            void                *p_arg,
                            uint16_t             pri)
{
     am_jobq_job_init(p_job, func, p_arg, pri);
}

/******************************************************************************/
int am_isr_defer_job_add (am_isr_defer_job_t *p_job)
{
    if (__g_isr_defer_handle == NULL) {
        return -AM_EPERM;
    }
    
    am_jobq_post(__g_isr_defer_handle, p_job);
 
    if (__gpfn_trigger_cb) {
        __gpfn_trigger_cb(__gp_cb_arg);
    }
 
    return AM_OK;
}

/******************************************************************************/
int am_isr_defer_job_process (void)
{
    return am_jobq_process(__g_isr_defer_handle);
}

/* end of file */
