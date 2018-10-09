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
 * \brief I2C �ӻ����̣��жϷ�ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� I2C ������ SCL ���ţ�
 *   2. PIO0_11 �������� I2C ������ SDA ���š�
 *
 * - ʵ������
 *   1. �ӻ���������д��ַ�����ݵ��ӻ�����ͨ�����ڴ�ӡ������
 *   2. �ӻ������������������ݣ���ͨ�����ڴ�ӡ����
 *   3. LED0 �� 200ms ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc_hw_i2c_slave_int.c src_lpc_hw_i2c_slave_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_i2c_slave_int
 * \copydoc demo_lpc_hw_i2c_slave_int.c
 */

/** [src_lpc_hw_i2c_slave_int] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc82x_clk.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __OPERATE_ADDR    0x50             /**< \brief ���������ӻ���ַ���� */

#define __TEST_LENTH      8                /**< \brief ���Զ�д���ֽ��� */

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
volatile uint8_t __g_i2c_slv_rxrdy_flg  = 0;  /**< \brief �ӻ�����׼��������ʶ */
volatile uint8_t __g_i2c_slv_txrdy_flg  = 0;  /**< \brief �ӻ�����׼��������ʶ */

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
am_local int __i2c_slave_init (amhw_lpc_i2c_t *p_hw_i2c,
                               uint8_t         dev_addr)
{
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_SLAVE_MODE);
    amhw_lpc_i2c_slv_addr_set(p_hw_i2c, AMHW_LPC_I2C_SLVADR_0, dev_addr);
    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_SLAVE_MODE);

    return AM_OK;
}

/**
 * \brief I2C �ӻ���������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_txbuf  ��������/��ַ����
 * \param[in] nbytes   ���ͻ���ĳ���
 *
 * \retval AM_OK �������
 */
am_local int __i2c_slv_send (amhw_lpc_i2c_t   *p_hw_i2c,
                             am_const uint8_t *p_txbuf,
                             uint32_t          nbytes)
{
    uint8_t i = 0;

    amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND);

    for (i = 0; i < nbytes; i++) {
        while (!__g_i2c_slv_txrdy_flg);
        __g_i2c_slv_txrdy_flg = 0;

        /* �ӻ�д������ */
        amhw_lpc_i2c_slvdat_write(p_hw_i2c, *p_txbuf++);

        amhw_lpc_i2c_slv_continue(p_hw_i2c);
        amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND);
    }

    return AM_OK;
}

/**
 * \brief I2C �ӻ���������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_rxbuf  ��������/��ַ����
 * \param[in] nbytes   ���ջ���ĳ���
 *
 * \retval AM_OK �������
 */
am_local int __i2c_slv_recv (amhw_lpc_i2c_t *p_hw_i2c,
                             uint8_t        *p_rxbuf,
                             uint32_t        nbytes)
{
    uint8_t i = 0;

    amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND);
    am_kprintf("2.\n");
    for (i = 0; i < nbytes; i++) {

        while (!__g_i2c_slv_rxrdy_flg);
        __g_i2c_slv_rxrdy_flg = 0;
    am_kprintf("3.\n");
        /* �ӻ��������� */
        *p_rxbuf++ = amhw_lpc_i2c_slvdat_read(p_hw_i2c);

        amhw_lpc_i2c_slv_continue(p_hw_i2c);
        amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND);

    }

    return AM_OK;
}

/**
 * \brief I2C �ӻ�����״̬����
 *
 * \param[in] p_hw_i2c   ָ�� I2C �Ĵ������ָ��
 * \param[in] i2c_status ��ǰ I2C ��������״̬����
 *
 * \return ��
 */
am_local void __i2c_slv_errorstat (amhw_lpc_i2c_t *p_hw_i2c,
                                   uint32_t        i2c_status)
{
    uint32_t slverr_stat = i2c_status;

    if(slverr_stat & AMHW_LPC_I2C_STAT_SLVNOTSTR) {
        p_hw_i2c->intenclr = AMHW_LPC_I2C_STAT_SLVNOTSTR;

    } else if (slverr_stat & AMHW_LPC_I2C_STAT_SLVDESEL) {
        p_hw_i2c->stat = AMHW_LPC_I2C_STAT_SLVDESEL;
    }
}

/**
 * \brief I2C �ӻ�״̬������
 *
 * \param[in] p_hw_i2c   ָ�� I2C �Ĵ������ָ��
 * \param[in] i2c_status ��ǰ I2C ��������״̬����
 *
 * \return ��
 */
am_local void __i2c_slv_sm_event (amhw_lpc_i2c_t *p_hw_i2c,
                                  uint32_t        i2c_status)
{
    uint32_t i2c_slv_stat = (p_hw_i2c->stat) & AMHW_LPC_I2C_SLAVE_STATE_MASK;

    switch (i2c_slv_stat) {

    case AMHW_LPC_I2C_STAT_SLVADDR:
        amhw_lpc_i2c_slv_continue(p_hw_i2c);
        amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND);
        break;

    case AMHW_LPC_I2C_STAT_SLVRX:
        __g_i2c_slv_rxrdy_flg = 1;
        break;

    case AMHW_LPC_I2C_STAT_SLVTX:
        __g_i2c_slv_txrdy_flg = 1;
        break;

    default:
        break;
    }
}

/**
 * \brief I2C �ӻ��жϷ�����
 *
 * \param[in] p_arg �жϺ�������ڲ���
 *
 * \return ��
 */
am_local void __i2c_slave_isr (void *p_arg)
{
    amhw_lpc_i2c_t *p_hw_i2c   = (amhw_lpc_i2c_t *)p_arg;
    uint32_t        i2c_status = p_hw_i2c->intstat;

    if (i2c_status == 0) {
        return;
    }

    __i2c_slv_errorstat(p_hw_i2c, i2c_status);

    if (i2c_status & AMHW_LPC_I2C_STAT_SLVPEND) {
        p_hw_i2c->intenclr = AMHW_LPC_I2C_INTENCLR_SLVPEND;
        __i2c_slv_sm_event(p_hw_i2c, i2c_status);
    }
}

void demo_lpc_hw_i2c_slave_int_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                      int             inum)
{
    uint8_t  i2c_rxdata_buf[__TEST_LENTH] = {0};
    uint8_t  i2c_rxaddr_buf[__TEST_LENTH] = {0};
    uint16_t i                            = 0;

    /* I2C �ӻ���ʼ������ */
    __i2c_slave_init(p_hw_i2c, __OPERATE_ADDR);

    /* ʹ�� slave ����ж� */
    amhw_lpc_i2c_int_enable(p_hw_i2c, AMHW_LPC_I2C_INTENSET_SLVPEND |
                                      AMHW_LPC_I2C_INTENSET_SLVNOTSTR |
                                      AMHW_LPC_I2C_INTENSET_SLVDESEL);

    am_int_connect(inum, __i2c_slave_isr, p_hw_i2c);
    am_int_enable(inum);

    am_kprintf("1.\n");
    
    /* �����������͸��ӻ��ĵ�ַ */
    __i2c_slv_recv(p_hw_i2c,
                   (uint8_t *)i2c_rxaddr_buf,
                   1);
    am_kprintf("10.\n");
    /* �����������͸��ӻ������� */
    __i2c_slv_recv(p_hw_i2c,
                   (uint8_t *)i2c_rxdata_buf,
                   __TEST_LENTH);

    /* �����������͸��ӻ��ĵ�ַ */
    __i2c_slv_recv(p_hw_i2c,
                   (uint8_t *)i2c_rxaddr_buf,
                   1);


    /* ���ʹ��������յ������� */
    __i2c_slv_send(p_hw_i2c,
                   (uint8_t *)i2c_rxdata_buf,
                   __TEST_LENTH);

    AM_DBG_INFO("slave receive address is 0x%02x \r\n", i2c_rxaddr_buf[0]);

    for (i = 0;i < __TEST_LENTH; i++) {
        AM_DBG_INFO("slave transmit %2dst data is 0x%02x \r\n",
                    i,
                    i2c_rxdata_buf[i]);
    }
}
/** [src_lpc_hw_i2c_slave_int] */

/* end of file */
