package eu.eurobotsim.psyche;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.avatar.Event;
import eu.eurobotsim.avatar.GoForwardAction;
import eu.eurobotsim.avatar.InteractionFinishedEvent;
import eu.eurobotsim.avatar.ObjectInSensorEvent;
import eu.eurobotsim.avatar.RotateAction;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Vec;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.simulation.Robot;
import eu.eurobotsim.world.GetCoinInteraction;

public class FreezeAtFirstSight implements Psyche {

	private float simulatedTime;

	private long startime;

	private Point position;

	private Vec direction;

	public void start(Robot robot) {
		System.out.println("START");
		simulatedTime = 0;
		if(robot != null && robot.getAvatar() != null) {
		this.position = robot.getAvatar().getPosition();
		this.direction = robot.getAvatar().getDirection();
		startime = System.currentTimeMillis();
		robot.execute(new GetCoinInteraction());
		}
	}

	public void signalEvent(Avatar robot, Event event) {
		if (event instanceof ObjectInSensorEvent) {
			ObjectInSensorEvent e = (ObjectInSensorEvent) event;
			System.out.println("DETECTION " + e.getSensor());
			robot.execute(new GoForwardAction(0));
			robot.execute(new RotateAction(0));
		} else if (event instanceof InteractionFinishedEvent) {
			System.out.println("Interaction finished");
			robot.execute(new GoForwardAction(120f));
			robot.execute(new RotateAction(1f));
		}
	}

	public void timeEllapsed(float dt) {
		simulatedTime += dt;
	}

}
