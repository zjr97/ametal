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
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� I2C ������ SCL ���ţ�
 *   2. PIOB_7 �������� I2C ������ SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_i2c_slave_poll.c src_zlg116_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg116_hw_i2c_slave_poll
 * \copydoc demo_zlg116_hw_i2c_slave_poll.c
 */

/** [src_zlg116_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** ���������ӻ���ַ���� */
#define OPERATE_ADDR      0x50

#define EEPROM_BUFFER_LEN (0x20)

#define __I2C_SLV_ST_IDLE         0      /*< \brief ����״̬ */
#define __I2C_SLV_ST_ADDR_MATCH   1      /*< \brief ��ַƥ��״̬ */
#define __I2C_SLV_ST_SUBADDR_GET  2      /*< \brief ��ȡ�ӵ�ַ״̬ */
#define __I2C_SLV_ST_TXBYTE_GET   3      /*< \brief ��ȡ���͵�����״̬ */
#define __I2C_SLV_ST_RXBYTE_PUT   4      /*< \brief �������� ״̬*/
#define __I2C_SLV_ST_STOP         5      /*< \brief ֹͣ״̬ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static am_bool_t is_sub_addr = AM_FALSE;      /**< I2C �ӻ���ַ��־ */
static uint8_t   sub_addr;                    /**< I2C �ӻ���ַ */
static uint8_t   eeprom[EEPROM_BUFFER_LEN];   /**< ������ */

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
static int __i2c_slave_init (amhw_zlg_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* �ر� I2C �����������ò��� */
    amhw_zlg_i2c_disable(p_hw_i2c);

    amhw_zlg_i2c_rx_tl_set(p_hw_i2c, 0);
    amhw_zlg_i2c_tx_tl_set(p_hw_i2c, 1);

    amhw_zlg_i2c_slave_addr_set (p_hw_i2c, dev_addr);

    p_hw_i2c->ic_con = AMHW_ZLG_I2C_SLAVE |
                       AMHW_ZLG_I2C_7BITADDR_SLAVE;

    amhw_zlg_i2c_intr_mask_clear (p_hw_i2c, 0xfff);

    amhw_zlg_i2c_enable(p_hw_i2c);

    return AM_OK;
}

/**
 * \brief I2C ״̬������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 *
 * \return ��
 */

static void __i2c_slave_event (amhw_zlg_i2c_t *p_hw_i2c)
{
    static uint8_t status = __I2C_SLV_ST_IDLE;

    switch (status) {

    /* ����״̬ */
    case __I2C_SLV_ST_IDLE:
        if (p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_START_DET) {
            amhw_zlg_i2c_clr_start_det_get(p_hw_i2c);
        } else {
            break;
        }
        /* no break */

     /* ��ַƥ��״̬ */
    case __I2C_SLV_ST_ADDR_MATCH:

        if( p_hw_i2c->ic_status & AMHW_ZLG_STATUS_FLAG_SLV_ACTIVITY) {
            status = __I2C_SLV_ST_SUBADDR_GET;
            sub_addr = 0;
        } else {
            status = __I2C_SLV_ST_IDLE;
        }
        break;

    /* ��ȡ�ӵ�ַ״̬  */
    case __I2C_SLV_ST_SUBADDR_GET:
        if ( is_sub_addr ==  AM_TRUE ) {
            if( p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_RX_FULL ) {
                sub_addr =  amhw_zlg_i2c_dat_read (p_hw_i2c);
                is_sub_addr = AM_FALSE;
            }
        } else {
            if (p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_RD_REQ ) {
                amhw_zlg_i2c_clr_rd_req_get(p_hw_i2c);
                status = __I2C_SLV_ST_TXBYTE_GET;
                is_sub_addr = AM_TRUE;
            } else if (p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_RX_FULL ){
                status = __I2C_SLV_ST_RXBYTE_PUT;
                is_sub_addr = AM_TRUE;
            }
        }
        break;

    /* ��ȡ���͵�����״̬  */
    case __I2C_SLV_ST_TXBYTE_GET:
        if (p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_TX_EMPTY ) {
            amhw_zlg_i2c_dat_write (p_hw_i2c, eeprom[sub_addr++]);
            sub_addr %= EEPROM_BUFFER_LEN;
        }

        if(p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_STOP_DET) {
            amhw_zlg_i2c_clr_stop_det_get(p_hw_i2c);
            status = __I2C_SLV_ST_STOP;
        }

        break;

    /* �������� ״̬  */
    case __I2C_SLV_ST_RXBYTE_PUT:
        if ( p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_RX_FULL ) {
            eeprom[sub_addr++] = amhw_zlg_i2c_dat_read (p_hw_i2c);
            sub_addr %= EEPROM_BUFFER_LEN;
        }
        if(p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_STOP_DET) {
            amhw_zlg_i2c_clr_stop_det_get(p_hw_i2c);
            status = __I2C_SLV_ST_STOP;
        }
        break;

    /* ֹͣ״̬ */
    case __I2C_SLV_ST_STOP:

        /** �����������������ʱ �����������ܻ������ݣ�������ֹ����1,��ʱ��� */
        if ( p_hw_i2c->ic_raw_intr_stat & AMHW_ZLG_INT_FLAG_TX_ABRT ) {
            amhw_zlg_i2c_clr_tx_abrt_get(p_hw_i2c);
        }
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c, AMHW_ZLG_INT_FLAG_TX_EMPTY);

        status = __I2C_SLV_ST_IDLE;
        break;

    default:
        break;
    }
}

/**
 * \brief �������
 */
void demo_zlg_hw_i2c_slave_poll_entry (amhw_zlg_i2c_t *p_hw_i2c)
{

    __i2c_slave_init(p_hw_i2c, OPERATE_ADDR); /* I2C �ӻ���ʼ������ */

    while(1) {
        __i2c_slave_event(p_hw_i2c);
    }
}
/** [src_zlg116_hw_i2c_slave_poll] */

/* end of file */
