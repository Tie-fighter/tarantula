/*
 * vision.h
 *
 *  Created on: Mar 27, 2013
 *      Author: thomas
 */

#ifndef VISION_H_
#define VISION_H_


void processFrame(int position, std::vector backgrounds, Mat frame);

void getTargets (int minSize);


#endif /* VISION_H_ */
