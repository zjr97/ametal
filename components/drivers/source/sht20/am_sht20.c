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
 * \brief  SHT20 ��ʪ�ȴ�����Ӧ�ýӿ�ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 2017-7-13  sky, first implementation.
 * \endinternal
 */

#include "am_sht20.h"

#define SHT20_DEVICE_ADDR           0x40        /* SHT20 I2C��ַ */
#define SHT20_TRIG_HUMIDITY         0           /* ����ʪ�� */
#define SHT20_TRIG_TEMPERATURE      1           /* �����¶� */

/**
 * \brief SHT20����������
 */
typedef enum am_sht20_command {
    TRIG_T_MEASUREMENT_HM    = 0xE3,     // command trig. temp meas. hold master
    TRIG_RH_MEASUREMENT_HM   = 0xE5,     // command trig. humidity meas. hold master
    TRIG_T_MEASUREMENT_POLL  = 0xF3,     // command trig. temp meas. no hold master
    TRIG_RH_MEASUREMENT_POLL = 0xF5,     // command trig. humidity meas. no hold master
    USER_REG_W               = 0xE6,     // command writing user register
    USER_REG_R               = 0xE7,     // command reading user register
    SOFT_RESET               = 0xFE      // command soft reset
} am_sht20_command_t;

/**
 * \brief SHT20������ CRC ����ʽ
 */
const uint16_t __g_polynomial = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001

/**
 * \brief SHT20������ CRCУ��
 */
static int8_t __sht20_check_crc (uint8_t *p_data, uint8_t nb_bytes, uint8_t check_sum)
{
    uint8_t crc = 0;
    uint8_t byte_ctr;
    uint8_t bit = 0;

    //calculates 8-Bit checksum with given __g_polynomial
    for (byte_ctr = 0; byte_ctr < nb_bytes; ++byte_ctr) {
        crc ^= (p_data[byte_ctr]);
        for (bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ __g_polynomial;
            } else {
                crc = (crc << 1);
            }
        }
    }

    if (crc != check_sum) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * \brief SHT20�������������ʪ��
 */
static float __sht20_calc_rh (uint16_t s_rh)
{
    float humidity_rh;  // variable for result
    s_rh &= ~0x0003;    // clear bits [1..0] (status bits)
    // RH= -6 + 125 * SRH/2^16
    humidity_rh = -6.0 + 125.0/65536 * (float)s_rh;
    return humidity_rh;
}

/**
 * \brief SHT20�����������¶�[��C]
 */
static float __sht20_calc_temperature_c (uint16_t s_t)
{
    float temperature_c; // variable for result
    s_t &= ~0x0003;     // clear bits [1..0] (status bits)
    //T= -46.85 + 175.72 * ST/2^16
    temperature_c = -46.85 + 175.72/65536 * (float)s_t;
    return temperature_c;
}

/**
 * \brief SHT20��������ѯʽ����
 * \note type : 0 for humidity, 1 for temperature
 */
static int __sht20_measure_poll (am_sht20_handle_t handle, uint8_t type, uint16_t *p_measurand)
{
    uint8_t  cmd;
    uint8_t  temp_value[3] = {0, 0, 0};
    int      ret           = AM_OK;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* д�������� */
    switch (type) {

    case SHT20_TRIG_HUMIDITY:       /* ʪ�Ȳ��� */
        cmd = TRIG_RH_MEASUREMENT_POLL;
        ret = am_i2c_write(p_i2c_dev,
                           0,              //���ӵ�ַ
                           &cmd,
                           1);
        break;

    case SHT20_TRIG_TEMPERATURE:    /* �¶Ȳ��� */
        cmd = TRIG_T_MEASUREMENT_POLL;
        ret = am_i2c_write(p_i2c_dev,
                           0,               //���ӵ�ַ
                           &cmd,
                           1);
        break;

    default:
        break;
    }

    /* ��鷢���Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }

    /* �ȴ�������� */
    am_mdelay(100);

    /* ��ȡ�������� */
    ret = am_i2c_read(p_i2c_dev,
                      0,            //���ӵ�ַ
                      temp_value,
                      3);

    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }

    /* ����¶� */
    *p_measurand = temp_value[0] * 256 + temp_value[1];

    /* ��֤У��� */
    ret = __sht20_check_crc(temp_value, 2, temp_value[2]);

    return ret;
}

/**
 * \brief SHT20��������ȡ�¶�
 */
int am_sht20_temperature_read (am_sht20_handle_t handle, float *p_temperature)
{
    int      ret = AM_OK;
    uint16_t s_t;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    ret = __sht20_measure_poll(handle, SHT20_TRIG_TEMPERATURE, &s_t);
    if (AM_OK != ret) {
        return ret;
    }

    *p_temperature = __sht20_calc_temperature_c(s_t);

    return ret;
}

/**
 * \brief SHT20��������ȡʪ��
 */
int am_sht20_humidity_read (am_sht20_handle_t handle, float *p_humidity)
{
    int      ret = AM_OK;
    uint16_t s_rh;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    ret = __sht20_measure_poll(handle, SHT20_TRIG_HUMIDITY, &s_rh);
    if (AM_OK != ret) {
        return ret;
    }

    *p_humidity = __sht20_calc_rh(s_rh);

    return ret;
}

/**
 * \brief SHT20�����������λ
 */
int am_sht20_soft_reset (am_sht20_handle_t handle)
{
    int     ret;
    uint8_t soft_reset_cmd = SOFT_RESET;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* д��λָ�� */
    ret = am_i2c_write(p_i2c_dev,
                       0,              //���ӵ�ַ
                       &soft_reset_cmd,
                       1);

    /* ��Ҫ15ms�ﵽ����״̬ */
    am_mdelay(20);

    return ret;
}

/**
 * \brief SHT20��������ʼ��
 */
am_sht20_handle_t am_sht20_init (am_sht20_dev_t *p_dev, am_i2c_handle_t i2c_handle)
{
    /* ��֤������Ч�� */
    if (NULL == p_dev || NULL == i2c_handle) {
        return NULL;
    }

    /* ��ʼ���ú�sht20�豸��Ϣ */
    am_i2c_mkdev(&(p_dev->i2c_dev),
                 i2c_handle,
                 SHT20_DEVICE_ADDR,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_NONE);   //���ӵ�ַ

    return p_dev;
}

/**
 * \brief SHT20 �豸���ʼ��
 */
void am_sht20_deinit (am_sht20_handle_t handle)
{

}

/* end of file */
