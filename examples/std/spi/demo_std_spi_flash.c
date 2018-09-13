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
 * \brief SPI ��д FLASH(MX25L3206E) ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �ӿں� FLASH ��Ӧ�Ľӿ����ӡ�
 *
 * - ʵ������
 *   1. д���ݵ� FLASH��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \note
 *   1. �ɼ������������£�ֱ��ʹ�� am_spi_write_then_read() ��
 *      am_spi_write_then_write() �������ɡ�
 *
 * \par Դ����
 * \snippet demo_std_spi_flash.c src_std_spi_flash
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_spi_flash
 * \copydoc demo_std_spi_flash.c
 */

/** [src_std_spi_flash] */
#include "ametal.h"
#include "am_spi.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**
 * \brief ���� FLASH �������
 */
#define WREN       0x06 /**< \brief SPI_FLASH дʹ������ */
#define WRDI       0x04 /**< \brief SPI_FLASH ��ȡ ID ���� */
#define RDSR       0x05 /**< \brief SPI_FLASH ��ȡ״̬���� */
#define WRSR       0x01 /**< \brief SPI_FLASH д״̬���� */
#define READ       0x03 /**< \brief SPI_FLASH ���������� */
#define WRITE      0x02 /**< \brief SPI_FLASH д�������� */
#define SE         0xD8 /**< \brief SPI_FLASH ������������ */
#define CHIP_ERASE 0x60 /**< \brief SPI_FLASH ��Ƭ�������� */

#define FLASH_PAGE_SIZE 256 /**< \brief SPI_FLASH ҳ��С���� */

#define TEST_ADDR 0x0000          /**< \brief SPI_FLASH ����ҳ��ַ */
#define TEST_LEN  FLASH_PAGE_SIZE /**< \brief �����ֽڳ��� */

static uint8_t g_tx_buf[TEST_LEN] = {0x9F}; /**< \brief SPI_FLASH д���ݻ��� */
static uint8_t g_rx_buf[TEST_LEN] = {0};    /**< \brief SPI_FLASH �����ݻ��� */

/**
 * \brief �ж� SPI_FLASH �Ƿ���æ״̬
 */
static am_bool_t flash_isbusy_chk (am_spi_device_t *p_dev)
{
    uint8_t cmd_data = RDSR;
    uint8_t status_data;

    am_spi_write_then_read(p_dev,
                          &cmd_data,
                           1,
                          &status_data,
                           1);

    return (status_data & 0x01) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief дʹ��
 */
static void flash_wren (am_spi_device_t *p_dev)
{
    uint8_t tx_cmd = WREN; /* ���͵�ָ�� */

    /* ���ô������������дʹ������ */
    am_spi_write_then_write(p_dev,
                           &tx_cmd,
                            1,
                            NULL,
                            0);
}

/**
 * \brief ��������
 */
static void spi_flash_erase (am_spi_device_t *p_dev, uint32_t addr )
{
    uint8_t tx_cmd[4]; /* ���͵�ָ�� */
    uint8_t cmd_len;   /* ָ��� */

    flash_wren(p_dev);

    tx_cmd[0] = SE;
    tx_cmd[1] = (addr >> 16) & 0xff;
    tx_cmd[2] = (addr >>  8) & 0xff;
    tx_cmd[3] = addr & 0xff;

    cmd_len   = 4;

    am_spi_write_then_write(p_dev,
                            tx_cmd,
                            cmd_len,
                            NULL,
                            0);

    /* �ȴ� FLASH ���ڿ���״̬ */
    while (flash_isbusy_chk(p_dev) == AM_TRUE);
}

/**
 * \brief д����
 */
static void spi_flash_write (am_spi_device_t *p_dev,
                             uint32_t         addr,
                             uint32_t         length)
{
    uint8_t tx_cmd[4]; /* ���͵�ָ�� */

    flash_wren(p_dev);

    /* д��дָ��� 24 λ��ַ */
    tx_cmd[0] = WRITE;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;

    am_spi_write_then_write(p_dev,
                            tx_cmd,
                            4,
                            g_tx_buf,
                            length);

    /* �ȴ� FLASH ���ڿ���״̬ */
    while (flash_isbusy_chk(p_dev) == AM_TRUE);
}

/**
 * \brief ������
 */
 static void spi_flash_read (am_spi_device_t *p_dev,
                             uint32_t         addr,
                             uint32_t         length)
{
    uint8_t tx_cmd[4]; /* ���͵�ָ�� */

    /* д���ָ��� 24 λ��ַ */
    tx_cmd[0] = READ;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;

    am_spi_write_then_read(p_dev,
                           tx_cmd,
                           4,
                           g_rx_buf,
                           length);

    /* �ȴ� FLASH ���ڿ���״̬ */
    while (flash_isbusy_chk(p_dev) == AM_TRUE);
}

/**
 * \brief ID ���
 */
static void flash_id_chk (am_spi_device_t *p_dev)
{
    uint8_t tx_cmd = 0x9F; /* ���͵�ָ�� */
    uint8_t rd_id[3];

    am_spi_write_then_read(p_dev,
                          &tx_cmd,
                           1,
                           rd_id,
                           3);

    /* �ȴ� FLASH ���ڿ���״̬ */
    while (flash_isbusy_chk(p_dev) == AM_TRUE);

    AM_DBG_INFO("The ID is %x, %x ,%x\r\n", rd_id[0], rd_id[1], rd_id[2]);
}

/**
 * \brief FLASH ����
 */
static void spi_flash_test_demo (am_spi_device_t *p_dev,
                                 uint32_t         addr,
                                 uint32_t         length)
{
    uint32_t i;

    /* ���оƬ ID */
    flash_id_chk(p_dev);

    /* ������ǰ��ַ������ */
    spi_flash_erase(p_dev, addr);

    AM_DBG_INFO("FLASH erase ok\r\n");

    for (i = 0; i < length; i++) {
        g_tx_buf[i] = i + 1;
    }

    /* д�����ݵ��趨 FLASH ��ַ */
    spi_flash_write(p_dev, addr, length);
    am_mdelay(10);

    AM_DBG_INFO("FLASH write ok\r\n");

    for (i = 0; i < length; i++) {
        g_rx_buf[i] = 0;
    }

    /* ���趨�� FLASH ��ַ�ж�ȡ���� */
    spi_flash_read(p_dev, addr, length);
    am_mdelay(10);

    /* ����У�� */
    for (i = 0; i < length; i++) {

        /* ����ȡ��������ͨ�����ڴ�ӡ���� */
        AM_DBG_INFO(" read %2dst data is : 0x%2x \r\n", i, g_rx_buf[i]);
        if(g_rx_buf[i] != ((1 + i) & 0xFF)) {
            AM_DBG_INFO("verify failed!\r\n");
            while(1);
        }
    }
}

/**
 * \brief �������
 */
void demo_std_spi_flash_entry (am_spi_handle_t spi_handle,
                               int             cs_pin,
                               uint32_t        test_addr,
                               uint32_t        test_length)
{
    am_spi_device_t g_spi_device;

    am_spi_mkdev(&g_spi_device,
                  spi_handle,
                  8,
                  AM_SPI_MODE_0,
                  1000000,
                  cs_pin,
                  NULL);

    am_spi_setup(&g_spi_device);

    AM_DBG_INFO("SPI flash test start!\r\n");

    spi_flash_test_demo(&g_spi_device, test_addr, test_length);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_spi_flash] */

/* end of file */
