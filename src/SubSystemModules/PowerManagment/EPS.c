#include "EPS.h"

////////////////////////////////////
/// I NEED TO ADD ERROR CHECKING ///
///////////////////////////////////

int EPS_Init(void){
    // set saved values from fram
    // DOES NOT CHECK IF ITS VAILD I NEED TO DO THAT LATER
    FRAM_read((unsigned char*) &eps_mode_volts.full_mode_up_tend, EPS_FULL_MODE_UP_TEND_ADDR, 4);
    FRAM_read((unsigned char*) &eps_mode_volts.full_mode_down_tend, EPS_FULL_MODE_DOWN_TEND_ADDR, 4);

    FRAM_read((unsigned char*) &eps_mode_volts.cruise_mode_up_tend, EPS_CRUISE_MODE_UP_TEND_ADDR, 4);
    FRAM_read((unsigned char*) &eps_mode_volts.cruise_mode_down_tend, EPS_CRUISE_MODE_DOWN_TEND_ADDR, 4);

    FRAM_read((unsigned char*) &eps_mode_volts.safe_mode_up_tend, EPS_SAFE_MODE_UP_TEND_ADDR, 4);
    FRAM_read((unsigned char*) &eps_mode_volts.safe_mode_down_tend, EPS_SAFE_MODE_DOWN_TEND_ADDR, 4);
    

    // set alpha value
    FRAM_read((unsigned char*) &alpha_value, EPS_ALPHA_FILTER_VALUE_ADDR, 4);


    int rc = IMEPSV2_PIU_Init(&imeps_i2c_addr, 1);
    if(rc == 0){
    }
    else{
        logError(rc, "IMEPSV2_PIU_Init() failed");
        return 1;
    }

	return 0;
}

// https://en.wikipedia.org/wiki/Exponential_smoothing

// if this is the first time the alpha func is being ran
Boolean first_alpha_run;
#define ALPHA_SENSOR_SAMPLING_RATE 30 // the time per sec the payload sensor is ran


int EPS_Conditioning(){


	//int ret=0;
	//voltage_t t;
	//voltage_tend = getFilteredVolt(t);
	//ret = GetBatteryVoltage(&t);
	//last_voltage = t;
	//if(ret!=0)
	//{
	//	return -1;
	//}
	//if(voltage_tend==-1)
	//{
	//	if(t>=FULL_MODE_DOWN_TEND)
	//	{
	//		return EnterFullMode();
	//	}

	//	if(t>=CRUISE_MODE_DOWN_TEND)
	//	{
	//		return EnterCruiseMode();
	//	}
	//	if(t>=SAFE_MODE_DOWN_TEND)
	//	{
	//		return EnterSafeMode();
	//	}
	//	else
	//	{
	//		return EnterCriticalMode();
	//	}
	//}
	//else
	//{
	//	if(t>=FULL_MODE_UP_TEND)
	//	{
	//		return EnterFullMode();
	//	}

	//	if(t>=CRUISE_MODE_UP_TEND)
	//	{
	//		return EnterCruiseMode();
	//	}
	//	if(t>=SAFE_MODE_UP_TEND)
	//	{
	//		return EnterSafeMode();
	//	}
	//	else
	//	{
	//		return EnterCriticalMode();
	//	}
	//}
}

int UpdateThresholdVoltages(struct eps_mode_volts_t new_eps_mode_volts){
    eps_mode_volts = new_eps_mode_volts;
    return 0;
}

int UpdateAlpha(float new_alpha){
    alpha_value = new_alpha;
    return 0;
}

struct eps_mode_volts_t GetThresholdVoltages(){
    return eps_mode_volts;
}

float GetAlpha(){
    return alpha_value;
}

int EPS_save_settings(){
    // set saved values from fram
    // DOES NOT CHECK IF ITS VAILD I NEED TO DO THAT LATER
    FRAM_write((unsigned char*) &eps_mode_volts.full_mode_up_tend, EPS_FULL_MODE_UP_TEND_ADDR, 4);
    FRAM_write((unsigned char*) &eps_mode_volts.full_mode_down_tend, EPS_FULL_MODE_DOWN_TEND_ADDR, 4);

    FRAM_write((unsigned char*) &eps_mode_volts.cruise_mode_up_tend, EPS_CRUISE_MODE_UP_TEND_ADDR, 4);
    FRAM_write((unsigned char*) &eps_mode_volts.cruise_mode_down_tend, EPS_CRUISE_MODE_DOWN_TEND_ADDR, 4);

    FRAM_write((unsigned char*) &eps_mode_volts.safe_mode_up_tend, EPS_SAFE_MODE_UP_TEND_ADDR, 4);
    FRAM_write((unsigned char*) &eps_mode_volts.safe_mode_down_tend, EPS_SAFE_MODE_DOWN_TEND_ADDR, 4);
    

    // set alpha value
    FRAM_write((unsigned char*) &alpha_value, EPS_ALPHA_FILTER_VALUE_ADDR, 4);


    return 0;
};


// not this does not save this to fram to do that run "EPS_save_settings()"
int EPS_reset_settings(){
    eps_mode_volts.full_mode_up_tend = DEFFAULT_FULL_MODE_UP_TEND;
    eps_mode_volts.full_mode_down_tend = DEFFAULT_FULL_MODE_DOWN_TEND;

    eps_mode_volts.cruise_mode_up_tend = DEFFAULT_CRUISE_MODE_UP_TEND;


    eps_mode_volts.safe_mode_up_tend = DEFFAULT_SAFE_MODE_UP_TEND;
    eps_mode_volts.safe_mode_down_tend = DEFFAULT_SAFE_MODE_DOWN_TEND;

    alpha_value = DEFAULT_ALPHA_VALUE;

    return 0;
}

// not this does not save this to fram to do that run "EPS_save_settings()"
int RestoreDefaultThresholdVoltages(){
    eps_mode_volts.full_mode_up_tend = DEFFAULT_FULL_MODE_UP_TEND;
    eps_mode_volts.full_mode_down_tend = DEFFAULT_FULL_MODE_DOWN_TEND;

    eps_mode_volts.cruise_mode_up_tend = DEFFAULT_CRUISE_MODE_UP_TEND;
    eps_mode_volts.cruise_mode_down_tend = DEFFAULT_CRUISE_MODE_DOWN_TEND;

    eps_mode_volts.safe_mode_up_tend = DEFFAULT_SAFE_MODE_UP_TEND;
    eps_mode_volts.safe_mode_down_tend = DEFFAULT_SAFE_MODE_DOWN_TEND;


    return 0;
}

// not this does not save this to fram to do that run "EPS_save_settings()"
int RestoreDefaultAlpha(){
    alpha_value = DEFAULT_ALPHA_VALUE;
    return 0;
}

voltage_t GetBatteryVoltage()
{
    // i dont know how to do this with imeps
	//gom_eps_hk_t response;
	//int err = (GomEpsGetHkData_general(0,&response));
    //if(err != E_NO_SS_ERR && err != E_IS_INITIALIZED){
	//    logError(err, "failed to get battery voltage");
    //    return -1;
    //}

	//return response.fields.vbatt;
}



// i dont know what these are
//int CMDGetHeaterValues(sat_packet_t *cmd);
//
//int CMDSetHeaterValues(sat_packet_t *cmd);
