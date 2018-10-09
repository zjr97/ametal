/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MicroPort �û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_MICROPORT_H
#define __AM_HWCONF_MICROPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_mtd.h"
#include "am_ftl.h"
#include "am_time.h"
#include "am_mx25xx.h"
#include "am_ds1302.h"
#include "am_ep24cxx.h"
#include "am_rx8025t.h"
#include "am_pcf85063.h"
#include "am_alarm_clk.h"

/*******************************************************************************
  MicroPort-DS1302 ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 *
 * \param ��
 *
 * \return DS1302 ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_ds1302_handle_t am_microport_ds1302_inst_init (void);

/**
 * \brief MicroPort-DS1302 ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ�
 *
 * \param ��
 *
 * \return RTC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_microport_ds1302_rtc_inst_init (void);

/**
 * \brief MicroPort-DS1302 ʵ����ʼ������ DS1302 ����ϵͳʱ�䣩
 *
 * \param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_microport_ds1302.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_microport_ds1302_time_inst_init (void);

/*******************************************************************************
  MicroPort-RTC(PCF85063) ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-RTC(PCF85063) ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 *
 * \param ��
 *
 * \return PCF85063 ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pcf85063_handle_t am_microport_rtc_inst_init (void);

/**
 * \brief MicroPort-RTC(PCF85063) ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ�
 *
 * \param ��
 *
 * \return RTC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_microport_rtc_rtc_inst_init (void);

/**
 * \brief MicroPort-RTC(PCF85063) ʵ����ʼ����ʹ��ͨ�õ����ӹ��ܣ�
 *
 * \param ��
 *
 * \return ALARM_CLK ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_alarm_clk_handle_t am_microport_rtc_alarm_clk_inst_init (void);

/**
 * \brief MicroPort-RTC(PCF85063) ʵ����ʼ������ PCF85063 ����ϵͳʱ�䣩
 *
 * \param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_microport_rtc.c �ļ��е������Ƿ���ȷ
 */
int am_microport_rtc_time_inst_init (void);

/*******************************************************************************
  MicroPort-RX8025T ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 *
 * \param ��
 *
 * \return RX8025T ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rx8025t_handle_t am_microport_rx8025t_inst_init (void);

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ�
 *
 * \param ��
 *
 * \return RTC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_microport_rx8025t_rtc_inst_init (void);

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��ͨ�õ����ӹ��ܣ�
 *
 * \param ��
 *
 * \return ALARM_CLK ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_alarm_clk_handle_t  am_microport_rx8025t_alarm_clk_inst_init (void);

/**
 * \brief MicroPort-RX8025T ʵ����ʼ������ RX8025T ����ϵͳʱ�䣩
 *
 * \param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_microport_rx8025t.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_microport_rx8025t_time_inst_init (void);

/*******************************************************************************
  MicroPort-FLASH(MX25xx) ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-FLASH(MX25xx) ʵ����ʼ��
 *
 * \param ��
 *
 * \return MX25XX ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_mx25xx_handle_t am_microport_flash_inst_init (void);

/**
 * \brief MicroPort-FLASH(MX25xx) ʵ����ʼ����ʹ�� MTD ��׼�ӿڣ�
 *
 * \param ��
 *
 * \return MTD ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_mtd_handle_t am_microport_flash_mtd_inst_init (void);

/**
 * \brief MicroPort-FLASH(MX25xx) ʵ����ʼ����ʹ�� FTL ��׼�ӿڣ�
 *
 * \param ��
 *
 * \return FTL ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_ftl_handle_t am_microport_flash_ftl_inst_init (void);

/*******************************************************************************
  MicroPort-EEPROM ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-EEPROM ʵ����ʼ����ʹ��оƬ���ܣ�
 *
 * \param ��
 *
 * \return EP24CXX ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_ep24cxx_handle_t am_microport_eeprom_inst_init (void);

/**
 * \brief MicroPort-EEPROM ʵ����ʼ������ FM24C02 ������׼�� NVRAM �豸��
 *
 * \param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_microport_eeprom.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_microport_eeprom_nvram_inst_init (void);

/*******************************************************************************
  MicroPort-RS485 ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MicroPort-RS485 ʵ����ʼ��
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_microport_rs485_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_MICROPORT_H */

/* end of file */
