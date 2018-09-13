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
 * \brief WAIT implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-09-01  tee, first implementation.
 * \endinternal
 */
#include "am_wait.h"


/******************************************************************************/

/* ʹ��ֵ������Ϣ */
#define __WAIT_VAL_INIT     0   /* ��ʼֵΪ0                    */
#define __WAIT_VAL_DONE     1   /* ʹ��am_wait_done()����ֵΪ 1 */
#define __WAIT_VAL_TIMEOUT  2   /* ��ʱʱ������ֵΪ2             */

/* ״̬���Ա�ʾ��ǰ�ȴ��ṹ��״̬ */
#define __WAIT_STAT_INIT             0   /* ��ʼ״̬            */
#define __WAIT_STAT_WAIT_ON          1   /* �ȴ�״̬            */
#define __WAIT_STAT_WAIT_ON_TIMEOUT  2   /* �ȴ�״̬������ʱ��   */

/******************************************************************************/

static void __timer_callback (void *p_arg)
{
    am_wait_t *p_wait = (am_wait_t *)p_arg;
    
    p_wait->val = __WAIT_VAL_TIMEOUT;
    
    am_softimer_stop(&p_wait->timer);
}

/******************************************************************************/

/* �ȴ��źų�ʼ�� */
int am_wait_init (am_wait_t *p_wait)
{
    if (p_wait == NULL) {
        return -AM_EINVAL;
    }
    
    p_wait->val   = __WAIT_VAL_INIT;
    p_wait->stat  = __WAIT_STAT_INIT;
    
    am_softimer_init(&p_wait->timer,__timer_callback, p_wait);
    
    return AM_OK;
}

int am_wait_on (am_wait_t *p_wait)
{
    if (p_wait == NULL) {
        return -AM_EINVAL;
    }
    
    p_wait->stat = __WAIT_STAT_WAIT_ON;
    
    while(p_wait->val == __WAIT_VAL_INIT);
    
    p_wait->val  = __WAIT_VAL_INIT;
    p_wait->stat = __WAIT_STAT_INIT;
    
    return AM_OK;
}

int am_wait_done(am_wait_t *p_wait)
{
    if (p_wait == NULL) {
        return -AM_EINVAL;
    }
    
    p_wait->val  = __WAIT_VAL_DONE;

    return AM_OK;
}

int am_wait_on_timeout(am_wait_t *p_wait, uint32_t timeout_ms)
{
    int ret;
    
    /* ��ʼ��ʱ */
    am_softimer_start(&p_wait->timer,timeout_ms);
    
    p_wait->stat = __WAIT_STAT_WAIT_ON_TIMEOUT;
    
    while(p_wait->val == __WAIT_VAL_INIT);
    
    if (p_wait->val == __WAIT_VAL_DONE) {  /* �ɹ��ȵ������ź� */
        ret = AM_OK;
    } else {                               /* ��ʱ�ź�     */
        ret = -AM_ETIME;
    }
    
    p_wait->val  = __WAIT_VAL_INIT;
    p_wait->stat = __WAIT_STAT_INIT;       /* �ص���ʼ̬   */
    
    am_softimer_stop(&p_wait->timer);
    
    return ret;
}

/* end of file */
