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
 * \brief  ZigBee ģ�� ZM516X ����
 *
 * \internal
 * \par modification history:
 * - 1.01 18-01-16  pea, update API to v1.03 manual
 * - 1.00 15-09-06  afm, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zm516x.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_int.h"
#include <string.h>

#define __ZM516X_CFG_TAG    "\xAB\xBC\xCD"    /**< \brief ��������֡֡ͷ */
#define __ZM516X_COM_TAG    "\xDE\xDF\xEF"    /**< \brief ��ʱ����֡֡ͷ */

#define __ZM516X_CFG_END    0xAA              /**< \brief ��������֡֡β */

#define __ZM516X_CMD_BUF_LEN       100    /**< \brief ����泤�� */
#define __ZM516X_RSP_BUF_LEN       100    /**< \brief Ӧ�𻺴泤�� */
#define __ZM516X_CMD_SPACE_TIME    5      /**< \brief ����֡���ʱ�䣬��λ��ms */

/** \brief ���ò����������� */
enum __ZM516X_CFG_CMD {
    ZM516X_CFG_CONFIG_GET       = 0xD1,    /**< \brief ��ȡ�������� */
    ZM516X_CFG_CHAN_SET         = 0xD2,    /**< \brief ����ͨ���� */
    ZM516X_CFG_DISCOVER         = 0xD4,    /**< \brief ���� */
    ZM516X_CFG_REMOTE_GET       = 0xD5,    /**< \brief ��ȡԶ��������Ϣ */
    ZM516X_CFG_CONFIG_SET       = 0xD6,    /**< \brief �޸����ã����óɹ��踴λ */
    ZM516X_CFG_RESET            = 0xD9,    /**< \brief ��λ */
    ZM516X_CFG_REDEFAULT        = 0xDA,    /**< \brief �ָ��������ã����óɹ��踴λ */
    ZM516X_CFG_SRC_DIS          = 0xDC,    /**< \brief ��ͷ��ʾԴ��ַ�����óɹ��踴λ */
    ZM516X_CFG_GPIO_DIR         = 0xE1,    /**< \brief ����/��ȡ GPIO �������óɹ��踴λ */
    ZM516X_CFG_IO_ADC_UPLOAD    = 0xE2,    /**< \brief IO/AD �ɼ�����/��ȡ�����óɹ��踴λ */
    ZM516X_CFG_GPIO_STATE       = 0xE3,    /**< \brief ����/��ȡ GPIO ��ƽ */
    ZM516X_CFG_PWM              = 0xE4,    /**< \brief PWM ������� */
    ZM516X_CFG_NETWORK_SET      = 0xE5,    /**< \brief �������������ܣ����óɹ��踴λ */
    ZM516X_CFG_JOIN_ENABLE      = 0xE6,    /**< \brief ��������ӻ��������� */
    ZM516X_CFG_SLAVE_GET        = 0xE7,    /**< \brief ��ѯ����ģ��洢�Ĵӻ���Ϣ */
    ZM516X_CFG_STATE_GET        = 0xE8,    /**< \brief ��ѯ���ӻ�״̬ */
};

/** \brief ��ʱ������������ */
enum __ZM516X_COM_CMD {
    ZM516X_COM_CHAN_SET         = 0xD1,    /**< \brief �޸�ͨ���� */
    ZM516X_COM_DEST_SET         = 0xD2,    /**< \brief �޸�Ŀ�������ַ */
    ZM516X_COM_SRC_DIS          = 0xD3,    /**< \brief ��ͷ��ʾԴ��ַ */
    ZM516X_COM_GPIO_DIR_SET     = 0xD4,    /**< \brief ���� GPIO ���� */
    ZM516X_COM_GPIO_GET         = 0xD5,    /**< \brief ��ȡ GPIO ��ƽ */
    ZM516X_COM_GPIO_SET         = 0xD6,    /**< \brief ���� GPIO ��ƽ */
    ZM516X_COM_ADC_GET          = 0xD7,    /**< \brief ��ȡ ADC ��ֵ */
    ZM516X_COM_SLEEP            = 0xD8,    /**< \brief �������� */
    ZM516X_COM_MODE_SET         = 0xD9,    /**< \brief ����ͨѶģʽ */
    ZM516X_COM_CSQ_GET          = 0xDA,    /**< \brief ��ȡ�ź�ǿ�� */
};

/** \brief ���ò�����������Ӧ�� */
enum __ZM516X_CFG_ERR {
    ZM516X_CFG_OK              = 0x00,    /**< \brief �����ɹ� */
    ZM516X_CFG_LENGTH_FAUSE    = 0x01,    /**< \brief ֡���ȴ��� */
    ZM516X_CFG_ADDRESS_FAUSE   = 0x02,    /**< \brief ��ַ���� */
    ZM516X_CFG_CHECK_FAUSE     = 0x03,    /**< \brief ֡�ֽ�У����� */
    ZM516X_CFG_WRITE_FAUSE     = 0x04,    /**< \brief д���� */
    ZM516X_CFG_OTHER_FAUSE     = 0x05,    /**< \brief �������� */
};

/** \brief ��ʱ������������Ӧ�� */
enum __ZM516X_COM_ERR {
    ZM516X_COM_OK              = 0x00,    /**< \brief �����ɹ� */
};

typedef struct __firmware_info {
    uint8_t   runing_status;
    uint8_t   dev_type[2];
    uint8_t   firmware_version[2];
} __firmware_info_t;

/**
 * @addtogroup am_zm516x
 * @{
 */

/**
 * \brief ACK �����жϷ�����
 */
am_local void __ack_pint_isr (void *p_arg)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)p_arg;

    am_wait_done(&p_dev->ack_wait);
}

/** \brief ���� ZigBee ���� */
am_local am_bool_t am_zm516x_send_cmd (am_uart_rngbuf_handle_t  rngbuf_handle,
                                       uint8_t                 *p_cmd,
                                       uint16_t                 cmd_len,
                                       uint8_t                 *p_rsp,
                                       uint16_t                *p_rsp_len,
                                       uint16_t                 timeout)
{
    uint16_t  i;
    int32_t   len   = 0;
    int32_t   index = 0;
    int32_t   key;
    am_bool_t flag  = AM_FALSE;

    am_uart_rngbuf_send(rngbuf_handle, p_cmd, cmd_len);

    key = am_int_cpu_lock();

    am_rngbuf_flush(&rngbuf_handle->rx_rngbuf);

    am_int_cpu_unlock(key);

    if (p_rsp == NULL) {
        return AM_TRUE;   /* Ӧ���޷���ֵ��ֱ�ӷ��� AM_TRUE */
    }

    for (i = 0; i < timeout; i++) {
        len = am_uart_rngbuf_receive(rngbuf_handle,
                                     p_rsp,
                                     __ZM516X_RSP_BUF_LEN);
        if (len > 0) {
            index = len;
            flag = AM_TRUE;
            break;
        }
    }
    if (flag == AM_FALSE) {
        return AM_FALSE;
    }

    /* Ӧ��֡���Ϊ 100ms��Ӧ����� */
    for (i = 0; i < 10; i++) {
        len = am_uart_rngbuf_receive(rngbuf_handle,
                                    &p_rsp[index],
                                     __ZM516X_RSP_BUF_LEN - index);
        if (len > 0) {
            index += len;
            i = 0;
            continue;
        }
    }

    *p_rsp_len = index;

    return AM_TRUE;
}

/** \brief �� ZigBee ģ�鷢�� nbytes ���ֽ����� */
am_err_t am_zm516x_send (am_zm516x_handle_t handle,
                         const void        *p_buf,
                         size_t             nbytes)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;

    return am_uart_rngbuf_send(p_dev->uart_handle, (uint8_t *)p_buf, nbytes);
}

/** \brief �� ZigBee ģ�鷢�� nbytes ���ֽ����ݣ����ȴ� ACK */
am_err_t am_zm516x_send_with_ack (am_zm516x_handle_t handle,
                                  const void        *p_buf,
                                  size_t             nbytes)
{
    int32_t          num   = 0;
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;

    if (-1 == p_dev->p_devinfo->ack_pin) {
        return -AM_ENOTSUP;
    }

    num = am_uart_rngbuf_send(p_dev->uart_handle, (uint8_t *)p_buf, nbytes);

    if (am_wait_on_timeout(&p_dev->ack_wait,
                            p_dev->p_devinfo->ack_timeout) != AM_OK) {
        return -AM_ETIMEDOUT;
    } else {
        return num;
    }
}

/** \brief �� ZigBee ģ����� maxbytes ���ֽ����� */
am_err_t am_zm516x_receive (am_zm516x_handle_t handle,
                            void              *p_buf,
                            size_t             maxbytes)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;

    return am_uart_rngbuf_receive(p_dev->uart_handle,
                                  (uint8_t *)p_buf,
                                  maxbytes);
}

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief ��ȡ ZigBee ģ���������Ϣ���������D1�� */
am_err_t am_zm516x_cfg_info_get (am_zm516x_handle_t    handle,
                                 am_zm516x_cfg_info_t *p_info)
{
    am_zm516x_dev_t  *p_dev                         = (am_zm516x_dev_t *)handle;
    uint8_t           cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t           rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t          rsp_len;
    __firmware_info_t firmware_info;

    if ((NULL == handle) || (NULL == p_info)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_CONFIG_GET;
    cmd_buf[4] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_CONFIG_GET) {
            return -AM_EPERM;
        }
        memcpy(p_info, &rsp_buf[4], sizeof(am_zm516x_cfg_info_t));

        memcpy(&firmware_info,
               &rsp_buf[4 + sizeof(am_zm516x_cfg_info_t)],
               sizeof(__firmware_info_t));

        handle->dev_type[0] = firmware_info.dev_type[0];
        handle->dev_type[1] = firmware_info.dev_type[1];

        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ���� ZigBee ģ��ͨ���ţ��������D2�� */
am_err_t am_zm516x_cfg_channel_set (am_zm516x_handle_t handle, uint8_t chan)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_CHAN_SET;
    cmd_buf[4] = chan;
    cmd_buf[5] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           6,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_CHAN_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��������ģ�飨�������D4�� */
am_err_t am_zm516x_discover (am_zm516x_handle_t     handle,
                             uint8_t                buf_size,
                             am_zm516x_base_info_t *p_base_info,
                             uint8_t               *p_get_size)
{
    am_zm516x_dev_t *p_dev                         = (am_zm516x_dev_t *)handle;
    uint8_t          i                             = 0;
    uint8_t          num                           = 0;
    uint8_t          pack_size                     = 0;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_base_info) || (NULL == p_get_size)) {
        return -AM_EINVAL;
    }

    pack_size = sizeof(am_zm516x_base_info_t) + 4;

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_DISCOVER;
    cmd_buf[4] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        num = rsp_len / pack_size;
        num = (num > buf_size) ? buf_size : num;

        *p_get_size = 0;

        for (i = 0; i < num; i++) {
            if (memcmp(rsp_buf + pack_size * i, __ZM516X_CFG_TAG, 3) != 0) {
                return -AM_EPERM;
            }
            if (rsp_buf[pack_size * i + 3] != ZM516X_CFG_DISCOVER) {
                return -AM_EPERM;
            }
            memcpy(p_base_info + i,
                  &rsp_buf[pack_size * i + 4],
                   sizeof(am_zm516x_base_info_t));
            (*p_get_size)++;
        }

        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡԶ��������Ϣ���������D5�� */
am_err_t am_zm516x_remote_info_get (am_zm516x_handle_t       handle,
                                    am_zm516x_addr_t        *p_zb_addr,
                                    am_zm516x_remote_info_t *p_remote_info)
{
    am_zm516x_dev_t *p_dev                         = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_remote_info)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_REMOTE_GET;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           7,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_REMOTE_GET) {
            return -AM_EPERM;
        }
        memcpy(p_remote_info, &rsp_buf[4], sizeof(am_zm516x_remote_info_t));
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief �޸� ZigBee ģ���������Ϣ���������D6�������óɹ��踴λ */
am_err_t am_zm516x_cfg_info_set (am_zm516x_handle_t    handle,
                                 am_zm516x_cfg_info_t *p_info)
{
    am_zm516x_dev_t     *p_dev = (am_zm516x_dev_t *)handle;
    am_zm516x_cfg_info_t zb_info;
    uint8_t              cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t              rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t             rsp_len;

    if ((NULL == handle) || (NULL == p_info)) {
        return -AM_EINVAL;
    }

    if (am_zm516x_cfg_info_get(handle, &zb_info) != AM_OK) {
        return -AM_EPERM;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_CONFIG_SET;
    cmd_buf[4] = zb_info.my_addr[0];
    cmd_buf[5] = zb_info.my_addr[1];
    memcpy(&cmd_buf[6], p_info, sizeof(am_zm516x_cfg_info_t));
    cmd_buf[6 + sizeof(am_zm516x_cfg_info_t)] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           7 + sizeof(am_zm516x_cfg_info_t),
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_CONFIG_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ʹ ZigBee ģ�鸴λ���������D9�� */
void am_zm516x_reset (am_zm516x_handle_t handle)
{
    am_zm516x_dev_t     *p_dev = (am_zm516x_dev_t *)handle;
    am_zm516x_cfg_info_t zb_info;
    uint8_t              cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint16_t             rsp_len;

    if (am_zm516x_cfg_info_get(handle, &zb_info) != AM_OK) {
        return;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_RESET;
    cmd_buf[4] = zb_info.my_addr[0];
    cmd_buf[5] = zb_info.my_addr[1];
    cmd_buf[6] = handle->dev_type[0];
    cmd_buf[7] = handle->dev_type[1];
    cmd_buf[8] = __ZM516X_CFG_END;

    am_zm516x_send_cmd(p_dev->uart_handle, cmd_buf, 9, NULL, &rsp_len, 50);
    am_mdelay(200);
}

/** \brief �ָ� ZigBee ģ��������ã��������DA�������óɹ��踴λ */
am_err_t am_zm516x_default_set (am_zm516x_handle_t handle)
{
    am_zm516x_dev_t     *p_dev = (am_zm516x_dev_t *)handle;
    am_zm516x_cfg_info_t zb_info;
    uint8_t              cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t              rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t             rsp_len;

    if (am_zm516x_cfg_info_get(handle, &zb_info) != AM_OK) {
        return -AM_EPERM;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_REDEFAULT;
    cmd_buf[4] = zb_info.my_addr[0];
    cmd_buf[5] = zb_info.my_addr[1];
    cmd_buf[6] = handle->dev_type[0];
    cmd_buf[7] = handle->dev_type[1];
    cmd_buf[8] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           9,
                           rsp_buf,
                          &rsp_len,
                           70) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_REDEFAULT) {
            return -AM_EPERM;
        }
        if (rsp_buf[8] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/**
 * \brief ���� ZigBee ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ���������DC����
 *        ���óɹ��踴λ
 */
am_err_t am_zm516x_cfg_display_head_set (am_zm516x_handle_t handle,
                                         am_zm516x_addr_t  *p_zb_addr,
                                         am_bool_t          flag)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_SRC_DIS;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = flag;
    cmd_buf[7] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           8,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_SRC_DIS) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ����ָ����ַ ZigBee ģ��� GPIO ������������������E1�� */
am_err_t am_zm516x_cfg_gpio_dir_set (am_zm516x_handle_t handle,
                                     am_zm516x_addr_t  *p_zb_addr,
                                     uint8_t            dir)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_GPIO_DIR;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 1;
    cmd_buf[7] = dir;
    cmd_buf[8] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           9,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_GPIO_DIR) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != dir) {
            return -AM_EPERM;
        }
        if (rsp_buf[7] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ��� GPIO ������������������E1�� */
am_err_t am_zm516x_cfg_gpio_dir_get (am_zm516x_handle_t handle,
                                     am_zm516x_addr_t  *p_zb_addr,
                                     uint8_t           *p_dir)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_dir)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_GPIO_DIR;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 0;
    cmd_buf[7] = 0;
    cmd_buf[8] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           9,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_GPIO_DIR) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[7] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        *p_dir = rsp_buf[6];
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief IO/AD �ɼ����ã��������E2�������óɹ��踴λ */
am_err_t am_zm516x_cfg_io_adc_upload_set (am_zm516x_handle_t handle,
                                          am_zm516x_addr_t  *p_zb_addr,
                                          uint8_t            dir,
                                          uint16_t           period,
                                          am_bool_t          is_dormant)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_IO_ADC_UPLOAD;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 1;
    cmd_buf[7] = dir;
    cmd_buf[8] = AM_BITS_GET(period, 8, 8);
    cmd_buf[9] = AM_BITS_GET(period, 0, 8);
    cmd_buf[10] = (is_dormant != AM_FALSE) ? 1 : 0;
    cmd_buf[11] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           12,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_IO_ADC_UPLOAD) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != dir) {
            return -AM_EPERM;
        }
        if ((rsp_buf[7] != AM_BITS_GET(period, 8, 8)) ||
            (rsp_buf[8] != AM_BITS_GET(period, 0, 8))){
            return -AM_EPERM;
        }
        if (rsp_buf[9] != ((is_dormant != AM_FALSE) ? 1 : 0)) {
            return -AM_EPERM;
        }
        if (rsp_buf[10] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief IO/AD �ɼ����û�ȡ���������E2�� */
am_err_t am_zm516x_cfg_io_adc_upload_get (am_zm516x_handle_t handle,
                                          am_zm516x_addr_t  *p_zb_addr,
                                          uint8_t           *p_dir,
                                          uint16_t          *p_period,
                                          uint8_t           *p_is_dormant)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_IO_ADC_UPLOAD;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 0;
    memset(cmd_buf + 7, 0, 4);
    cmd_buf[11] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           12,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_IO_ADC_UPLOAD) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[10] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }

        if (NULL != p_dir) {
            *p_dir = rsp_buf[6];
        }
        if (NULL != p_period) {
            *p_period = (rsp_buf[7] << 8) | rsp_buf[8];
        }
        if (NULL != p_is_dormant) {
            *p_is_dormant = rsp_buf[9];
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ����ָ����ַ ZigBee ģ��� GPIO ���ֵ���������E3�� */
am_err_t am_zm516x_cfg_gpio_set (am_zm516x_handle_t handle,
                                 am_zm516x_addr_t  *p_zb_addr,
                                 uint8_t            value)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_GPIO_STATE;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 1;
    cmd_buf[7] = value;
    cmd_buf[8] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           9,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_GPIO_STATE) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != value) {
            return -AM_EPERM;
        }
        if (rsp_buf[7] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ��� GPIO ����ֵ���������E3�� */
am_err_t am_zm516x_cfg_gpio_get (am_zm516x_handle_t handle,
                                 am_zm516x_addr_t  *p_zb_addr,
                                 uint8_t           *p_value)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_value)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_GPIO_STATE;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 0;
    cmd_buf[7] = 0;
    cmd_buf[8] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           9,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_GPIO_STATE) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[7] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }

        *p_value = rsp_buf[6];
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ����ָ����ַ ZigBee ģ��� PWM ���ֵ���������E4�� */
am_err_t am_zm516x_cfg_pwm_set (am_zm516x_handle_t handle,
                                am_zm516x_addr_t  *p_zb_addr,
                                am_zm516x_pwm_t   *p_pwm)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;
    uint16_t         i;
    uint32_t         temp;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_pwm)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_PWM;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 1;

    for (i = 0; i < 4; i++) {
        memcpy(&temp, &((p_pwm + i)->freq), sizeof(uint32_t));
        temp = AM_LONGSWAP(temp);
        memcpy(cmd_buf + 5 * i + 7, &temp, 4);
        cmd_buf[5 * i + 11] = (p_pwm + i)->duty_cycle;
    }

    cmd_buf[27] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           28,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_PWM) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }

        for (i = 0; i < 4; i++) {
            memcpy(&temp, &((p_pwm + i)->freq), sizeof(uint32_t));
            temp = AM_LONGSWAP(temp);
            if ((memcmp(rsp_buf + 5 * i + 6, &temp, 4) != 0) ||
                (rsp_buf[5 * i + 10] != (p_pwm + i)->duty_cycle)) {
                return -AM_EPERM;
            }
        }

        if (rsp_buf[26] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ��� PWM ���ֵ���ã��������E4�� */
am_err_t am_zm516x_cfg_pwm_get (am_zm516x_handle_t handle,
                                am_zm516x_addr_t  *p_zb_addr,
                                am_zm516x_pwm_t   *p_pwm)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;
    uint16_t         i;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_pwm)) {
        return -AM_EINVAL;
    }

    if (2 != p_zb_addr->addr_size) {
        return -AM_EFAULT;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_PWM;
    cmd_buf[4] = p_zb_addr->p_addr[0];
    cmd_buf[5] = p_zb_addr->p_addr[1];
    cmd_buf[6] = 0;
    memset(cmd_buf + 7, 0, 20);
    cmd_buf[27] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           28,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_PWM) {
            return -AM_EPERM;
        }
        if (memcmp(rsp_buf + 4, p_zb_addr->p_addr, 2) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[26] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }

        for (i = 0; i < 4; i++) {
            memcpy(&((p_pwm + i)->freq), rsp_buf + 5 * i + 7, sizeof(uint32_t));
            (p_pwm + i)->duty_cycle = rsp_buf[5 * i + 11];
        }

        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief �������������ܣ��������E5�������óɹ��踴λ */
am_err_t am_zm516x_cfg_network_set (am_zm516x_handle_t handle,
                                    am_bool_t          state,
                                    uint8_t            type)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_NETWORK_SET;
    cmd_buf[4] = (state != AM_FALSE) ? 1 : 0;
    cmd_buf[5] = type;
    cmd_buf[6] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           7,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_NETWORK_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ((state != AM_FALSE) ? 1 : 0)) {
            return -AM_EPERM;
        }
        if (rsp_buf[5] != type) {
            return -AM_EPERM;
        }
        if (rsp_buf[6] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��������ӻ��������磨�������E6�� */
am_err_t am_zm516x_cfg_join_enable (am_zm516x_handle_t handle,
                                    uint16_t           time)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_JOIN_ENABLE;
    cmd_buf[4] = AM_BITS_GET(time, 8, 8);
    cmd_buf[5] = AM_BITS_GET(time, 0, 8);
    cmd_buf[6] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           7,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_JOIN_ENABLE) {
            return -AM_EPERM;
        }
        if ((rsp_buf[4] != AM_BITS_GET(time, 8, 8)) ||
            (rsp_buf[5] != AM_BITS_GET(time, 0, 8))){
            return -AM_EPERM;
        }
        if (rsp_buf[6] != ZM516X_CFG_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ѯ����ģ��洢�Ĵӻ���Ϣ���������E7�� */
am_err_t am_zm516x_cfg_slave_get (am_zm516x_handle_t      handle,
                                  uint8_t                 buf_size,
                                  am_zm516x_slave_info_t *p_slave_info,
                                  uint8_t                *p_get_size)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len = 1;

    if ((NULL == handle) || (NULL == p_slave_info) || (NULL == p_get_size)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_SLAVE_GET;
    cmd_buf[4] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_SLAVE_GET) {
            return -AM_EPERM;
        }
        if (rsp_buf[rsp_len - 1] != __ZM516X_CFG_END) {
            return -AM_EPERM;
        }

        *p_get_size = (buf_size > rsp_buf[4]) ? rsp_buf[4] : buf_size;

        memcpy(p_slave_info,
               rsp_buf + 5,
              *p_get_size * sizeof(am_zm516x_slave_info_t));

        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ѯ���ӻ�״̬���������E8�� */
am_err_t am_zm516x_cfg_state_get (am_zm516x_handle_t handle,
                                  uint8_t           *p_state,
                                  uint8_t           *p_response_state)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_CFG_TAG, 3);
    cmd_buf[3] = ZM516X_CFG_STATE_GET;
    cmd_buf[4] = __ZM516X_CFG_END;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_CFG_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_CFG_STATE_GET) {
            return -AM_EPERM;
        }

        if (NULL != p_state) {
            *p_state = rsp_buf[4];
        }
        if (NULL != p_response_state) {
            *p_response_state = rsp_buf[5];
        }

        return AM_OK;
    }
    return -AM_EPERM;
}

/*******************************************************************************
  ��ʱ����
*******************************************************************************/

/** \brief ���� ZigBee ģ��ͨ���ţ���ʱ���D1�� */
am_err_t am_zm516x_channel_set (am_zm516x_handle_t handle, uint8_t chan)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_CHAN_SET;
    cmd_buf[4] = chan;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_CHAN_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ���� ZigBee ģ��Ŀ���ַ����ʱ���D2�� */
am_err_t am_zm516x_dest_addr_set (am_zm516x_handle_t handle,
                                  am_zm516x_addr_t  *p_zb_addr)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_DEST_SET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           4 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_DEST_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ���� ZigBee ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ����ʱ���D3�� */
am_err_t am_zm516x_display_head_set (am_zm516x_handle_t handle, am_bool_t flag)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_SRC_DIS;
    cmd_buf[4] = flag;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_SRC_DIS) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ����ָ����ַ ZigBee ģ��� GPIO �������������ʱ���D4�� */
am_err_t am_zm516x_gpio_dir (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t            dir)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_GPIO_DIR_SET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);
    cmd_buf[4 + p_zb_addr->addr_size] = dir;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf, 5 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_GPIO_DIR_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4+p_zb_addr->addr_size] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ��� GPIO ����ֵ����ʱ���D5�� */
am_err_t am_zm516x_gpio_get (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t           *p_value)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_GPIO_GET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           4 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_GPIO_GET) {
            return -AM_EPERM;
        }
        *p_value = rsp_buf[4+p_zb_addr->addr_size];
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ����ָ����ַ ZigBee ģ���GPIO���ֵ����ʱ���D6�� */
am_err_t am_zm516x_gpio_set (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t            value)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_GPIO_SET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);
    cmd_buf[4 + p_zb_addr->addr_size] = value;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_GPIO_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4 + p_zb_addr->addr_size] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ���ADת��ֵ����ʱ���D7�� */
am_err_t am_zm516x_ad_get (am_zm516x_handle_t handle,
                           am_zm516x_addr_t  *p_zb_addr,
                           uint8_t            chan,
                           uint16_t          *p_value)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_value)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_ADC_GET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);
    cmd_buf[4+p_zb_addr->addr_size] = chan;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_ADC_GET) {
            return -AM_EPERM;
        }
        *p_value = rsp_buf[4+p_zb_addr->addr_size] << 8 |
                   rsp_buf[5+p_zb_addr->addr_size];
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ���� ZigBee ģ�����˯��ģʽ����ʱ���D8�� */
void am_zm516x_enter_sleep (am_zm516x_handle_t handle)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_SLEEP;
    cmd_buf[4] = 0x01;

    am_zm516x_send_cmd(p_dev->uart_handle, cmd_buf, 5, NULL, &rsp_len, 50);
    am_mdelay(200);
}

/** \brief ���� ZigBee ģ���ͨѶģʽ����ʱ���D9�� */
am_err_t am_zm516x_mode_set (am_zm516x_handle_t    handle,
                             am_zm516x_comm_mode_t mode)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_MODE_SET;
    cmd_buf[4] = mode;

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           5,
                           rsp_buf,
                          &rsp_len,
                           50) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_MODE_SET) {
            return -AM_EPERM;
        }
        if (rsp_buf[4] != ZM516X_COM_OK) {
            return -AM_EPERM;
        }
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ��ȡָ����ַ ZigBee ģ����ź�ǿ�ȣ���ʱ���DA�� */
am_err_t am_zm516x_sigal_get (am_zm516x_handle_t handle,
                              am_zm516x_addr_t  *p_zb_addr,
                              uint8_t           *p_signal)
{
    am_zm516x_dev_t *p_dev = (am_zm516x_dev_t *)handle;
    uint8_t          cmd_buf[__ZM516X_CMD_BUF_LEN] = {0};
    uint8_t          rsp_buf[__ZM516X_RSP_BUF_LEN] = {0};
    uint16_t         rsp_len;

    if ((NULL == handle) || (NULL == p_zb_addr) || (NULL == p_signal)) {
        return -AM_EINVAL;
    }

    memcpy(cmd_buf, __ZM516X_COM_TAG, 3);
    cmd_buf[3] = ZM516X_COM_CSQ_GET;
    memcpy(&cmd_buf[4], p_zb_addr->p_addr, p_zb_addr->addr_size);

    if (am_zm516x_send_cmd(p_dev->uart_handle,
                           cmd_buf,
                           4 + p_zb_addr->addr_size,
                           rsp_buf,
                          &rsp_len,
                           100) == AM_TRUE) {
        if (memcmp(rsp_buf, __ZM516X_COM_TAG, 3) != 0) {
            return -AM_EPERM;
        }
        if (rsp_buf[3] != ZM516X_COM_CSQ_GET) {
            return -AM_EPERM;
        }
        *p_signal = rsp_buf[4+p_zb_addr->addr_size];
        return AM_OK;
    }
    return -AM_EPERM;
}

/** \brief ZM516Xģ���ʼ�� */
am_zm516x_handle_t am_zm516x_init (am_zm516x_dev_t            *p_dev,
                                   const am_zm516x_dev_info_t *p_info,
                                   am_uart_handle_t            uart_handle)
{
    am_zm516x_cfg_info_t cfg_info;

    if ((NULL == p_dev) || (NULL == p_info) || (NULL == uart_handle)) {
        return NULL;
    }

    p_dev->p_devinfo = (am_zm516x_dev_info_t *)p_info;

    p_dev->uart_handle = am_uart_rngbuf_init(&p_dev->uart_rngbuf_dev,
                                              uart_handle,
                                              p_info->p_rxbuf,
                                              p_info->rxbuf_size,
                                              p_info->p_txbuf,
                                              p_info->txbuf_size);

    am_uart_rngbuf_ioctl(p_dev->uart_handle,
                         AM_UART_RNGBUF_TIMEOUT,
                         (void *)10);

    if (-1 != p_info->rst_pin) {
        am_gpio_pin_cfg(p_info->rst_pin, AM_GPIO_OUTPUT_INIT_HIGH);
        am_gpio_set(p_info->rst_pin, AM_GPIO_LEVEL_LOW);
        am_mdelay(1);
        am_gpio_set(p_info->rst_pin, AM_GPIO_LEVEL_HIGH);
        am_mdelay(5);
    }

    if (-1 != p_info->ack_pin) {
        am_gpio_pin_cfg(p_info->ack_pin, AM_GPIO_INPUT | AM_GPIO_PULLDOWN);
        am_gpio_trigger_connect(p_info->ack_pin, __ack_pint_isr, (void *)p_dev);
        am_gpio_trigger_cfg(p_info->ack_pin, AM_GPIO_TRIGGER_RISE);
        am_gpio_trigger_on(p_info->ack_pin);

        am_wait_init(&p_dev->ack_wait);
    }

    am_zm516x_cfg_info_get(p_dev, &cfg_info);

    return (am_zm516x_handle_t)(p_dev);
}

/** \brief ZM516Xģ����ʼ�� */
am_err_t am_zm516x_deinit (am_zm516x_handle_t handle)
{
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    if (-1 != handle->p_devinfo->ack_pin) {
        am_gpio_trigger_off(handle->p_devinfo->ack_pin);
        am_gpio_trigger_disconnect(handle->p_devinfo->ack_pin,
                                   __ack_pint_isr,
                                   handle);
        am_gpio_pin_cfg(handle->p_devinfo->ack_pin,
                        AM_GPIO_INPUT | AM_GPIO_FLOAT);
    }

    if (-1 != handle->p_devinfo->rst_pin) {
        am_gpio_pin_cfg(handle->p_devinfo->rst_pin,
                        AM_GPIO_INPUT | AM_GPIO_FLOAT);
    }

    return AM_OK;
}

/** @} */

/* end of file */
