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
 * \brief USB DEVICE����
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-19  sdq, first implementation
 * \endinternal
 */
#ifndef __AMHW_ZLG217_USBD_H
#define __AMHW_ZLG217_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "amhw_zlg217_usbd.h"
#include "am_usb_dci.h"

/**
 * \addtogroup am_zlg217_if_usbd
 * \copydoc am_zlg217_usbd.h
 * @{
 */

/**< \brief zlg217֧�ֵ����˵���� */
#define     AM_ZLG217_USBD_MAX_EP_CNT         5

/**< \brief zlg217һ�����շ�������ֽڸ��� */
#define     AM_ZLG217_USBD_MAX_EP_DATA_CNT    64

/**< \brief ������������ */
#define     AM_ZLG217_USB_CTRL_SETUP          0x00
#define     AM_ZLG217_USB_CTRL_IN             0x01
#define     AM_ZLG217_USB_CTRL_OUT            0x02
#define     AM_ZLG217_USB_CTRL_IDLE           0xFF

/**
 * \brief ����������
 *
 *  HOST��������������ͺ����������Ҫ��ӻ�����������
 *  �������������¼�����������Խ���ϼ�������ֱ�ӻ�ȡ�����԰�����˳���������������֮��
 */
typedef struct am_zlg217_usb_descriptor {
    uint16_t  desc_wValue;     /* ��8λΪ���������ͣ���8λΪ��������� */
    uint16_t  desc_size;       /* ��������С */
    uint8_t  *p_desc;          /* ���������� */
}am_zlg217_usb_descriptor_t;

/**
 * \brief ZLG217 USB Device initialize parameter structure
 */
typedef struct am_zlg217_usbd_devinfo{
    uint32_t usb_regbase;          /**< \brief usb ����ַ */

    int inum;                      /**< \brief �жϺ� */

    am_zlg217_usb_descriptor_t *p_descriptor;    /**< \brief �������׵�ַ */

    uint8_t descriptor_num;        /**< \brief ���������� */

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */
}am_zlg217_usbd_devinfo_t;

/** \brief �˵�״̬�ṹ */
typedef struct am_zlg217_usbd_ep_stat
{
    uint8_t inuse;         /**< \brief �˵��Ƿ�ᱻʹ�ã��˵����������Ƿ��иö˵㣩 */
    uint8_t stalled;       /**< \brief �˵��Ƿ����� */
    //uint8_t transferring;  /**< \brief �Ƿ����ڴ��� */

    /**< \brief �˵��ַ
     * [D7]    : �˵�Ĵ��䷽��  1:IN 0:OUT
     * [D6:D4] : ������ֵΪ0
     * [D3:D0] : �˵�� */
    uint8_t endpoint_address;

    /**< \brief �˵�һ���Դ����������С */
    uint16_t max_packet_size;

    /**< \brief �˵㴫������
     *  [D7:D2] ����
     *  [D1:D0] 00�����ƴ���
     *          01��ͬ������
     *          10����������
     *          11���жϴ��� */
    uint8_t  transfer_type;
} am_zlg217_usbd_ep_stat_t;

/**
 * \brief ZLG217 USBD device structure
 */
typedef struct am_zlg217_usbd_dev {
    /**< \brief Device handle used to identify the device object belongs to */
    am_usbd_dev_t  device;

    /**< \brief �ж�״̬
     *          D4���˵��ж�
     *          D3��SOF
     *          D2������
     *          D1�����߹���
     *          D0�����߸�λ����
     */
    uint8_t int_stat;

    /**< \brief �����жϵĶ˵㣬Ϊ1��ʾ�����жϣ�Ϊ0��ʾû�з����ж�
     *   D7:D5  ����
     *   D4~D0  ��Ӧ�����жϵĶ˵�4~�˵�0��
     */
    union {
        uint8_t int_ep_flag;
        struct {
            uint8_t ep0 : 1;
            uint8_t ep1 : 1;
            uint8_t ep2 : 1;
            uint8_t ep3 : 1;
            uint8_t ep4 : 1;
        }int_ep_flag_field;
    }int_ep_union;

    /**< \brief �˵��жϵ����ͣ�Ϊ1��ʾ�����жϣ�Ϊ0��ʾû�з����ж�
     *   D7:OUT_STALL
     *   D6:OUT_ACK
     *   D5:OUT_NACK
     *   D4:IN_STALL
     *   D3:IN_ACK
     *   D2:IN_NACK
     *   D1:END       �˵㴫�����
     *   D0:SETUP     ���յ�SETUP��
     */
    union {
        uint8_t ep_int_type[AM_ZLG217_USBD_MAX_EP_CNT];
        struct {
            uint8_t setup     : 1;
            uint8_t end       : 1;
            uint8_t in_nack   : 1;
            uint8_t in_ack    : 1;
            uint8_t in_stall  : 1;
            uint8_t out_nack  : 1;
            uint8_t out_ack   : 1;
            uint8_t out_stall : 1;
        }ep_int_type_field[AM_ZLG217_USBD_MAX_EP_CNT];
    }ep_int_type_union;

    /**< \brief ���յ���setup���е����� */
    am_usb_setup_struct_t setup_data;

    /**< \brief USB��ǰ���ڴ������������
     *     AM_ZLG217_USB_CTRL_SETUP      0x00
     *     AM_ZLG217_USB_CTRL_IN         0x01
     *     AM_ZLG217_USB_CTRL_OUT        0x02
     *     AM_ZLG217_USB_CTRL_IDLE       0xFF
     */
    uint8_t running_ctrl_state;

    //uint8_t ep_num;     /**< \brief ʹ�õĶ˵���� */

    /**< \brief �˵�״̬ */
    am_zlg217_usbd_ep_stat_t endpoint_state[AM_ZLG217_USBD_MAX_EP_CNT];

    /**< \brief �豸��Ϣ�ṹָ�� */
    const am_zlg217_usbd_devinfo_t *p_info;
}am_zlg217_usbd_dev_t;

/**< \brief ����˵��жϴ�����ָ������ */
typedef void (*USB_DeviceInterruptEndpoint_t)(am_zlg217_usbd_dev_t *);

/**< \brief �������Ķ˵��ж����� �Ĵ��������� */
typedef void (*USB_DeviceInterruptEndpointType_t)(am_zlg217_usbd_dev_t *);

extern am_usbd_handle_t am_zlg217_usbd_init (am_zlg217_usbd_dev_t *p_dev,
                                   const am_zlg217_usbd_devinfo_t *p_devinfo);

extern void am_zlg217_usbd_deinit (const am_zlg217_usbd_devinfo_t *p_info);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_ZLG217_USBD_H */

/* end of file */
