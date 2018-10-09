/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ADC Ӳ�������ӿ�ʵ��
 *
 * 1. 12λ��αƽ�����ģת����;
 * 2. ģ���������Ŷ��12����
 * 3. 2������������ת�����У�
 * 4. ��ѡ���/����ֵ�ȽϺ͡���㴩Խ����⣻
 * 5. ֧�ֵ���ģʽ�͵͹���ģʽ��
 * 6. ��ѹ������Χ�� Vrefn �� Vrefp (����ֵΪ 3V; ���ɳ��� VDD �ĵ�ѹֵ)��
 * 7. 12λ��ת�����ʸߴ� 1.2 MHz�������ʣ�
 * 8. ͻ��ת��ģʽ֧�ֵ�ͨ�����ͨ�����룻
 * 9. ֧��DMAģʽ��
 * 10. Ӳ��У��ģʽ��
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-25  hgo, add annotation.
 * - 1.00 15-07-15  bob, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "hw/amhw_lpc82x_adc.h"

/******************************************************************************
* Public functions
*******************************************************************************/

/**
 * \brief ADC У��
 */
 
void amhw_lpc82x_adc_calibrate (amhw_lpc82x_adc_t *p_hw_adc,
                                uint32_t           sysclk_freq)
{
    uint32_t ctrl = amhw_lpc82x_adc_ctrl_get(p_hw_adc);
    uint32_t tmp = ctrl;
  
    if (0 == (ctrl & AMHW_LPC82X_ADC_CTRL_CALMODE)) {

         /* ����ģʽλ���Ƶϵ��һ��д��������Ƶ��Ϊ500KHz */
        ctrl |= (AMHW_LPC82X_ADC_CTRL_CALMODE | (sysclk_freq / 500000 - 1));
        amhw_lpc82x_adc_config(p_hw_adc, ctrl);
      
        /* ֱ��У����� */
        while(amhw_lpc82x_adc_ctrl_get(p_hw_adc) &
              AMHW_LPC82X_ADC_CTRL_CALMODE);

        amhw_lpc82x_adc_config(p_hw_adc, tmp);
    }
}

/* end of file */
