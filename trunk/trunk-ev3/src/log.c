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

int lCount;
char **l;
FILE *logFile;
void initLog(int leftTicksPerM, int rightTicksPerM, float encoderDist) {
	lCount = 0;
	l = malloc(sizeof(char*) * 1000);
	logFile = fopen("log.txt", "w");
	if (logFile == NULL) {
		printf("Unable to create log file\n");
	}

	fprintf(logFile, "// encoder resolution in tick per meter \r\n");
	fprintf(logFile, "leftResolution:%d\r\n", leftTicksPerM);
	fprintf(logFile, "rightResolution:%d\r\n", rightTicksPerM);
	fprintf(logFile, "// distance between the 2 encoders in meter\r\n");
	fprintf(logFile, "encoderDistance:%f\r\n", encoderDist);
	fprintf(logFile,
			"// time (ms), left encoder (ticks), right encoder (ticks), left motor power (1-100), right motor power (1-100), x (mm), y (mm), theta (rad)\r\n");
}

void flushLog() {
	if (lCount <= 0) {
		return;
	}
	int i;
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
	l = malloc(sizeof(char*) * 1000);
}
void closeLog() {
	flushLog();
	fclose(logFile);
}
void log_status(long timeInMillis, long lEndcoder, long rEncoder, int lPower,
		int rPower, float x, float y, float theta) {
	if (logFile == NULL) {
		printf("initLog error, exiting");
		exit(2);
	}
	char *str = malloc(sizeof(char) * 200);
	sprintf(str, "%ld,%ld,%ld,%d,%d,%f,%f,%f", timeInMillis, lEndcoder,
			rEncoder, lPower, rPower, x, y, theta);
	l[lCount] = str;
	lCount++;
	if (lCount >= 100) {
		flushLog();
	}
}
