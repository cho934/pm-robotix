package eu.eurobotsim.micromouse;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.avatar.Event;
import eu.eurobotsim.avatar.GoForwardAction;
import eu.eurobotsim.avatar.RotateAction;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.simulation.Robot;

public class Brain implements Psyche {

	private Robot robot;

	private int state = 0;

	public void start(Robot robot) {
		this.robot = robot;
	}

	public void signalEvent(Avatar avatar, Event event) {
	}

	public void timeEllapsed(float dt) {
		switch (state) {
		case 0:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getX() > 450) {
				robot.execute(new GoForwardAction(0));
				state = 1;
			}
			break;
		case 1:
			robot.execute(new RotateAction(1));
			if (Math.abs(robot.getAvatar().getDirection().getAngle() - Math.PI
					/ 2) < 0.05) {
				robot.execute(new RotateAction(0));
				state = 2;
			}
			break;
		case 2:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getY() > 150) {
				robot.execute(new GoForwardAction(0));
				state = 3;
			}
			break;
		case 3:
			robot.execute(new RotateAction(1));
			if (Math.abs(robot.getAvatar().getDirection().getAngle() - Math.PI) < 0.05) {
				robot.execute(new RotateAction(0));
				state = 4;
			}
			break;
		case 4:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getX() <= 50) {
				robot.execute(new GoForwardAction(0));
				state = 5;
			}
			break;
		case 5:
			robot.execute(new RotateAction(-2));
			if (Math.abs(robot.getAvatar().getDirection().getAngle() - Math.PI
					/ 2) < 0.05) {
				robot.execute(new RotateAction(0));
				state = 6;
			}
			break;
		case 6:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getY() >= 450) {
				robot.execute(new GoForwardAction(0));
				state = 7;
			}
			break;
		case 7:
			robot.execute(new RotateAction(-2));
			if (Math.abs(robot.getAvatar().getDirection().getAngle()) < 0.05) {
				robot.execute(new RotateAction(0));
				state =  8;
			}
			break;
		case 8:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getX() >= 250) {
				robot.execute(new GoForwardAction(0));
				state = 9;
			}
			break;
		case 9:
			robot.execute(new RotateAction(-2));
			if (Math.abs(robot.getAvatar().getDirection().getAngle() + Math.PI / 2) < 0.05) {
				robot.execute(new RotateAction(0));
				state =  10;
			}
			break;
		case 10:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getY() <= 350) {
				robot.execute(new GoForwardAction(0));
				state = 11;
			}
			break;
		case 11:
			robot.execute(new RotateAction(-2));
			if (Math.abs(robot.getAvatar().getDirection().getAngle() - Math.PI) < 0.1) {
				robot.execute(new RotateAction(0));
				state =  12;
			}
			break;
		case 12:
			robot.execute(new GoForwardAction(100));
			if (robot.getAvatar().getPosition().getX() <= 150) {
				robot.execute(new GoForwardAction(0));
				state = 13;
			}
			break;
		}
	}
}
