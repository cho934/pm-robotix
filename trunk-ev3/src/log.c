/*
 * log.c
 *
 *  Created on: Feb 25, 2014
 *      Author: maillard
 */
#include "mcontrol/global.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

static int lCount;
static char **l;
static FILE *logFile;
static int log_closed = 0;

void initLog(int leftTicksPerM, int rightTicksPerM, float encoderDist) {
	lCount = 0;
	l = (char **) calloc(1000, sizeof(char*));
	logFile = fopen("/mnt/card/log.txt", "w");
	if (logFile == NULL) {
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

void flushLog() {
	if (lCount <= 0) {
		return;
	}
	int i = 0;
	for (i = 0; i < lCount; i++) {
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
void closeLog() {
	if (log_closed == 0) {
		flushLog();
		fclose(logFile);
		log_closed = 1;
		free(l);
	}
}
void log_status(long timeInMillis, long lEndcoder, long rEncoder, int lPower,
		int rPower, int ord0, int ord1, int current0, int current1, float x,
		float y, float theta) {
	if (logFile == NULL) {
		printf("initLog error, exiting");
		exit(2);
	}
	char *str = (char *) calloc(200, sizeof(char));
	sprintf(str, "%ld,%ld,%ld,%d,%d,%d,%d,%d,%d,%f,%f,%f", timeInMillis,
			lEndcoder, rEncoder, lPower, rPower, ord0, ord1, current0, current1,
			x, y, theta);
	l[lCount] = str;
	lCount++;
	if (lCount >= 100) {
		flushLog();
	}
}
