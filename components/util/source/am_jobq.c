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
 * \brief job queue library
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "am_jobq.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-18  tee, first implementation
 * \endinternal
 */
#include "am_common.h"
#include "am_jobq.h"
#include "am_int.h"
#include "am_bitops.h"

/*******************************************************************************
  �ڲ�ʹ�ú궨��
*******************************************************************************/

/* ��־�����ѱ��������                        */
#define __JOBQ_JOB_ENQUEUED      0x100

/* ��־��ǰ����������ڴ�����                   */
#define __JOBQ_FLG_RUNNING   0x01

/** \brief ��λ�����ȼ��е���Ӧλ  */
#define __JOBQ_BITMAP_GRP_SET(bitmap_grp, pri) \
               bitmap_grp |= (1 << ((pri) >> 5))

/** \brief ���������ȼ��е���Ӧλ  */
#define __JOBQ_BITMAP_GRP_CLR(bitmap_grp, pri) \
               bitmap_grp &= ~(1 << ((pri) >> 5))
               
/** \brief ��λ�������ȼ�����Ӧλ  */
#define __JOBQ_BITMAP_JOB_SET(bitmap_job, pri) \
               bitmap_job[(pri) >> 5] |= (1 << ((pri) & 0x1F))

/** \brief �����������ȼ�����Ӧλ  */
#define __JOBQ_BITMAP_JOB_CLR(bitmap_job, pri) \
               bitmap_job[(pri) >> 5] &= ~(1 << ((pri) & 0x1F))


/******************************************************************************/

static const unsigned char __ffs8_table[256] = {
    0, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    8, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
};

/* 
 * �ú�����ȡ��һ���޷��������������λ1����λ�ã��� 0x01 ����λ��Ϊ 1
 */
int __jobq_ffs (unsigned int x )
{
    int pos = 0;  /* ��¼���λΪ1��λ�ã���ʼΪ0  */

    if ( !(x & 0xffff) ) {  /* ��16λΪ0�����λ1�����ڸ�16λ */
        x >>= 16;
        pos += 16;
    }
    
    if ( !(x & 0xff) ) {   /* 16λ�У���8λΪ0�����λ1�����ڸ�8λ */
        x >>= 8;
        pos += 8;
    }
    
    x &= 0xff;
    pos +=  __ffs8_table[x]; /* ����ȡλ�� */
    return pos;
}

/******************************************************************************/
am_jobq_handle_t am_jobq_queue_init (am_jobq_queue_t     *p_jobq_queue,
                                     unsigned int         pri_num,
                                     struct am_list_head *p_heads,
                                     unsigned int        *p_bitmap_job)
{
    int i;
    int key;

    uint8_t grp_num;
    
    if ((p_jobq_queue == NULL) || (p_heads == NULL) || (p_bitmap_job == NULL)) {
        return NULL;
    }

    grp_num = (pri_num + 31) >> 5;
    
    for (i = 0; i < grp_num; i++) {
        p_bitmap_job[i] = 0;
    }

    /* ��ʼ���������ȼ�����������ͷ */
    for (i = 0; i < pri_num; i++) {
        am_list_head_init(&p_heads[i]);
    }
    
    key = am_int_cpu_lock();

    p_jobq_queue->bitmap_grp   = 0;
    p_jobq_queue->p_heads      = p_heads;
    p_jobq_queue->pri_num      = pri_num;
    p_jobq_queue->p_bitmap_job = p_bitmap_job;
 
    am_int_cpu_unlock(key);
    
    return p_jobq_queue;
}

/******************************************************************************/

void am_jobq_job_init (am_jobq_job_t  *p_job,
                       am_pfnvoid_t    func,
                       void           *p_arg,
                       uint16_t        pri)
{
    p_job->func  = func;
    p_job->p_arg = p_arg;
    p_job->pri   = pri;
    p_job->flags = 0;
    
    am_list_head_init(&p_job->node);
}

/******************************************************************************/
int am_jobq_post (am_jobq_queue_t *p_jobq_queue, am_jobq_job_t *p_job)
{
    uint32_t pri;
    int      key;

    if (p_jobq_queue == NULL || p_job == NULL || p_job->func == NULL) {
        return -AM_EINVAL;
    }

    key = am_int_cpu_lock();

    /* ��ʱʹ�øñ��������־      */
    pri = p_job->flags;
    
    /* ����û���ڶ����У��Ž������ */
    if ((pri & (__JOBQ_JOB_ENQUEUED)) == 0) {
        
        p_job->flags = pri | __JOBQ_JOB_ENQUEUED;

        /* extract just the priority field */
        pri = p_job->pri > (p_jobq_queue->pri_num - 1) ?
                           (p_jobq_queue->pri_num - 1) :
                            p_job->pri;
        
        __JOBQ_BITMAP_GRP_SET(p_jobq_queue->bitmap_grp, pri);
        __JOBQ_BITMAP_JOB_SET(p_jobq_queue->p_bitmap_job, pri);
        
        /* �������������ȼ���������β�� */
        am_list_add_tail(&p_job->node, &p_jobq_queue->p_heads[pri]);

        am_int_cpu_unlock(key);

        return AM_OK;
    }

    am_int_cpu_unlock(key);

    return -AM_EBUSY;
}
 
/******************************************************************************/
int am_jobq_process (am_jobq_queue_t *p_jobq_queue)
{
    int             key;
    am_pfnvoid_t    func;
    void           *p_arg;

    struct am_list_head *p_q;
    am_jobq_job_t       *p_job;
 
    if (p_jobq_queue == NULL) {
        return -AM_EINVAL;
    }
    
    /* ������������ڴ����� */
    if ((p_jobq_queue->flags & __JOBQ_FLG_RUNNING) != 0) {
        return -AM_EBUSY;
    }
    
    key = am_int_cpu_lock();
   
    p_jobq_queue->flags |= __JOBQ_FLG_RUNNING;

    am_int_cpu_unlock(key);

    while(1) {

        unsigned int pri;

        key = am_int_cpu_lock();
        
        /* ���������κ����� */
        if (p_jobq_queue->bitmap_grp == 0) {
            p_jobq_queue->flags &= ~__JOBQ_FLG_RUNNING;
            am_int_cpu_unlock(key);
            return AM_OK;
        }
        
        /* �ҵ�������������ȼ���ߵ���     */
        pri = __jobq_ffs(p_jobq_queue->bitmap_grp) - 1;
 
        /* �ҵ����ȼ���ߵ����е�������ȼ� */
        pri = __jobq_ffs(p_jobq_queue->p_bitmap_job[pri]) - 1 + (pri << 5);
 
        /* Remove the job from the appropriate queue */
        p_q = &p_jobq_queue->p_heads[pri];

        /* ȡ����һ������ */
        p_job = am_list_entry(p_q->next, am_jobq_job_t, node);
        
        /* �Ӷ�����ɾ�������� */
        am_list_del_init(p_q->next);
        
        /* �����ȼ�����Ϊ�գ�ɾ����Ӧ���ȼ���־λ */
        if (am_list_empty_careful(p_q)) {
            __JOBQ_BITMAP_JOB_CLR(p_jobq_queue->p_bitmap_job, pri);
            
            /* �������Ѿ�û������ */
            if (p_jobq_queue->p_bitmap_job[pri >> 5] == 0) {
                __JOBQ_BITMAP_GRP_CLR(p_jobq_queue->bitmap_grp, pri);
            }
        }

        p_job->flags &= ~__JOBQ_JOB_ENQUEUED;

        func  = p_job->func;
        p_arg = p_job->p_arg;
        
        am_int_cpu_unlock(key);

        if (func) {
            func(p_arg);
        }
    }
}

/* end of file */
