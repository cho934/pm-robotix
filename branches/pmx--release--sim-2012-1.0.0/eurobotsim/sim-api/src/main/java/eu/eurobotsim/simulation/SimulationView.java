package eu.eurobotsim.simulation;

import java.awt.Image;

/**
 * A view of the Simulation, constructed by the Simulation.
 * 
 * @author David Naramski
 * 
 */
public interface SimulationView {

	/**
	 * Refresh the representation of the simulation
	 */
	void refresh();

	/**
	 * Get the representation of the simulation
	 * 
	 * @return
	 */
	Image getImage();

	/**
	 * Get the width of the image
	 * 
	 * @return
	 */
	int getWidth();

	/**
	 * Get the height of the image
	 * 
	 * @return
	 */
	int getHeight();

}
