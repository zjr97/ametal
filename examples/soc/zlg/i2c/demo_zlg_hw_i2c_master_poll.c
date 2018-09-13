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
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ���� EEPROM �� I2C ���ŵ���Ӧ���š�
 *
 * - ʵ������
 *   1. д���ݵ� EEPROM��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_i2c_master_poll.c src_zlg116_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg116_hw_i2c_master_poll
 * \copydoc demo_zlg116_hw_i2c_master_poll.c
 */

/** [src_zlg116_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define I2C_M_7BIT    0x0000u          /**< \brief 7-bits �豸��ַ */
#define I2C_M_10BIT   0x0001u          /**< \brief 10-bit �豸��ַ */
#define I2C_M_WR      0x0000u          /**< \brief д���� */
#define I2C_M_RD      0x0002u          /**< \brief ������ */
#define I2C_M_NOSTART 0x0010u          /**< \brief ��������������ʶ */

#define I2C_SPEED     400000            /**< \brief I2C �������ٶȲ������� */
#define EEPROM_ADDR   (0xa0 >> 1)       /**< \brief EEPROM �豸��ַ���� */
#define TEST_LEN      0X08                 /**< \brief ���� EEPROM ��ҳ��С */

/**
 * \brief I2C ����ṹ�嶨�壬��Ҫ���� I2C ��ѯģʽ��
 */
typedef struct i2c_transfer {

    /** \brief I2C�豸��ַ */
    volatile uint16_t   addr;

    /** \brief I2C �豸�����Լ�transfer��Ҫ�������ʶ */
    volatile uint16_t   flags;

    /** \brief I2C �������ݻ���ָ�� */
    volatile void      *p_buf;

    /** \brief I2C ���ݻ��泤�� */
    volatile uint16_t   length;
} i2c_transfer_t;

/** \brief I2C ����ṹ�� */
static i2c_transfer_t __g_i2c1_transfer;

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
static int __i2c_mktrans (i2c_transfer_t *p_trans,
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
static void __i2c_mst_start (amhw_zlg_i2c_t *p_hw_i2c,
                             i2c_transfer_t *p_trans)
{
    if(!(p_trans->flags & I2C_M_NOSTART)) {

        amhw_zlg_i2c_disable(p_hw_i2c);

        /* �����豸��ַ */
        amhw_zlg_i2c_tar_set(p_hw_i2c, p_trans->addr);

        amhw_zlg_i2c_con_clear (p_hw_i2c, AMHW_ZLG_I2C_7BITADDR_MASTER);

        amhw_zlg_i2c_enable(p_hw_i2c);
		}

    if (p_trans->flags & I2C_M_RD) {
        amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0100);
    }
}

/**
 * \brief I2C �������͵�ַ/����
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  ָ��I2C����ṹ���ָ��
 * \param[in] stop     �Ƿ���ֹͣ�ź�
 *                         AM_TRUE  : ��
 *                         AM_FALSE : ��
 *
 * \retval AM_OK �������
 */
static int __i2c_mst_send (amhw_zlg_i2c_t *p_hw_i2c,
                           i2c_transfer_t *p_trans,
                           am_bool_t       stop)

{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {

        while (!(p_hw_i2c->ic_status & AMHW_ZLG_STATUS_FLAG_TFNF));
        if (i == (p_trans->length - 1) && stop) {
            amhw_zlg_i2c_dat_write(p_hw_i2c,
                                   0x200 | ((uint8_t *)(p_trans->p_buf))[i]);
        } else {
            amhw_zlg_i2c_dat_write(p_hw_i2c,
                                  ((uint8_t *)(p_trans->p_buf))[i]);
        }
    }

    while (!(p_hw_i2c->ic_status & AMHW_ZLG_STATUS_FLAG_MST_ACTIVITY));

    return AM_OK;
}

/**
 * \brief I2C �������յ�ַ/����
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  ָ��I2C����ṹ���ָ��
 * \param[in] stop     �Ƿ���ֹͣ�ź�
 *                         AM_TRUE  : ��
 *                         AM_FALSE : ��
 *
 * \retval AM_OK �������
 */
static int __i2c_mst_recv (amhw_zlg_i2c_t *p_hw_i2c,
                           i2c_transfer_t *p_trans,
                           am_bool_t       stop)
{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {
        while (!(p_hw_i2c->ic_status & AMHW_ZLG_STATUS_FLAG_RFNE));

        /* �������� */
        ((uint8_t *)(p_trans->p_buf))[i] = amhw_zlg_i2c_dat_read(p_hw_i2c);

        if (i == (p_trans->length - 2) && stop) {
            amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0300);
        } else if (i <= (p_trans->length - 2)){
            amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0100);
        }
    }
    return AM_OK;
}

/**
 * \brief I2C ������ʼ������
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] speed    �����ٶȲ���
 *
 * \retval  AM_OK     �������
 * \retval -AM_EINVAL ������Ч
 */
static int __i2c_mst_init (amhw_zlg_i2c_t *p_hw_i2c,
                           uint32_t        speed,
                           uint32_t        clk_rate)
{
    uint16_t mode  = AMHW_ZLG_I2C_NORMAL_SPEED;
    uint16_t count = (clk_rate / speed) / 2;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* �ر� I2C �����������ò��� */
    amhw_zlg_i2c_disable (p_hw_i2c);

    /* �������� */
    if (speed <= 100000) {
        amhw_zlg_i2c_ss_scl_low_set(p_hw_i2c, count);
        amhw_zlg_i2c_ss_scl_high_set(p_hw_i2c, count);
        mode = AMHW_ZLG_I2C_NORMAL_SPEED;
    } else {

        amhw_zlg_i2c_fs_scl_low_set(p_hw_i2c, count);
        amhw_zlg_i2c_fs_scl_high_set(p_hw_i2c, count);
        mode = AMHW_ZLG_I2C_HIGH_SPEED;
    }

    p_hw_i2c->ic_con = (mode |
                        AMHW_ZLG_I2C_MASTER |
                        AMHW_ZLG_I2C_RESTART_ENABLE);

    amhw_zlg_i2c_rx_tl_set(p_hw_i2c, 0);
    amhw_zlg_i2c_tx_tl_set(p_hw_i2c, 1);

    /* ����ж� */
    amhw_zlg_i2c_intr_mask_clear (p_hw_i2c, 0xfff);

    return AM_OK;
}

/**
 * \brief �������
 */
void demo_zlg_hw_i2c_master_poll_entry (amhw_zlg_i2c_t *p_hw_i2c,
                                        uint32_t        clk_rate)
{
    i2c_transfer_t *p_trans              = &__g_i2c1_transfer;
    uint8_t         eeprom_buf[16]       = {0};
    uint8_t         test_addr[2]         = {0x00};
    uint8_t         i;

    __i2c_mst_init(p_hw_i2c, I2C_SPEED, clk_rate);   /* I2C ������ʼ������ */

     /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_WR),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send (p_hw_i2c, p_trans, AM_FALSE);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = i + 0xA;
    }

     /* ���� transfer �ṹ�������д������ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_NOSTART | I2C_M_WR),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send(p_hw_i2c, p_trans, AM_TRUE);

    am_mdelay(10);

    /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_WR | I2C_M_NOSTART),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_send (p_hw_i2c, p_trans, AM_FALSE);


   /* ���� transfer �ṹ���������ȡ���� */
    for (i = 0; i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_RD),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mst_start(p_hw_i2c, p_trans);
    __i2c_mst_recv(p_hw_i2c, p_trans, AM_TRUE);

    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        am_kprintf("Read EEPROM the %2dth data is  : 0x%02x\r\n", i, eeprom_buf[i]);

        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 0xA)) {
            am_kprintf("verify failed!\r\n");
            break;
        }
    }

    if (TEST_LEN == i) {
        am_kprintf("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg116_hw_i2c_master_poll] */

/* end of file */
