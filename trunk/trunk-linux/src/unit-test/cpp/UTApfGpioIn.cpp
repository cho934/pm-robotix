/*!
 * \file
 * \brief Implémentation de la classe ApfInModeTest, Test d'une entrée par interruption "blocking read" de la carte DevLightV2.
 *
 */

#include <cstring>
#include "UTApfGpioIn.hpp"

//pour la partie V1
#include <iostream>
#include <fstream>

//pour la partie V2

extern "C"
{

#include <as_devices/as_gpio.h>

//pour la partie V3
#include <sys/ioctl.h>
#include <linux/ppdev.h>
}

#include "../../common/cpp/Chronometer.hpp"

#define GPIORDDIRECTION	_IOR(PP_IOCTL, 0xF0, int)
#define GPIOWRDIRECTION	_IOW(PP_IOCTL, 0xF1, int)
#define GPIORDDATA	_IOR(PP_IOCTL, 0xF2, int)
#define GPIOWRDATA	_IOW(PP_IOCTL, 0xF3, int)
#define GPIORDMODE	_IOR(PP_IOCTL, 0xF4, int)
#define GPIOWRMODE	_IOW(PP_IOCTL, 0xF5, int)

std::string test::UTApfGpioIn::INPUT_PORT_PATH_DEV = "/dev/gpio/P"; // écriture (write) et lecture (read) blocante sur pin
std::string test::UTApfGpioIn::INPUT_PORT_PATH_PROC =
		"/proc/driver/gpio/port"; //lecture port/dir/irq : cat /proc/driver/gpio/portD

void test::UTApfGpioIn::run(int argc, char *argv[])
{

	// The gpio port (A, B, C or D)
	std::string inGpioPort;
	std::string inPin;
	std::string inProg;

	std::cout
			<< "APF : Test de different mode de -Read- et -Blocking Read- via GPIO."
			<< std::endl;

	if (argc < 4)
	{
		std::cout << "USAGE: UNIT_TEST " << argv[1]
				<< " [GPIO_PORT:A B C D] [GPIO_PIN:0...31] [V1...4]"
				<< std::endl;
	}
	if (argc > 2)
	{
		inGpioPort = argv[2];
	}
	else
	{
		//demande du port
		std::cout << "[IN_GPIO_PORT:A B C D] : " << std::flush;
		std::cin >> inGpioPort;
	}
	if (argc > 3)
	{
		inPin = argv[3];
	}
	else
	{
		//demande de la pin
		std::cout << "[IN_PIN:0->31]: " << std::flush;
		std::cin >> inPin;
	}

	if (argc > 4)
	{
		inProg = argv[4];
	}
	else
	{
		//demande de la pin
		std::cout << "[V1 V2 V3 V4]: " << std::flush;
		std::cin >> inProg;
	}

	if (inProg == "V1")
	{
		//mode read (lecture blocante + lecture portD par fstream /proc/driver/gpio
		in_V1_blockingReadFstream(inGpioPort, inPin);
	}
	else if (inProg == "V2")
	{
		//mode read (lecture blocante + lecture portD par accès direct /proc/driver/gpio
		in_V2_blockingread(inGpioPort, inPin);
	}
	else if (inProg == "V3")
	{
		//mode lecture blocante like as_devices (utilise select/epoll)
		in_V3_ioctl_for_pin(inGpioPort, inPin);
	}
	else if (inProg == "V4")
	{
		//mode lecture non blocante like as_devices
		in_V4_ioctl_for_port(inGpioPort, inPin);
	}
}

/*
 * \ brief Compte les fronts (sans blocking-read) par ioctl sur le port entier.
 *
 * Résultat : moteur à pleine vitesse :
 * test::ApfInTest2 INFO  nbi: 676 ;nbtest: 847 ;time-us:2968627 ;diff-time-us:4436 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 677 ;nbtest: 849 ;time-us:2973191 ;diff-time-us:4564 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 678 ;nbtest: 822 ;time-us:2977555 ;diff-time-us:4364 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 679 ;nbtest: 812 ;time-us:2981987 ;diff-time-us:4432 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 680 ;nbtest: 833 ;time-us:2986393 ;diff-time-us:4406 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 681 ;nbtest: 830 ;time-us:2990898 ;diff-time-us:4505 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 682 ;nbtest: 844 ;time-us:2995360 ;diff-time-us:4462 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 683 ;nbtest: 799 ;time-us:2999734 ;diff-time-us:4374 ;pin=1 0 ;DephG:1 ;DephD:0
 test::ApfInTest2 INFO  nbi: 684 ;nbtest: 811 ;time-us:3004041 ;diff-time-us:4307 ;pin=1 0 ;DephG:1 ;DephD:0
 * Conclusion :
 * ->fonctionne correctement avec logggerInitialize utilisant uniquement MemoryAppender.
 * ->le système moins chargé que la v3  car 800 tests sont possibles entre 2 fronts.
 *
 */
void test::UTApfGpioIn::in_V4_ioctl_for_port(std::string, std::string)
{

	logger().info() << "V4 - compte les fronts (sans blocking-read) par ioctl "
			<< utils::end;
	int fdport, ret, nbtest = 0, nbi = 0, temp;
	bool i = false, lasti = false;
	bool dephG = false;
	bool dephD = false;
	long portval;
	const char * filePort = "/dev/gpio/portD";

	logger().info() << "Opening " << filePort << utils::end;
	if ((fdport = open(filePort, O_RDONLY)) < 0)
	{
		logger().info() << "Error :  " << filePort << utils::end;
		perror("Error");
		exit(1);
	}

	utils::Chronometer chrono;
	chrono.start();
	long now = chrono.getElapsedTimeInMicroSec();
	long last = chrono.getElapsedTimeInMicroSec();

	long start = now;
	logger().debug() << "while" << utils::end;
	while (now < start + 3000000)
	{
		ret = ioctl(fdport, GPIORDDATA, &portval); // irq doit être configuré en front montant
		if (ret < 0)
		{
			printf("Can't read gpio data\n");
		}

		/*
		 //todo passer les paramètres qui vont bien et ajouter le time en paramètre
		 //codeur gauche
		 temp = (portval >> 24) & 0x03;//garde que le 24 et le 25
		 i = temp & 0x01;
		 dephG = (temp >> 1) & 0x01;
		 */

		//codeur droit
		temp = (portval >> 19); //garde que le 24 et le 25
		i = temp & 0x01;
		dephD = (temp >> 7) & 0x01;

		if (i != lasti) //front montant et descendant
		{
			if (i > lasti) //front montant
			{
				now = chrono.getElapsedTimeInMicroSec();
				logger().info() << " nbi: " << nbi << " ;nbtest: " << nbtest
						<< " ;time-us:" << now << " ;diff-time-us:"
						<< now - last << " ;pin=" << i << " " << lasti
						<< " ;DephG:" << dephG << " ;DephD:" << dephD
						<< utils::end;
				last = now;
				nbi++;
				nbtest = 0;
			}
			lasti = i;
		}
		nbtest++;
	}
	close(fdport);
}

/*!
 * \brief V3 : Compte les fronts d'un codeur (sans blocking-read) par ioctl sur un pin
 * et affiche les déphasages gauche et droit (sens de marche).
 *
 * Résultat : moteur à pleine vitesse :
 * test::ApfInTest2 INFO  nbi: 684 ;nbtest: 266 ;time-us:2957639 ;diff-time-us:4346 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 685 ;nbtest: 272 ;time-us:2961993 ;diff-time-us:4354 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 686 ;nbtest: 258 ;time-us:2966231 ;diff-time-us:4238 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 687 ;nbtest: 269 ;time-us:2970547 ;diff-time-us:4316 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 688 ;nbtest: 270 ;time-us:2974944 ;diff-time-us:4397 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 689 ;nbtest: 267 ;time-us:2979232 ;diff-time-us:4288 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 690 ;nbtest: 265 ;time-us:2983415 ;diff-time-us:4183 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 691 ;nbtest: 259 ;time-us:2987667 ;diff-time-us:4252 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 692 ;nbtest: 276 ;time-us:2992075 ;diff-time-us:4408 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 693 ;nbtest: 278 ;time-us:2996578 ;diff-time-us:4503 ;pin=1 0 ;DephG:1 ;DephD:1
 * test::ApfInTest2 INFO  nbi: 694 ;nbtest: 273 ;time-us:3000949 ;diff-time-us:4371 ;pin=1 0 ;DephG:1 ;DephD:1
 * conclusion : 
 * ->fonctionne correctement avec logggerInitialize utilisant uniquement MemoryAppender.
 * ->le système est chargé car uniquement 260 tests sont possibles entre 2 fronts.
 */

void test::UTApfGpioIn::in_V3_ioctl_for_pin(std::string inGpioPort,
		std::string inPin)
{
	//code basé sur le target/demos/gpio/blink_led.c
	//http://armadeus.git.sourceforge.net/git/gitweb.cgi?p=armadeus/armadeus;a=blob_plain;f=target/demos/gpio/blink_led.c;hb=HEAD

	logger().info() << "V3 - compte les fronts (sans blocking-read) par ioctl "
			<< utils::end;

	int fdpin, ret, i = 0, nbtest = 0, lasti = 0, nbi = 0, portval;
	int fdpindephG, fdpindephD;
	int valdephG, valdephD;

	std::string LED_GPIO_PATH = "/dev/gpio/P";
	std::string filePort;
	filePort = LED_GPIO_PATH + inGpioPort + inPin;

	std::string pd25 = "/dev/gpio/PD25";
	std::string pd26 = "/dev/gpio/PD26";

	logger().info() << "Opening " << filePort << utils::end;
	if ((fdpin = open(filePort.c_str(), O_RDONLY)) < 0)
	{
		logger().info() << "Error :  " << filePort << utils::end;
		perror("Error");
		exit(1);
	}
	if ((fdpindephG = open(pd25.c_str(), O_RDONLY)) < 0)
	{
		logger().info() << "Error :  " << "/dev/gpio/PD25" << utils::end;
		perror("Error");
		exit(1);
	}
	if ((fdpindephD = open(pd26.c_str(), O_RDONLY)) < 0)
	{
		logger().info() << "Error :  " << "/dev/gpio/PD26" << utils::end;
		perror("Error");
		exit(1);
	}
	logger().info()
			<< "WARNING : Are you sure the pin mode/dir/irq are configured ?"
			<< utils::end;

	utils::Chronometer chrono;
	chrono.start();
	long now = chrono.getElapsedTimeInMicroSec();
	long last = chrono.getElapsedTimeInMicroSec();

	long start = now;
	logger().debug() << "while" << utils::end;
	while (now < start + 3000000)
	{
		ret = ioctl(fdpin, GPIORDDATA, &portval); // irq doit être configuré en front montant
		if (ret < 0)
		{
			printf("Can't read gpio data\n");
		}
		if (portval != 0)
		{
			i = 1;
		}
		else
		{
			i = 0;
		}

		ioctl(fdpindephG, GPIORDDATA, &valdephG);
		if (valdephG != 0)
		{
			valdephG = 1;
		}
		else
		{
			valdephG = 0;
		}

		ioctl(fdpindephD, GPIORDDATA, &valdephD);
		if (valdephD != 0)
		{
			valdephD = 1;
		}
		else
		{
			valdephD = 0;
		}

		if (i != lasti) //front montant et descendant
		{
			if (i > lasti) //front montant
			{
				now = chrono.getElapsedTimeInMicroSec();
				logger().info() << " nbi: " << nbi << " ;nbtest: " << nbtest
						<< " ;time-us:" << now << " ;diff-time-us:"
						<< now - last << " ;pin=" << i << " " << lasti
						<< " ;DephG:" << valdephG << " ;DephD:" << valdephD
						<< utils::end;
				last = now;
				nbi++;
				nbtest = 0;
			}
			lasti = i;
		}
		nbtest++;
	}
	close(fdpin);
}

/*!
 * \brief V2 : Utilise le module as_devices.
 *
 * Resultat : moteur à pleine vitesse : sans blocking read (logggerInitialize with MemoryAppender) :
 *
 * test::ApfInTest2 INFO Read:3335 ;time:1988182 600 pin=1
 test::ApfInTest2 INFO Read:3336 ;time:1988754 572 pin=1
 test::ApfInTest2 INFO Read:3337 ;time:1989322 568 pin=0
 test::ApfInTest2 INFO Read:3338 ;time:1989888 566 pin=0
 test::ApfInTest2 INFO Read:3339 ;time:1990457 569 pin=0
 test::ApfInTest2 INFO Read:3340 ;time:1991090 633 pin=1
 test::ApfInTest2 INFO Read:3341 ;time:1991669 579 pin=1
 test::ApfInTest2 INFO Read:3342 ;time:1992244 575 pin=1
 test::ApfInTest2 INFO Read:3343 ;time:1992814 570 pin=1
 test::ApfInTest2 INFO Read:3344 ;time:1993380 566 pin=0
 test::ApfInTest2 INFO Read:3345 ;time:1993951 571 pin=0
 test::ApfInTest2 INFO Read:3346 ;time:1994525 574 pin=0
 test::ApfInTest2 INFO Read:3347 ;time:1995097 572 pin=0
 test::ApfInTest2 INFO Read:3348 ;time:1995731 634 pin=1
 test::ApfInTest2 INFO Read:3349 ;time:1996462 731 pin=1
 test::ApfInTest2 INFO Read:3350 ;time:1997087 625 pin=1
 test::ApfInTest2 INFO Read:3351 ;time:1997667 580 pin=0
 test::ApfInTest2 INFO Read:3352 ;time:1998236 569 pin=0
 test::ApfInTest2 INFO Read:3353 ;time:1998801 565 pin=0
 test::ApfInTest2 INFO Read:3354 ;time:1999370 569 pin=0
 test::ApfInTest2 INFO Read:3355 ;time:1999993 623 pin=1
 test::ApfInTest2 INFO Read:3356 ;time:2000580 587 pin=1
 *
 *
 * avec blocking read : (fonctionne correctement avec logggerInitialize utilisant uniquement MemoryAppender).
 * conclusion : 700 fronts montants en 3s toutes les 4200us !
 * le mode GPIO_IRQ_MODE_BOTH ne fonctionne pas !
 *
 * test::ApfInTest2 INFO Read:686 ;time-us:2945369 ;diff-time-us:4214 ;pin=0
 test::ApfInTest2 INFO Read:687 ;time-us:2949623 ;diff-time-us:4254 ;pin=0
 test::ApfInTest2 INFO Read:688 ;time-us:2953960 ;diff-time-us:4337 ;pin=0
 test::ApfInTest2 INFO Read:689 ;time-us:2958170 ;diff-time-us:4210 ;pin=0
 test::ApfInTest2 INFO Read:690 ;time-us:2962386 ;diff-time-us:4216 ;pin=0
 test::ApfInTest2 INFO Read:691 ;time-us:2966713 ;diff-time-us:4327 ;pin=0
 test::ApfInTest2 INFO Read:692 ;time-us:2971152 ;diff-time-us:4439 ;pin=0
 test::ApfInTest2 INFO Read:693 ;time-us:2975462 ;diff-time-us:4310 ;pin=0
 test::ApfInTest2 INFO Read:694 ;time-us:2979504 ;diff-time-us:4042 ;pin=0
 test::ApfInTest2 INFO Read:695 ;time-us:2983694 ;diff-time-us:4190 ;pin=0
 test::ApfInTest2 INFO Read:696 ;time-us:2988010 ;diff-time-us:4316 ;pin=0
 test::ApfInTest2 INFO Read:697 ;time-us:2992400 ;diff-time-us:4390 ;pin=0
 test::ApfInTest2 INFO Read:698 ;time-us:2996592 ;diff-time-us:4192 ;pin=0
 test::ApfInTest2 INFO Read:699 ;time-us:3000815 ;diff-time-us:4223 ;pin=0
 * 
 */
void test::UTApfGpioIn::in_V2_blockingread(std::string inGpioPort,
		std::string inPin)
{
	logger().info()
			<< "V2 - Blocking-read with as_devices : as_gpio_blocking_get_pin_value() "
			<< utils::end;
	int i = 0;
	utils::Chronometer chrono;
	chrono.start();
	long now = chrono.getElapsedTimeInMicroSec();
	long last = chrono.getElapsedTimeInMicroSec();

	int ret = 0, pinDephG = 0, pinDephD = 0;
	struct as_gpio_device *pd24, *pd25, *pd26;

	char test;
	strcpy(&test, inGpioPort.c_str());
	pd24 = as_gpio_open(test, atoi(inPin.c_str()));
	pd25 = as_gpio_open(test, 25);
	pd26 = as_gpio_open(test, 26);

	logger().info()
			<< "WARNING : Are you sure the pin mode/dir/irq are configured ?"
			<< utils::end;
	//as_gpio_set_pin_direction(pd24, 0);
	//as_gpio_set_irq_mode(pd24, GPIO_IRQ_MODE_RISING);
	//as_gpio_set_irq_mode(pd26, GPIO_IRQ_MODE_RISING);

	long start = now;
	logger().info() << "while" << utils::end;

	while (now < start + 3000000) //sur 3 secondes, doit obtenir 710 imp, moteurs à fond
	{

		//recupere la valeur
		//pinValue = as_gpio_get_pin_value(pd24);//pas de blockisans blocking-readng
		ret = as_gpio_blocking_get_pin_value(pd24, 0, 10000); //attente de 10000us sur codeur gauche
		if (ret != -10) //si different de timeout
		{
			i++;

			//lecture des dephasages gauche
			pinDephG = as_gpio_get_pin_value(pd25);
			pinDephD = as_gpio_get_pin_value(pd26);

			now = chrono.getElapsedTimeInMicroSec();
			logger().info() << "Read:" << i << " ;time-us:" << now
					<< " ;diff-time-us:" << now - last << " ;DephG:" << pinDephG
					<< " ;DephD:" << pinDephD << utils::end;
			last = now;
		}
	}
	as_gpio_close(pd24);
	logger().info() << "end" << utils::end;

}

/*!
 * \brief V1 : Affiche le port D de l'APF9328 et compte les impulsions d'un codeur, 
 * et affiche les déphasages gauche et droit (sens de marche)..
 * avec blocking read et fstream (/dev/gpio/PortD).
 *
 * Fonctionne.
 *
 * Resultat :
 * test::ApfInTest2 INFO     11100111000011000000000001000000 - IMPGD:1 - IMPDD:1
 test::ApfInTest2 INFO /dev/gpio/PD19 : 58 time: 20392 0
 test::ApfInTest2 INFO     11100111000011000000000001000000 - IMPGD:1 - IMPDD:1
 test::ApfInTest2 INFO /dev/gpio/PD19 : 59 time: 28313 1
 test::ApfInTest2 INFO     11100111000011000000000001000000 - IMPGD:1 - IMPDD:1
 test::ApfInTest2 INFO /dev/gpio/PD19 : 60 time: 36313 0
 test::ApfInTest2 INFO     11100011000011000000000001000000 - IMPGD:1 - IMPDD:0
 test::ApfInTest2 INFO /dev/gpio/PD19 : 61 time: 88307 1
 test::ApfInTest2 INFO     11100011000011000000000001000000 - IMPGD:1 - IMPDD:0
 test::ApfInTest2 INFO /dev/gpio/PD19 : 62 time: 14983 0
 test::ApfInTest2 INFO     11100011000011000000000001000000 - IMPGD:1 - IMPDD:0
 test::ApfInTest2 INFO /dev/gpio/PD19 : 63 time: 14573 1
 * 
 */
void test::UTApfGpioIn::in_V1_blockingReadFstream(std::string inGpioPort,
		std::string inPin)
{
	int fd_input, retval = 0, iomask = 0x00;
	unsigned short c = 0;
	std::string filePort;
	filePort = INPUT_PORT_PATH_DEV.append(inGpioPort).append(inPin);

	logger().info() << "V1 - Blocking-read read() + lecture fstream du portD:"
			<< filePort << utils::end;

	//Open GPIO device for communication
	fd_input = open(filePort.c_str(), O_RDONLY);
	if (fd_input < 0)
	{
		printf("Open Failed : %s\n", filePort.c_str());
		exit(EXIT_FAILURE);
	}
	logger().debug() << "fd_input opened" << utils::end;

	logger().info()
			<< "WARNING : Are you sure the pin mode/dir/irq are configured ?"
			<< utils::end;

	//Set this process as owner of device file
	retval = fcntl(fd_input, F_SETOWN, getpid());
	if (retval < 0)
	{
		printf("F_SETOWN fails for%s\n", filePort.c_str());
		exit(EXIT_FAILURE);
	}

	std::string filePort2;
	filePort2 = INPUT_PORT_PATH_PROC.append(inGpioPort);

	int nbtest = 0;
	std::fstream io;
	std::string value;

	utils::Chronometer chrono;
	chrono.start();
	long now = chrono.getElapsedTimeInMicroSec();
	long last = chrono.getElapsedTimeInMicroSec();

	long start = now;
	logger().debug() << "while" << utils::end;
	while (now < start + 3000000)
	{
		//detection front montant/descendant
		read(fd_input, &c, 1); //read bloquant : IRQ necessaire

		io.open(filePort2.c_str(), std::fstream::in);
		io >> value;
		io.close();
		now = chrono.getElapsedTimeInMicroSec();
		logger().info() << filePort << " : " << nbtest << " time: "
				<< now - last << " " << iomask << utils::end;
		//logger().info() << "    " << value << " - " << value[31-atoi(inPin.c_str())] << utils::end;
		logger().info() << "    " << value << " - IMPGD:" << value[6]
				<< " - IMPDD:" << value[5] << utils::end;

		iomask ^= 1; //(iomask == 0x00)?0x01:0x00;
		nbtest++;
		last = now;
	}
	close(fd_input);
}
