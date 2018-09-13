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
 * \brief A Flash Translation Layer memory card driver
 *
 * \internal
 * \par Modification history
 * - 1.00 16-08-23  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_FTL_H
#define __AM_FTL_H

#include "ametal.h"
#include "am_mtd.h"
#include "am_nvram.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief FTL��Ҫʹ�õ����ڴ棨RAM���ռ��С
 *
 * \param[in] size           : �洢��������
 * \param[in] erase_size     : ������Ԫ��С
 * \param[in] logic_blk_size : �߼���Ĵ�С
 * \param[in] nb_log_blocks  : ��־�����
 *
 * \return FTL��Ҫʹ�õ����ڴ棨RAM���ռ��С
 */
#define AM_FTL_RAM_SIZE_GET(size, erase_size, logic_blk_size, nb_log_blocks) \
   (((logic_blk_size) + 4)                                                   \
     + ((size) / (erase_size) * 2)                                           \
     + ((nb_log_blocks) * (sizeof(struct log_buf)))                          \
     + ((nb_log_blocks) * ((erase_size) / (logic_blk_size)))                 \
     + (((((size) / (erase_size)) + 31) / 32) * sizeof(uint32_t)))
 
typedef struct am_ftl_info {

    /** \brief RAM ������   */
    uint8_t  *p_buf;

    /** \brief RAM �������ĳ��ȣ�����Ϊ AM_FTL_RAM_SIZE_GET() ��õ���ֵ  */
    size_t    len;

    /**
     * \brief �߼���Ĵ�С
     *
     * һ���� MTD �豸��д���С���磺SPI FLASH��ҳ��С����Ȼ�Ϊд���С��
     * ��������ʹ�� \sa am_ftl_read() ���� \sa am_ftl_write() ������/д������
     * ʱ��ÿ�ζ�/д����������Ϊ�߼����С
     */
    size_t     logic_blk_size;

    /**
     * \brief ��־���������ʹ�ö��ٸ�����飨������Ԫ�����������ݣ���ֵԽ��Ч��Խ��
     * ����Ӧ��ʵ�����ݿ�ͻ���٣�һ������£����������� 2 ~ 10֮�䣬����С��2��
     */
    size_t     nb_log_blocks;

    /** \brief ����������飨������Ԫ����������ʼ�ļ����齫���ᱻʹ��     */
    size_t     reserved_blocks;

} am_ftl_info_t ;


/**
 * FTL ����ṹ�嶨��
 */
typedef struct am_ftl_serv {

    /** \brief The MTD handle                                */
    am_mtd_handle_t mtd;

    /** \brief MAX lbn for read and write operation         */
    uint32_t        max_lbn;

    /** \brief The number of physical blocks(exclude reserved blocks) */
    unsigned int    nb_blocks;

     /** \brief free buf size, (nblock + 31 / 32)             */
    uint8_t         free_size;

    /** \brief sectors per block can be used store data      */
    uint8_t         sectors_per_blk;

    /** \brief The sectors use for header                    */
    uint8_t         sectors_hdr;

    /** \brief last used free block  */
    uint16_t        last_free;

     /** \brief The First EUN for each virtual unit          */
    uint16_t       *p_eun_table;

    /** \brief Store all free blocks                         */
    uint32_t       *p_free;

    /** \brief The 512 byte buffer for copy                  */
    uint8_t         *p_wr_buf;

    /** \brief Log buffer information */
    struct log_buf {
        uint16_t  used;        /**< \brief  used sectors           */
        uint16_t  lbn;         /**< \brief  related logic block    */
        uint16_t  pbn;         /**< \brief  related physical block */
        uint8_t  *p_map;       /**< \brief  sector map             */
    }*p_log_buf;

    const   am_ftl_info_t  *p_info;
 
} am_ftl_serv_t;

/** \brief FTL������Ͷ���  */
typedef am_ftl_serv_t *am_ftl_handle_t;
 
/**
 * \brief FTL��ʼ��
 *
 * \param[in] p_ftl      : FTL ʵ��
 * \param[in] p_info     : FTL ʵ����Ϣ
 * \param[in] mtd_handle : ������  MTD �洢�豸
 *
 * \return FTL ��������ֵΪNULLʱ��ʾ��ʼ��ʧ��
 */
am_ftl_handle_t  am_ftl_init (am_ftl_serv_t          *p_ftl,
                              const am_ftl_info_t    *p_info,
                              am_mtd_handle_t         mtd_handle);

/**
 * \brief ��ȡ�û����õ��߼��������lbn_num��
 *
 * ��д�߼���ʱ���߼����ŵ���Ч��ΧΪ : 0 ~ (lbn_num - 1)
 *
 * ÿ���߼���Ĵ洢����Ϊ��ʼ����Ϣ��ָ�����߼����С��
 */
size_t am_ftl_max_lbn_get (am_ftl_serv_t *p_ftl);

/**
 * \brief д��һ������
 *
 * \param[in] handle : FTL ʵ�����
 * \param[in] lbn   : �߼���
 * \param[in] p_buf : ���ݴ�ŵĻ����������ȹ̶�Ϊ��ʼ��ʱָ�����߼����С��
 *
 * \retval AM_OK : д�����ݳɹ�
 * \retval  < 0  : д��ʧ��
 */
int am_ftl_write (am_ftl_handle_t handle, unsigned int lbn, void *p_buf);

/**
 * \brief ��ȡһ������
 *
 * \param[in] handle : FTL ʵ�����
 * \param[in] lbn   : �߼���
 * \param[in] p_buf : ���ݴ�ŵĻ����������ȹ̶�Ϊ��ʼ��ʱָ�����߼����С��
 *
 * \retval AM_OK : д�����ݳɹ�
 * \retval  < 0  : д��ʧ��
 */
int am_ftl_read (am_ftl_handle_t handle, unsigned int lbn, void *p_buf);

/**
 * \brief ��ʼ�� NVRAM ���ܣ��Ա�ʹ��NVRAM�ӿڷ��ʴ洢��
 *
 * \param[in] handle : FTL ʵ�����
 * \param[in] p_dev  : NVRAM �豸ʵ��
 * \param[in] p_name : NVRAM �豸������ NVRAM�洢���б��е��豸����Ӧ
 *
 * \retval AM_OK : ��ʼ���ɹ�
 * \retval  < 0  : ��ʼ��ʧ��
 */
int am_ftl_nvram_init (am_ftl_handle_t   handle,
                       am_nvram_dev_t   *p_dev,
                       const char       *p_name);

#ifdef __cplusplus
}
#endif

#endif /* __AM_FTL_H */
