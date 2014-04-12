/*!
 * \file
 * \brief Implémentation de la classe LedBarTest..
 */

#include "LedBarTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::LedBarTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "LedBarTest - Blink Led board by ActionManager" << utils::end;

	try
	{
		pmx::Robot robot;
		robot.start();


	    logger().info() << " ledBar().reset()" << utils::end;
	    robot.ledBar().startReset();
	    sleep(1);

	    logger().info() << " ledBar().flash()" << utils::end;
	    robot.ledBar().startFlash();
	    sleep(1);


	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startBlinkPin(3, 30, 50000, true)" << utils::end;
	    robot.ledBar().startBlinkPin(3, 30, 50000, true);

	    logger().info() << " ledBar()startBlinkPin(4, 10, 200000, false)" << utils::end;
	    robot.ledBar().startBlinkPin(4, 10, 200000, false);
	    //TODO pmx::LedIndicator::instance().blinkPin(4, 10, 200000);
	    sleep(2);
	    robot.ledBar().stopAndWait(true);

	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startBlink(30, 50000, true)" << utils::end;
	    robot.ledBar().startBlink(30, 50000, true);

	    logger().info() << " ledBar().startBlink(10, 200000, false)" << utils::end;
	    robot.ledBar().startBlink(10, 200000, false);
	    //TODO pmx::LedIndicator::instance().blink(10, 200000);
	    sleep(2);
	    robot.ledBar().stopAndWait(true);

	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startK2Mil(2, 200000, true)" << utils::end;
	    robot.ledBar().startK2Mil(2, 200000, true);


	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startK2Mil(3, 100000, false) + sleep 10" << utils::end;
	    robot.ledBar().startK2Mil(3, 100000, false);
	    sleep(6);
	    robot.ledBar().stopAndWait(true);

	    robot.ledBar().startReset();
	    logger().info() << " ledBar().flashValue(0xAA) + LEDIndicator + sleep 2" << utils::end;
	    robot.ledBar().startFlashValue(0xAA);
	    //TODO pmx::LedIndicator::instance().flashValue(0xAA);
	    sleep(2);


	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startAlternate(20, 200000, 0x33, 0xCC, true)" << utils::end;
	    robot.ledBar().startAlternate(20, 200000, 0x33, 0xCC, true);

	    robot.ledBar().startReset();
	    logger().info() << " ledBar().startAlternate(20, 200000, 0xC3, 0x3C, false) + LEDIndicator + sleep 5" << utils::end;
	    robot.ledBar().startAlternate(20, 200000, 0xC3, 0x3C, false);
	     sleep(3);
	    robot.ledBar().startReset();
	    robot.ledBar().stopAndWait(true);

		robot.stop();

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}
	logger().info() << "End of RobotTest." << utils::end;
}

