package eu.eurobotsim.robot;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.avatar.Event;
import eu.eurobotsim.simulation.Robot;

/**
 * The Psyche is the brain of the Avatar. It receive Event and timing
 * information from the Simulation and fire back Action to the Avatar.
 * 
 * @author David Naramski
 * 
 */
public interface Psyche {

	/**
	 * Start the activity of the Psyche, the brain of the Avatar. This signal is
	 * triggered by the Simulation when the Avatar is ready to execute Action.
	 * 
	 * @param robot
	 */
	void start(Robot robot);

	/**
	 * An asynchronous Event transmitted by the Simulation. This is meant to be
	 * used by the Simulation when one of the Avatar sensors detect something.
	 * 
	 * @param robot
	 * @param event
	 */
	void signalEvent(Avatar avatar, Event event);

	/**
	 * A timing event to simulate the time flow of the simulation. The Psyche
	 * can be aware of the time flow via this signal.
	 * 
	 * @param dt
	 */
	void timeEllapsed(float dt);

}
