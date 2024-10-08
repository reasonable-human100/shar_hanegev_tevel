/*
 * @file	EPS.h
 * @brief	EPS- Energy Powering System.This system is incharge of the energy consumtion
 * 			the satellite and switching on and off power switches(5V, 3V3)
 * @see		inspect logic flowcharts thoroughly in order to write the code in a clean manner.
 */
#ifndef EPS_H_
#define EPS_H_

// #include <satellite-subsystems/GomEPS.h>

#include "satellite-subsystems/imepsv2_piu.h"
#include "satellite-subsystems/imepsv2_piu_types.h"
#include "utils.h"
#include "GlobalStandards.h"
#include "hal/Storage/FRAM.h"
#include "EPSOperationModes.h"
#include "SubSystemModules/Communication/SatCommandHandler.h"
#include <stdint.h>

/*
 	 	 	 	  ______
			  ___|		|___
 	 	 	 |				|
 	 	 	 |	FULL MODE	|
 	 	 	 |- - - - - - -	|	-> FULL UP = 7400
 	 	 	 |- - - - - - - |	-> FULL DOWN = 7300
 	 	 	 |				|
 	 	 	 |	CRUISE MODE	|
 	 	 	 |- - - - - - -	|	-> CRUISE UP = 7200
 	 	 	 |- - - - - - - |	-> CRUISE DOWN = 7100
 	 	 	 |				|
 	 	 	 |	SAFE MODE	|
 	 	 	 |- - - - - - -	| 	-> SAFE UP = 6600
 	 	 	 |- - - - - - - |	-> SAFE DOWN = 6500
 	 	 	 |______________|
 */

//#define NUMBER_OF_SOLAR_PANELS	    6
//#define NUMBER_OF_THRESHOLD_VOLTAGES 	6 

#define DEFAULT_ALPHA_VALUE 0.3

// in Mv
#define DEFFAULT_FULL_MODE_DOWN_TEND 7300
#define DEFFAULT_FULL_MODE_UP_TEND 7400

#define DEFFAULT_CRUISE_MODE_DOWN_TEND 7100
#define DEFFAULT_CRUISE_MODE_UP_TEND 7200

#define DEFFAULT_SAFE_MODE_DOWN_TEND 6500
#define DEFFAULT_SAFE_MODE_UP_TEND 6600

#define DEFFAULT_CIRTICAL_MODE_DOWN_TEND 5500

IMEPSV2_PIU_t imeps_i2c_addr = {IMEPS_I2C_ADDR};

// set to the saved values in fram see eps.c
struct eps_mode_volts_t {
    voltage_t full_mode_down_tend;
    voltage_t full_mode_up_tend;

    voltage_t cruise_mode_down_tend;
    voltage_t cruise_mode_up_tend;

    voltage_t safe_mode_down_tend;
    voltage_t safe_mode_up_tend;

}eps_mode_volts;

float alpha_value; // also set from fram in eps.c

typedef union __attribute__ ((__packed__)){
struct {
	int16_t H1_MIN;
	int16_t H1_MAX;
	int16_t H2_MIN;
	int16_t H2_MAX;
	int16_t H3_MIN;
	int16_t H3_MAX;
}value;
}HeaterValues;
/*!
 * @brief initializes the EPS subsystem.
 * @return	0 on success
 * 			-1 on failure of init
 */
int EPS_Init();

/*!
 * @brief EPS logic. controls the state machine of which subsystem
 * is on or off, as a function of only the battery voltage
 * @return	0 on success
 * 			-1 on failure setting state of channels
 */
int EPS_Conditioning();

// saves alpha and eps_mode_volts to the fram
int EPS_save_settings();

// resets alpha and eps_mode_volts to the default values
int EPS_reset_settings();

short GetBatteryVoltage();

/*!
 * @brief setting the new EPS logic threshold voltages on the FRAM.
 * @param[in] eps_mode_volts_t with the new voltages 
 * @return	0 on success
 * 			-1 on failure setting new threshold voltages
 * 			-2 on invalid thresholds
 * 			ERR according to <hal/errors.h>
 */
int UpdateThresholdVoltages(struct eps_mode_volts_t new_eps_mode_volts);

/*!
 * @brief getting the EPS logic threshold  voltages on the FRAM.
 * @param[out] thresh_volts a buffer to hold the threshold values
 * @return	0 on success
 * 			-1 on NULL input array
 * 			-2 on FRAM read errors
 */
struct eps_mode_volts_t GetThresholdVoltages();

/*!
 * @brief getting the smoothing factor (alpha) from the FRAM.
 * @param[out] alpha a buffer to hold the smoothing factor
 * @return	0 on success
 * 			-1 on NULL input array
 * 			-2 on FRAM read errors
 */
float GetAlpha();

/*!
 * @brief setting the new voltage smoothing factor (alpha) on the FRAM.
 * @param[in] new_alpha new value for the smoothing factor alpha
 * @note new_alpha is a value in the range - (0,1)
 * @return	0 on success
 * 			-1 on failure setting new smoothing factor
 * 			-2 on invalid alpha
 * @see LPF- Low Pass Filter at wikipedia: https://en.wikipedia.org/wiki/Low-pass_filter#Discrete-time_realization
 */
int UpdateAlpha(float new_alpha);

/*!
 * @brief setting the new voltage smoothing factor (alpha) to be the default value.
 * @return	0 on success
 * 			-1 on failure setting new smoothing factor
 * @see DEFAULT_ALPHA_VALUE
 */
int RestoreDefaultAlpha();

/*!
 * @brief	setting the new EPS logic threshold voltages on the FRAM to the default.
 * @return	0 on success
 * 			-1 on failure setting smoothing factor
  * @see EPS_DEFAULT_THRESHOLD_VOLTAGES
 */
int RestoreDefaultThresholdVoltages();



//int CMDGetHeaterValues(sat_packet_t *cmd);
//
//int CMDSetHeaterValues(sat_packet_t *cmd);


#endif
