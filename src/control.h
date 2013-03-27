/*
 * control.h
 *
 *  Created on: Mar 27, 2013
 *      Author: thomas
 */

#ifndef CONTROL_H_
#define CONTROL_H_

void moveTo(int x, int y, int speed);

void moveToPosition(int position, int speed);

void fireGun(int gunID, int duration);
void fireGuns(int duration);

void controlLaser(int LaserID, bool state);

#endif /* CONTROL_H_ */
