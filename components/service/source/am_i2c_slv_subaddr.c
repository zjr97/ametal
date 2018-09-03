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
 * \brief I2C implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-19  vir, first implementation.
 * \endinternal
 */
#include "am_i2c_slv_subaddr.h"

/**
 * \brief ��������
 */
static int __i2c_slv_subaddr_addr_match(void *p_arg, am_bool_t is_rx);
static int __i2c_slv_subaddr_txbyte_get(void *p_arg, uint8_t *p_outbyte);
static int __i2c_slv_subaddr_rxbyte_put(void *p_arg, uint8_t inbyte);
static void __i2c_slv_subaddr_tran_stop(void *p_arg);
static int __i2c_slv_subaddr_gen_call(void *p_arg, uint8_t byte);

/**
 * \brief �ص���������
 */
static am_i2c_slv_cb_funcs_t __g_subaddr_cb_funs = {
        __i2c_slv_subaddr_addr_match,
        __i2c_slv_subaddr_txbyte_get,
        __i2c_slv_subaddr_rxbyte_put,
        __i2c_slv_subaddr_tran_stop,
        __i2c_slv_subaddr_gen_call,
};
/**
 * \brief �ж��ӵ�ַ����Ч��
 */
static int __i2c_slv_subaddr_validator(void * p_arg)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
        if ( p_dev->subaddr >= p_dev->reg_num ) {
            return AM_ERROR;
        }
    } else {
        if ( p_dev->subaddr >= p_dev->reg_info->reg_len ) {
            return AM_ERROR;
        }
    }
    return AM_OK;
}

/**
 * \brief ����ӵ�ַ
 */
static int __i2c_slv_subaddr_get( void * p_arg,  uint8_t inbyte)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    /* 2�ֽڵ��ӵ�ַ ����*/
    if ( p_dev->subaddr_dev_flags & AM_I2C_SLV_SUBADDR_2BYTE ){
        if( p_dev->subaddr_count_flag == 1) {
            /* �Ƚ����ܵ������ֽڷ��� subaddr �� */
            p_dev->subaddr  |=  inbyte << 8;
            p_dev->subaddr_count_flag = 0;  /* �´ν��ܴӵ�0����ʼ���� �ӵ�ַ�ֽ��� */
            p_dev->is_subaddr = AM_FALSE;   /* �������ӵ�ַ */
            return AM_OK;
        } else {
            p_dev->subaddr_count_flag = 1;
            p_dev->subaddr    = inbyte;  /* ���ܵ�һ���ֽ��ӵ�ַ */
        }
    } else {
        /* ����Ĭ�� λһ���ֽڵ��ӵ�ַ */
        p_dev->subaddr    = inbyte;
        p_dev->is_subaddr = AM_FALSE;  /* ��ʾ�ѽ��ܵ��ӵ�ַ */
        return AM_OK;
    }

    /* ��ʾû������ ����ܴ��� */
    return AM_ERROR;
}


/**
 * \brief ��ַƥ��ʱ�ص�
 */
static int __i2c_slv_subaddr_addr_match(void *p_arg, am_bool_t is_rx)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    /** ִ���û����õĻص� */
    if (p_dev->p_cb_funs->pfn_addr_match ) {
        p_dev->p_cb_funs->pfn_addr_match( p_dev->p_arg, is_rx);
    }
    /* ׼����ν��ܻ������� */
    p_dev->is_subaddr = AM_TRUE;
    p_dev->data_count = 0;

    return AM_I2C_SLV_ACK;
}
/**
 * \brief ��ȡһ�������ֽڻص�����
 */
static int __i2c_slv_subaddr_txbyte_get(void *p_arg, uint8_t *p_outbyte)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    if ( NULL == p_dev->cur_reg_info) {
        return AM_I2C_SLV_NACK;
    }

    /*  �ж��Ƿ�֧������ */
    if (p_dev->subaddr_dev_flags & AM_I2C_SLV_SUBADDR_NSELF_INCREASING ) {
        if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
            if( p_dev->data_count >= p_dev->cur_reg_info->reg_len) {
                /* �ӻ�����Ӧ ����������0 */
                *p_outbyte = 0;
                return AM_I2C_SLV_NACK;
            }
        } else if (p_dev->data_count >= p_dev->reg_bit_width) {
            *p_outbyte = 0;
            return AM_I2C_SLV_NACK;
        }
    }

    /** �ӵ�ַ��������  */
    if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
        if ( p_dev->off_byte  >=  p_dev->cur_reg_info->reg_len ) {
            p_dev->off_byte = 0;
            p_dev->cur_reg_info = p_dev->cur_reg_info + 1;  /* ��ȡ��һ���ӵ�ַ��Ӧ�ļĴ�����Ϣ */

            /* �����˼Ĵ������ܸ��� ����0�ӵ�ַ��ʼ  */
            if ( p_dev->cur_reg_info == ( p_dev->reg_info + p_dev->reg_num)) {
                p_dev->cur_reg_info =   p_dev->reg_info;
            }
        }
    } else {
        p_dev->off_byte %= p_dev->cur_reg_info->reg_len;   /* ������ͷ��ʼ */
    }

    *p_outbyte = p_dev->cur_reg_info->p_reg_addr[ p_dev->off_byte];

    p_dev->off_byte++;         /* �ֽ�ƫ�Ƽ�1 */
    p_dev->is_rx = AM_FALSE;    /* ��ʾ ����״̬ */
    p_dev->data_count++;       /* ���ܵ����ݼ�1(�������ӵ�ַ���� ) */

    return AM_I2C_SLV_ACK;
}

/**
 * \brief ���յ�һ���ֽڻص�
 */
static int __i2c_slv_subaddr_rxbyte_put(void *p_arg, uint8_t inbyte)
{

    int ret ;
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;
    uint8_t temp = 0;

    /* ��ȡ�ӵ�ַ */
    if ( p_dev->is_subaddr == AM_TRUE ) {
        ret =  __i2c_slv_subaddr_get( p_dev, inbyte);

        if ( AM_OK != ret ) {
            return ret;
        }
         /* �ж��ӵ�ַ����Ч�� */
         ret = __i2c_slv_subaddr_validator(p_dev);
        if ( AM_OK != ret ) {
            p_dev->cur_reg_info = NULL;
            return ret;
        }
        if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
            /* �Ĵ�����������  */
             p_dev->cur_reg_info = p_dev->reg_info + p_dev->subaddr;
             p_dev->off_byte = 0;
        } else {
            /* �Ĵ����ռ���� ���� (8λ��16λ��32λ)*/
            p_dev->cur_reg_info  = p_dev->reg_info;
            p_dev->off_byte    = inbyte * (p_dev->reg_bit_width);
        }
        return ret;
    }

    if ( NULL == p_dev->cur_reg_info) {
        return AM_I2C_SLV_NACK;
    }

    /*  �ж��Ƿ�֧������ */
    if (p_dev->subaddr_dev_flags & AM_I2C_SLV_SUBADDR_NSELF_INCREASING ) {
        if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
            if( p_dev->data_count >= p_dev->cur_reg_info->reg_len) {
                /* �ӻ�����Ӧ */
                return AM_I2C_SLV_NACK;
            }
        } else if (p_dev->data_count >= p_dev->reg_bit_width) {
            return AM_I2C_SLV_NACK;
        }
    }

    /** �ӵ�ַ��������  */
    if ( p_dev->reg_mode &  AM_I2C_SLV_REG_IRREGULAR ) {
        if ( p_dev->off_byte  >=  p_dev->cur_reg_info->reg_len ) {
            p_dev->off_byte = 0;
            p_dev->cur_reg_info = p_dev->cur_reg_info + 1;  /* ��ȡ��һ���ӵ�ַ��Ӧ�ļĴ�����Ϣ */

            /* �����˼Ĵ������ܸ��� ����0�ӵ�ַ��ʼ  */
            if ( p_dev->cur_reg_info == ( p_dev->reg_info + p_dev->reg_num)) {
                p_dev->cur_reg_info =   p_dev->reg_info;
            }
        }
    } else {
        p_dev->off_byte %= p_dev->cur_reg_info->reg_len;   /* ������ͷ��ʼ */
    }


    if ( p_dev->cur_reg_info->p_reg_wr) {
        /* ����д�������� ,�����ܵ������ݴ洢����*/
        if( p_dev->cur_reg_info->p_reg_wr [p_dev->off_byte] ) {
            temp =  p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte];
            p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte] = inbyte;
            p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte] &= ~p_dev->cur_reg_info->p_reg_wr[p_dev->off_byte];
            p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte] |= temp & p_dev->cur_reg_info->p_reg_wr[p_dev->off_byte];
        } else {
            p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte] = inbyte;
        }
    } else {
        /* ��û���ö�д��־��Ĭ�Ͽɶ���д */
        p_dev->cur_reg_info->p_reg_addr[p_dev->off_byte] = inbyte;
    }

    p_dev->off_byte++;          /* �ֽ�ƫ�Ƽ�1 */
    p_dev->is_rx = AM_TRUE;    /* ��ʾ �������״̬ */
    p_dev->data_count++;       /* ���ܵ����ݼ�1(�������ӵ�ַ���� ) */

    return AM_I2C_SLV_ACK;
}


/**
 * \brief ����ֹͣ�ص�
 */
static void __i2c_slv_subaddr_tran_stop(void *p_arg)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    if ( p_dev->p_cb_funs->pfn_tran_finish) {
        /* ��������ص� */
        p_dev->p_cb_funs->pfn_tran_finish( p_dev->p_arg,
                                           p_dev->is_rx,
                                           p_dev->subaddr,
                                           p_dev->data_count);
    }
    /* ������� ,�´ν�����Ҫ���½����ֵ�ַ */
    p_dev->is_subaddr = AM_TRUE;
    p_dev->data_count = 0;
}

/**
 * \brief �㲥�ص�����
 */
static int __i2c_slv_subaddr_gen_call(void *p_arg, uint8_t byte)
{
    am_i2c_slv_subaddr_device_t  *p_dev = ( am_i2c_slv_subaddr_device_t *)p_arg;

    if ( p_dev->p_cb_funs->pfn_gen_call ) {
        p_dev->p_cb_funs->pfn_gen_call(p_dev->p_arg, byte);
    }

    return AM_I2C_SLV_ACK;
}

/**
 * \brief ����һ�����ӵ�ַ���豸
 */
void am_i2c_slv_subaddr_mkdev( am_i2c_slv_subaddr_device_t   *p_dev,
                               am_i2c_slv_handle_t            handle,
                               am_i2c_slv_subaddr_cb_funcs_t *p_cb_funs,
                               void                          *p_arg,
                               uint16_t                       dev_addr,
                               uint16_t                       dev_flags,
                               am_i2c_slv_subaddr_reg_info_t *p_reg_info,
                               uint32_t                       reg_num,
                               uint8_t                        reg_mode)
{
    am_i2c_slv_device_t  *p_i2c_slv_dev = NULL;

    if ( NULL == p_dev     ||
         NULL == p_reg_info ) {
        return ;
    }

    p_i2c_slv_dev = & p_dev->i2c_slv_dev;

    /** ��ʼ�������ӵ�ַ���豸�ṹ�� */
    p_dev->is_subaddr         = AM_TRUE;
    p_dev->subaddr            = 0;
    p_dev->subaddr_count_flag = 0;
    p_dev->data_count         = 0;
    p_dev->off_byte           = 0;

    p_dev->subaddr_dev_flags = dev_flags;

    /** �ص����� */
    p_dev->p_cb_funs         = p_cb_funs;
    p_dev->p_arg             = p_arg;

    /** �ӵ�ַ�мĴ�����Ϣ */
    p_dev->reg_info          = p_reg_info;
    p_dev->cur_reg_info      = NULL;
    p_dev->reg_num           = reg_num;
    p_dev->reg_mode  = reg_mode;


    if ( reg_mode  & AM_I2C_SLV_REG_16_BIT) {
        /** 16λ �������ֽ� */
        p_dev->reg_bit_width = 2;
    } else if ( dev_flags & AM_I2C_SLV_REG_32_BIT ) {
        /* 32 λ ���ĸ��ֽ� */
        p_dev->reg_bit_width = 4;
    } else {
        /* 8λ ��1�ֽ� ��Ĭ�� */
        p_dev->reg_bit_width = 1;
    }

    /** ��ʼ�� ���豸�ṹ�� */
    am_i2c_slv_mkdev (p_i2c_slv_dev,
                      handle,
                      &__g_subaddr_cb_funs ,
                      dev_addr,
                      dev_flags,
                      p_dev);

}

/* end of file */
