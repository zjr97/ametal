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
 * \brief ADC ���ð��ӵ���������(NTC)��������¶����̣�ͨ����׼�ӿ�ʵ��
 *
 * ��  demo �����ڵ��͵� NTC ��·��
 *
 *                -------------- Vref
 *                |
 *                |
 *               ---
 *               | |
 *          NTC  | |
 *               | |
 *               ---
 *                |
 *                |-------------- ADC ����ˣ�ADC���ɼ��õ�ĵ�ѹ��
 *                |
 *               ---
 *               | |
 *      ��ѹ���� | |
 *               | |
 *               ---
 *                |
 *                |
 *                ---------------- GND
 *
 * - �������裺
 *   1. ��ADC�������������Ӧ��ADC��������
 *
 * - ʵ������
 *   1. ���Դ�������¶�ֵ��
 *
 * \par Դ����
 * \snippet demo_std_adc_ntc.c src_std_adc_ntc
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-10  hgo, modified
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc_ntc
 * \copydoc demo_std_adc_ntc.c
 */

/** [src_std_adc_ntc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_adc.h"

/*******************************************************************************
 *  ȫ�ֱ�������
*******************************************************************************/

/**
 * \brief ��ֵ�¶ȱ�
 *
 * �б��ж�Ӧ���¶�ֵ������-20~87�棬����1�档���磬-20�ȶ�Ӧ����ֵ�� 70988�� ��ʾ
 * 70988ŷķ��Ӧ���¶ȼ�Ϊ -20�ȡ�
 *
 * 25�ȣ����£���Ӧ����ֵΪ 100K�� ����Ӧ�� NTC Ϊ 100K NTC��NTC�Գ�����ֵ��Ϊ���ֵ��
 *
 * ��ͬ NTC ���裬����Ӧ�����ݿ��ܲ�ͬ��
 */
static const uint32_t g_temp_res_val[] = {

    /* -20�� ~  -9�� */
    70988,67491,64191,61077,58135,55356,52730,50246,47896,45672,43567,41572,

    /*  -8�� ~   3�� */
    39682,37891,36192,34580,33050,31597,30218,28907,27662,26477,25351,24279,

    /*   4�� ~  15�� */
    23259,22288,21363,20482,19642,18842,18078,17350,16656,15993,15360,14756,

    /*  16�� ~  27�� */
    14178,13627,13100,12596,12114,11653,11212,10790,10387,10000, 9630, 9275,

    /*  28�� ~  39�� */
    8936, 8610, 8298, 7999, 7712, 7437, 7173, 6920, 6677, 6444, 6220, 6005,

    /*  40�� ~  51�� */
    5799, 5600, 5410, 5227, 5050, 4881, 4718, 4562, 4411, 4267, 4127, 3995,

    /*  52�� ~  63�� */
    3867, 3744, 3626, 3512, 3402, 3296, 3194, 3096, 3002, 2910, 2822, 2737,

    /*  64�� ~  75�� */
    2655, 2576, 2500, 2426, 2355, 2286, 2220, 2156, 2094, 2034, 1976, 1920,

    /*  76�� ~  87�� */
    1866, 1813, 1763, 1714, 1666, 1621, 1576, 1533, 1492, 1451, 1412, 1375,
};

static const int res_val_num = sizeof(g_temp_res_val) / sizeof(g_temp_res_val[0]);
static const int temp_start  = -20;    /* �������ʼ�¶�Ϊ-20�� */

static uint32_t __adc_code_get (am_adc_handle_t handle, int chan)
{
    int      adc_bits = am_adc_bits_get(handle, chan);
    int      i;
    uint32_t sum;

    /*
     * ����ADCת�������ɼ�12�� CODE ֵ
     *
     * ʵ��Ӧ���У���ʹ�õ� ADC λ����ȷ���ģ����������ֶ����������
     */
    if (adc_bits <= 8) {
        uint8_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else if (adc_bits <= 16) {
        uint16_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else {
        uint32_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    }
    return (sum / 12);
}

/**
 * \brief �¶������1��֮��ͨ���㷨ȡ�����ֵ
 *
 * \param[in] t1 : ��߽��¶�
 * \param[in] t1 : �ұ߽��¶�
 *
 * \return temp : �¶�ֵ
 */
static int16_t __ntc_temp_get_from_range (int t1,int t2, uint32_t res)
{
    int r1 = g_temp_res_val[t1 - temp_start];  /* �õ��¶�1��Ӧ����ֵ */
    int r2 = g_temp_res_val[t2 - temp_start];  /* �õ��¶�2��Ӧ����ֵ */

    int r  = res;
    int temp;

    /* Ϊ����С������������256��������8λ�� */
    temp =  (((t2 - t1) * (r - r1)) << 8) / (r2 - r1) + (t1 << 8);

    return temp;
}

/**
 * \brief ���ַ����������Ӧ���¶�ֵ
 *
 * \param[in]  res : ������ֵ
 *
 * \return temp : �¶�ֵ
 */
static int16_t __ntc_res_to_temp (uint32_t res)
{
    int16_t   temp;
    int low, high, mid;     /* ���ַ����������±� */
    int t1,t2;              /* ����������¶�ֵ t1 ~ t2 */

    low  = 0;               /* ��ʼ���ϱ߽�Ϊ��һ�� */
    high = res_val_num - 1; /* ��ʼ���±߽�Ϊ���һ�� */

    while(1) {

        /* ����һλ����Ч�� (low + high)/2 */
        mid = (low + high) >> 1;

        /* ���ǡ����� */
        if (res == g_temp_res_val[mid]) {
            /* �����¶�ֵ������256�� */
            temp = (mid - 20) << 8;
            break;
        }

        /* ��ֵ�����м�ֵ����������ΧΪǰ�벿�֣�����highֵ */
        if (res > g_temp_res_val[mid]) {
            high = mid;
        } else {

            /* ��ֵС���м�ֵ����������ΧΪ��벿�֣�����lowֵ */
            low = mid;
        }

        /* ������Χȷ����1���ڣ��ҵ��¶�������Χ */
        if (high - low == 1) {

            /* �ұ߽��¶�ֵ */
            t2 = high + temp_start;

            /* ��߽��¶�ֵ */
            t1 = low - 1 + temp_start;

            /* ��������¶�ֵ */
            temp = __ntc_temp_get_from_range(t1, t2, res);

            break;
        }
    }

    return temp;
}

/**
 * \brief �������
 */
void demo_std_adc_ntc_entry (am_adc_handle_t handle,
                             int             chan,
                             uint32_t        res_fixed)
{
    int16_t         temp;      /* �¶�ֵ */
    uint32_t        res;       /* ����������ֵ */
    uint32_t        adc_bits;
    uint32_t        code;

    /* ���ò�����Ϊ 6000 */
    am_adc_rate_set(handle, chan, 6000);

    /* ��ȡADC�ο���ѹ����λ��mV */
    adc_bits = am_adc_bits_get(handle,chan);

    while (1) {

        /**
         * ���ݵ����ѹ��·�ɵ�:
         *    ������ѹ =  vref * (res_fixed / (res_ntc + res_fixed))
         *
         * �ٶ� ADCλ��Ϊ N�������õ���ֵΪ CODE�� �������ѹΪ��
         *
         * (CODE / (1 << N)) * Vref
         *
         * �������湫ʽ�ɵã�
         *
         * (CODE / (1 << N)) * Vref =  vref * (res_fixed / (res_ntc + res_fixed))
         *
         * ͬʱ��ȥ vref ��
         *
         * (CODE / (1 << N)) = (res_fixed / (res_ntc + res_fixed))
         *
         * �ɴ˿ɵã�
         *
         * res_ntc = (((1 << N) - CODE) * res_fixed) / CODE
         *
         */
        code = __adc_code_get(handle, chan);

        res  = (((1 << adc_bits) - code) * res_fixed) / code;

        temp = __ntc_res_to_temp(res);      /* ������ת�����¶Ȳ��� */

        AM_DBG_INFO("the temperature is %d.%2d ��\r\n",
                    temp >> 8,                   /* �¶�������256��  */
                    (temp & 0xFF) * 100 / 256);  /* ��ӡ��λС��         */

        am_mdelay(500);
    }
}
/** [src_std_adc_ntc] */

/* end of file */
