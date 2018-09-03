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
 * \brief FM175XX�Ĵ�������
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-21  sky, first implementation.
 * - 1.01 17-10-31  sdq, make somd changes.
 * \endinternal
 */
 
#ifndef __FM175XX_REG_H
#define __FM175XX_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_fm175xx.h"
/** 
 * \addtogroup am_if_fm175xx_reg
 * \copydoc am_fm175xx_reg.h
 * @{
 */

/**
 * \name FM175XX_REG FM175XX�Ĵ�������
 * @{
 */
#define AM_FM175XX_COMMAND_REG           0x01   /**< \brief ������ֹͣ����ִ�� */
#define AM_FM175XX_COMIEN_REG            0x02   /**< \brief �ж�����ʹ�����ֹλ */
#define AM_FM175XX_DIVIEN_REG            0x03   /**< \brief �ж�����ʹ�����ֹλ */
#define AM_FM175XX_COMIRQ_REG            0x04   /**< \brief �����ж�����λ */
#define AM_FM175XX_DIVIRQ_REG            0x05   /**< \brief �����ж�����λ */
#define AM_FM175XX_ERROR_REG             0x06   /**< \brief ��ʾ��һ��ִ��ָ��Ĵ���״̬ */
#define AM_FM175XX_STATUS1_REG           0x07   /**< \brief ͨѶ����״̬λ */
#define AM_FM175XX_STATUS2_REG           0x08   /**< \brief ���ջ��ͷ������Ŀ���״̬λ */
#define AM_FM175XX_FIFODATA_REG          0x09   /**< \brief 64λfifo��������� */
#define AM_FM175XX_FIFOLEVEL_REG         0x0a   /**< \brief fifo����Ч������� */
#define AM_FM175XX_WATERLEVEL_REG        0x0b   /**< \brief fifo�������羯��ļ��� */
#define AM_FM175XX_CONTROL_REG           0x0c   /**< \brief ���ƼĴ��� */
#define AM_FM175XX_BITFRAMING_REG        0x0d   /**< \brief ����λ��֡��ʽ���� */
#define AM_FM175XX_COLL_REG              0x0e   /**< \brief RF�ӿڼ�⵽��һ����ͻλ��λ�� */
#define AM_FM175XX_EX_REG                0x0f   /**< \brief ��չ�Ĵ��� */
#define AM_FM175XX_MODE_REG              0x11   /**< \brief ���շ���ģʽ */
#define AM_FM175XX_TXMODE_REG            0x12   /**< \brief �����������ʺ�֡��ʽ*/
#define AM_FM175XX_RXMODE_REG            0x13   /**< \brief �����������ʺ�֡��ʽ */
#define AM_FM175XX_TXCONTROL_REG         0x14   /**< \brief ������������TX1��TX2���� */
#define AM_FM175XX_TXASK_REG             0x15   /**< \brief ������������ */
#define AM_FM175XX_TXSEL_REG             0x16   /**< \brief ���������ź�Դѡ�� */
#define AM_FM175XX_RXSEL_REG             0x17   /**< \brief �ڲ����������� */
#define AM_FM175XX_RXTHRESHOLD_REG       0x18   /**< \brief ������������ֵѡ�� */
#define AM_FM175XX_DEMOD_REG             0x19   /**< \brief ��������� */
#define AM_FM175XX_TX_REG                0x1c   /**< \brief ���Ʋ���ISO/IEC 14443������� */
#define AM_FM175XX_RX_REG                0x1d   /**< \brief ���Ʋ���ISO/IEC 14443���ղ��� */
#define AM_FM175XX_TYPEB_REG             0x1e   /**< \brief ISO/IEC 14443B ���ƣ�FM17510�üĴ���δʹ�ã� */
#define AM_FM175XX_SERIALSPEED_REG       0x1f   /**< \brief ѡ����UART�ӿ��ٶȣ�FM17510�üĴ���δʹ�ã� */
#define AM_FM175XX_CRCMSB_REG            0x21   /**< \brief CRC�������߶� */
#define AM_FM175XX_CRCLSB_REG            0x22   /**< \brief CRC�������Ͷ� */
#define AM_FM175XX_MODWIDTH_REG          0x24   /**< \brief ���ƿ�ȿ��� */
#define AM_FM175XX_RFCFG_REG             0x26   /**< \brief ���ý����������RF��ƽ */
#define AM_FM175XX_GSN_REG               0x27   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */
#define AM_FM175XX_CWGSP_REG             0x28   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */
#define AM_FM175XX_MODGSP_REG            0x29   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */
#define AM_FM175XX_TMODE_REG             0x2a   /**< \brief �ڲ���ʱ��ģʽ���� */
#define AM_FM175XX_TPRESCALER_REG        0x2b   /**< \brief �ڲ���ʱ��Ԥ�������� */
#define AM_FM175XX_TRELOADMSB_REG        0x2c   /**< \brief �ڲ���ʱ��16λ����ֵ��λ */
#define AM_FM175XX_TRELOADLSB_REG        0x2d   /**< \brief �ڲ���ʱ��16λ����ֵ��λ */
#define AM_FM175XX_TCOUNTERVALMSB_REG    0x2e   /**< \brief �ڲ���ʱ��16λ����ֵ��λ */
#define AM_FM175XX_TCOUNTERVALLSB_REG    0x2f   /**< \brief �ڲ���ʱ��16λ����ֵ��λ */
#define AM_FM175XX_TESTSEL1_REG          0x31   /**< \brief �����ź����� */
#define AM_FM175XX_TESTSEL2_REG          0x32   /**< \brief �����ź����ü�PRBS���� */
#define AM_FM175XX_TESTPINEN_REG         0x33   /**< \brief D1-D7�����������ʹ�ܣ�FM17510�üĴ���δʹ�ã� */
#define AM_FM175XX_TESTPINVALUE_REG      0x34   /**< \brief ��������I/O����ʱ,����D1-D7���ŵ�ֵ��FM17510�üĴ���δʹ�ã� */
#define AM_FM175XX_TESTBUS_REG           0x35   /**< \brief ��ʾ�ڲ��������ߵ�״̬ */
#define AM_FM175XX_TESTCTRL_REG          0x36   /**< \brief ���Կ��� */
#define AM_FM175XX_ANALOGTEST_REG        0x38   /**< \brief ��������AUX1��AUX2 */
#define AM_FM175XX_TESTDAC1_REG          0x39   /**< \brief ΪTestDAC1�������ֵ */
#define AM_FM175XX_TESTDAC2_REG          0x3a   /**< \brief ΪTestDAC2�������ֵ��FM17510�üĴ���δʹ�ã� */
#define AM_FM175XX_TESTADC_REG           0x3b   /**< \brief ��ʾADC I��Q��ʵ��ֵ */

/** @} */


/**
 * \name FM175XX_REG FM175XX��չ�Ĵ�������
 * @{
 */
#define AM_FM175XX_LPCD_CTRL1            0x01
#define AM_FM175XX_LCPD_CTRL2            0X02
#define AM_FM175XX_LPCD_CTRL3            0x03
#define AM_FM175XX_LPCD_CTRL4            0x04
#define AM_FM175XX_LPCD_BIAS_CURRENT     0x05
#define AM_FM175XX_LPCD_ACD_REFERECE     0x06
#define AM_FM175XX_LPCD_SLEEP_CFG        0x07
#define AM_FM175XX_LPCD_READY_CFG        0x08
#define AM_FM175XX_LPCD_DETECT_CFG       0x09
#define AM_FM175XX_LPCD_VMIDBD_CFG       0x0A
#define AM_FM175XX_LPCD_AUTO_WUP_CFG     0x0B
#define AM_FM175XX_LPCD_ADC_RESULT_L     0x0C
#define AM_FM175XX_LPCD_ADC_RESULT_H     0x0D
#define AM_FM175XX_LPCD_THRESHOLD_MIN_L  0x0E
#define AM_FM175XX_LPCD_THRESHOLD_MIN_H  0x0F
#define AM_FM175XX_LPCD_THRESHOLD_MAX_L  0X10
#define AM_FM175XX_LPCD_THRESHOLD_MAX_H  0x11
#define AM_FM175XX_LPCD_IRQ              0x12
#define AM_FM175XX_LPCD_RFT1             0x13
#define AM_FM175XX_LPCD_RFT2             0x14
#define AM_FM175XX_LPCD_RFT3             0x15
#define AM_FM175XX_LPCD_RFT4             0x16
#define AM_FM175XX_LPCD_RFT5             0x1B
#define AM_FM175XX_LPCD_MISC             0x1C


/** @} */


/**
 * \name Command����Ĵ������� (0x01)
 * @{
 */

#define AM_FM175XX_COMMAND_RCV_OFF         0x20        /**< \brief ��Ƶģ��������ر� */
#define AM_FM175XX_COMMAND_POWER_DOWN      0x10        /**< \brief �����������ģʽ */
#define AM_FM175XX_COMMAND_MASK            0x0F        /**< \brief ָ��Ĵ������� */

/** @} */


/**
 * \name CommIEN�ж�����ʹ�����ֹ���ƼĴ������� (0x02)
 * @{
 */

#define AM_FM175XX_COMMIEN_IRQ_INV         0x80    /**< \brief IRQ�ź�ȡ�� ȱʡΪ1 */
#define AM_FM175XX_COMMIEN_TX_IEN          0x40    /**< \brief ����TXIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_RX_IEN          0x20    /**< \brief ����RXIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_IDLE_IEN        0x10    /**< \brief ����IDLEIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_HIALERT_IEN     0x08    /**< \brief ����HIALERTIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_LOALERT_IEN     0x04    /**< \brief ����HIALERTIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_ERR_IEN         0x02    /**< \brief ����ERRIRQ�����ж����󴫵ݵ�IRQ */
#define AM_FM175XX_COMMIEN_TIMER_IEN       0x01    /**< \brief ����TIMERIRQ��ʱ���ж����󴫵ݵ�IRQ */

/** @} */


/**
 * \name DivIEN�ж�����ʹ�����ֹ���ƼĴ������� (0x03)
 * @{
 */
 
#define AM_FM175XX_DIVIEN_IRQ_PUSHPULL     0x80    /**< \brief IRQ���Ź���ģʽ 1CMOS 0��©��� */
#define AM_FM175XX_DIVIEN_TINACT_IEN       0x10    /**< \brief ����TIN�ж����󴫵ݵ�IRQ��FM17510��֧�֣� */
#define AM_FM175XX_DIVIEN_CRC_IEN          0x04    /**< \brief ����CRC�ж����󴫵ݵ�IRQ */

/** @} */


/**
 * \name CommIRq�жϿ�������Ĵ������� (0x04)
 * @{
 */
 
#define AM_FM175XX_COMMIRQ_SET1            0x80    /**< \brief COMMIRQ�жϱ�� д0��0�Ĵ��������б�� */
#define AM_FM175XX_COMMIRQ_TX_IRQ          0x40    /**< \brief �������ݵ����һλ������������1 */
#define AM_FM175XX_COMMIRQ_RX_IRQ          0x20    /**< \brief ���յ�����ĩβʱ��1 */
#define AM_FM175XX_COMMIRQ_IDLE_IRQ        0x10    /**< \brief ִ�е�δָ֪��ʱ��1 */
#define AM_FM175XX_COMMIRQ_HIALERT_IRQ     0x08    /**< \brief STATUS1�Ĵ�����HIALERT��1ʱ��1 */
#define AM_FM175XX_COMMIRQ_LOALERT_IRQ     0x04    /**< \brief STATUS1�Ĵ�����LOALERT��1ʱ��1 */
#define AM_FM175XX_COMMIRQ_ERR_IRQ         0x02    /**< \brief ERR�Ĵ��������κ�errλʱ��1 */
#define AM_FM175XX_COMMIRQ_TIMER_IRQ       0x01    /**< \brief TimerValue������0ʱ��1 */

/** @} */


/**
 * \name DivIRq�жϿ�������Ĵ������� (0x05)
 * @{
 */
 
#define AM_FM175XX_DIVIRQ_SET2             0x80    /**< \brief DIVIRQ�жϱ�� д1��0�Ĵ��������б�� */
#define AM_FM175XX_DIVIRQ_TINACT_IRQ       0x10    /**< \brief TIN����ʱ ��1��FM17510��֧�֣� */
#define AM_FM175XX_DIVIRQ_CRC_IRQ          0x04    /**< \brief CRCָ������������ݴ�����ɺ���1 */

/** @} */


/**
 * \name Error����Ĵ������� (0x06)
 * @{
 */
 
#define AM_FM175XX_ERROR_WR_ERR            0x80    /**< \brief ������������ݱ�����д��fifoʱ��λ */
#define AM_FM175XX_ERROR_TEMP_ERR          0x40    /**< \brief �ڲ��¶ȴ�����������ʱ��1 */
#define AM_FM175XX_ERROR_BUFFER_ERR        0x10    /**< \brief fifo����ʱ��ͼдfifo��1 */
#define AM_FM175XX_ERROR_COLL_ERR          0x08    /**< \brief ��⵽��ͻ��1(��AЭ����106kbitʱ��Ч),����������ʱ�Զ����� */
#define AM_FM175XX_ERROR_CRC_ERR           0x04    /**< \brief RxMode�Ĵ�����RxCRCEN��1��CRC����ʧ��ʱ��1,����������ʱ�Զ����� */
#define AM_FM175XX_ERROR_PARITY_ERR        0x02    /**< \brief ��żУ��ʧ��ʱ��1(��AЭ����106kbitʱ��Ч),����������ʱ�Զ����� */
#define AM_FM175XX_ERROR_PROTOCOL_ERR      0x01    /**< \brief SOF�����Authent�������ֽ�������ȷʱ��1 */

/** @} */


/**
 * \name Status1״̬�Ĵ���1���� (0x07)
 * @{
 */
 
#define AM_FM175XX_STATUS1_CRC_OK          0x40    /**< \brief CRC������Ϊ0 */
#define AM_FM175XX_STATUS1_CRC_READY       0x20    /**< \brief CRC������� */
#define AM_FM175XX_STATUS1_IRQ             0x10    /**< \brief ���ж� */
#define AM_FM175XX_STATUS1_TRUNING         0x08    /**< \brief ��ʱ���������� */
#define AM_FM175XX_STATUS1_HIALERT         0x02    /**< \brief fifo�е�HIALERT �ֽ���С��WaterLevel */
#define AM_FM175XX_STATUS1_LOALERT         0x01    /**< \brief fifo�е�LOALERT �ֽ���С��WaterLevel */

/** @} */


/**
 * \name Status2״̬�Ĵ���2���� (0x08)
 * @{
 */
 
#define AM_FM175XX_STATUS2_TEMP_SENS_CLEAR     0x80    /**< \brief �¶���125�澯����ʱ,�ø�λ��������¶ȴ��� */
#define AM_FM175XX_STATUS2_I2C_FORCE_HS        0x40    /**< \brief I2C�����˲�������.��1Ϊ����ģʽ,��0�����Ӧ�õ�I2CЭ�����. */
#define AM_FM175XX_STATUS2_CRYPTO1_ON          0x08    /**< \brief M1 Crypto1��Ԫ����.M1����Ч,�ڳɹ�ִ��Authentָ�����1,�������� */
#define AM_FM175XX_STATUS2_MODEM_STATE_MASK    0x07    /**< \brief ����״̬��״̬���� */
#define AM_FM175XX_STATUS2_MODEM_STATE_IDLE    0x00    /**< \brief ����״̬������ */
#define AM_FM175XX_STATUS2_MODEM_STATE_SS      0x01    /**< \brief ����״̬���ȴ�StartSend��Ч */
#define AM_FM175XX_STATUS2_MODEM_STATE_TW      0x02    /**< \brief ����״̬��TxWait,ֱ��RF������ */
#define AM_FM175XX_STATUS2_MODEM_STATE_SEND    0x03    /**< \brief ����״̬�������� */
#define AM_FM175XX_STATUS2_MODEM_STATE_RW      0x04    /**< \brief ����״̬��RxWait,ֱ��RF������ */
#define AM_FM175XX_STATUS2_MODEM_STATE_DW      0x05    /**< \brief ����״̬��DataWait */
#define AM_FM175XX_STATUS2_MODEM_STATE_RECV    0x06    /**< \brief ����״̬�������� */

/** @} */


/**
 * \name FIFOLevel�Ĵ������� (0x0a)
 * @{
 */
 
#define AM_FM175XX_FIFOLEVEL_FLUSH_BUFFER      0x80    /**< \brief ��1����ڲ�fifo�������Ķ�дָ���ERR�Ĵ����е�BufferOvflλ,����Ϊ0 */
#define AM_FM175XX_FIFOLEVEL_MASK              0x7f    /**< \brief fifo�������е��ֽ���,д��+1,��ȡ-1 */

/** @} */


/**
 * \name WaterLevel�Ĵ������� (0x0b)
 * @{
 */
 
#define AM_FM175XX_WATERLEVEL_MASK         0x3F    /**< \brief fifo��ˮ��,��������ֽ� */

/** @} */


/**
 * \name Control�������ƼĴ������� (0x0c)
 * @{
 */
 
#define AM_FM175XX_CONTROL_TSTOPNOW        0x80    /**< \brief ��ʱ������ֹͣ */
#define AM_FM175XX_CONTROL_TSTARTNOW       0x40    /**< \brief ��ʱ���������� */
#define AM_FM175XX_CONTROL_RX_LAST_BITS    0x07    /**< \brief �������ֽڵ���Чλ��,Ϊ0��ȫ����Ч */

/** @} */


/**
 * \name BitFraming�Ĵ�������,����λ��֡��ʽ���� (0x0d)
 * @{
 */
 
#define AM_FM175XX_BITFRAMING_STARTSEND    0x80    /**< \brief ���ݷ��俪ʼ,��λֻ��Transceiverִ��ʱ��Ч */
#define AM_FM175XX_BITFRAMING_RXALIGN_0    0x00    /**< \brief ���λ���ڵ�0λ,����λ˳�� */
#define AM_FM175XX_BITFRAMING_RXALIGN_1    0x10    /**< \brief ���λ���ڵ�1λ,����λ˳�� */
#define AM_FM175XX_BITFRAMING_RXALIGN_7    0x70    /**< \brief ���λ���ڵ�7λ,����λ˳�� */
#define AM_FM175XX_BITFRAMING_TXLASTBITS   0x07    /**< \brief ������ֽڵ��跢�͵�λ��,Ϊ0��ȫ����Ҫ���� */

/** @} */


/**
 * \name CollIRq�Ĵ�������,RF�ӿڼ�⵽�ĵ�һ����ͻλ (0x0e)
 * @{
 */

/** \brief ��0������ͻλ֮������н���λ�����(106kbit��Ч,������1) */
#define AM_FM175XX_COLLIRQ_VALUES_AFTERCOLL    0x80

/** \brief û��⵽��ͻ���ͻ��CollPos��Χ��ʱ��1(��λֻ��14443A��д��ģʽ�±����) */
#define AM_FM175XX_COLLIRQ_COLLPOS_NOTVALID    0x20

/** \brief ��һ����ͻλλ��,00��ʾ32λ,01��ʾ1λ(��λֻ��14443A��д��ģʽ��,��COLLPOS_NOTVALIDΪ0ʱ�����) */
#define AM_FM175XX_COLLIRQ_COLLPOS             0x1f

/** @} */


/**
 * \name EX��չ�Ĵ������� (0x0f)
 * @{
 */

#define AM_FM175XX_EX_MODE                 0xc0    /**< \brief ��չ�Ĵ�������ģʽ */
#define AM_FM175XX_EX_MODE_W_ADDR          0x40    /**< \brief ��չ�Ĵ���д�������ַ */
#define AM_FM175XX_EX_MODE_R_ADDR          0x80    /**< \brief ��չ�Ĵ�������������ַ */
#define AM_FM175XX_EX_MODE_W_DATA          0xc0    /**< \brief ��չ�Ĵ���д����չ���� */
#define AM_FM175XX_EX_MODE_R_DATA          0x00    /**< \brief ��չ�Ĵ���������չ���� */
#define AM_FM175XX_EX_MODE_ADDR_DATA       0x3f    /**< \brief ������ַ������ */

/** @} */

/**
 * \name Mode�Ĵ�������,���巢��ͽ���ģʽ (0x11)
 * @{
 */

#define AM_FM175XX_MODE_MSB_FIRST          0x80    /**< \brief CRCЭ��������MSBλ���ȼ���CRC,CRCResult�Ĵ����ж�MSB��LSBҲ��λ��ת */
#define AM_FM175XX_MODE_TXWAIT_RF          0x20    /**< \brief ��д����ģʽʱֻ��RF�����������·������ */
#define AM_FM175XX_MODE_POLTIN             0x08    /**< \brief TIN���ŵļ���,1�ߵ�ƽ��Ч,0�͵�ƽ��Ч��FM17510��֧�֣� */
#define AM_FM175XX_MODE_CRC_PRESET_MASK    0x03    /**< \brief CRCУ��Ԥ��ֵ */
#define AM_FM175XX_MODE_CRC_PRESET_0000    0x00    /**< \brief CRCУ��Ԥ��ֵ0000 */
#define AM_FM175XX_MODE_CRC_PRESET_6363    0x01    /**< \brief CRCУ��Ԥ��ֵ6363 */
#define AM_FM175XX_MODE_CRC_PRESET_a671    0x02    /**< \brief CRCУ��Ԥ��ֵa671 */
#define AM_FM175XX_MODE_CRC_PRESET_ffff    0x03    /**< \brief CRCУ��Ԥ��ֵffff */

/** @} */


/**
 * \name TxMode�Ĵ�������,���巢���������ʺ�֡��ʽ (0x12)
 * @{
 */
 
#define AM_FM175XX_TXMODE_TXCRC_EN         0x80    /**< \brief ��1���ݷ���ʱʹ��CRCУ������(��106kbit������0) */
#define AM_FM175XX_TXMODE_TXSPEED_MASK     0x70    /**< \brief ������������ */
#define AM_FM175XX_TXMODE_TXSPEED_106KBIT  0x00    /**< \brief ��������106kbit */
#define AM_FM175XX_TXMODE_TXSPEED_212KBIT  0x10    /**< \brief ��������212kbit */
#define AM_FM175XX_TXMODE_TXSPEED_424KBIT  0x20    /**< \brief ��������424kbit */
#define AM_FM175XX_TXMODE_TXSPEED_848KBIT  0x30    /**< \brief ��������848kbit */
#define AM_FM175XX_TXMODE_INV_MOD          0x08    /**< \brief ��1,�������ݵĵ��Ʒ��� */

/** @} */


/**
 * \name RxMode�Ĵ�������,��������������ʺ�֡��ʽ (0x13)
 * @{
 */
 
#define AM_FM175XX_RXMODE_RXCRC_EN         0x80    /**< \brief ��1���ݽ���ʱʹ��CRCУ������(��106kbit������0) */
#define AM_FM175XX_RXMODE_RXSPEED_MASK     0x70    /**< \brief ������������ */
#define AM_FM175XX_RXMODE_RXSPEED_106KBIT  0x00    /**< \brief ��������106kbit */
#define AM_FM175XX_RXMODE_RXSPEED_212KBIT  0x10    /**< \brief ��������212kbit */
#define AM_FM175XX_RXMODE_RXSPEED_424KBIT  0x20    /**< \brief ��������424kbit */
#define AM_FM175XX_RXMODE_RXSPEED_848KBIT  0x30    /**< \brief ��������848kbit */
#define AM_FM175XX_RXMODE_RXNOERR          0x08    /**< \brief ��1,������Ч������,���������ּ���.����14443B,����RxSOFReq��Ϊ1 */
#define AM_FM175XX_RXMODE_RXMULTIPLE       0x04    /**< \brief ��0,���������յ�һ������֮֡���ٽ���.��1,������ն������֡ */

/** @} */


/**
 * \name TxControl�Ĵ�������,������������Tx1��Tx2���� (0x14)
 *
 * \note FM17510û��TX2��صĶ���
 * @{
 */
#define AM_FM175XX_TXCONTROL_INV_TX2RF_ON  0x80    /**< \brief ��1,��TX2����ʹ��,������TX2������ź�ȡ�� */
#define AM_FM175XX_TXCONTROL_INV_TX1RF_ON  0x40    /**< \brief ��1,��TX1����ʹ��,������TX2������ź�ȡ�� */
#define AM_FM175XX_TXCONTROL_INV_TX2RF_OFF 0x20    /**< \brief ��1,��TX2�����ر�,������TX2������ź�ȡ�� */
#define AM_FM175XX_TXCONTROL_INV_TX1RF_OFF 0x10    /**< \brief ��1,��TX1�����ر�,������TX2������ź�ȡ�� */
#define AM_FM175XX_TXCONTROL_TX2_CW        0x08    /**< \brief ��1,TX2���������δ���Ƶ�13.56MHz�������ز�;��0,����� */
#define AM_FM175XX_TXCONTROL_TX2RF_EN      0x02    /**< \brief ��1,TX2������ɷ������ݵ��Ƶ�13.56MHz�����ز� */
#define AM_FM175XX_TXCONTROL_TX1RF_EN      0x01    /**< \brief ��1,TX1������ɷ������ݵ��Ƶ�13.56MHz�����ز� */

/** @} */


/**
 * \name TxASK�Ĵ�������,������������ (0x15)
 * @{
 */

#define AM_FM175XX_TXASK_FORCE_100ASK      0x40    /**< \brief ��1,Force100ASKǿ������һ��100%ASK���� */

/** @} */


/**
 * \name TxSel�Ĵ�������,���������ź�Դѡ�� (0x16)
 * @{
 */
 
#define AM_FM175XX_TXSEL_DRIVER_SEL_MASK       0x30    /**< \brief ����Tx1��Tx2���������� */
#define AM_FM175XX_TXSEL_DRIVER_SEL_TRISTATE   0x00    /**< \brief ����Tx1��Tx2������ѡ����̬ */
#define AM_FM175XX_TXSEL_DRIVER_SEL_IN         0x10    /**< \brief ����Tx1��Tx2������ѡ���ڲ��������ĵ����ź� */
#define AM_FM175XX_TXSEL_DRIVER_SEL_TIN        0x20    /**< \brief ����Tx1��Tx2������ѡ��TIN�ĵ����ź� */
#define AM_FM175XX_TXSEL_DRIVER_SEL_HIGH       0x30    /**< \brief ����Tx1��Tx2����ѡ��ߵ�ƽ */
#define AM_FM175XX_TXSEL_TOUT_SEL_MASK         0x0f    /**< \brief ����Tx1��Tx2����ѡ��ߵ�ƽ */

/**
 * \name TOUT���ŵ�����ѡ��FM17510��֧�֣�
 * @{
 */
#define AM_FM175XX_TXSEL_TOUT_SEL_TRISTATE     0x00    /**< \brief TOUT���ŵ�����ѡ����̬ */
#define AM_FM175XX_TXSEL_TOUT_SEL_LOW          0x01    /**< \brief TOUT���ŵ�����ѡ��͵�ƽ */
#define AM_FM175XX_TXSEL_TOUT_SEL_HIGH         0x02    /**< \brief TOUT���ŵ�����ѡ��ߵ�ƽ */
#define AM_FM175XX_TXSEL_TOUT_SEL_Testbus      0x03    /**< \brief TOUT���ŵ�����ѡ��TestBus */
#define AM_FM175XX_TXSEL_TOUT_SEL_in           0x04    /**< \brief TOUT���ŵ�����ѡ���ڲ��������ĵ����ź� */
#define AM_FM175XX_TXSEL_TOUT_SEL_rcevs        0x05    /**< \brief TOUT���ŵ�����ѡ������͵Ĵ��������� */
#define AM_FM175XX_TXSEL_TOUT_SEL_sends        0x07    /**< \brief TOUT���ŵ�����ѡ����յ��Ĵ���������(��Ҫ��M1ģʽ��ʹ��) */

/** @} */

/** @} */


/**
 * \name RxSel�Ĵ�������,�ڲ����������� (0x17)
 * @{
 */
 
#define AM_FM175XX_RXSEL_UARTSEL_MASK          0xc0    /**< \brief ѡ��ǽӴ�UART���������� */
#define AM_FM175XX_RXSEL_UARTSEL_LOW           0x00    /**< \brief �ǽӴ�UART����̶��͵�ƽ */
#define AM_FM175XX_RXSEL_UARTSEL_TIN           0x40    /**< \brief TIN�İ����źţ�FM17510��֧�֣� */
#define AM_FM175XX_RXSEL_UARTSEL_IN            0x80    /**< \brief �����ڲ�ģ���·�ĵ����ź� */
#define AM_FM175XX_RXSEL_UARTSEL_TIN_M         0xc0    /**< \brief ��������TIN�ĵ����źţ��ٶȸ���424kbit��ʱ����Ч����FM17510��֧�֣� */
#define AM_FM175XX_RXSEL_RXWAIT                0x3f    /**< \brief ������ɷ����,����������Rxwait�����ʱ���ӳٺ󱻼��� */

/** @} */


/**
 * \name RxThreshold�Ĵ�������,������������ֵѡ�� (0x18)
 * @{
 */

/** \brief �������ܽ��յ���С�ź�ǿ��(�������ˮƽ��������) */
#define AM_FM175XX_RXTHRESHOLD_MINLEVEL   0xf0

/** \brief ���뵽������������˹�ر��������bit���ǿ��bit������ͻλ����С�ź�ǿ�� */
#define AM_FM175XX_RXTHRESHOLD_COLLLEVEL  0x07    

/** @} */


/**
 * \name Demod�Ĵ�������,��������� (0x19)
 * @{
 */
 
#define AM_FM175XX_DEMOD_ADDIQ_MASK        0xc0    /**< \brief ���չ�����I��Qͨ����ʹ������ */
#define AM_FM175XX_DEMOD_ADDIQ_S           0x00    /**< \brief ѡ���ǿͨ�� */
#define AM_FM175XX_DEMOD_ADDIQ_KEEP_S      0x40    /**< \brief ѡ���ǿͨ��,������ͨѶ�����б��ֲ��� */
#define AM_FM175XX_DEMOD_ADDIQ_IQ          0x80    /**< \brief �ϲ�I��Qͨ�� */
#define AM_FM175XX_DEMOD_FIXIQ             0x20    /**< \brief ��1ʱADDIQΪX0����չ̶�Iͨ��,ΪX1����չ̶�Qͨ��  */
#define AM_FM175XX_DEMOD_TYPEB_EOF_MODE    0x10    /**< \brief 0:�߼�0+��1+�޸��ز����� 1:�߼�0+�޸��ز����ƣ�FM17510��֧�֣� */
#define AM_FM175XX_DEMOD_TAU_RCV           0x0c    /**< \brief ���ݽ��չ����иı��ڲ�ʱ�䳣��(ע:����Ϊ00,PLL�����ݽ����ж���) */
#define AM_FM175XX_DEMOD_TAU_SYNC          0x03    /**< \brief ��burst�иı��ڲ�PLL��ʱ�䳣�� */

/** @} */


/**
 * \name Tx�Ĵ�������,���Ʋ���ISO/IEC 14443A������� (0x1c)
 * @{
 */
 
#define AM_FM175XX_TX_WAIT         0x03    /**< \brief ��λ�����˸�����Ӧʱ��.ȱʡֵΪ��λֵ��7bit */

/** @} */


/**
 * \name Rx�Ĵ������� (0x1d)
 * @{
 */
 
#define AM_FM175XX_RX_PARITY_DIS   0x10    /**< \brief ����λ��1,�շ���żУ�鶼�ر�,У��λ��Ϊ��ͨ����λ���� */

/** @} */


/**
 * \name TypeB�Ĵ�������,ISO/IEC 14443B���� (0x1e)��FM17510��֧�֣�
 * @{
 */

#define AM_FM175XX_TYPEB_RXSOF_REQ         0x80    /**< \brief ��λ��1,����SOF��ʼ���������ᱻ���� */
#define AM_FM175XX_TYPEB_RXEOF_REQ         0x40    /**< \brief ��λ��1,����EOF�������������ᴥ��Э����� */
#define AM_FM175XX_TYPEB_EOFSOF_WIDTH      0x10    /**< \brief ��1,SOF��EOF����ISO/IEC 14443B�ж������󳤶�;��0,������С���� */
#define AM_FM175XX_TYPEB_NO_TXSOF          0x08    /**< \brief ��1,������SOF */
#define AM_FM175XX_TYPEB_NO_TXEOF          0x04    /**< \brief ��1,������EOF */
#define AM_FM175XX_TYPEB_TX_EGT            0x03    /**< \brief EGT����,����Ϊ0,1,2��3 */

/** @} */


/**
 * \name SerialSpeed�Ĵ�������,ѡ����UART�ӿڵ��ٶȣ�FM17510��֧�֣� (0x1f)
 * @{
 */

#define AM_FM175XX_SERIALSPEED_BR_T0       0xe0    /**< \brief BR_T0�������ڵ��ڴ����ٶ� */
#define AM_FM175XX_SERIALSPEED_BR_T1       0x0f    /**< \brief BR_T1�������ڵ��ڴ����ٶ� */

/** @} */


/**
 * \name RFCfg�Ĵ�������,���ý��������� (0x26)
 * @{
 */
 
#define AM_FM175XX_RFCFG_RXGAIN_MASK       0x70    /**< \brief ��������ѹ����ָ������ */
#define AM_FM175XX_RFCFG_RXGAIN_18DB       0x00    /**< \brief ��������ѹ����ָ��18dB */
#define AM_FM175XX_RFCFG_RXGAIN_23DB       0x10    /**< \brief ��������ѹ����ָ��23dB */
#define AM_FM175XX_RFCFG_RXGAIN_18DB_TOO   0x20    /**< \brief ��������ѹ����ָ��18dB */
#define AM_FM175XX_RFCFG_RXGAIN_23DB_TOO   0x30    /**< \brief ��������ѹ����ָ��23dB */
#define AM_FM175XX_RFCFG_RXGAIN_33DB       0x40    /**< \brief ��������ѹ����ָ��33dB */
#define AM_FM175XX_RFCFG_RXGAIN_38DB       0x50    /**< \brief ��������ѹ����ָ��38dB */
#define AM_FM175XX_RFCFG_RXGAIN_43DB       0x60    /**< \brief ��������ѹ����ָ��43dB */
#define AM_FM175XX_RFCFG_RXGAIN_48DB       0x70    /**< \brief ��������ѹ����ָ��48dB */

/** @} */


/**
 * \name GsN�Ĵ�������,��������ʱ,ѡ��������������TX1��TX2��N�����ĵ絼 (0x27)
 * @{
 */

/**
 * \brief �޵���ʱ�����N�����ĵ絼,�������������,������������������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 *        3.�üĴ�����ֵֻ��TX1,TX2��������ʱʹ��
 */
#define AM_FM175XX_CWGSN                   0xf0

/**
 * \brief ����ʱ�����N�����ĵ絼,�ɿ��Ƶ������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 *        3.�üĴ�����ֵֻ��TX1,TX2��������ʱʹ��
 */
#define AM_FM175XX_MODGSN                  0x0f

/** @} */


/**
 * \name CWGsP�Ĵ�������,�������޵���ʱ��P�����ĵ絼 (0x28)
 * @{
 */

/**
 * \brief �޵���ʱ�����P�����ĵ絼,�������������,�������ļ���������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 */
#define AM_FM175XX_CWGSP                   0x3f

/** @} */


/**
 * \name ModGsP�Ĵ������� (0x29)
 * @{
 */

/**
 * \brief ����ʱ�����P�����ĵ絼,�������������,�������ļ���������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 */
#define AM_FM175XX_MODGSP                  0x3f

/** @} */


/**
 * \name TMode�Ĵ���,TPrescaler�Ĵ�������,�����˶�ʱ������ (0x2A)
 * @{
 */
 
#define AM_FM175XX_T_AUTO                  0x80    /**< \brief 0��ʱ������Э��Ӱ�� 1��ʱ���Զ����� */
#define AM_FM175XX_T_GATE_MASK             0x60    /**< \brief ��ʱ���ſ����� */
#define AM_FM175XX_T_GATE_NONE             0x00    /**< \brief ��ʱ�����ſ� */
#define AM_FM175XX_T_GATE_TIN              0x20    /**< \brief ��ʱ����TIN���ſ� */
#define AM_FM175XX_T_GATE_AUX1             0x40    /**< \brief ��ʱ����AUX1���ſ� */
#define AM_FM175XX_T_AUTO_RESTART          0x10    /**< \brief 1��ʱ������װ��ֵ�Զ�����������,0����������0ʱֹͣ */

/**
 * \brief TPrescaler�ĸ���λ
 *        ��ʱ��Ƶ�� f=13.56Mhz/(2*TPrescaler+1)
 *        TPrescaler=[TPrescaler_HI:TPrescaler_Lo]
 */
#define AM_FM175XX_T_PRESCALER_HI          0x0f    /**< \brief TPrescaler�ĸ���λ */

/** @} */


/**
 * \name TestSel1�Ĵ�������,�����ź����� (0x31)
 * @{
 */
 
#define AM_FM175XX_TSTBUS_BITSEL           0x07    /**< \brief �Ӳ�������ѡ��λ����TOUT */

/** @} */


/**
 * \name TestSel2�Ĵ�������,�����ź����ú�PRBS���� (0x32)
 * @{
 */
 
#define AM_FM175XX_TSTBUS_FLIP             0x80    /**< \brief ��1 �������߰�D432651˳��ӳ�䵽���ж˿� */
#define AM_FM175XX_PRBS9                   0x40    /**< \brief ����ITU-TO150������ʹ��PRBS9���� */
#define AM_FM175XX_PRBS15                  0x20    /**< \brief ����ITU-TO150������ʹ��PRBS15���� */
#define AM_FM175XX_TSTBUS_SEL              0x1f    /**< \brief ѡ��������� */

/** @} */


/**
 * \name TestPinEn�Ĵ�������,D1~D6�����������ʹ�� ��FM17510��֧�֣�(0x33)
 * @{
 */
#define AM_FM175XX_RS232LINE_EN            0x80    /**< \brief ��0 ����UART��MX��DTRQ����Ч */

/**
 * \brief ʹ��D1~D6�����������
 *        ��bit1��1,ʹ��D1�������;bit5��1,ʹ��D5�������
 *        ֻ��ʹ�ܴ��нӿ�ʱ��Ч.SPI=>D1~D4 UART��RS232LineEn��1ʱ=>D1~D4
 */
#define AM_FM175XX_TESTPIN_EN              0x7e

/** @} */


/**
 * \name TestPinValue�Ĵ�������,����I/Oʱ,������7λ���ж˿ڵ�ֵ��FM17510��֧�֣� (0x34)
 * @{
 */
 
#define AM_FM175XX_U_SEL_O                 0x80    /**< \brief ��1 ͨ����λ����7�����ж˿ڵ�I/O���� */

/**
 * \brief ����I/Oʱ,������7λ���ж˿ڵ�ֵ.ÿ���˿ڶ������ɼĴ���TestPinEn�Ĵ���
 *        �е�TestPinEnλ��ʹ��.
 *        ע:��UselO��1,���Ĵ�����ʾ������D6~D1��ʵ��״̬
 *           ��UselO��0,���Ĵ����õ�����TestPinValue�Ĵ�����ֵ
 */
#define AM_FM175XX_TEST_PIN_VALUE          0x7e

/** @} */


/**
 * \name TestCtrl�Ĵ�������,���Կ��� (0x36)
 * @{
 */
 
/** \brief ��1 ���������ڲ��źŴ��������Ե�ִ��,��������106kbitͨѶģʽ�µĲ������� */
#define AM_FM175XX_AMP_RCV                 0x40

/** @} */


/**
 * \name AnalogTest�Ĵ�������,��������AUX1��AUX2��FM17510��֧��AUX2�� (0x38)
 * @{
 */
 
#define AM_FM175XX_ANALOG_SEL_AUX1_MASK        0xf0    /**< \brief ����AUX1���� */
#define AM_FM175XX_ANALOG_SEL_AUX1_TRISTATE    0x00    /**< \brief AUX1��̬ */
#define AM_FM175XX_ANALOG_SEL_AUX1_DAC1        0x10    /**< \brief TestDAC1(AUX1)��� */
#define AM_FM175XX_ANALOG_SEL_AUX1_CORR1       0x20    /**< \brief �����ź�Corr1 */
#define AM_FM175XX_ANALOG_SEL_AUX1_CORR2       0x30    /**< \brief �����ź�Corr2 */
#define AM_FM175XX_ANALOG_SEL_AUX1_MINLEVEL    0x40    /**< \brief �����ź�MINLEVEL */
#define AM_FM175XX_ANALOG_SEL_AUX1_ADC_I       0x50    /**< \brief �����ź�ADCͨ��I */
#define AM_FM175XX_ANALOG_SEL_AUX1_ADC_Q       0x60    /**< \brief �����ź�ADCͨ��Q */
#define AM_FM175XX_ANALOG_SEL_AUX1_ADC_IQ      0x70    /**< \brief �����ź�ADCͨ��IQ�ϲ� */
#define AM_FM175XX_ANALOG_SEL_AUX1_HIGH        0xa0    /**< \brief HIGH */
#define AM_FM175XX_ANALOG_SEL_AUX1_LOW         0xb0    /**< \brief LOW */
#define AM_FM175XX_ANALOG_SEL_AUX1_T           0xc0    /**< \brief ������Ч״̬ */
#define AM_FM175XX_ANALOG_SEL_AUX1_R           0xd0    /**< \brief ������Ч״̬ */
#define AM_FM175XX_ANALOG_SEL_AUX1_SC          0xe0    /**< \brief ��⵽���ز� */
#define AM_FM175XX_ANALOG_SEL_AUX1_TESTBUS_BIT 0xf0    /**< \brief TestSel1�Ĵ�����TstBusBitSelλ����� */

#define AM_FM175XX_ANALOG_SEL_AUX2_MASK        0x0f    /**< \brief ����AUX2���� */
#define AM_FM175XX_ANALOG_SEL_AUX2_TRISTATE    0x00    /**< \brief AUX1��̬ */
#define AM_FM175XX_ANALOG_SEL_AUX2_DAC1        0x01    /**< \brief TestDAC2(AUX2)��� */
#define AM_FM175XX_ANALOG_SEL_AUX2_CORR1       0x02    /**< \brief �����ź�Corr1 */
#define AM_FM175XX_ANALOG_SEL_AUX2_CORR2       0x03    /**< \brief �����ź�Corr2 */
#define AM_FM175XX_ANALOG_SEL_AUX2_MINLEVEL    0x04    /**< \brief �����ź�MINLEVEL */
#define AM_FM175XX_ANALOG_SEL_AUX2_ADC_I       0x05    /**< \brief �����ź�ADCͨ��I */
#define AM_FM175XX_ANALOG_SEL_AUX2_ADC_Q       0x06    /**< \brief �����ź�ADCͨ��Q */
#define AM_FM175XX_ANALOG_SEL_AUX2_ADC_IQ      0x07    /**< \brief �����ź�ADCͨ��IQ�ϲ� */
#define AM_FM175XX_ANALOG_SEL_AUX2_HIGH        0x0a    /**< \brief HIGH */
#define AM_FM175XX_ANALOG_SEL_AUX2_LOW         0x0b    /**< \brief LOW */
#define AM_FM175XX_ANALOG_SEL_AUX2_T           0x0c    /**< \brief ������Ч״̬ */
#define AM_FM175XX_ANALOG_SEL_AUX2_R           0x0d    /**< \brief ������Ч״̬ */
#define AM_FM175XX_ANALOG_SEL_AUX2_SC          0x0e    /**< \brief ��⵽���ز� */
#define AM_FM175XX_ANALOG_SEL_AUX2_TESTBUS_BIT 0x0f    /**< \brief TestSel1�Ĵ�����TstBusBitSelλ����� */

/** @} */


/**
 * \name TestDAC1�Ĵ�������,����TestDAC1�Ĳ���ֵ (0x39)
 * @{
 */
 
/** \brief ����TestDAC1�Ĳ���ֵ.DAC1���������ͨ�����üĴ���AnalogTest��AUX1��0001���л���AUX1 */
#define AM_FM175XX_TESTDAC1        0x3f

/** @} */


/**
 * \name TestDAC2�Ĵ�������,����TestDAC2�Ĳ���ֵ (0x3a)
 * @{
 */
 
/** \brief ����TestDAC2�Ĳ���ֵ.DAC2���������ͨ�����üĴ���AnalogTest��AUX2��0001���л���AUX2 */
#define AM_FM175XX_TESTDAC2        0x3f

/** @} */


/**
 * \name TestADC�Ĵ�������,��ʾ��ADC I��Qͨ����ʵ��ֵ (0x3b)
 * @{
 */
 
#define AM_FM175XX_ADC_I           0xf0    /**< \brief ��ʾ��ADC Iͨ����ʵ��ֵ */
#define AM_FM175XX_ADC_Q           0x0f    /**< \brief ��ʾ��ADC Qͨ����ʵ��ֵ */

/** @} */


/**
 * \name LpcdCtrl��չ�Ĵ������� (0x0f/0x01)
 * @{
 */
#define AM_
#define AM_FM175XX_LPCD_EN          0x01    /**< \brief ʹ�� LPCDģʽ  */
#define AM_FM175XX_LPCD_RSTN        0x02    /**< \brief LPCD��λ   */
#define AM_FM175XX_LPCD_CALIBRA_EN  0x04    /**< \brief LPCD ����ģʽʹ��   */
#define AM_FM175XX_LPCD_CMP_1       0x08    /**< \brief �Ƚϴ��� 1��   */
#define AM_FM175XX_LPCD_CMP_3       0x13    /**< \brief �Ƚϴ���3��    */
#define AM_FM175XX_LPCD_IE          0x10    /**< \brief ʹ��LPCD�ж�  */
#define AM_FM175XX_CTRL_SET         0x20    /**< \brief LPCD �Ĵ���λ��������   */
#define AM_FM175XX_CTRL_CLR         0x00    /**< \brief LPCD �Ĵ���λ�������  */
/** @} */


/**
 * \name HpdCtrl��չ�Ĵ������� (0x0f/0x03)
 * @{
 */

#define AM_FM175XX_EXMODE          0xc0    /**< \brief ��չ�Ĵ���ģʽ��,����ʼ��0 */

/**
 * \brief �͹���ģʽ����
 *        ��0 ��pin NPD=0��LPCDEn=0(ȱʡ)ʱ,оƬ����DPDģʽ
 *        ��1 ��pin NPD=0��LPCDEn=0(ȱʡ)ʱ,оƬ����HPDģʽ
 */
#define AM_FM175XX_HPDEN           0x20

/** @} */

/**
 * \name Lpcd Irq��չ�Ĵ������� (0x0f/0x12)
 * @{
 */
#define AM_FM175XX_LPCD_INT_IDLE          0x00  /**< \brief ���ж�*/
#define AM_FM175XX_LPCD_CARD_IRQ          0x01  /**< \brief �������ж�*/
#define AM_FM175XX_LPCD_CALIB_IRQ         0x04  /**< \brief ��У����ж� */
#define AM_FM175XX_LPCD_WUP_IRQ           0x10  /**< \brief �Զ������ж� */
/** @} */

/**
 * \name UseRet��չ�Ĵ������� (0x0f/0x1b)
 * @{
 */

/**
 * \brief �͹���ģʽ����
 *        ��0 ���ṩ�ؼ����ݵı��湦��
 *        ��1 ��ʾ��HPDģʽ��LPCDģʽ�±���ؼ��Ĵ���������,���˳�ʱ�ĳ�ʼ������
 */
#define AM_FM175XX_USERET          0x10

/** @} */

/**
 * \name LPCD MISC��չ�Ĵ������� (0x0f/0x1c)
 * @{
 */

#define AM_FM175XX_LCPD_CALIB_VMID_EN  0x01    /**< \brief LPCD ��������ģʽ�е�Vmindʹ��*/

/** @} */


/**
 * \name LVDctrl��չ�Ĵ�������,�͵�ѹ�������� (0x0f/0x1d)
 * @{
 */

#define AM_FM175XX_LVD_IRQ         0x10    /**< \brief 1��ʾ�����͵�ѹ����,д0����˼Ĵ��� */
#define AM_FM175XX_LVD_EFF         0x08    /**< \brief �����͵�ѹ����ʱ1���ֵ�·��λ,0�����жϱ�־ */
#define AM_FM175XX_LVD_LE          0x04    /**< \brief 1�͵�ѹ�����ж�ʹ��,ȱʡ��ʹ�� */
#define AM_FM175XX_LVD_CTRL_MASK   0x03    /**< \brief ��ѹ�������� */
#define AM_FM175XX_LVD_CTRL_NONE   0x00    /**< \brief ��ʹ��LVD���� */
#define AM_FM175XX_LVD_CTRL_1_9V   0x01    /**< \brief ����1.9V���� */
#define AM_FM175XX_LVD_CTRL_2_1V   0x02    /**< \brief ����2.1V����(ȱʡ) */
#define AM_FM175XX_LVD_CTRL_2_4V   0x03    /**< \brief ����2.4V���� */

/** @} */


/**
 * @} am_if_fm175xx_reg
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __FM175XX_REG_H */

/* end of file */
