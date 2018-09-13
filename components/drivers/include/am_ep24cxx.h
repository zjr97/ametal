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
 * \brief ep24cxx ͨ��EEPROM����
 *
 * EP24CXX ��ָ�볣����CAT24C02��CAT24C08��һϵ��EEPROM����оƬ��оƬ������
 * 1kbit �� 1Mbit��
 *
 * \internal
 * \par modification history:
 * - 1.00 16-08-03  tee, first implementation
 * \endinternal
 */

#ifndef __AM_EP24CXX_H
#define __AM_EP24CXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "am_i2c.h"
#include "am_nvram.h"

/**
 * @addtogroup am_if_ep24cxx
 * @copydoc am_ep24cxx.h
 * @{
 */

/**
 * \brief ���� EEPROM оƬ���Զ���һ��оƬ
 *
 *     ��ͬоƬ֮���һЩ���ԣ�������ҳ��С�ȣ����ܴ��ڲ��죬ͨ������������ԣ�
 * ����ȷ��һ��оƬ��һϵ��������ͬ��оƬ������������6�����ԣ�
 *
 * 1. ҳ��С
 *     ��AT24C02�з�ҳ��ҳ��СΪ8�ֽڣ���AT24C1024��ҳ��СΪ256�ֽڡ��޷�ҳʱ��
 * ��������Ч��
 *
 * 2. ���޷�ҳ
 *     ��AT24C02�з�ҳ��ҳ��СΪ8�ֽڣ������繫˾��FRAM�޷�ҳ��
 *
 * 3. ���ݵ�ַ��������ַ�е�λ�� 
 *     һ��أ���AT24C02��������ַ�в��������ݵ�ַ��������AT24C1024��
 * ���������ϴ󣬹���1024Kbit����128K = 2 ^ 17��������ݵ�ַ��Ҫ17 bits��оƬ��
 * ��ʱ��Ϊ�˽�ʡͨ���ֽ������Ĵ�����ַʹ��2�ֽڣ�16 bits�������Ա�ʾ���ݵ�ַ��
 * ��16λ�����ݵ�ַ�����λ��ŵ�������ַ�С���ʱ�������Ե�ֵ��Ϊ1��
 *
 * 4. �Ĵ�����ַ���ֽ���
 *     ��AT24C02���Ĵ�����ַΪ1�ֽڣ����Ա�ʾ���ݵ�ַ����ʱ�������Ե�ֵΪ1������
 * ��AT24C1024���Ĵ�����ַΪ2�ֽڣ����Ա�ʾ���ݵ�ַ�ĵ�16λ����ʱ�������Ե�ֵ��
 * Ϊ2��
 *
 * 5. оƬ������byte��
 *     ��AT24C02������Ϊ2K bit��������Ϊ 256 �ֽڡ�������AT24C1024������1024K
 * bit����128K �ֽڡ�������������һ���Ĺ��ɣ���Ϊ128�ֽڵ�2���ݴ���������
 *     �������� = (2^n) * 128
 * ��ˣ�ʵ�ʱ�ʾ����ʱ����ʹ������ֵn����ʾ����������AT24C02����nֵΪ1������
 * AT24C1024���� n ֵΪ 10��
 *
 * 6. д��ʱ��
 *     EEPROM��оƬд��ʱ����в��죬��AT24C02��д��ʱ��Ϊ 5ms�������繫˾��FRAM
 * �޷�ҳд��ʱ��Ϊ0,����ȴ���
 *
 *     ��6�����Լ���ȷ���Ķ���һ��оƬ��һϵ����ͬ���Ե�оƬ������ʹ��һ��32λ
 * ������ͳһ�ı�ʾ��Щ���ԡ�32λ���ݵ�λ�������£�
 *
 * - bit[15:0]  ��ҳ��С
 * - bit[18:16] �����ݵ�ַ��������ַ�е�λ�� 
 * - bit[19]    ���Ĵ�����ַ���ֽ�����0: ���ֽ�  1: ˫�ֽ�
 * - bit[23:20] ��оƬ����, (2^n)*128 bytes, n = 0 ~ 15
 * - bit[31:24] ��д��ʱ�䣬��λms����Чֵ��0 ~ 255
 *
 * \param[in] page_size                  : ҳ��С��
 * \param[in] data_addr_bits_in_slv_addr : ���ݵ�ַ��������ַ�е�λ��
 * \param[in] reg_addr_double_bytes      : �Ĵ�����ַ˫�ֽڡ�0�����ֽڣ�1:��˫�ֽ�
 * \param[in] chip_size                  : оƬ������size = (2^n)*128 bytes
 * \param[in] write_time                 : д��ʱ�䣬��λms 
 *
 * \return 32λ���ݣ���ʾһ���ض���оƬ��һϵ��������ͬ��оƬ��
 * 
 * \note һ��أ��û�����ֱ��ʹ�øú꣬Ӧʹ���Ѿ�����õ�оƬ�ͺš�
 */
#define AM_EP24CXX_TYPE_DEF(page_size,                  \
                            data_addr_bits_in_slv_addr, \
                            reg_addr_double_bytes,      \
                            chip_size,                  \
                            write_time)                 \
       (((page_size) << 0)                   | \
        ((data_addr_bits_in_slv_addr) << 16) | \
        ((reg_addr_double_bytes) << 19)      | \
        ((chip_size)      << 20)             | \
        ((write_time)     << 24))
 
/**
 * \name ��֪��һЩоƬ�ͺŶ���
 *
 *     ��ʹ�õ�оƬ�ͺŴ˴�δ���壬����ʹ�� \sa AM_EP24CXX_CHIP_DEF() �궨��һ
 * ���µ�оƬ��
 * 
 * @{
 */

/** \brief AT24C01 */
#define AM_EP24CXX_AT24C01      AM_EP24CXX_TYPE_DEF(8,   0,  0,  0,  5)

/** \brief AT24C02 */
#define AM_EP24CXX_AT24C02      AM_EP24CXX_TYPE_DEF(8,   0,  0,  1,  5)

/** \brief AT24C04 */
#define AM_EP24CXX_AT24C04      AM_EP24CXX_TYPE_DEF(16,  1,  0,  2,  5)

/** \brief AT24C08 */
#define AM_EP24CXX_AT24C08      AM_EP24CXX_TYPE_DEF(16,  2,  0,  3,  5)

/** \brief AT24C16 */
#define AM_EP24CXX_AT24C16      AM_EP24CXX_TYPE_DEF(16,  3,  0,  4,  5)

/** \brief AT24C32 */
#define AM_EP24CXX_AT24C32      AM_EP24CXX_TYPE_DEF(32,  0,  1,  5,  5)

/** \brief AT24C64 */
#define AM_EP24CXX_AT24C64      AM_EP24CXX_TYPE_DEF(32,  0,  1,  6,  5)

/** \brief AT24C128 */
#define AM_EP24CXX_AT24C128     AM_EP24CXX_TYPE_DEF(64,  0,  1,  7,  5)

/** \brief AT24C256 */
#define AM_EP24CXX_AT24C256     AM_EP24CXX_TYPE_DEF(64,  0,  1,  8,  5)

/** \brief AT24C512 */
#define AM_EP24CXX_AT24C512     AM_EP24CXX_TYPE_DEF(128, 0,  1,  9,  5)

/** \brief AT24CM01 */
#define AM_EP24CXX_AT24CM01     AM_EP24CXX_TYPE_DEF(256, 1,  1,  10, 5)

/** \brief CAT24C01 */
#define AM_EP24CXX_CAT24C01     AM_EP24CXX_TYPE_DEF(16,  0,  0,  0,  5)

/** \brief CAT24C02 */
#define AM_EP24CXX_CAT24C02     AM_EP24CXX_TYPE_DEF(16,  0,  0,  1,  5)

/** \brief CAT24C04 */
#define AM_EP24CXX_CAT24C04     AM_EP24CXX_TYPE_DEF(16,  1,  0,  2,  5)

/** \brief CAT24C08 */
#define AM_EP24CXX_CAT24C08     AM_EP24CXX_TYPE_DEF(16,  2,  0,  3,  5)

/** \brief CAT24C16 */
#define AM_EP24CXX_CAT24C16     AM_EP24CXX_TYPE_DEF(16,  3,  0,  4,  5)

/** \brief FM24C02 */
#define AM_EP24CXX_FM24C02      AM_EP24CXX_TYPE_DEF(8,   0,  0,  1,  5)

/** \brief FM24C04 */
#define AM_EP24CXX_FM24C04      AM_EP24CXX_TYPE_DEF(16,  1,  0,  2,  5)

/** \brief FM24C08 */
#define AM_EP24CXX_FM24C08      AM_EP24CXX_TYPE_DEF(16,  2,  0,  3,  5)

/** \brief FM24C16 */
#define AM_EP24CXX_FM24C16      AM_EP24CXX_TYPE_DEF(16,  3,  0,  4,  5)

/** \brief FM24C32 */
#define AM_EP24CXX_FM24C32      AM_EP24CXX_TYPE_DEF(32,  0,  1,  5,  5)

/** \brief FM24C64 */
#define AM_EP24CXX_FM24C64      AM_EP24CXX_TYPE_DEF(32,  0,  1,  6,  5)

/** \brief FM24C128 */
#define AM_EP24CXX_FM24C128     AM_EP24CXX_TYPE_DEF(64,  0,  1,  7,  5)

/** \brief FM24C256 */
#define AM_EP24CXX_FM24C256     AM_EP24CXX_TYPE_DEF(64,  0,  1,  8,  5)

/** \brief FM24C512 */
#define AM_EP24CXX_FM24C512     AM_EP24CXX_TYPE_DEF(128, 0,  1,  9,  5)

/** \brief FM24C1024 */
#define AM_EP24CXX_FM24C1024    AM_EP24CXX_TYPE_DEF(256, 1,  1,  10, 5)

/** @} */

/**
 * \brief ep24cxx�豸��Ϣ�ṹ�嶨��
 */
typedef struct am_ep24cxx_devinfo {
    
    /** \brief �豸 7-bit �ӻ���ַ */
    uint8_t                        slv_addr;

    /** \brief оƬ�ͺţ��磺 \sa #AM_EP24CXX_AT24C02 */
    uint32_t                       type;
    
} am_ep24cxx_devinfo_t;
 
/**
 * \brief ep24cxx�豸�ṹ�嶨��
 */
typedef struct am_ep24cxx_dev {

    /** \brief I2C�ӻ��豸             */
    am_i2c_device_t                i2c_dev;
 
    /** \brief ep24cxx�豸�ṩ�� NVRAM ��׼���� */
    am_nvram_dev_t                *p_serv;
    
    /** \brief ָ���豸��Ϣ��ָ��      */
    const am_ep24cxx_devinfo_t    *p_devinfo;
    
} am_ep24cxx_dev_t;

/** \brief ep24cxx ����������� */
typedef am_ep24cxx_dev_t *am_ep24cxx_handle_t;
 
/**
 * \brief ep24cxx��ʼ������
 *
 * ep24xx�����ṩ��׼�� NVRAM ���񣬸ó�ʼ���������ر�׼�� NVRAM ��������
 *
 * \param[in] p_dev      : ָ��ep24cxx�豸��ָ��
 * \param[in] p_devinfo  : ָ��ep24cxx�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼������������ʹ�ø�I2C�����ep24cxxͨ�ţ�
 *
 * \return ����ep24cxx��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_ep24cxx_handle_t am_ep24cxx_init (am_ep24cxx_dev_t           *p_dev,
                                     const am_ep24cxx_devinfo_t *p_devinfo,
                                     am_i2c_handle_t             i2c_handle);
                                   
/**
 * \brief ��ʼ��EP24CXX��NVRAM���ܣ���ϵͳ�ṩ  NVRAM ��׼����
 * 
 *   �ú�����EP24CXX�豸��Ϊ��׼��NVRAM�豸ע�ᵽϵͳ��
 * 
 * \param[in] handle      : ep24cxx�������
 * \param[in] p_dev       : NVRAM ��׼�豸
 * \param[in] p_dev_name  : NVRAM ��׼�豸���豸��
 *
 * \return AM_OK, �ṩNVRAM����ɹ�������ֵ���ṩNVRAM����ʧ�ܡ�
 *
 * \note ʹ�øú����󣬼���ʹ��NVRAM��׼�ӿ� am_nvram_set() �� am_nvram_get() ����
 * EP24CXX�洢����ʹ�õĶα����� am_nvram_cfg.c�ļ��ж��壬�洢���������豸������
 * ��дΪ�˴� p_name ָ�������֣��� p_name Ϊ  "fm24c02", �������g_nvram_segs[]��
 * �����б�����������5���洢�Σ�����Ϊʾ������
 *    {"ip",         0,  0,  4,   "fm24c02"},
 *    {"ip",         1,  4,  4,   "fm24c02"},
 *    {"temp_limit", 0,  8,  4,   "fm24c02"},
 *    {"system",     0,  12, 50,  "fm24c02"},
 *    {"test",       0,  62, 178, "fm24c02"},
 */
int am_ep24cxx_nvram_init (am_ep24cxx_handle_t   handle,
                           am_nvram_dev_t       *p_dev,
                           const char           *p_dev_name);

/**
 * \brief ����д��
 * 
 * \param[in] handle     : ep24cxx�������
 * \param[in] start_addr : ����д�����ʼ��ַ
 * \param[in] p_buf      : ��д�������
 * \param[in] len        ��д�����ݳ���
 *
 * \return AM_OK, ����д��ɹ�������ֵ������д��ʧ�ܡ�
 */                      
int am_ep24cxx_write (am_ep24cxx_handle_t  handle, 
                      int                  start_addr, 
                      uint8_t             *p_buf, 
                      int                  len);

  
/**
 * \brief ���ݶ�ȡ
 * 
 * \param[in]  handle    : ep24cxx�������
 * \param[in]  start_addr: ���ݶ�ȡ����ʼ��ַ
 * \param[out] p_buf     : ��Ŷ�ȡ���ݵĻ�����
 * \param[in]  len       ����ȡ���ݵĳ���
 *
 * \return AM_OK, ���ݶ�ȡ�ɹ�������ֵ�����ݶ�ȡʧ�ܡ�
 */
int am_ep24cxx_read (am_ep24cxx_handle_t handle,
                     int                 start_addr, 
                     uint8_t            *p_buf, 
                     int                 len);
                              
/**
 * \brief ep24cxx���ʼ������
 *
 * ������ʹ��ָ����ep24cxx�豸ʱ������ʹ�øú������ʼ�����豸�����ͷ������Դ
 *
 * \param[in] handle : ep24cxx�������
 *
 * \return AM_OK, ���ʼ���ɹ�������ֵ�����ʼ��ʧ�ܡ�
 */                              
int am_ep24cxx_deinit (am_ep24cxx_handle_t handle);
                              
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_EP24CXX_H */

/* end of file */
