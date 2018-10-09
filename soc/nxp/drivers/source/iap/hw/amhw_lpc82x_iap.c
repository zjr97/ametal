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
 * \brief ��Ӧ���б��(IAP) HW��ʵ��.
 * 
 * \internal
 * \par Modification history
 * - 1.02 15-12-05  cyl, modify the namespace.
 * - 1.01 15-09-22  aii, check.
 * - 1.00 15-07-05  oce, first implementation.
 * \endinternal
 */
 
#include "ametal.h"
#include "hw/amhw_lpc82x_iap.h"

/*******************************************************************************
  Public functions
*******************************************************************************/

/**
 * \brief д����ǰ������׼������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_prepare (uint32_t start_sec, 
                                                uint32_t end_sec)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_PREPARE;
    command[1] = start_sec;
    command[2] = end_sec;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief ����RAM��������FLASH�У��൱��FLASHд����
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_copy (uint32_t dst_addr, 
                                             uint32_t src_addr, 
                                             uint32_t nbytes)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_COPY_RAM_TO_FLASH;
    command[1] = dst_addr;
    command[2] = (uint32_t)src_addr;
    command[3] = nbytes;
    command[4] = 0;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief ��������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_erase_sector (uint32_t start_sec, 
                                                     uint32_t end_sec)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_ERASE_SECTOR;
    command[1] = start_sec;
    command[2] = end_sec;
    command[3] = 0;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief ҳ��������ҳ���ҳ����
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_erase_page (uint32_t start_page, 
                                                   uint32_t end_page)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_ERASE_PAGE;
    command[1] = start_page;
    command[2] = end_page;
    command[3] = 0;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief �������������������
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_blank_check (uint32_t start_sec, 
                                                    uint32_t end_sec)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_BLANK_CHECK;
    command[1] = start_sec;
    command[2] = end_sec;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief ��Part IDֵ
 */
uint32_t amhw_lpc82x_iap_part_id_read (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_PARTID_READ;
    
    amhw_lpc82x_iap_entry(command, result);

    return result[1];
}

/**
 * \brief ��boot code�汾��
 */
uint16_t amhw_lpc82x_iap_boot_ver_read (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_BOOT_VER_READ;
    
    amhw_lpc82x_iap_entry(command, result);

    return result[1];
}

/**
 * \brief �Ƚ������ڴ��е�����
 */
 
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_compare (uint32_t dst_addr, 
                                                uint32_t src_addr, 
                                                uint32_t nbytes)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_COMPARE;
    command[1] = dst_addr;
    command[2] = src_addr;
    command[3] = nbytes;
    
    amhw_lpc82x_iap_entry(command, result);

    return (amhw_lpc82x_iap_stat_t)result[0];
}

/**
 * \brief ͨ��IAP�� boot loader�����л���ISPģʽ
 */
void amhw_lpc82x_iap_reinvoke_isp (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_LPC82X_IAP_CMD_REINVOKE_ISP;
    
    amhw_lpc82x_iap_entry(command, result);
}

/**
 * \brief ��������UID(��128λ)
 */
amhw_lpc82x_iap_stat_t amhw_lpc82x_iap_unique_id_read (uint32_t uid[4])
{
    uint32_t command[5], result[5];

    command[0] = AMHW_LPC82X_IAP_CMD_READ_UID;
    
    amhw_lpc82x_iap_entry(command, result);
    
    uid[0] = result[1];
    uid[1] = result[2];
    uid[2] = result[3];
    uid[3] = result[4];

    return (amhw_lpc82x_iap_stat_t)result[0];
}


/* end of file */
