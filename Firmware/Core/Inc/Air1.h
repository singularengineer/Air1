/*
 * Air1.h
 *
 *  Created on: Feb 14, 2023
 *      Author: SingularEngineer
 */

#ifndef INC_AIR1_H_
#define INC_AIR1_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "LCD_I2C.h"
#include "SI5351.h"

#define LOOPSPEED 100

void Air1APP();
int16_t Encoder_Diff();
void UpdateFreqency();
void UpdateCursor();

#ifdef __cplusplus
}
#endif

#endif /* INC_AIR1_H_ */
