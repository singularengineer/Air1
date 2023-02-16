/*
 * Air1.c
 *
 *  Created on: Feb 14, 2023
 *      Author: SingularEngineer
 */

#include "Air1.h"

void Air1APP()
{

	HAL_GPIO_TogglePin(LED_HB_GPIO_Port, LED_HB_Pin);
	HAL_Delay(200);

}
