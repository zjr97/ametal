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
 * \brief ZLG72128�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-22  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_ZLG72128_H
#define __AM_ZLG72128_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_i2c.h"
#include "am_softimer.h"

/**
 * @addtogroup am_if_zlg72128
 * @copydoc am_zlg72128.h
 * @{
 */

/**
 * \name ��ͨ��������1�� ~ ��3�����а�������ֵ�궨��
 * 
 *     �оٳ��� am_zlg72128_key_cb_t �ص������е� key_val ���ܵ�һϵ��ֵ������
 * ʹ��key_valֵ����һϵ�к�ֵ����Ӧ�Աȣ����ж�����һ�������¡��������������
 * AM_ZLG72128_KEY_x_y �����У�x������һ�У�1 ~ 3����y��ʾ��һ�У�1 ~ 8)
 *
 * @{
 */
 
#define  AM_ZLG72128_KEY_1_1     1     /**< \brief ��1�ŵ�1������  */
#define  AM_ZLG72128_KEY_1_2     2     /**< \brief ��1�ŵ�2������  */
#define  AM_ZLG72128_KEY_1_3     3     /**< \brief ��1�ŵ�3������  */
#define  AM_ZLG72128_KEY_1_4     4     /**< \brief ��1�ŵ�4������  */
#define  AM_ZLG72128_KEY_1_5     5     /**< \brief ��1�ŵ�5������  */
#define  AM_ZLG72128_KEY_1_6     6     /**< \brief ��1�ŵ�6������  */
#define  AM_ZLG72128_KEY_1_7     7     /**< \brief ��1�ŵ�7������  */
#define  AM_ZLG72128_KEY_1_8     8     /**< \brief ��1�ŵ�8������  */
                               
#define  AM_ZLG72128_KEY_2_1     9     /**< \brief ��2�ŵ�1������  */
#define  AM_ZLG72128_KEY_2_2     10    /**< \brief ��2�ŵ�2������  */
#define  AM_ZLG72128_KEY_2_3     11    /**< \brief ��2�ŵ�3������  */
#define  AM_ZLG72128_KEY_2_4     12    /**< \brief ��2�ŵ�4������  */
#define  AM_ZLG72128_KEY_2_5     13    /**< \brief ��2�ŵ�5������  */
#define  AM_ZLG72128_KEY_2_6     14    /**< \brief ��2�ŵ�6������  */
#define  AM_ZLG72128_KEY_2_7     15    /**< \brief ��2�ŵ�7������  */
#define  AM_ZLG72128_KEY_2_8     16    /**< \brief ��2�ŵ�8������  */


#define  AM_ZLG72128_KEY_3_1     17    /**< \brief ��3�ŵ�1������  */
#define  AM_ZLG72128_KEY_3_2     18    /**< \brief ��3�ŵ�2������  */
#define  AM_ZLG72128_KEY_3_3     19    /**< \brief ��3�ŵ�3������  */
#define  AM_ZLG72128_KEY_3_4     20    /**< \brief ��3�ŵ�4������  */
#define  AM_ZLG72128_KEY_3_5     21    /**< \brief ��3�ŵ�5������  */
#define  AM_ZLG72128_KEY_3_6     22    /**< \brief ��3�ŵ�6������  */
#define  AM_ZLG72128_KEY_3_7     23    /**< \brief ��3�ŵ�7������  */
#define  AM_ZLG72128_KEY_3_8     24    /**< \brief ��3�ŵ�8������  */

/** @} */



/**
 * \name ���ܰ�������4�����а�������ź궨��
 * 
 *   ���ܰ����ӵ�4�п�ʼ���������ң����ζ���Ϊ F0 ~ F7����״̬�ֱ��밴���ص�����
 * �е� funkey_val ֵ�� bit0 ~ bit7 ��Ӧ��0λ���£�1Ϊ�ͷš�����funkey_val��8��
 * ���ܼ������ֵ������ֱ��ʹ�����8λ��ֵʵ�ֽ�Ϊ���ӵİ������ơ���ֻ��Ҫ��
 * �ļ������ĳ�����ܼ���״̬������ʹ��#AM_ZLG72128_FUNKEY_CHECK()����ĳһ��
 * �ܼ���״̬��#AM_ZLG72128_FUNKEY_CHECK()���funkey_num����Ϊ0 ~ 7������ʹ��
 * �˴�����ĺ�ֵ��#AM_ZLG72128_FUNKEY_0 ~ #AM_ZLG72128_FUNKEY_7
 * 
 *
 * @{
 */
 
#define  AM_ZLG72128_FUNKEY_0     0     /**< \brief ���ܼ�1  */
#define  AM_ZLG72128_FUNKEY_1     1     /**< \brief ���ܼ�2  */
#define  AM_ZLG72128_FUNKEY_2     2     /**< \brief ���ܼ�3  */
#define  AM_ZLG72128_FUNKEY_3     3     /**< \brief ���ܼ�4  */
#define  AM_ZLG72128_FUNKEY_4     4     /**< \brief ���ܼ�4  */
#define  AM_ZLG72128_FUNKEY_5     5     /**< \brief ���ܼ�5  */
#define  AM_ZLG72128_FUNKEY_6     6     /**< \brief ���ܼ�6  */
#define  AM_ZLG72128_FUNKEY_7     7     /**< \brief ���ܼ�7  */
                               
/** @} */

/**
 * \name �������ʾ��λ�ķ���
 * ���� \sa am_zlg72128_digitron_shift() ������ \a dir ������
 * @{
 */
 
#define  AM_ZLG72128_DIGITRON_SHIFT_RIGHT   0   /**< \brief ����  */
#define  AM_ZLG72128_DIGITRON_SHIFT_LEFT    1   /**< \brief ����  */

/** @} */


/**
 * \name ���ܰ�������4�����а�����״̬����
 * 
 *   ���ܰ����ӵ�4�п�ʼ���������ң����ζ���Ϊ F0 ~ F7����״̬�ֱ��밴���ص�����
 * �е� funkey_val ֵ�� bit0 ~ bit7 ��Ӧ��0λ���£�1Ϊ�ͷš�����funkey_val��8��
 * ���ܼ������ֵ������ֱ��ʹ�����8λ��ֵʵ�ֽ�Ϊ���ӵİ������ơ���ֻ��Ҫ��
 * �ļ������ĳ�����ܼ���״̬������ʹ�øú���ĳһ���ܼ���״̬��
 *
 * \param[in] funkey_val : �����ص������л�ȡ���Ĺ��ܼ���ֵ
 * \param[in] funkey_num : ���ܼ���ţ���Чֵ��0 ~ 7���ֱ��Ӧ F0 ~ F7������ʹ��
 *                         ��ֵ#AM_ZLG72128_FUNKEY_0 ~ #AM_ZLG72128_FUNKEY_7
 *
 * \retval TRUE  : ��Ӧ���ܼ���ǰ�ǰ���״̬
 * \retval FALSE : ��Ӧ���ܼ���ǰ���ͷ�״̬
 */

#define  AM_ZLG72128_FUNKEY_CHECK(funkey_val, funkey_num)  \
               (((funkey_val) & (1 << ((funkey_num) & 0x07))) ? FALSE : TRUE)


/** @} */
 
/**
 * \name ����ܶ�
 * ���� \sa am_zlg72128_digitron_seg_ctrl() �ο��ƺ����� \a seg ������
 * @{
 */
 
#define  AM_ZLG72128_DIGITRON_SEG_A    0        /**< \brief a  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_B    1        /**< \brief b  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_C    2        /**< \brief c  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_D    3        /**< \brief d  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_E    4        /**< \brief e  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_F    5        /**< \brief f  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_G    6        /**< \brief g  ��  */
#define  AM_ZLG72128_DIGITRON_SEG_DP   7        /**< \brief dp ��  */

/** @} */

/**
 * \brief ������ͨ��������1�� ~ ��3�У��ص���������
 * 
 *     ����ʹ�� am_zlg72128_key_cb_set() �������øûص�������ϵͳ֮�У����а���
 * �¼�����ʱ�����ûص�������
 * 
 * \param[in] p_arg      : ���ûص�����ʱ�趨���û��Զ������
 *
 * \param[in] key_val    : ��ֵ���ӵ�1�п�ʼ����������˳���š���1�е�1������
 *                         ��ֵΪ1����1�е�2��������ֵΪ2���Դ����ơ�����ʹ��
 *                         ��ֱֵ���� AM_ZLG72128_KEY_*_*(#AM_ZLG72128_KEY_1_1) 
 *                         �Ƚϣ����ж�����һ�������¡�����أ�0��ʾ���κ���ͨ
 *                         �������¡�
 *
 * \param[in] repeat_cnt : ����������������ͨ����֧����������ֵ�����ڸ�������
 *                         key_val0��Ӧ����ͨ������������������funkey_val����
 *                         �Ĺ��ܼ�û�й�ϵ��0 ��ʾ�״ΰ�����δ����������ֵ��
 *                         ʾʶ�𵽵�������������������סʱ�䳬��2s�󣬿�ʼ��
 *                         ����Ч��������Ч��ʱ����Լ200ms����ÿ��200ms��
 *                         repeat_cnt��1��������һ�θú�����ֱ�������ͷš���ֵ
 *                         ���Ϊ255����������������255���򽫽�����������׶Σ�
 *                         ����û��ʱ���������ûص�������
 *
 * \param[in] funkey_val : ���ܼ���ֵ������8λ���ֱ����4�и���������Ӧ�����λ
 *                         ���4�е�1��������Ӧ���θ�λ���4�е�2��������Ӧ����
 *                         ��λ���4�е�8��������Ӧ��λֵΪ0������Ӧ�����£�λ
 *                         ֵΪ1������Ӧ��δ���¡�ֻҪ��ֵ�����ı䣬�ͻ��������
 *                         �Ļص�����������ʹ�ú꣺#AM_ZLG72128_FUNKEY_CHECK()��
 *                         �ж϶�Ӧ�Ĺ��ܼ��Ƿ��¡�
 *
 * \note ���ڹ��ܼ�����ͨ����������ʵ����ϼ�Ӧ�ã�����PC���ϵ�Alt��Shift�Ȱ�����
 *
 *     �羭���õ���һ�����ܣ��༭����ʱ��TAB�������ƣ������סShift������TAB��
 * ��Ϊ���ơ����Ժ�����ʵ�����ƵĹ��ܣ��繦�ܼ�0������Shift������ͨ����0����TA
 * B�����ڻص������еĴ���ʾ�������磺
 * \code 
 *
 *  // ����Ӧʹ�� am_zlg72128_key_cb_set()�������ú���ע���ϵͳ���Ա��ں��ʵ�ʱ
 *  // ����øûص�����
 *  static void zlg72128_key_callback (void    *p_arg,
 *                                     uint8_t  key_val,
 *                                     uint8_t  repeat_cnt,
 *                                     uint8_t  funkey_val)
 *
 *  {
 *       if (keyval == AM_ZLG72128_KEY_1_1) {
 *
 *           // ���ܼ����£�����
 *           if (AM_ZLG72128_FUNKEY_CHECK(fun_keyval, AM_ZLG72128_FUNKEY_0)) {
 *    
 *           } else {  // ���ܼ�δ���£���������
 *   
 *           }
 *      }
 *  }
 *   
 * \endcode
 * 
 */
typedef void (*am_zlg72128_key_cb_t) (void    *p_arg, 
                                      uint8_t  key_val, 
                                      uint8_t  repeat_cnt,
                                      uint8_t  funkey_val);
 
/**
 * \brief ZLG72128�豸��Ϣ�ṹ�嶨��
 * 
 * ����ʹ�ó�ʼ��������ȡhandleʱ��ָ���豸�������Ϣ��ʾ���豸��Ϣ�磺
 *
 *  const am_zlg72128_devinfo_t g_zlg72128_devinfo = {
 *      TRUE,     // ͨ������£�����ʹ���ж�����
 *      PIO0_8,   // ��MCU���ӵ��ж����ź�
 *      5,        // ����ʹ���ж����ţ���ò���������ѯ��ʱ��������������Ϊ5ms
 *  }
 */
typedef struct am_zlg72128_devinfo {

    /**
     * \brief ZLG72128��λ���ţ���ʹ��ʱ���磬�̶�Ϊ�ߵ�ƽʱ������Ϊ -1
     */
    int                      rst_pin;

    /** 
     * \brief �Ƿ�ʹ���ж����ţ���Ϊ��ʡһ��IO��Դ����ɲ�ʹ���жϷ�ʽ��
     * TRUE  : ʹ���ж�����(int_pin ����ָ�����ź�)���������ж��л�ȡ��ֵ 
     * FALSE : ��һ����ʱ������interval_ms����ָ������ѯ��ֵ
     */
    am_bool_t                use_int_pin;
    
    /** \brief ���� use_int_pin Ϊ TRUE ʱ���ò�����Ч��ָ���ж����� */
    int                      int_pin;
    
    /** \brief ���� use_int_pin Ϊ FALSE ʱ���ò�����Ч��ָ����ѯ��ʱ���� */
    uint32_t                 interval_ms;

} am_zlg72128_devinfo_t;

/**
 * \brief ZLG72128�豸�ṹ�嶨��
 */
typedef struct am_zlg72128_dev {
    
    am_zlg72128_key_cb_t     pfn_key_cb;     /**< \brief ������ͨ���ص�����   */
    void                    *pfn_key_arg;    /**< \brief ����ص���������     */
    am_i2c_device_t          i2c_dev;        /**< \brief I2C�ӻ��豸          */
    am_i2c_handle_t          handle;         /**< \brief I2C�����׼handle    */
    am_softimer_t            timer;          /**< \brief �����ʱ��           */
    am_i2c_transfer_t        trans[2];       /**< \brief ����I2C���ݴ���      */
    am_i2c_message_t         msg;            /**< \brief ��Ϣ���ڲ�ʹ��       */
    volatile uint8_t         state;          /**< \brief ״̬                 */
    uint8_t                  key_buf[4];     /**< \brief ��ֵ��ص�4���Ĵ���  */
    
    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_zlg72128_devinfo_t  *p_devinfo;
    
} am_zlg72128_dev_t;


/** \brief ����ZLG72128�������  */
typedef struct am_zlg72128_dev *am_zlg72128_handle_t; 
                                      
/**
 * \brief ZLG72128��ʼ������
 *
 * ʹ��ZLG72128ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����ZLG72128��handle��
 *
 * \param[in] p_dev      : ָ��ZLG72128�豸��ָ��
 * \param[in] p_devinfo  : ָ��ZLG72128�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼������������ʹ�ø�I2C�����ZLG72128ͨ�ţ�
 *
 * \return ����ZLG72128��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_zlg72128_handle_t am_zlg72128_init (am_zlg72128_dev_t           *p_dev,
                                       const am_zlg72128_devinfo_t *p_devinfo,
                                       am_i2c_handle_t              i2c_handle);

/**
 * \brief ��ͨ��������1�� ~ ��3�����а������ص�����ע��
 *
 * ���а����¼�����ʱ�������ô˴����õĻص������������¼���������3�������
 *  1. ����ͨ��������
 *  2. ��ͨ����һֱ���£���������״̬
 *  3. ��һ���ܰ���״̬�����仯���ͷ�->���� �� ����->�ͷ�
 *
 * \param[in] handle      : ZLG72128�Ĳ������
 * \param[in] pfn_key_cb  : �����ص�����
 * \param[in] p_arg       : �ص������Ĳ���
 *
 * \retval AM_OK      : ���ûص������ɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_zlg72128_key_cb_set (am_zlg72128_handle_t  handle, 
                            am_zlg72128_key_cb_t  pfn_key_cb,
                            void                 *p_arg);

/**
 * \brief �����������˸ʱ�䣬�����趨ĳλ��˸ʱ����������ʱ���Ϩ�������ʱ��
 *
 *     ��������Ϊ���������ʱ���Ϊ500ms��ʱ�䵥λΪms����Ч��ʱ��Ϊ��
 *  150��200��250��������800��850��900���� 150ms ~ 900ms������50msΪ��ࡣ
 *  ��ʱ�䲻��ǡ��Ϊ��Щֵ���������һ����ӽ���ֵ��
 *
 * \param[in] handle : ZLG72128�Ĳ������
 * \param[in] on_ms  : ����������ʱ�䣬��ЧֵΪ 150ms ~ 900ms������50msΪ���
 * \param[in] off_ms : Ϩ�������ʱ�䣬��ЧֵΪ 150ms ~ 900ms������50msΪ���
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ������ʧ�ܣ����ݴ������
 *
 * \note ��������˸ʱ�䲢��������������˸���������ĳλ����˸���غ��ܿ���
 * ��˸���� \sa am_zlg72128_digitron_flash_ctrl()
 */
int am_zlg72128_digitron_flash_time_cfg (am_zlg72128_handle_t  handle,
                                         uint8_t               on_ms,
                                         uint8_t               off_ms);

/**
 * \brief ���ƣ��򿪻�رգ��������˸��Ĭ�Ͼ�����˸
 *
 * \param[in] handle   : ZLG72128�Ĳ������
 * \param[in] ctrl_val : ����ֵ��λ0 ~ 11�ֱ��Ӧ�������ҵ�����ܡ�ֵΪ1ʱ��˸��
 *                       ֵΪ0ʱ����˸��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ������ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_flash_ctrl (am_zlg72128_handle_t  handle,
                                     uint16_t              ctrl_val);
                                
/**
 * \brief ��������ܵ���ʾ���ԣ�����ʾ��ر���ʾ��
 *
 *     Ĭ������£���������ܾ����ڴ���ʾ״̬���򽫰���12λ�����ɨ�裬ʵ���У�
 *  ������Ҫ��ʾ��λ��������12λ����ʱ������ʹ�øú����ر�ĳЩλ����ʾ��
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] ctrl_val  : ����ֵ��λ0 ~ λ11�ֱ��Ӧ�������ҵ�����ܡ�
 *                        ֵΪ1�ر���ʾ��ֵΪ0����ʾ
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ������ʧ�ܣ����ݴ������
 *
 * \note �������ö���ΪϨ����벻ͬ�����ö���ΪϨ�����ʱ�������ͬ����ɨ�裬ͬ
 * ����Ҫ��ÿ��ɨ��ʱ�����Ӧ�Ķ��롣ʹ�øú����ر�ĳЩλ����ʾ���ǴӸ����ϲ�
 * ��ɨ���λ��
 */
int am_zlg72128_digitron_disp_ctrl (am_zlg72128_handle_t  handle, 
                                    uint16_t              ctrl_val);


/**
 * \brief �����������ʾ���ַ�
 *
 *      ZLG72128�Ѿ��ṩ�˳�����10�����ֺ�21����ĸ��ֱ����ʾ������Ҫ��ʾ��֧�ֵ�
 *  ͼ�Σ�����ֱ��ʹ�� \sa am_zlg72128_digitron_dispbuf_set() ����ֱ�����ö��롣
 *
 * \param[in] handle     : ZLG72128�Ĳ������
 * \param[in] pos        : ������ʾ��λ�ã���Чֵ 0 ~ 11
 * \param[in] ch         : ��ʾ���ַ���֧���ַ� 0123456789AbCdEFGHiJLopqrtUychT
 *                         �Լ��ո�����ʾ��
 * \param[in] is_dp_disp : �Ƿ���ʾС���㣬TRUE:��ʾ; FALSE:����ʾ
 * \param[in] is_flash   : ��λ�Ƿ���˸��TRUE:��˸; FALSE:����˸
 *
 * \retval AM_OK       : ���óɹ�
 * \retval -AM_EINVAL  : ��������
 * \retval -AM_ENOTSUP : ��֧�ֵ��ַ�
 * \retval -AM_EIO     : ����ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_disp_char (am_zlg72128_handle_t  handle, 
                                    uint8_t               pos,
                                    char                  ch,
                                    am_bool_t             is_dp_disp,
                                    am_bool_t             is_flash);
                                    
/**
 * \brief ��ָ��λ�ÿ�ʼ��ʾһ���ַ���
 *
 * \param[in] handle     : ZLG72128�Ĳ������
 * \param[in] start_pos  : �ַ�����ʼλ��
 * \param[in] p_str      : ��ʾ���ַ���
 *
 * \retval AM_OK       : ���óɹ�
 * \retval -AM_EINVAL  : ��������
 * \retval -AM_ENOTSUP : ��֧�ֵ��ַ�
 * \retval -AM_EIO     : ����ʧ�ܣ����ݴ������
 *
 * \note ��������֧�ֵ��ַ������ַ�λ������ʾ
 */
int am_zlg72128_digitron_disp_str (am_zlg72128_handle_t  handle, 
                                   uint8_t               start_pos,
                                   const char           *p_str);
/**
 * \brief �����������ʾ�����֣�0 ~ 9��
 *
 * \param[in] handle     : ZLG72128�Ĳ������
 * \param[in] pos        : ������ʾ��λ�ã���Чֵ 0 ~ 11
 * \param[in] num        : ��ʾ�����֣�0 ~ 9
 * \param[in] is_dp_disp : �Ƿ���ʾС���㣬TRUE:��ʾ; FALSE:����ʾ
 * \param[in] is_flash   : ��λ�Ƿ���˸��TRUE:��˸; FALSE:����˸
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ������ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_disp_num (am_zlg72128_handle_t  handle, 
                                   uint8_t               pos,
                                   uint8_t               num,
                                   am_bool_t             is_dp_disp,
                                   am_bool_t             is_flash);

/**
 * \brief ֱ�������������ʾ�����ݣ����룩
 *
 *      ���û���Ҫ��ʾһЩ�Զ��������ͼ��ʱ������ʹ�øú�����ֱ�����ö��롣һ
 *  ��������ZLG72128�Ѿ��ṩ�˳�����10�����ֺ�21����ĸ��ֱ����ʾ���û�����ʹ��
 *  �˺���ֱ�����ö��룬����ֱ��ʹ�� \sa ������ʾ���ֻ���ĸ 
 *      Ϊ����������ö�������λ��ʾ�Ķ��룬����������һ������д���������
 *  ��ʾ�Ķ��롣
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] start_pos : �������ö�����ʼλ�ã���Чֵ 0 ~ 11
 * \param[in] p_buf     : �����ŵĻ�����
 * \param[in] num       : �������õ�����ܶ���ĸ���
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ������ʧ�ܣ����ݴ������
 *
 * \note �� start_pos + num ��ֵ���� 12 �������Ļ��������ݱ�������
 */
int am_zlg72128_digitron_dispbuf_set (am_zlg72128_handle_t  handle, 
                                      uint8_t               start_pos,
                                      uint8_t              *p_buf,
                                      uint8_t               num);

/**
 * \brief ֱ�ӿ��ƶεĵ�����Ϩ��
 *
 *     Ϊ�˸������Ŀ����������ʾ���ṩ��ֱ�ӿ���ĳһ�ε����ԣ������𣩡�
 *
 * \param[in] handle : ZLG72128�Ĳ������
 * \param[in] pos    : ���ƶ�������λ����Чֵ 0 ~ 11
 * \param[in] seg    : �Σ���Чֵ 0 ~ 7���ֱ��Ӧ��a,b,c,d,e,f,g,dp
 *                     ����ʹ�����к꣺
 *                       - AM_ZLG72128_DIGITRON_SEG_A
 *                       - AM_ZLG72128_DIGITRON_SEG_B
 *                       - AM_ZLG72128_DIGITRON_SEG_C
 *                       - AM_ZLG72128_DIGITRON_SEG_D
 *                       - AM_ZLG72128_DIGITRON_SEG_E
 *                       - AM_ZLG72128_DIGITRON_SEG_F
 *                       - AM_ZLG72128_DIGITRON_SEG_G
 *                       - AM_ZLG72128_DIGITRON_SEG_DP
 *
 * \param[in] is_on  : �Ƿ�����öΣ�TRUE:����; FALSE:Ϩ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : ����ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_seg_ctrl (am_zlg72128_handle_t  handle, 
                                   uint8_t               pos,
                                   char                  seg,
                                   am_bool_t             is_on);

/**
 * \brief ��ʾ��λ����
 *
 *      ʹ��ǰ��������ܵ���ʾ���ƻ����ƣ�����ָ���Ƿ���ѭ���ƶ����������ѭ��
 *   ��λ������λ���ұ߿ճ���λ�����ƣ�����߿ճ���λ�����ƣ�������ʾ�κ����ݡ�
 *   ����ѭ���ƶ�����ճ���λ������ʾ���Ƴ�λ�����ݡ�
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] dir       : ��λ����
 *                       - AM_ZLG72128_DIGITRON_SHIFT_LEFT   ����
 *                       - AM_ZLG72128_DIGITRON_SHIFT_RIGHT  ����
 *                                 
 * \param[in] is_cyclic : �Ƿ���ѭ����λ��TRUE��ѭ����λ��FALSE����ѭ����λ           
 * \param[in] num       : ������λ��λ������Чֵ 0�����ƶ��� ~ 11������ֵ��Ч
 *
 * \retval AM_OK      : ��λ�ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    ����λʧ�ܣ����ݴ������
 *
 * \note ������λ��˵��
 *
 *   ʵ���У����ܻᷢ����λ�����෴���������ڿ��ܴ�������Ӳ����ƣ�
 *   1�� ���ұ�Ϊ0������ܣ���������Ϊ��11��10��9��8��7��6��5��4��3��2�� 1�� 0
 *   2�� �����Ϊ0������ܣ���������Ϊ�� 0�� 1��2��3��4��5��6��7��8��9��10��11
 *   ����Ҫȡ����Ӳ�����ʱ COM0 ~ COM11 ��������Ӧ���������������λ�á�
 *
 *       �˴����ƺ����Ƶĸ������ԡ������ֲᡷ�е���Ӧ�õ�·Ϊ�ο��ģ������ұ�
 *   Ϊ0������ܡ���ô���ƺ����Ƶĸ���ֱ�Ϊ��
 *   ���ƣ������0��ʾ�л���1�������1��ʾ�л���2�������������10��ʾ�л���11
 *   ���ƣ������11��ʾ�л���10�������1��ʾ�л���2�������������10��ʾ�л���11
 *   
 *   �ɼ�����Ӳ����·��������λ�����෴�ģ�����λЧ������Ҳǡǡ���෴�ģ��˴�
 * ֻ��Ҫ��΢ע�⼴�ɡ�
 */
int am_zlg72128_digitron_shift (am_zlg72128_handle_t  handle, 
                                uint8_t               dir,
                                am_bool_t             is_cyclic,
                                uint8_t               num);
 
/**
 * \brief ��λ���������ܵ�����LED��Ϩ��
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 *
 * \retval AM_OK      : ��λ��ʾ�ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_disp_reset (am_zlg72128_handle_t handle);

/**
 * \brief �����������LED����0.5S��������˸�����ڲ����������ʾ�Ƿ�����
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 *
 * \retval AM_OK      : �������ģʽ�ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : ʧ�ܣ����ݴ������
 */
int am_zlg72128_digitron_disp_test (am_zlg72128_handle_t handle);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG72128_H */

/* end of file */
