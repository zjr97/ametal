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
 * \brief LPC82x ��Ӧ���б��(IAP)Ӳ�������ӿ�
 *
 * IAP - ͨ��ROM�ĺ���ʵ�֣��ṩ��FLASH���в�����һϵ�нӿں�����
 * �ӿں�����Ҫ�������¼��֣�
 *     - ����д����ǰ��׼�������ӿں�����
 *     - ��RAM�������ݵ�FLASH�ӿں�����
 *     - ���������ӿں�����
 *     - �����հ׼��ӿں�����
 *     - ��ȡPartID�ӿں�����
 *     - ��ȡBOOT_VERSION�ӿں�����
 *     - ���ݱȽϽӿں�����
 *     - ���½���ISPģʽ�ӿں�����
 *     - ��ȡUID�ӿں�����
 *     - ҳ�����ӿں�����
 *
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-05  cyl, modify the namespace. 
 * - 1.01 15-09-22  aii, check.
 * - 1.00 15-07-02  oce, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_IAP_H
#define __AMHW_LPC82X_IAP_H

#include "ametal.h"
#include "am_lpc82x.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_iap
 * \copydoc amhw_lpc82x_iap.h
 * @{
 */

/** IAP ROM API���� */
typedef void (*amhw_lpc82x_iap_entry_t)(uint32_t[], uint32_t[]);

/**
 * \name IAPָ���
 * @{
 */

/** \brief ����׼������         */    
#define AMHW_LPC82X_IAP_CMD_PREPARE             50  
/** \brief ��RAM�������ݵ�FLASH */
#define AMHW_LPC82X_IAP_CMD_COPY_RAM_TO_FLASH   51  
/** \brief ������������         */
#define AMHW_LPC82X_IAP_CMD_ERASE_SECTOR        52  
/** \brief �����������         */
#define AMHW_LPC82X_IAP_CMD_BLANK_CHECK         53  
/** \brief ��ȡPartID����       */
#define AMHW_LPC82X_IAP_CMD_PARTID_READ         54  
/** \brief ��ȡBOOT_VERSION     */
#define AMHW_LPC82X_IAP_CMD_BOOT_VER_READ       55  
/** \brief ���ݱȽ�ָ��         */
#define AMHW_LPC82X_IAP_CMD_COMPARE             56  
/** \brief ���½���ISPģʽ      */
#define AMHW_LPC82X_IAP_CMD_REINVOKE_ISP        57  
/** \brief ��UID                */
#define AMHW_LPC82X_IAP_CMD_READ_UID            58  
/** \brief ҳ����ָ��           */
#define AMHW_LPC82X_IAP_CMD_ERASE_PAGE          59  

/** @} */

/**
 * \brief IAP״̬
 */
typedef enum amhw_lpc82x_iap_stat {
    
    /** \brief ָ��ִ�гɹ�          */
    AMHW_LPC82X_IAP_STAT_SUCCESS             = 0,  
    /** \brief ��Чָ��              */
    AMHW_LPC82X_IAP_STAT_INVALID_CMD         = 1,  
    /** \brief Դ��ַδ���ֶ���      */
    AMHW_LPC82X_IAP_STAT_SRC_ADDR_ERROR      = 2,  
    /** \brief Ŀ���ַ�������      */
    AMHW_LPC82X_IAP_STAT_DST_ADDR_ERROR      = 3,  
    /** \brief Դ��ַ�����ڴ�ӳ����  */
    AMHW_LPC82X_IAP_STAT_SRC_ADDR_NOT_MAPPED = 4,  
    /** \brief Ŀ���ַδ���ڴ�ӳ��  */
    AMHW_LPC82X_IAP_STAT_DST_ADDR_NOT_MAPPED = 5,  
    /** \brief �ֽڸ���ֵ����        */
    AMHW_LPC82X_IAP_STAT_COUNT_ERROR         = 6,  
    /** \brief ����ֵ����            */
    AMHW_LPC82X_IAP_STAT_INVALID_SECTOR      = 7,  
    /** \brief �����ǿ�              */
    AMHW_LPC82X_IAP_STAT_SECTOR_NOT_BLANK    = 8,  
    /** \brief ����׼��ָ��û��ִ��  */
    AMHW_LPC82X_IAP_STAT_SECTOR_NOT_PREPARED = 9,  
    /** \brief Դ��Ŀ���ַ���ݲ�ͬ  */
    AMHW_LPC82X_IAP_STAT_COMPARE_ERROR       = 10, 
    /** \brief FLASHæ״̬           */
    AMHW_LPC82X_IAP_STAT_BUSY                = 11
    
} amhw_lpc82x_iap_stat_t;


/**
 * \brief �ú�������ֱ�ӵ���ROM API����
 *
 * \param[in]  cmd_param     : ָ���������
 * \param[out] status_result : ָ��ִ�н�����������
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iap_entry (uint32_t cmd_param[], uint32_t status_result[])
{
    ((amhw_lpc82x_iap_entry_t) LPC82X_IAP_ENTRY_LOCATION)(cmd_param, 
                                                          status_result);
}

/**
 * \brief д����ǰ������׼������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ���������ű�����ڻ������ʼ������
 *
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_prepare (uint32_t start_sec, 
                                                uint32_t end_sec);

/**
 * \brief ����RAM��������FLASH�У��൱��FLASHд����
 *
 * \param[in] dst_addr : Ŀ��FLASH��ַ��Ӧ���� 256 �ֽڶ���
 * \param[in] src_addr : ����ԴRAM�ĵ�ַ��Ӧ�����ֶ���
 * \param[in] nbytes   : ���Ƶ����ݸ���, Ӧ���� 256��512 ��1024 ���� 4096
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note �ú�����������FLASH���������ڵ��øú���ǰ����
 *        amhw_lpc82x_iap_prepare()��������д��׼������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_copy (uint32_t dst_addr,
                                             uint32_t src_addr,
                                             uint32_t nbytes);

/**
 * \brief ��������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ���������ű�����ڻ������ʼ�����ţ��ú�����������FLASH���������ڵ��ø�
 *       ����ǰ����amhw_lpc82x_iap_prepare()��������׼������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_erase_sector (uint32_t start_sec,
                                                     uint32_t end_sec);

/**
 * \brief ҳ��������ҳ���ҳ����
 *
 * \param[in] start_page : ��ʼҳ��
 * \param[in] end_page   : ����ҳ��
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ����ҳ�ű�����ڻ������ʼҳ�ţ��ú�����������FLASH���������ڵ��ø�
 *       ����ǰ����amhw_lpc82x_iap_prepare()��������׼������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_erase_page (uint32_t start_page,
                                                   uint32_t end_page);

/**
 * \brief �������������������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 *
 * \return IAPָ��ִ�е�״̬��ִ������ɹ�(AMHW_LPC82X_IAP_STAT_SUCCESS)��������Ϊ�ա�
 *
 * \note ���������ű�����ڻ������ʼ������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_blank_check (uint32_t start_sec, 
                                                    uint32_t end_sec);

/**
 * \brief ��Part IDֵ
 * \return Part IDֵ
 */
uint32_t amhw_lpc82x_iap_part_id_read (void);

/**
 * \brief ��boot code�汾��
 * \return boot code�汾��, �汾�Ÿ�ʽ��<�ֽ�1(���汾��)>.<�ֽ�0(�ΰ汾��)>
 */
uint16_t amhw_lpc82x_iap_boot_ver_read (void);

/**
 * \brief �Ƚ������ڴ��е�����
 *
 * \param[in] dst_addr : ���ݱȽϵ�����Ŀ���ַ��������FLASH��ַ����RAM��ַ
 * \param[in] src_addr : ���ݱȽϵ�����Դ��ַ��������FLASH��ַ����RAM��ַ
 * \param[in] nbytes   : ���ݱȽϵĸ���
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ��ַӦ�����ֶ��룬�ֽڸ���Ӧ����4��������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_compare (uint32_t dst_addr,
                                                uint32_t src_addr,
                                                uint32_t nbytes);

/**
 * \brief ͨ��IAP�� boot loader�����л���ISPģʽ
 * \return ��
 */
void amhw_lpc82x_iap_reinvoke_isp (void);

/**
 * \brief ��������UID(��128λ)
 * \param[out] uid :
 *              - uid[0] : ��һ��32λ���� (��͵�ַ�����λ0~31��
 *              - uid[1] : �ڶ���32λ����
 *              - uid[2] : ������32λ����
 *              - uid[3] : ���ĸ�32λ����
 * \return IAPָ��ִ�е�״̬
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_unique_id_read (uint32_t uid[4]);

/**
 * @} amhw_if_iap
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LPC82X_IAP_H */

/* end of files */
