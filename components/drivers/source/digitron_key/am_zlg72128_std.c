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
 * \brief ZLG72128ͨ�ýӿڣ���������ܽӿںͰ����ӿڣ�����ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-05-22  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_input.h"
#include "am_zlg72128_std.h"

/*******************************************************************************
    Local Macro defines
*******************************************************************************/

#define __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie) \
    am_zlg72128_std_dev_t *p_dev = (am_zlg72128_std_dev_t *)p_cookie\

/*******************************************************************************
    Local Functions
*******************************************************************************/

static int __zlg72128_key_code_report (am_zlg72128_std_dev_t *p_dev,
                                       int                    row,
                                       int                    col,
                                       int                    key_state)
{
    int     i;
    uint8_t flags;
    uint8_t actual_row = row;
    uint8_t actual_col = col;

    if ((p_dev->p_info->key_use_row_flags & (1 << row)) &&
        (p_dev->p_info->key_use_col_flags & (1 << col))){

        if (p_dev->p_info->key_use_row_flags != 0x0F) {

            flags = p_dev->p_info->key_use_row_flags;

            for (i = 0; i < row; i++) {
                if ((flags & (1 << i)) == 0) {      /* skip unused rows */
                    actual_row--;
                }
            }
        }

        if (p_dev->p_info->key_use_col_flags != 0xFF) {

            flags = p_dev->p_info->key_use_col_flags;

            for (i = 0; i < col; i++) {
                if ((flags & (1 << i)) == 0) {      /* skip unused cols */
                    actual_col--;
                }
            }
        }

        am_input_key_report(p_dev->p_info->p_key_codes\
                            [actual_row * p_dev->num_cols + actual_col],
                            key_state);
    }

    return AM_OK;
}

/******************************************************************************/
static void __zlg72128_key_process (void    *p_arg,
                                    uint8_t  key_val,
                                    uint8_t  repeat_cnt,
                                    uint8_t  funkey_val)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_arg);
    
    int     i = 0;
    uint8_t change = 0;
    int     row = 0;
    int     col = 0;

    if (key_val != 0x00) {
        key_val--;                     /* let the key_code start from 0 */
        row = key_val / 8;
        col = key_val % 8;
        __zlg72128_key_code_report(p_dev, row, col, AM_INPUT_KEY_STATE_PRESSED);
    }

    if (p_dev->p_info->key_use_row_flags & AM_ZLG72128_STD_KEY_ROW_3) {

        if (p_dev->f_key != funkey_val) {

            change = p_dev->f_key ^ funkey_val;

            for (i = 0; i < 8; i++) {

                if (change & (1 << i)) {
                    __zlg72128_key_code_report(p_dev,
                                               3,
                                               i,
                                               (funkey_val & (1 << i)) ?
                                               AM_INPUT_KEY_STATE_RELEASED :
                                               AM_INPUT_KEY_STATE_PRESSED);
                }
            }

            p_dev->f_key = funkey_val;
        }
    }
}
 
/*******************************************************************************
  Standard digitron driver functions
*******************************************************************************/

static int __digitron_decode_set (void      *p_cookie,
                                  uint16_t (*pfn_decode) (uint16_t ch))
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    if ((p_dev == NULL) || (pfn_decode == NULL)) {
        return -AM_EINVAL;
    }

    p_dev->pfn_decode = pfn_decode;

    return AM_OK;
}

/******************************************************************************/
static int __digitron_blink_set (void *p_cookie, int index, am_bool_t blink)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    AM_BIT_MODIFY(p_dev->blink_flags, index, blink);

    am_zlg72128_digitron_flash_ctrl(p_dev->handle, p_dev->blink_flags);

    return AM_OK;
}

/******************************************************************************/
static int __digitron_disp_at (void *p_cookie, int index, uint16_t seg)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    am_zlg72128_digitron_dispbuf_set(p_dev->handle,
                                     index,
                                     (uint8_t *)&seg,
                                      1);

    return AM_OK;
}

/******************************************************************************/
static int __digitron_disp_char_at (void *p_cookie, int index, const char ch)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    uint8_t seg = 0x00;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    if (am_zlg72128_digitron_disp_char(p_dev->handle,
                                       index,
                                       ch,
                                       AM_FALSE,
                                       AM_FALSE) == -AM_ENOTSUP) {

        if ('.' == ch) {

            am_zlg72128_digitron_seg_ctrl(p_dev->handle,
                                          index,
                                          AM_ZLG72128_DIGITRON_SEG_DP,
                                          AM_TRUE);
        } else {

            if (p_dev->pfn_decode) {
                seg = p_dev->pfn_decode(ch);
            }

            am_zlg72128_digitron_dispbuf_set(p_dev->handle,
                                             index,
                                             &seg,
                                              1);
        }
    }

    return AM_OK;
}

/******************************************************************************/
static int __digitron_disp_str (void       *p_cookie,
                                int         index,
                                int         len,
                                const char *p_str)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);



    if ((p_dev == NULL) || (p_str == NULL)) {
        return -AM_EINVAL;
    }

    am_zlg72128_digitron_disp_str(p_dev->handle, index, p_str);

    return AM_OK;
}

/******************************************************************************/
static int __digitron_clr (void *p_cookie)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);


    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    am_zlg72128_digitron_disp_reset(p_dev->handle);

    return AM_OK;
}

/******************************************************************************/
static int __digitron_enable (void *p_cookie)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    am_zlg72128_digitron_disp_ctrl(p_dev->handle, 0x0000);

    return AM_OK;
}

/******************************************************************************/
static int __digitron_disable (void *p_cookie)
{
    __DIGITRON_ZLG72128_DEV_DECL(p_dev, p_cookie);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }
    am_zlg72128_digitron_disp_ctrl(p_dev->handle, 0xFFFF);

    return AM_OK;
}

/*******************************************************************************
  Global variables
*******************************************************************************/

static const am_digitron_disp_ops_t __g_zlg72128_digitron_dev_ops = {
    __digitron_decode_set,
    __digitron_blink_set,
    __digitron_disp_at,
    __digitron_disp_char_at,
    __digitron_disp_str,
    __digitron_clr,
    __digitron_enable,
    __digitron_disable,
};

/******************************************************************************/
int am_zlg72128_std_init (am_zlg72128_std_dev_t           *p_dev,
                          const am_zlg72128_std_devinfo_t *p_info,
                          am_i2c_handle_t                  i2c_handle)
{
    uint8_t i;
    
    if ((p_dev == NULL) || (p_info == NULL)) {
        return -AM_EINVAL;
    }

    p_dev->blink_flags = 0x0000;
    p_dev->p_info      = p_info;
    p_dev->f_key       = 0xFF;
    p_dev->num_cols    = 0;
    p_dev->num_rows    = 0;
    p_dev->handle      = am_zlg72128_init(&p_dev->zlg72128_dev,
                                          &p_info->base_info,
                                          i2c_handle);
    if (p_dev->handle == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < 8; i++) {

        if (p_info->key_use_col_flags & (1 << i)) {
            p_dev->num_cols++;
        }

        if (p_info->key_use_row_flags & (1 << i)) {
            p_dev->num_rows++;
        }
    }

    am_zlg72128_key_cb_set(p_dev->handle, __zlg72128_key_process, p_dev);

    am_zlg72128_digitron_disp_reset(p_dev->handle);

    am_zlg72128_digitron_flash_time_cfg(p_dev->handle,
                                        p_info->blink_on_time,
                                        p_info->blink_off_time);

    return am_digitron_dev_add(&p_dev->digitron_dev,
                               &p_info->id_info,
                               &__g_zlg72128_digitron_dev_ops,
                                p_dev);
}

/* end of file */
