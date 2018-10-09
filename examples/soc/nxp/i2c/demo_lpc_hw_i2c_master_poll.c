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
 * \brief I2C ��д EEPROM ���̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� EEPROM �� SCL ���ţ�
 *   2. PIO0_11 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� __TEST_LENTH �ֽ����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *   3. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED0 �� 200ms �����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc_hw_i2c_master_poll.c src_lpc_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_i2c_master_poll
 * \copydoc demo_lpc_hw_i2c_master_poll.c
 */

/** [src_lpc_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc82x_clk.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __I2C_M_7BIT    0x0000u          /**< \brief 7-bits �豸��ַ */
#define __I2C_M_10BIT   0x0001u          /**< \brief 10-bit �豸��ַ */
#define __I2C_M_WR      0x0000u          /**< \brief д���� */
#define __I2C_M_RD      0x0002u          /**< \brief ������ */
#define __I2C_M_NOSTART 0x0010u          /**< \brief ��������������ʶ */

#define __TEST_LENTH    8                /**< \brief ���Զ�д���ֽ���(���ܴ���ҳ��С) */

/**
 * \brief I2C ����ṹ�嶨�壬��Ҫ���� I2C ��ѯģʽ��
 */
typedef struct i2c_transfer {

    /** \brief I2C �豸��ַ */
    volatile uint16_t addr;

    /** \brief I2C �豸�����Լ� transfer ��Ҫ�������ʶ */
    volatile uint16_t flags;

    /** \brief I2C �������ݻ���ָ�� */
    volatile void    *p_buf;

    /** \brief I2C ���ݻ��泤�� */
    volatile uint16_t length;
} i2c_transfer_t;

/** \brief I2C ����ṹ�� */
am_local i2c_transfer_t __g_i2c0_transfer;

/**
 * \brief I2C ����ṹ��������ú���
 *
 * \param[in] p_trans ָ�� I2C ����ṹ���ָ��
 * \param[in] addr    �豸��ַ����
 * \param[in] flags   ������Ʊ�ʶλ����
 * \param[in] p_buf   ָ���ͻ��߽������ݻ����ָ��
 * \param[in] length  ������ֽڳ��Ȳ���
 *
 * \retval AM_OK ����ṹ���������
 */
am_local int __i2c_mktrans (i2c_transfer_t *p_trans,
                            uint16_t        addr,
                            uint16_t        flags,
                            void           *p_buf,
                            uint16_t        length)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }

    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf;
    p_trans->length = length;

    return AM_OK;
}

/**
 * \brief I2C ������������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_trans  ָ�� I2C ����ṹ���ָ��
 *
 * \return ��
 */
am_local void __i2c_mst_start (amhw_lpc_i2c_t *p_hw_i2c,
                               i2c_transfer_t *p_trans)
{
    uint16_t dev_addr = (p_trans->addr) << 1;

    if(!(p_trans->flags & __I2C_M_NOSTART)) {

        if (p_trans->flags & __I2C_M_RD) {
            dev_addr |= 0x1;            /* ���� bit0 Ϊ 1��������ǰΪ������ */
        } else {
            dev_addr |= 0x0;            /* ���� bit0 Ϊ 0��������ǰΪд���� */
        }

        /* �����豸��ַ */
        amhw_lpc_i2c_mstdat_write(p_hw_i2c, dev_addr);
        amhw_lpc_i2c_mst_start(p_hw_i2c);       /* I2C ���������������ź� */
    }
}

/**
 * \brief I2C �������͵�ַ/����
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_trans  ָ�� I2C ����ṹ���ָ��
 *
 * \retval AM_OK �������
 */
am_local int __i2c_mst_send (amhw_lpc_i2c_t *p_hw_i2c,
                             i2c_transfer_t *p_trans)

{
    uint8_t i = 0;

    for (i = 0; i < p_trans->length; i++) {

        while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));
        while ((p_hw_i2c->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
               AMHW_LPC_I2C_STAT_MSTTX);

        amhw_lpc_i2c_mstdat_write(p_hw_i2c, ((uint8_t *)(p_trans->p_buf))[i]);
        amhw_lpc_i2c_mst_continue(p_hw_i2c);
    }
    while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));
    while ((p_hw_i2c->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
           AMHW_LPC_I2C_STAT_MSTTX);

    return AM_OK;
}

/**
 * \brief I2C�������յ�ַ/����
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_trans  ָ�� I2C ����ṹ���ָ��
 *
 * \retval AM_OK �������
 */
am_local int __i2c_mst_recv (amhw_lpc_i2c_t *p_hw_i2c,
                             i2c_transfer_t *p_trans)
{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {
        while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));

        while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));
        while ((p_hw_i2c->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
                    AMHW_LPC_I2C_STAT_MSTRX);

        /* �������� */
        ((uint8_t *)(p_trans->p_buf))[i] = amhw_lpc_i2c_mstdat_read(p_hw_i2c);

        if (i != (p_trans->length - 1)) {
            amhw_lpc_i2c_mst_continue(p_hw_i2c);
        }
    }
    return AM_OK;
}


/**
 * \brief I2C ������ʼ������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] speed    �����ٶȲ���
 * \param[in] clkdiv   I2C ����ʱ�ӷ�Ƶ����
 *
 * \retval  AM_OK     �������
 * \retval -AM_EINVAL ������Ч
 */
am_local int __i2c_mst_init (amhw_lpc_i2c_t *p_hw_i2c,
                             uint32_t        clkdiv)
{
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* �ر� I2C �����������ò��� */
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    /* ����ʱ�ӷ�Ƶ���� */
    amhw_lpc_i2c_clkdiv_set(p_hw_i2c, clkdiv);

    /* ����������ɣ����� I2C ������ */
    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    return AM_OK;
}

void demo_lpc_hw_i2c_master_poll_entey(amhw_lpc_i2c_t *p_hw_i2c,
                                       uint32_t        clkdiv,
                                       uint8_t         addr)
{
    uint8_t         i                        = 0;
    uint8_t         eeprom_buf[__TEST_LENTH] = {0};
    uint8_t         test_addr[2]             = {0x00};
    i2c_transfer_t *p_trans                  = &__g_i2c0_transfer;
    
    /* I2C ������ʼ������ */
    __i2c_mst_init(p_hw_i2c, clkdiv);

     /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  addr,
                  (__I2C_M_7BIT | __I2C_M_WR),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send(p_hw_i2c, p_trans);

    for (i = 0;i < __TEST_LENTH; i++) {
        eeprom_buf[i] = i + 0xA;
    }

     /* ���� transfer �ṹ�������д������ */
    __i2c_mktrans(p_trans,
                  addr,
                  (__I2C_M_7BIT | __I2C_M_NOSTART | __I2C_M_WR),
                  (uint8_t *)eeprom_buf,
                  __TEST_LENTH);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send(p_hw_i2c, p_trans);

    /* ������ǰ���� */
    amhw_lpc_i2c_mst_stop(p_hw_i2c);

    am_mdelay(10);

    /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  addr,
                  (__I2C_M_7BIT | __I2C_M_WR),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send(p_hw_i2c, p_trans);


   /* ���� transfer �ṹ���������ȡ���� */
    for (i = 0; i < __TEST_LENTH; i++) {
        eeprom_buf[i] = 0;
    }
    __i2c_mktrans(p_trans,
                  addr,
                  (__I2C_M_7BIT | __I2C_M_RD),
                  (uint8_t *)eeprom_buf,
                  __TEST_LENTH);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_recv(p_hw_i2c, p_trans);

    /* ������ǰ���� */
    amhw_lpc_i2c_mst_stop(p_hw_i2c);

    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < __TEST_LENTH; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is 0x%02x\r\n",
                    i,
                    eeprom_buf[i]);

        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 0xA)) {
            AM_DBG_INFO("verify failed!\r\n");
            break;
        }
    }

    if (__TEST_LENTH == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    /* У��ɹ���LED0 �� 200ms ʱ������˸ */
    AM_FOREVER {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}
/** [src_lpc_hw_i2c_master_poll] */

/* end of file */
