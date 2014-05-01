#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "robot.h"

#include "mcontrol/motion.h"
#include "mcontrol/encoder.h"
#include "log.h"
#include "mcontrol/global.h"
#include "mcontrol/path_manager.h"

void debug(const char *str) {
	FILE *logFile = fopen("/mnt/card/hello.txt", "w");
	fprintf(logFile,"%s", str);
	fprintf(logFile, "--\r\n");
	fclose(logFile);
}

void test() {

	robot_startMotors();

	printf("SET SPEED TO 100\n");

	robot_setMotorRightSpeed(100);
	robot_setMotorLeftSpeed(100);

	sleep(5);
	printf("SET SPEED TO 0\n");
	robot_setMotorRightSpeed(0);
	robot_setMotorLeftSpeed(0);

	sleep(5);
	printf("SLEEP STOP\n");
	robot_stopMotorLeft();
	robot_stopMotorRight();
	robot_dispose();

	sleep(2);

}

void testExternalCounters(int seconds, int enableMotors) {

	robot_init();
	if (enableMotors > 0) {
		robot_startMotors();
	}
	int speed = 20;
	//PROCESS SENSOR DATA
	long lStart = robot_getLeftExternalCounter();
	long rStart = robot_getRightExternalCounter();

	// Boucle principale
	int i;
	for (i = 0; i < seconds; i++) {
		if (enableMotors > 0) {
			// Update la vitesse
			robot_setMotorRightSpeed(speed);
			robot_setMotorLeftSpeed(speed);
			if (speed < 100 && i % 20) {
				speed++;
			}
		}
		printf("Current speed: %d , counters: left: %ld right: %ld\n", speed,
				robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		printf("Counters from start : left: %ld  right: %ld\n",
				robot_getLeftExternalCounter() - lStart,
				robot_getRightExternalCounter() - rStart);
		usleep(1000 * 1000);
	}
	if (enableMotors > 0) {
		printf("Motors stopped\n");
		robot_setMotorRightSpeed(0);
		robot_setMotorLeftSpeed(0);
	}
	printf("Waiting 1s\n");
	sleep(1);
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed,
			robot_getLeftExternalCounter(), robot_getRightExternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n",
			lStart - robot_getLeftExternalCounter(),
			rStart - robot_getRightExternalCounter());

	robot_dispose();
	printf("END\n");

}
void testInternalCounters(int seconds, int enableMotors) {

	if (enableMotors > 0) {
		robot_startMotors();
	}
	int speed = 0;
	//PROCESS SENSOR DATA
	long lStart = robot_getLeftInternalCounter();
	long rStart = robot_getRightInternalCounter();
	long lP = lStart;
	long rP = rStart;
	// Boucle principale
	int i;
	for (i = 0; i < seconds; i++) {
		if (enableMotors > 0) {
			// Update la vitesse
			robot_setMotorRightSpeed(speed);
			robot_setMotorLeftSpeed(speed);
			if (speed < 100 && i % 20) {
				speed++;
			}
		}
		long robotGetLeftInternalCounter = robot_getLeftInternalCounter();
		long robotGetRightInternalCounter = robot_getRightInternalCounter();
		printf("Current power: %d , counters: left: %ld right: %ld\n", speed,
				robotGetLeftInternalCounter, robotGetRightInternalCounter);
		printf(
				"Counters from start : left: %ld  right: %ld  Delta: %ld %ld -> %ld\n",
				robotGetLeftInternalCounter - lStart,
				robotGetRightInternalCounter - rStart,
				robotGetLeftInternalCounter - lP,
				robotGetRightInternalCounter - rP,
				(robotGetLeftInternalCounter - lP)
						- (robotGetRightInternalCounter - rP));
		usleep(1000 * 1000);
		lP = robotGetLeftInternalCounter;
		rP = robotGetRightInternalCounter;
	}
	if (enableMotors > 0) {
		printf("Motors stopped\n");
		robot_setMotorRightSpeed(0);
		robot_setMotorLeftSpeed(0);
	}
	printf("Waiting 1s\n");
	sleep(1);
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed,
			robot_getLeftInternalCounter(), robot_getRightInternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n",
			lStart - robot_getLeftInternalCounter(),
			rStart - robot_getRightInternalCounter());

	robot_dispose();
	printf("END\n");

}
void init(int lResolution, int rResolution, float dist, int startAsserv) {
	debug("b");
	robot_init();
	debug("c");
	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);
	debug("d");
	initLog(lResolution, rResolution, dist);
	debug("e");
	printf("Encoders resolution: %d %d , distance: %f\n", lResolution,
			rResolution, dist);
	debug("f");
	if (startAsserv > 0) {
		motion_Init();
	}
}

void launchAndEndAfterCmd(RobotCommand* cmd) {
	printf("Check cmd\n");
	checkRobotCommand(cmd);

	path_LaunchTrajectory(cmd);
	printf("path_WaitEndOfTrajectory\n");
	int result = path_WaitEndOfTrajectory();

	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result, TRAJ_OK);

	robot_setMotorLeftSpeed(0);
	robot_setMotorRightSpeed(0);
	free(cmd);
	closeLog();

}

void motionLine(int mm) {
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_Line(cmd, meters);
	printf("Loading line command for %d mm (%f meters)\n", mm, meters);
	launchAndEndAfterCmd(cmd);

}

void motionRotate(int degres) {
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float rad = (degres * M_PI) / 180.0;
	// 90 cms
	motion_Rotate(cmd, rad);
	printf("Loading rotate command %d degres (%f rad)\n", degres, rad);
	launchAndEndAfterCmd(cmd);
}

void testEncoders() {
	robot_init();
	int i;
	printf("Reading encoder during 20s\n");
	for (i = 0; i < 20; i++) {
		printf("testInit : left: %ld right: %ld \n",
				robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		sleep(1);
	}
}

void mainProgram() {
	debug("a");

	int lRes = 3800;
	int rRes = 3800;
	float dist = 0.128f;
	init(lRes, rRes, dist, 0);

	robot_startMotors();

	printf("SET SPEED TO 20\n");

	robot_setMotorRightSpeed(20);
	robot_setMotorLeftSpeed(20);

	sleep(1);
	robot_setMotorRightSpeed(-40);
	robot_setMotorLeftSpeed(-40);
	sleep(1);

	printf("SET SPEED TO 0\n");
	robot_setMotorRightSpeed(0);
	robot_setMotorLeftSpeed(0);
	sleep(1);

	robot_stopMotorLeft();
	robot_stopMotorRight();
	robot_dispose();

}

int main(int argc, const char* argv[]) {
#ifdef SIMULATED
	printf("Simulation mode enabled\n");
#endif

	// Prints each argument on the command line.
	int i;
	for (i = 0; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}
	if (argc == 1) {
		mainProgram();
	}
	if (argc != 3) {
		printf("Utilisation : EV3 commande parametre\n");
		printf("Examples:\n");
		printf(
				"- rotation sur la droite de 90 degres :        EV3 rotate 90\n");
		printf(
				"- avance de 500mm en ligne droite :            EV3 line  500\n");
		printf(
				"- mise à 100 des moteurs pendant 5s :          EV3 test0 null\n");
		printf(
				"- affiche les codeurs externes 30s :           EV3 test1  30\n");
		printf(
				"- avance et affiche les codeurs externes 5s :  EV3 test2   5\n");
		printf(
				"- avance et affiche les codeurs internes 5s :  EV3 test3   5\n");
		printf(
				"- avance pour reglage PID sur 300mm :          EV3 pidAD 300\n");
		printf(
				"- test de l'attente de départ 1 fois :         EV3 waitstart 1\n");
		printf(
				"- test de l'arret d'urgence 20s :              EV3 emergency 20s\n");
		printf(
				"- test de la detection 5s :                    EV3 test_detect 5\n");
		return 0;
	}
	if (strcmp(argv[1], "test0") == 0) {
		test();
	} else {
		int lRes = 3800;
		int rRes = 3800;
		float dist = 0.128f;

		if (strcmp(argv[1], "line") == 0) {
			init(lRes, rRes, dist, 1);
			int mm = atoi(argv[2]);
			motionLine(mm);
		} else if (strcmp(argv[1], "rotate") == 0) {
			init(lRes, rRes, dist, 1);
			int degres = atoi(argv[2]);
			motionRotate(degres);
		} else if (strcmp(argv[1], "test0") == 0) {
			init(lRes, rRes, dist, 0);
			test();
		} else if (strcmp(argv[1], "test1") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testExternalCounters(secs, 0);
		} else if (strcmp(argv[1], "test2") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testExternalCounters(secs, 1);
		} else if (strcmp(argv[1], "test3") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testInternalCounters(secs, 1);
		} else if (strcmp(argv[1], "test_detect") == 0) {
			int nb = atoi(argv[2]);
			init(lRes, rRes, dist, 0);
			//int secs = atoi(argv[2]);
			//testInternalCounters(secs, 1);
			int i = 0;
			for (i = 0; i < nb; i++) {
				printf("detect at :%d\n", robot_isDetectingObstacle());
				sleep(1);
			}
		} else if (strcmp(argv[1], "pidAD") == 0) {
			int mm = atoi(argv[2]);
			init(lRes, rRes, dist, 1);
			RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
			float meters = mm / 1000.0f;
			motion_StepOrderAD(cmd, 0.0f, meters / valueVTops, 5);
			launchAndEndAfterCmd(cmd);
		} else if (strcmp(argv[1], "waitstart") == 0) {
			init(lRes, rRes, dist, 0);
			printf("Waiting for start signal\n");
			robot_waitStart();
			printf("Robot started\n");
		} else if (strcmp(argv[1], "emergency") == 0) {
			printf("Waiting for emergency signal\n");
			while (robot_isRunning() > 0) {
				usleep(100);
			}
			printf("Emergency detected\n");
		} else {
			printf("Commande %s inconnue\n", argv[1]);
		}
	}

//testEncoders();
//test();
//testExternalCounters();
//test_motor_encoder();
//calibrate();
//testMotionLine();
//testMotionRotate90();
//motion_DoRotate(M_PI*1.0f);
	printf("Bye\n");
	return 0;
}
