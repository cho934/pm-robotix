#ifndef _PID_H_
#define _PID_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

#define MAX_PID_SYSTEM_NUMBER	6	      //maximum number of pid system, must be positive
#define MAX_PWM_VALUE			100					//maximum value for pwm
#define MAX_D_PERIOD 			64	        //maximum number of period for derivation computation,
//must be between 1 and 255
#if MAX_D_PERIOD <= 1
#pragma error Max_D_Period must be greater than 1
#elif MAX_D_PERIOD > 255
#pragma error Max_D_Period must be lower than 255
#endif

//structure used to stock configuration values of the PID system
typedef struct
{
	int kP;			//proportionnal coefficient (unit = 1/vTops)
	int kI;			//integral coefficient (unit = 1/vTops/Sample)
	int kD;			//derivation coefficient (unit = Sample/vTops)

	int dPeriod;		//derivation interval, must be smaller than MAX_D_PERIOD (unit = Sample)
	int iMax;			//absolute value of the bound of sum of errors (unit = vTops)
} pidConfig;

typedef struct
{
	pidConfig conf;					//pid system configuration

	int dValues[MAX_D_PERIOD];	//all the previous values of error (used for derivation)
	long errSum;					//sum of all the errors
	int curDiff;					//current index in the dValues table
} pidSystemValues;

pidSystemValues systemValues[MAX_PID_SYSTEM_NUMBER];

//PID system are identified by a number
typedef int PID_SYSTEM;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! \brief Initialisation of the PID system
void pid_Init(void);
//! \brief Create a new PID system
//! \return The new system ID
PID_SYSTEM pid_Create(void);
//! \brief Configure the PID system
//! \param system The system that is configured
//! \param config The new configuration
void pid_Configure(PID_SYSTEM system, pidConfig config);
//! \brief Configure kP value of the PID system
void pid_ConfigKP(PID_SYSTEM system, long kp);
//! \brief Configure kI value of the PID system
void pid_ConfigKI(PID_SYSTEM system, long ki);
//! \brief Configure kD value of the PID system
void pid_ConfigKD(PID_SYSTEM system, long kd);
//! \brief Configure dPeriod value of the PID system
void pid_ConfigDPeriod(PID_SYSTEM system, int dperiod);
//! \brief Configure iMax value of the PID system
void pid_ConfigIMax(PID_SYSTEM system, long imax);
void pid_GetConfig(pidConfig &pidConfig, PID_SYSTEM system);
long pid_Compute(PID_SYSTEM system, long error);
long pid_ComputeRcva(PID_SYSTEM system, long error, long vitesse);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif //_PID_H_
