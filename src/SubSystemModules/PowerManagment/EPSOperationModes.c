#include "EPSOperationModes.h"
#include "SubSystemModules/Housekepping/payload.h"
#include "SubSystemModules/Communication/TRXVU.h"

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Full mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterFullMode(){
    is_transmition_allowed = 1;
    payload_state = 1;

    EpsState = 1;
    return 0;
}

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Cruise mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterCruiseMode(){
    is_transmition_allowed = 1;
    payload_state = 0;

    EpsState = 2;
	return 0;
}

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Safe mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterSafeMode(){
    is_transmition_allowed = 0;
    payload_state = 0;

    EpsState = 3;
    return 0;
}

int GetSystemState(){
    return EpsState;
}
