/*
 * log.c
 *
 *  Created on: Feb 25, 2014
 *      Author: maillard
 */

#include "log.h"

#include <stdio.h>
#include <stdlib.h>

//#include "../Logger.hpp"
//#include "../LoggerFactory.hpp"
//#include "../SvgWriter.hpp"

//#include "global.h"

static int lCount;
static char **l;
static FILE *logFile = NULL;
static int log_closed = 0;

//TODO configurer ces parametres pour les 2 robots
void initLog(int leftTicksPerM, int rightTicksPerM, float encoderDist)
{
	lCount = 0;
	l = (char **) calloc(1000 * 1000, sizeof(char*));
#ifdef SIMULATED
	logFile = fopen("log.txt", "w");
#else
	logFile = fopen("/pmx/log.txt", "w");
#endif
	if (logFile == NULL)
	{
		printf("Unable to create log file\n");
	}

	fprintf(logFile, "// encoder resolution in tick per meter \r\n");
	fprintf(logFile, "leftResolution:%d\r\n", leftTicksPerM);
	fprintf(logFile, "rightResolution:%d\r\n", rightTicksPerM);
	fprintf(logFile, "// distance between the 2 encoders in meter\r\n");
	fprintf(logFile, "encoderDistance:%f\r\n", encoderDist);
	fprintf(logFile,
			"// time (ms), left encoder (ticks), right encoder (ticks), left motor power (0-100), right motor power (0-100), order0, order1, x (mm), y (mm), theta (rad)\r\n");
}

void flushLog()
{
	if (lCount <= 0)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < lCount; i++)
	{
		char *str = l[i];
		// append to file
		fprintf(logFile, "%s\r\n", str);
		// free
		free(str);

	}
	free(l);
	//
	lCount = 0;
	l = (char **) calloc(1000, sizeof(char*));
}
void closeLog()
{
	if (log_closed == 0)
	{
		flushLog();
		fclose(logFile);
		log_closed = 1;
		free(l);
	}
}
void log_status(long timeInMillis, long lEndcoder, long rEncoder, int lPower, int rPower, int ord0, int ord1,
		int current0, int current1, float x, float y, float theta)
{

	if (logFile == NULL)
	{
		printf("initLog error, exiting");
		exit(2);
	}
	char *str = (char *) calloc(200, sizeof(char));
	sprintf(str, "%ld,%ld,%ld,%d,%d,%d,%d,%d,%d,%f,%f,%f", timeInMillis, lEndcoder, rEncoder, lPower, rPower, ord0,
			ord1, current0, current1, x, y, theta);
	//printf("log_status %s\n", str);
	l[lCount] = str;
	lCount++;
	if (lCount >= 1000)
	{
		//flushLog();
	}
}

void apf_log(long timeInMillis, long dAlpha, long dDelta, int lPower, int rPower, int ord0, int ord1, int current0,
		int current1, float x, float y, float theta)
{
	/*
	if (logs::LoggerFactory::logger("motion").isActive(logs::Level::DEBUG))
	{
		logs::LoggerFactory::logger("motion").debug() << timeInMillis <<","<< dAlpha<<","<< dDelta<<","<< lPower<<","<< rPower<<","<< ord0<<","<<
		ord1<<","<< current0<<","<< current1<<","<< x<<","<< y<<","<< theta << logs::end;
	}*/
}


void apf_svg_writePosition(float x, float y, float theta)
{
	/*
	logs::SvgWriter::writePosition((double)x *1000, (double)y *1000, (double)theta, utils::SVG_POS_GREEN);
*/
	}


