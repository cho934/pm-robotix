#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "robot.h"
#include "ccbase.h"
#include "motion.h"
#include "encoder.h"
#include "log.h"
#include "ia.h"
#include "global.h"
#include "path_manager.h"
#include "robot_unitConversion.h"
void debug(const char *str) {
#ifdef SIMULATED
	printf("DEBUG: %s\n",str);
#else
	FILE *logFile = fopen("/mnt/card/hello.txt", "w");
	fprintf(logFile, "%s", str);
	fprintf(logFile, "--\r\n");
	fclose(logFile);
#endif
}
void init(int lResolution, int rResolution, float dist, int startAsserv) {

	robot_init();

	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);

	initLog(lResolution, rResolution, dist);

	printf("Encoders resolution: %d %d , distance: %f\n", lResolution, rResolution, dist);

	if (startAsserv > 0) {
		motion_Init();
		robot_initPID();
	}
}
void test() {
	robot_init();
	robot_startMotors();

	 printf("SET SPEED TO 100\n");

	 robot_setMotorRightSpeed(10);
	 robot_setMotorLeftSpeed(10);

	 sleep(1);
	 printf("SET SPEED TO 0\n");
	 robot_setMotorRightSpeed(0);
	 robot_setMotorLeftSpeed(0);

	 printf("SLEEP STOP\n");
	 robot_stopMotorLeft();
	 robot_stopMotorRight();
	//robot_startMenu();
	robot_waitStart();
	int lRes;
	int rRes;
	float dist;

	lRes = 3800;
	rRes = 3800;
	dist = 0.128f;

	init(lRes, rRes, dist, 1);
	robot_startMotors();

	cc_moveForwardTo(0, 500);
	cc_moveForwardTo(1400, 500);
	cc_moveForwardTo(1400, 00);

}
boolean obj1() {
	cc_goToZone("zone 2");
	return TRUE;
}
boolean obj2() {
	cc_goToZone("zone 3");
	return TRUE;
}

boolean funny() {
	printf("Ca fume, c'est fun");
	return TRUE;
}
void testIA() {
	ia_createZone("zone 1", 0, 0, 100, 100, 50, 50, 45);
	ia_createZone("zone 2", 1000, 1000, 100, 100, 50, 50, 0);
	ia_createZone("zone 3", 2000, 0, 100, 100, 50, 50, 90);

	ia_setPath("zone 1", "zone 2", 600, 600);
	ia_setPath("zone 1", "zone 3", 700, 600);
	ia_setPath("zone 2", "zone 3", 800, 600);

	ia_addAction("objectif 1", &obj1);
	ia_addAction("objectif 2", &obj2);

	ia_setEndAction("funny action", &funny, 90);
	ia_start();
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
		printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		printf("Counters from start : left: %ld  right: %ld\n", robot_getLeftExternalCounter() - lStart,
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
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
			robot_getRightExternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n", lStart - robot_getLeftExternalCounter(),
			rStart - robot_getRightExternalCounter());

	robot_dispose();
	printf("END\n");

}

void testLeftExternalCounters(int seconds, int enableMotors) {

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

			robot_setMotorLeftSpeed(speed);
			if (speed < 100 && i % 20) {
				speed++;
			}
		}
		printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		printf("Counters from start : left: %ld  right: %ld\n", robot_getLeftExternalCounter() - lStart,
				robot_getRightExternalCounter() - rStart);
		usleep(1000 * 1000);
	}
	if (enableMotors > 0) {
		printf("Motors stopped\n");

		robot_setMotorLeftSpeed(0);
	}
	printf("Waiting 1s\n");
	sleep(1);
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
			robot_getRightExternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n", lStart - robot_getLeftExternalCounter(),
			rStart - robot_getRightExternalCounter());

	robot_dispose();
	printf("END\n");

}
void testRightExternalCounters(int seconds, int enableMotors) {

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
			if (speed < 100 && i % 20) {
				speed++;
			}
		}
		printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		printf("Counters from start : left: %ld  right: %ld\n", robot_getLeftExternalCounter() - lStart,
				robot_getRightExternalCounter() - rStart);
		usleep(1000 * 1000);
	}
	if (enableMotors > 0) {
		printf("Motors stopped\n");

		robot_setMotorRightSpeed(0);
	}
	printf("Waiting 1s\n");
	sleep(1);
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftExternalCounter(),
			robot_getRightExternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n", lStart - robot_getLeftExternalCounter(),
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
		printf("Current power: %d , counters: left: %ld right: %ld\n", speed, robotGetLeftInternalCounter,
				robotGetRightInternalCounter);
		printf("Counters from start : left: %ld  right: %ld  Delta: %ld %ld -> %ld\n",
				robotGetLeftInternalCounter - lStart, robotGetRightInternalCounter - rStart,
				robotGetLeftInternalCounter - lP, robotGetRightInternalCounter - rP,
				(robotGetLeftInternalCounter - lP) - (robotGetRightInternalCounter - rP));
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
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed, robot_getLeftInternalCounter(),
			robot_getRightInternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n", lStart - robot_getLeftInternalCounter(),
			rStart - robot_getRightInternalCounter());

	robot_dispose();
	printf("END\n");

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
		printf("testInit : left: %ld right: %ld \n", robot_getLeftExternalCounter(), robot_getRightExternalCounter());
		sleep(1);
	}
}

void mainProgram() {

	int lRes = 3800;
	int rRes = 3800;
	float dist = 0.128f;
	init(lRes, rRes, dist, 0);

	printf("START: (%f,%f) %f\n", cc_getX(), cc_getY(), cc_getThetaInDegree());

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
		test();
	}
	if (argc > 1) {
		printf("Utilisation : EV3 commande parametre\n");
		printf("Examples:\n");
		printf("- rotation sur la gauche de 90 degres :        EV3 rotate 90\n");
		printf("- cc_rotateLeft de 90 degres          :        EV3 cc_rotateLeft 90\n");
		printf("- avance de 500mm en ligne droite :            EV3 line  500\n");
		printf("- avance à x,y :100mm, 500mm                   EV3 goto  100 500\n");
		printf("- mise à 100 des moteurs pendant 5s :          EV3 test0 null\n");
		printf("- affiche les codeurs externes 30s :           EV3 test1  30\n");
		printf("- avance et affiche les codeurs externes 5s :  EV3 test2   5\n");
		printf("- avance et affiche les codeurs internes 5s :  EV3 test3   5\n");
		printf("- avance gauche et affiche les cod. ext. 5s :  EV3 testL   5\n");
		printf("- avance droite et affiche les cod. ext. 5s :  EV3 testR   5\n");
		printf("- reglage PID : tourne sur 90 degres :         EV3 pidA 90\n");
		printf("- reglage PID : avance   sur 300mm :           EV3 pidD 300\n");
		printf("- test de l'attente de départ 1 fois :         EV3 waitstart 1\n");
		printf("- test de l'arret d'urgence 20s :              EV3 emergency 20s\n");
		printf("- test de la detection 5s :                    EV3 test_detect 5\n");
		printf("- fait carré de 500mm :                        EV3 square 500\n");
		printf("- test ia :                                    EV3 testIA 0\n");

	}
	if (strcmp(argv[1], "test0") == 0) {
		test();
	} else {
		int lRes;
		int rRes;
		float dist;
		if (useExternalEncoders) {
			lRes = 3800;
			rRes = 3800;
			dist = 0.128f;
		} else {
			lRes = 1440;
			rRes = 1440;
			dist = 0.154;

		}

		if (strcmp(argv[1], "line") == 0) {
			init(lRes, rRes, dist, 1);
			int mm = atoi(argv[2]);
			motionLine(mm);
		} else if (strcmp(argv[1], "rotate") == 0) {
			init(lRes, rRes, dist, 1);
			int degres = atoi(argv[2]);
			motionRotate(degres);
		} else if (strcmp(argv[1], "cc_rotateLeft") == 0) {
			init(lRes, rRes, dist, 1);
			int degres = atoi(argv[2]);
			cc_rotateLeft(degres);
		} else if (strcmp(argv[1], "goto") == 0) {
			init(lRes, rRes, dist, 1);
			int x = atoi(argv[2]);
			int y = atoi(argv[3]);
			printf("cc_moveForwardTo %d %d\n", x, y);
			printf("START: (%f,%f) %f\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
			cc_moveForwardTo(x, y);
			printf("STOP: (%f,%f) %f\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
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
		} else if (strcmp(argv[1], "testL") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testLeftExternalCounters(secs, 1);
		} else if (strcmp(argv[1], "testR") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testRightExternalCounters(secs, 1);
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
		} else if (strcmp(argv[1], "pidA") == 0) {
			int degrees = atoi(argv[2]);
			init(lRes, rRes, dist, 1);
			RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
			float radians = (degrees * M_PI) / 180.0f;
			motion_StepOrderAD(cmd, convertDistTovTops(radians * distEncoderMeter / 2.0f), 0.0f, 5);
			launchAndEndAfterCmd(cmd);
		} else if (strcmp(argv[1], "pidD") == 0) {
			int mm = atoi(argv[2]);
			init(lRes, rRes, dist, 1);
			RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
			float meters = mm / 1000.0f;
			motion_StepOrderAD(cmd, 0.0f, meters / valueVTops, 5);

			launchAndEndAfterCmd(cmd);
		} else if (strcmp(argv[1], "square") == 0) {
			int mm = atoi(argv[2]);
			init(lRes, rRes, dist, 1);
			cc_moveForwardTo(mm, 0);
			cc_moveForwardTo(mm, mm);
			cc_moveForwardTo(0, mm);
			cc_moveForwardAndRotateTo(0, 0, 0);
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
		} else if (strcmp(argv[1], "testIA") == 0) {
			init(lRes, rRes, dist, 1);
			testIA();
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
	printf("End at : (%f,%f) %f\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
	printf("Bye\n");
	closeLog();
	return 0;
}
