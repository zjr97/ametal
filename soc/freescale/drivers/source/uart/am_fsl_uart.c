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
 * \brief UART ����ʵ��
 * 
 * \internal
 * \par Modification history.
 * - 1.03 18-03-16 sdq, fix the bug when uart bits set.
 * - 1.02 18-01-22 sdq, am_fsl_uart_deinit call to pfn_plfm_deinit is added.
 * 	                    call to amhw_fsl_uart_disable instead of
 * 	                    amhw_fsl_uart_enable when closing serial port.
 * - 1.01 16-09-16 nwt, fix the bug when uart tx/rx data by polling.
 * - 1.00 15-10-20 xym, first implementation.
 * \endinternal
 */
#include "am_fsl_uart.h"
#include "am_int.h"
#include "am_clk.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/**
 * \brief ����ģʽ����ѯ���жϣ�����
 */
int __uart_mode_set (am_fsl_uart_dev_t *p_dev, uint32_t new_mode);

/**
 * \brief ����Ӳ������
 */
int __uart_opt_set (am_fsl_uart_dev_t *p_dev, uint32_t opts);


/* Kl26 ���������������� */
static int __uart_ioctl (void *p_drv, int, void *);

static int __uart_tx_startup (void *p_drv);

static int __uart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __uart_poll_getchar (void *p_drv, char *p_char);

static int __uart_poll_putchar (void *p_drv, char outchar);

#if 0
static int __uart_connect (void *p_drv);
#endif

static void __uart_irq_handler (void *p_arg);

/** \brief ��׼��ӿں���ʵ�� */
static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
    __uart_ioctl,
    __uart_tx_startup,
    __uart_callback_set,
    __uart_poll_getchar,
    __uart_poll_putchar,
};

/******************************************************************************/

/**
 * \brief �豸���ƺ���
 *
 * ���а������û�ȡ�����ʣ�ģʽ���ã��ж�/��ѯ������ȡ֧�ֵ�ģʽ��Ӳ��ѡ�����õȹ��ܡ�
 *
 */
static int __uart_ioctl (void *p_drv, int request, void *p_arg)
{
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    int              status    = AM_OK;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
			status = amhw_fsl_uart_ver0_baudrate_set(p_dev->p_devinfo->p_hw_uart,
				                     am_clk_rate_get(p_dev->p_devinfo->clk_id),
									 (uint32_t)p_arg);
        }else{
			status = amhw_fsl_uart_ver1_baudrate_set(p_dev->p_devinfo->p_hw_uart,
				 	                 am_clk_rate_get(p_dev->p_devinfo->clk_id),
									 (uint32_t)p_arg);
        }


        if (status > 0) {
            p_dev->baud_rate = status;
            status = AM_OK;
        } else {
            status = -AM_EIO;
        }
        break;

     /* �����ʻ�ȡ */
    case AM_UART_BAUD_GET:
        *(int *)p_arg = p_dev->baud_rate;
        break;

    /* ģʽ���� */
    case AM_UART_MODE_SET:
        status = (__uart_mode_set(p_dev, (int)p_arg) == AM_OK)
                 ? AM_OK : -AM_EIO;
        break;

    /* ģʽ��ȡ */
    case AM_UART_MODE_GET:
        *(int *)p_arg = p_dev->channel_mode;
        break;

    /* ��ȡ���ڿ����õ�ģʽ */
    case AM_UART_AVAIL_MODES_GET:
        *(int *)p_arg = AM_UART_MODE_INT | AM_UART_MODE_POLL;
        break;

    /* ����ѡ������ */
    case AM_UART_OPTS_SET:
        status = (__uart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    /* ����ѡ���ȡ */
    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;
    default:
        status = -AM_EIO;
        break;
    }

    return (status);
}

/**
 * \brief �������ڷ���(�����ж�ģʽ)
 */
int __uart_tx_startup (void *p_drv)
{
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t     *p_hw_uart = p_dev->p_devinfo->p_hw_uart;
    
    /* ʹ��485���Ϳ������� */
    if (p_dev->p_devinfo->uart_int_485_send) {
        p_dev->p_devinfo->uart_int_485_send(AM_TRUE);
    }

    /* ʹ�ܷ����ж� */
    amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);

    return AM_OK;
}

/**
 * \brief �����жϷ���ص�����
 */
static int __uart_callback_set ( void  *p_drv,
                                 int    callback_type,
                                 void  *pfn_callback,
                                 void  *p_arg)
{
    am_fsl_uart_dev_t *p_dev = (am_fsl_uart_dev_t *)p_drv;

    switch (callback_type) {

    /* ���÷��ͻص������еĻ�ȡ�����ַ��ص����� */
    case AM_UART_CALLBACK_TXCHAR_GET:
        p_dev->pfn_txchar_get = (am_uart_txchar_get_t)pfn_callback;
        p_dev->txget_arg      = p_arg;
        return (AM_OK);

    /* ���ý��ջص������еĴ�Ž����ַ��ص����� */
    case AM_UART_CALLBACK_RXCHAR_PUT:
        p_dev->pfn_rxchar_put = (am_uart_rxchar_put_t)pfn_callback;
        p_dev->rxput_arg      = p_arg;
        return (AM_OK);

    /* ���ô����쳣�ص����� */
    case AM_UART_CALLBACK_ERROR:
        p_dev->pfn_err = (am_uart_err_t)pfn_callback;
        p_dev->err_arg = p_arg;
        return (AM_OK);

    default:
        return (-AM_ENOTSUP);
    }
}

/**
 * \brief ��ѯģʽ�·���һ���ַ�
*/
static int __uart_poll_putchar (void *p_drv, char outchar)
{
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t   *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    uint32_t  idle_stat;
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
    	 idle_stat = (uint32_t)(amhw_fsl_uart_ver0_intstat_get(p_hw_uart)>>7);
    }else{
    	 idle_stat = (uint32_t)(amhw_fsl_uart_ver1_intstat_get(p_hw_uart)>>7);
    }

    /* ����ģ���Ƿ����, 0:æ; 1: ���� */
    if(((uint8_t)idle_stat & amhw_fsl_uart_stat1_tdre_get(p_hw_uart)) == 0) {
        return (-AM_EAGAIN);
    } else {
        /* ��Ϊ����ģʽ */
        if (p_dev->p_devinfo->uart_int_485_send != NULL) {
            /* set to transmit mode */
            p_dev->p_devinfo->uart_int_485_send(AM_TRUE);
        }
        /* ����һ���ַ� */
        amhw_fsl_uart_txdata_write(p_hw_uart, outchar);

        /* �ȴ����Է��� */
        if (p_dev->p_devinfo->uart_int_485_send) {
            /* �����485�������������ȴ���ǰ�ֽڷ�����ɲ��ܸı����ݷ���  */
            while(!amhw_fsl_uart_stat1_tc_get(p_hw_uart));
            /* ��Ϊ����ģʽ */
            p_dev->p_devinfo->uart_int_485_send(AM_FALSE);
        } else {
            while(!amhw_fsl_uart_stat1_tdre_get(p_hw_uart));
        }
    }

    return (AM_OK);
}

/**
 * \brief ��ѯģʽ�½����ַ�
 */
static int __uart_poll_getchar (void *p_drv, char *p_char)
{
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t   *p_hw_uart = p_dev->p_devinfo->p_hw_uart;
    uint8_t            *p_inchar  = (uint8_t *)p_char;

    uint32_t  idle_stat;
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
    	 idle_stat = (uint16_t)(amhw_fsl_uart_ver0_intstat_get(p_hw_uart)>>5);
    }else{
    	 idle_stat = (uint16_t)(amhw_fsl_uart_ver1_intstat_get(p_hw_uart)>>5);
    }
    /* ����ģ���Ƿ���У�0:æ,���ڽ���; 1: �Ѿ����յ�һ���ַ�  */
    if(((uint8_t)idle_stat & amhw_fsl_uart_stat1_rdre_get(p_hw_uart)) == 0) {
        return (-AM_EAGAIN);
    }else {
        /* ����һ���ַ� */
        *p_inchar = amhw_fsl_uart_rxdata_read(p_hw_uart);
    }

    return (AM_OK);
}

/**
 * \brief ���ô���ģʽ
 */
int __uart_mode_set (am_fsl_uart_dev_t *p_dev, uint32_t new_mode)
{
    amhw_fsl_uart_t *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {

        am_int_connect(p_dev->p_devinfo->inum,
                       __uart_irq_handler,
                      (void *)p_dev);
        am_int_enable(p_dev->p_devinfo->inum);

        /* ʹ��RDRF����׼�ж� */
        amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_IRIE);
    } else {
        /* �ر����д����ж� */
        amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_ALL);
    }

    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
int __uart_opt_set (am_fsl_uart_dev_t *p_dev, uint32_t options)
{
    amhw_fsl_uart_t *p_hw_uart = p_dev->p_devinfo->p_hw_uart;
    uint8_t      cfg_flags = 0;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    /* �ڸı�UART�Ĵ���ֵǰ ���շ��ͽ��� */
    amhw_fsl_uart_disable(p_hw_uart);

    /* �������ݳ��� */
    switch (options & AM_UART_CSIZE) {

    case AM_UART_CS8:
        cfg_flags &= ~(1 << 4);
        cfg_flags |= AMHW_FSL_UART_C1_M_8BIT;
        break;

    default:
        break;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x01 << 5);
        cfg_flags |= AMHW_FSL_UART_BDH_SBNS_STOP_2;
    } else {
        cfg_flags &= ~(0x01 << 5);
        cfg_flags |= AMHW_FSL_UART_BDH_SBNS_STOP_1;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x03 << 0);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_FSL_UART_C1_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_FSL_UART_C1_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x03 << 0);
        cfg_flags |= AMHW_FSL_UART_C1_PARITY_NO;
    }

    /* �������Ч���� */

    amhw_fsl_uart_stop_bit_set (p_hw_uart, (cfg_flags & 0x20));
    amhw_fsl_uart_data_mode_set(p_hw_uart, (cfg_flags & 0x10));
    amhw_fsl_uart_parity_set(p_hw_uart,    (cfg_flags & 0x03));

    amhw_fsl_uart_enable(p_hw_uart);

    p_dev->options = options;

    return (AM_OK);
}


/******************************************************************************
  UART interrupt request handler
******************************************************************************/
/**
 * \brief ���ڽ����жϷ���
 */
void __uart_irq_rx_handler (am_fsl_uart_dev_t *p_dev)
{
	  char             data;
    amhw_fsl_uart_t *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    uint32_t  int_stat;
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
    	int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    }else{
    	int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }

    /* �Ƿ�Ϊ����Rx�ж� */
    if ((int_stat & AMHW_FSL_UART_INTSTAT_S1_RDRF) != 0) {

        /* ��ȡ�½������� */
        data = amhw_fsl_uart_rxdata_read(p_hw_uart);

        /* ����½������� */
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

/**
 * \brief ���ڷ����жϷ���
 */
void __uart_irq_tx_handler (am_fsl_uart_dev_t *p_dev)
{
    amhw_fsl_uart_t *p_hw_uart = p_dev->p_devinfo->p_hw_uart;
	  char             data;
    uint32_t         int_stat;
	
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
    	int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    }else{
    	int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }

    if (((int_stat & AMHW_FSL_UART_INTSTAT_S1_TDRE) != 0) || /* �Ƿ�Ϊ����Tx�ж� */
        ((int_stat & AMHW_FSL_UART_INTSTAT_S1_IDLE) != 0)) {

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_fsl_uart_txdata_write(p_hw_uart, data);
        } else {
            /* û�����ݴ��;͹رշ����ж� */
            amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);
            
            /* ��ֹ��485���Ϳ������� */
            if (p_dev->p_devinfo->uart_int_485_send) {
                p_dev->p_devinfo->uart_int_485_send(AM_FALSE);
            }
        }
    }
}

/**
 * \brief �����жϷ�����
 */
void __uart_irq_handler (void *p_arg)
{
    am_fsl_uart_dev_t  *p_dev     = (am_fsl_uart_dev_t *)p_arg;
    amhw_fsl_uart_t    *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    uint32_t  uart_int_stat;
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
    	uart_int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    }else{
    	uart_int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }

    if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_RDRF) {
         __uart_irq_rx_handler(p_dev);
    } else if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_TDRE) {
        __uart_irq_tx_handler(p_dev);
    } else {

    }
    /* �����ж� */
    if ((p_dev->other_int_enable & uart_int_stat) != 0) {

        uart_int_stat &= p_dev->other_int_enable;

        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AM_FSL_UART_ERRCODE_UART_OTHER_INT,
                           (void *)uart_int_stat,
                           1);
        }
    }

}

#if 0
/**
 * \brief UART�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 */
int __uart_connect (void *p_drv)
{
    am_fsl_uart_dev_t *p_dev = (am_fsl_uart_dev_t *)p_drv;

    /* �����ж������ţ������ж� */
    am_int_connect(p_dev->p_devinfo->inum, __uart_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    amhw_fsl_uart_int_enable(p_dev->p_devinfo->p_hw_uart,
                              p_dev->other_int_enable);

    return AM_OK;
}
#endif /* 0 */

/**
 * \brief Ĭ�ϻص�����
 *
 * \returns AW_ERROR
 */
static int __uart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

/**
 * \brief ���ڳ�ʼ������
 */
am_uart_handle_t am_fsl_uart_init (am_fsl_uart_dev_t           *p_dev,
                                    const am_fsl_uart_devinfo_t *p_devinfo)
{
    amhw_fsl_uart_t  *p_hw_uart;
    uint32_t          tmp;

    if (p_devinfo == NULL || p_devinfo->p_hw_uart == NULL) {
        return NULL;
    }

    /* ��ȡ���ò��� */
    p_hw_uart                = p_devinfo->p_hw_uart;
    p_dev->p_devinfo         = p_devinfo;
    p_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;
    p_dev->uart_serv.p_drv   = p_dev;
    p_dev->baud_rate         = p_devinfo->baud_rate;
    p_dev->options           = 0;

    /* ��ʼ��Ĭ�ϻص����� */
    p_dev->pfn_txchar_get    = (int (*) (void *, char*))__uart_dummy_callback;
    p_dev->txget_arg         = NULL;
    p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__uart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           =
                     (int (*) (void *, int, void*, int))__uart_dummy_callback;

    p_dev->err_arg           = NULL;

    p_dev->other_int_enable  = p_devinfo->other_int_enable  &
                               ~(AMHW_FSL_UART_INT_C2_TCIE |
                               AMHW_FSL_UART_INT_C2_IRIE   |
                               AMHW_FSL_UART_INT_C2_ILIE   |
                               AMHW_FSL_UART_INT_C2_TIE);

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* ��ȡ�������ݳ�������ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 4) & 0x01;

    switch (tmp) {

    case 0:
        p_dev->options |= AM_UART_CS7;
        break;

    case 1:
        p_dev->options |= AM_UART_CS8;
        break;

    default:
        p_dev->options |= AM_UART_CS8;
        break;
    }

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 0) & 0x03;

    if (tmp == 2) {
        p_dev->options |= AM_UART_PARENB;
    } else if (tmp == 3) {
        p_dev->options |= (AM_UART_PARENB | AM_UART_PARODD);
    }else{
    }
    /* ��ȡ����ֹͣλ����ѡ�� */
    if (p_devinfo->cfg_flags & AMHW_FSL_UART_BDH_SBNS_STOP_2) {
        p_dev->options |= AM_UART_STOPB;
    }else{

    }
    __uart_opt_set (p_dev, p_dev->options);

    /* ���ò����� */
    if(p_devinfo->ver == AM_FSL_UART_VER0){
    	p_dev->baud_rate  = amhw_fsl_uart_ver0_baudrate_set(p_hw_uart,
    			am_clk_rate_get(p_dev->p_devinfo->clk_id),
                p_devinfo->baud_rate);
    }else{
    	p_dev->baud_rate  = amhw_fsl_uart_ver1_baudrate_set(p_hw_uart,
    			am_clk_rate_get(p_dev->p_devinfo->clk_id),
                p_devinfo->baud_rate);
    }

    /* Ĭ����ѯģʽ  */
    __uart_mode_set(p_dev, AM_UART_MODE_POLL);

    /* uartʹ�� */
    amhw_fsl_uart_enable(p_hw_uart);

    return &(p_dev->uart_serv);
}

/**
 * \brief ����ȥ��ʼ��
 */
void am_fsl_uart_deinit (am_fsl_uart_dev_t *p_dev)
{
    amhw_fsl_uart_t *p_hw_uart   = p_dev->p_devinfo->p_hw_uart;
    p_dev->uart_serv.p_funcs = NULL;
    p_dev->uart_serv.p_drv   = NULL;

    if (p_dev->channel_mode == AM_UART_MODE_INT) {
        /* Ĭ��Ϊ��ѯģʽ */
        __uart_mode_set(p_dev, AM_UART_MODE_POLL);
    }
    /* �رմ��� */
    amhw_fsl_uart_disable(p_hw_uart);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */
