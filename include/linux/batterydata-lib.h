/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __BMS_BATTERYDATA_H
#define __BMS_BATTERYDATA_H

#include <linux/errno.h>

#define FCC_CC_COLS		5
#define FCC_TEMP_COLS		8

#define PC_CC_ROWS             31
#define PC_CC_COLS             13

#define PC_TEMP_ROWS		31
#define PC_TEMP_COLS		8

#define ACC_IBAT_ROWS		6
#define ACC_TEMP_COLS		3

#define MAX_SINGLE_LUT_COLS	20

#define MAX_BATT_ID_NUM		4
#define DEGC_SCALE		10

struct single_row_lut {
	int x[MAX_SINGLE_LUT_COLS];
	int y[MAX_SINGLE_LUT_COLS];
	int cols;
};

/**
 * struct sf_lut -
 * @rows:	number of percent charge entries should be <= PC_CC_ROWS
 * @cols:	number of charge cycle entries should be <= PC_CC_COLS
 * @row_entries:	the charge cycles/temperature at which sf data
 *			is available in the table.
 *		The charge cycles must be in increasing order from 0 to rows.
 * @percent:	the percent charge at which sf data is available in the table
 *		The  percentcharge must be in decreasing order from 0 to cols.
 * @sf:		the scaling factor data
 */
struct sf_lut {
	int rows;
	int cols;
	int row_entries[PC_CC_COLS];
	int percent[PC_CC_ROWS];
	int sf[PC_CC_ROWS][PC_CC_COLS];
};

/**
 * struct pc_temp_ocv_lut -
 * @rows:	number of percent charge entries should be <= PC_TEMP_ROWS
 * @cols:	number of temperature entries should be <= PC_TEMP_COLS
 * @temp:	the temperatures at which ocv data is available in the table
 *		The temperatures must be in increasing order from 0 to rows.
 * @percent:	the percent charge at which ocv data is available in the table
 *		The  percentcharge must be in decreasing order from 0 to cols.
 * @ocv:	the open circuit voltage
 */
struct pc_temp_ocv_lut {
	int rows;
	int cols;
	int temp[PC_TEMP_COLS];
	int percent[PC_TEMP_ROWS];
	int ocv[PC_TEMP_ROWS][PC_TEMP_COLS];
};

struct ibat_temp_acc_lut {
	int rows;
	int cols;
	int temp[ACC_TEMP_COLS];
	int ibat[ACC_IBAT_ROWS];
	int acc[ACC_IBAT_ROWS][ACC_TEMP_COLS];
};

struct batt_ids {
	int kohm[MAX_BATT_ID_NUM];
	int num;
};

enum battery_type {
	BATT_UNKNOWN = 0,
	BATT_PALLADIUM,
	BATT_DESAY,
	BATT_OEM,
	BATT_QRD_4V35_2000MAH,
	BATT_QRD_4V2_1300MAH,
};

/**
 * struct bms_battery_data -
 * @fcc:		full charge capacity (mAmpHour)
 * @fcc_temp_lut:	table to get fcc at a given temp
 * @pc_temp_ocv_lut:	table to get percent charge given batt temp and cycles
 * @pc_sf_lut:		table to get percent charge scaling factor given cycles
 *			and percent charge
 * @rbatt_sf_lut:	table to get battery resistance scaling factor given
 *			temperature and percent charge
 * @default_rbatt_mohm:	the default value of battery resistance to use when
 *			readings from bms are not available.
 * @delta_rbatt_mohm:	the resistance to be added towards lower soc to
 *			compensate for battery capacitance.
 * @rbatt_capacitve_mohm: the resistance to be added to compensate for
 *				battery capacitance
 * @flat_ocv_threshold_uv: the voltage where the battery's discharge curve
 *				starts flattening out.
 * @max_voltage_uv:	max voltage of the battery
 * @cutoff_uv:		cutoff voltage of the battery
 * @iterm_ua:		termination current of the battery when charging
 *			to 100%
 * @batt_id_kohm:	the best matched battery id resistor value
 */

/* <DTS2014042804721 chenyuanquan 20140428 begin */
struct bms_battery_data {
	unsigned int		fcc;
	struct single_row_lut	*fcc_temp_lut;
	struct single_row_lut	*fcc_sf_lut;
	struct pc_temp_ocv_lut	*pc_temp_ocv_lut;
	struct ibat_temp_acc_lut *ibat_acc_lut;
	struct sf_lut		*pc_sf_lut;
	struct sf_lut		*rbatt_sf_lut;
	int			default_rbatt_mohm;
	int			delta_rbatt_mohm;
	int			rbatt_capacitive_mohm;
	int			flat_ocv_threshold_uv;
	int			max_voltage_uv;
	int			cutoff_uv;
	int			iterm_ua;
	int			batt_id_kohm;
	const char		*battery_type;
#ifdef CONFIG_HUAWEI_KERNEL
	int			warm_bat_decidegc;
	int			warm_bat_chg_ma;
	int			warm_bat_mv;
	int			cool_bat_decidegc;
	int			cool_bat_chg_ma;
	int			cool_bat_mv;
	int			cold_bat_decidegc;
	int			hot_bat_decidegc;
#endif
};
/* DTS2014042804721 chenyuanquan 20140428 end> */

/* < DTS2014100804605 taohanwen 20141008 begin */
#ifdef CONFIG_HUAWEI_KERNEL
struct max77819_temp_control_info {
	short	cold_bat_degree;		/*lowest temperature to stop charging*/
	short	cool_bat_degree;		/*cool temprature to limit charging current and voltage*/
	int		imaxua_cool_bat;		/* ua max battery charging input current */
	int		vmaxuv_cool_bat;		/* uv max battery terminate voltage*/
	short	warm_bat_degree;		/*warm temprature to limit charging current and voltage*/
	int		imaxua_warm_bat;		/* ua max battery charging input current */
	int		vmaxuv_warm_bat;		/* uv max battery terminate voltage*/
	short	hot_bat_degree;			/*highest temperature to stop charging*/
	int		sys_limit_current;		/*the limit charging current by system*/
};

/*below info should be provided by Maxim with a *.INI file
for detailed infor, pls refer to maxim fuelgauge usermanual 20140916 beigin*/
#define MAX17048_MODEL_DATA_SIZE	64
/* < DTS2014102005552 taohanwen 20141020 begin */
/* add full capacity info */
struct max17048_batt_data{
	int		full_capacity;
	short	ini_rcompseg;
	char	ini_rcomp;
	int		ini_tempco_up;
	int		ini_tempco_dwon;
	char	ini_soccheck_a;
	char	ini_soccheck_b;
	short	ini_ocvtest;
	char	ini_bits;
	char	model_data[MAX17048_MODEL_DATA_SIZE];
};
/* DTS2014102005552 taohanwen 20141020 end > */
#endif
/* DTS2014100804605 taohanwen 20141008 end > */

#if defined(CONFIG_PM8921_BMS) || \
	defined(CONFIG_PM8921_BMS_MODULE) || \
	defined(CONFIG_QPNP_BMS) || \
	defined(CONFIG_QPNP_VM_BMS)
extern struct bms_battery_data  palladium_1500_data;
extern struct bms_battery_data  desay_5200_data;
extern struct bms_battery_data  oem_batt_data;
extern struct bms_battery_data QRD_4v35_2000mAh_data;
extern struct bms_battery_data  qrd_4v2_1300mah_data;

int interpolate_fcc(struct single_row_lut *fcc_temp_lut, int batt_temp);
int interpolate_scalingfactor(struct sf_lut *sf_lut, int row_entry, int pc);
int interpolate_scalingfactor_fcc(struct single_row_lut *fcc_sf_lut,
				int cycles);
int interpolate_pc(struct pc_temp_ocv_lut *pc_temp_ocv,
				int batt_temp_degc, int ocv);
int interpolate_ocv(struct pc_temp_ocv_lut *pc_temp_ocv,
				int batt_temp_degc, int pc);
int interpolate_slope(struct pc_temp_ocv_lut *pc_temp_ocv,
					int batt_temp, int pc);
int interpolate_acc(struct ibat_temp_acc_lut *ibat_acc_lut,
					int batt_temp, int ibat);
int linear_interpolate(int y0, int x0, int y1, int x1, int x);
int is_between(int left, int right, int value);
#else
static inline int interpolate_fcc(struct single_row_lut *fcc_temp_lut,
			int batt_temp)
{
	return -EINVAL;
}
static inline int interpolate_scalingfactor(struct sf_lut *sf_lut,
			int row_entry, int pc)
{
	return -EINVAL;
}
static inline int interpolate_scalingfactor_fcc(
			struct single_row_lut *fcc_sf_lut, int cycles)
{
	return -EINVAL;
}
static inline int interpolate_pc(struct pc_temp_ocv_lut *pc_temp_ocv,
			int batt_temp_degc, int ocv)
{
	return -EINVAL;
}
static inline int interpolate_ocv(struct pc_temp_ocv_lut *pc_temp_ocv,
			int batt_temp_degc, int pc)
{
	return -EINVAL;
}
static inline int interpolate_slope(struct pc_temp_ocv_lut *pc_temp_ocv,
					int batt_temp, int pc)
{
	return -EINVAL;
}
static inline int linear_interpolate(int y0, int x0, int y1, int x1, int x)
{
	return -EINVAL;
}
static inline int is_between(int left, int right, int value)
{
	return -EINVAL;
}
static inline int interpolate_acc(struct ibat_temp_acc_lut *ibat_acc_lut,
						int batt_temp, int ibat)
{
	return -EINVAL;
}
#endif

#endif
