package eu.eurobotsim.world;

import eu.eurobotsim.simulation.Robot;

/**
 * The GameMechanism implements the mechanism of the Simulation.
 * 
 * @author David Naramski
 * 
 */
public interface GameMechanism {

	void execute(Interaction interaction, Robot robot);

	/**
	 * Triggered by the Simulation when the simulation starts
	 */
	void start();

	/**
	 * Request the GameMechanism to simulate the next dt seconds and process all
	 * the simulated elements.
	 * 
	 * @param dt
	 */
	void step(float dt);

}
