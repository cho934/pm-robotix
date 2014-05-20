/*
 * log.h
 *
 *  Created on: Feb 25, 2014
 *      Author: maillard
 */

#ifndef LOG_H_
#define LOG_H_
void initLog(int leftTicksPerM, int rightTicksPerM, float encoderDist);
void log_status(long timeInMillis, long lEndcoder, long rEncoder, int lPower,
		int rPower, int ord0, int ord1, int current0, int current1, float x,
		float y, float theta);
void closeLog();


void apf_log(long timeInMillis, long lEndcoder, long rEncoder, int lPower,
		int rPower, int ord0, int ord1, int current0, int current1, float x,
		float y, float theta);

void apf_svg_writePosition(float x, float y, float theta);

#endif /* LOG_H_ */
