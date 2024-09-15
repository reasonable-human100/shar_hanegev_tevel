#include "EPSOperationModes.h"
#include "SubSystemModules/Communication/TRXVU.h"

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Full mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterFullMode(){
    UnMuteTRXVU(); // unmute TRXVU if its muted
	return 0;
}

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Cruise mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterCruiseMode(){
    muteTRXVU(600); // mute for 10 min
	return 0;
}

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Safe mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterSafeMode(){
    muteTRXVU(600); // mute for 10 min
	return 0;
}

/*!
 * @brief Executes the necessary procedure in order to initiate the system into Critical mode
 * @return	0 on success
 * 			errors according to <hal/errors.h>
 */
int EnterCriticalMode(){
    muteTRXVU(600); // mute for 10 min
	return 0;
}
