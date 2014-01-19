package eu.eurobotsim.avatar;

import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Vec;

/**
 * The Avatar is the representation of the robot in the Simulation.
 * 
 * @author David Naramski
 * 
 */
public interface Avatar {

	/**
	 * Execute one Action in the Simulation
	 * 
	 * @param action
	 */
	void execute(Action action);

	/**
	 * Get the direction of the Avatar in the Simulation
	 * @return
	 */
	Vec getDirection();

	/**
	 * Get the position of the Avatar in the Simulation
	 * 
	 * @return
	 */
	Point getPosition();

}
