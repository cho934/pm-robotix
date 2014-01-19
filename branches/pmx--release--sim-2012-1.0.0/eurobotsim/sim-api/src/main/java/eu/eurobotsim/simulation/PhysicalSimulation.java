package eu.eurobotsim.simulation;

import java.util.List;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Representation;
import eu.eurobotsim.robot.AvatarDef;
import eu.eurobotsim.robot.Psyche;

/**
 * The PhysicalSimulation is the simulated world that hosts the Avatar(s). This
 * class models the physics interaction between simulated object.
 * 
 * @author David Naramski
 * 
 */
public interface PhysicalSimulation {

	/**
	 * Instantiate a new Avatar in the PhysicalSimulation, according the
	 * AvatarDef and using the Psyche as a brain.
	 * 
	 * @param avatarDef
	 * @param psyche
	 * @return
	 */
	Avatar createAvatar(AvatarDef avatarDef, Psyche psyche);

	/**
	 * Request the Simulation to simulate the next dt seconds and process all
	 * the simulated elements.
	 * 
	 * @param dt
	 */
	void step(float dt);

	/**
	 * Create a SimulationView that represents the simulated world
	 * 
	 * @param width
	 * @param height
	 * @param simulationView
	 * @return
	 */
	SimulationView createDebugView(int width, int height,
			Rectangle simulationView);

	/**
	 * Return the Representation of all the BuildingBlock in the
	 * PhysicalSimulation. This is used to draw the PhysicalSimulation on the
	 * screen.
	 * 
	 * @return
	 */
	List<Representation> getRepresentation();

}
