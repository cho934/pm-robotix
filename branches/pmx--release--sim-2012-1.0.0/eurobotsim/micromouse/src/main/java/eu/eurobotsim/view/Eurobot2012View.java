package eu.eurobotsim.view;

import java.awt.Graphics2D;

import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.view.GenericView;

public class Eurobot2012View extends GenericView {

	public Eurobot2012View(PhysicalSimulation simWorld, int width, int height,
			Rectangle view) {
		super(simWorld, width, height, view);
	}

	@Override
	protected void clear(Graphics2D g) {
		super.clear(g);
	}
	
	@Override
	public void refresh() {
		super.refresh();
	}
}
