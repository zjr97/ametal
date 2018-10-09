/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief FM175xx LPCDģʽ
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *
 * - ʵ������
 *   1. ��ִ�в�������1 2�� ��󿨽���͹����Զ���Ƭ��⣨LPCD��ģʽ
 *   2. �������ø�Ӧ����FM175xx�豸�������������жϱ�־��ִ����Ӧ�趨������
 *   3. �ƿ���Ƭ�󣬴ﵽ�趨��AUTO_WUP_TIME��ʱ��ʱ��FM175xx�Զ��˳�LPCDģʽ���Զ����е�У��
 *
 * \par Դ����
 * \snippet demo_fm175xx_picca_lpcd_mode.c demo_fm175xx_picca_lpcd_mode
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-20  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fm175xx_picca_lpcd_mode
 * \copydoc demo_fm175xx_picca_lpcd_mode.c
 */

/** [src_demo_fm175xx_picca_lpcd_mode] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"

/**
 * \brief �����������ص�����  �û����Լ���������   �������Զ�ȡIDΪ��
 */
int8_t  picca_active_info(am_fm175xx_handle_t handle)
{
    uint8_t      tag_type[2]  = { 0 };      /* ATQA */
    uint8_t      uid[10]      = { 0 };      /* UID */
    uint8_t      uid_real_len =   0;        /* ���յ���UID�ĳ��� */
    uint8_t      sak[3]       = { 0 };      /* SAK */
    uint8_t      i;

    /* ���������  */
    if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                              (handle,
                                               AM_FM175XX_PICCA_REQ_ALL,
                                               tag_type,
                                               uid,
                                               &uid_real_len,
                                               sak)) {
        am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

        /* ��ӡUID */
        am_kprintf("UID  :");
        for (i = 0; i < uid_real_len; i++) {
            am_kprintf("%02x ", uid[i]);
        }
        am_kprintf("\n");

        /* ��ӡSAK */
        am_kprintf("SAK  :");
        for (i = 4; i <= uid_real_len; i+=3) {
            am_kprintf("%02x ", sak[(i - 4) / 3]);
        }
        am_kprintf("\n\n");
        return AM_OK;
    }else{
        return AM_ERROR;
    }
}

/**
 * \brief �û��ص�����
 *
 *  �����ж�֮�󽫻��Զ��˳�LPCDģʽ  �ٴν����û������am_fm175xx_lpcd_mode_entry
 *  ���½���LPCDģʽ
 */
static void  __fm175xx_lpcd_cb(void *p_arg)
{
    int *p_flag = (int *)p_arg;
    *p_flag =1;
}

/**
 * \brief LPCDģʽ
 */
void demo_fm175xx_picca_lpcd_mode (am_fm175xx_handle_t handle)
{
    int int_flag = 0;

    /* ���ûص���������������*/
    am_fm175xx_lpcd_cb_set(handle, __fm175xx_lpcd_cb, &int_flag);

    /* ����LPCDģʽ */
    am_fm175xx_lpcd_mode_entry(handle);

    while(1){

        am_mdelay(10);

        if(int_flag == 1){
            int_flag = 0;

            /*���ڴ˽�����Ӧ�Ĵ�����   �������Զ�ȡID��Ϊ��*/
            picca_active_info(handle);

            /* ���½���LPCDģʽ */
            am_fm175xx_lpcd_mode_entry(handle);
        }
    }
}

/** [demo_fm175xx_picca_lpcd_mode] */

/* end of file */
