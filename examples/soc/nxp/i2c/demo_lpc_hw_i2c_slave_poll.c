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
 * \brief I2C �ӻ����̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� I2C ������ SCL ���ţ�
 *   2. PIO0_11 �������� I2C ������ SDA ���š�
 *
 * \note
 *    �����̿�������ģ�� EEPROM��
 *
 * \par Դ����
 * \snippet demo_lpc_hw_i2c_slave_poll.c src_lpc_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_i2c_slave_poll
 * \copydoc demo_lpc_hw_i2c_slave_poll.c
 */

/** [src_lpc_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define __OPERATE_ADDR      0x50         /**< \brief ���������ӻ���ַ���� */

#define __EEPROM_BUFFER_LEN (0x20)       /**< \brief ģ��� EEPROM ��������С */

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
am_local uint32_t  __g_operate;              /**< \brief I2C �ӻ�����λ */
am_local am_bool_t __g_ssub_addr = AM_FALSE; /**< \brief I2C �ӻ���ַ��־ */
am_local uint8_t   __g_sub_addr;             /**< \brief I2C �ӻ���ַ */

am_local uint8_t   __g_eeprom_buf[__EEPROM_BUFFER_LEN]; /**< \brief ������ */

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
am_local int __i2c_slave_init (amhw_lpc_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_SLAVE_MODE);
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);

    amhw_lpc_i2c_slv_addr_set(p_hw_i2c, AMHW_LPC_I2C_SLVADR_0, dev_addr);

    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_SLAVE_MODE);

    return AM_OK;
}

/**
 * \brief I2C ״̬������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __i2c_slave_event (amhw_lpc_i2c_t *p_hw_i2c)
{
    if (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVPEND)) {
        return ;
    }

    /* �ӻ�δѡ�� */
    if (p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVDESEL) {
        __g_operate = 0;
        p_hw_i2c->stat |= AMHW_LPC_I2C_STAT_SLVDESEL;
        return ;
    }

    switch (p_hw_i2c->stat & AMHW_LPC_I2C_SLAVE_STATE_MASK) {

    /* �������ʹӻ���ַ */
    case AMHW_LPC_I2C_STAT_SLVADDR:

        /* �ӻ���ַƥ��ɹ� */
        if (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVIDX_MASK)) {
            __g_operate = amhw_lpc_i2c_slvdat_read(p_hw_i2c) & 0x1;
            if (!__g_operate) {
                __g_ssub_addr = AM_TRUE;
            } else {
                __g_operate = 1;
            }
            amhw_lpc_i2c_slv_continue(p_hw_i2c);
        }
        break;

    /* �ӻ����վ��� */
    case AMHW_LPC_I2C_STAT_SLVRX:
        if (__g_ssub_addr == AM_TRUE) {
            __g_sub_addr = amhw_lpc_i2c_slvdat_read(p_hw_i2c);
            amhw_lpc_i2c_slv_continue(p_hw_i2c);
            __g_ssub_addr =  AM_FALSE;
            break;
        }

        /* δ�� __g_sub_addr �Ϸ��Ե��ж� */
        __g_eeprom_buf[__g_sub_addr++] = amhw_lpc_i2c_slvdat_read(p_hw_i2c);
        amhw_lpc_i2c_slv_continue(p_hw_i2c);

        break;

    /* �ӻ����;��� */
    case AMHW_LPC_I2C_STAT_SLVTX:
        if (__g_operate) {
            amhw_lpc_i2c_slvdat_write(p_hw_i2c, __g_eeprom_buf[__g_sub_addr++]);
            amhw_lpc_i2c_slv_continue(p_hw_i2c);
        }
        break;

    default:
        break;
    }
}

void demo_lpc_hw_i2c_slave_poll_entry (amhw_lpc_i2c_t *p_hw_i2c)
{
    __i2c_slave_init(p_hw_i2c, __OPERATE_ADDR); /* I2C �ӻ���ʼ������ */

    AM_FOREVER {
        __i2c_slave_event(p_hw_i2c);
    }
}
/** [src_lpc_hw_i2c_slave_poll] */

/* end of file */
