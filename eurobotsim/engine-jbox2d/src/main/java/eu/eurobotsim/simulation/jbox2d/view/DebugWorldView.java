package eu.eurobotsim.simulation.jbox2d.view;

import java.awt.Image;
import java.awt.image.BufferedImage;

import org.jbox2d.callbacks.DebugDraw;

import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.simulation.SimulationView;
import eu.eurobotsim.simulation.jbox2d.PhysicalSimulationImpl;

public class DebugWorldView implements SimulationView {

	private PhysicalSimulationImpl simWorld;

	private BufferedImage image;

	private DebugDrawImpl debugDraw;

	public DebugWorldView(PhysicalSimulationImpl simWorld, int width, int height,
			Rectangle view) {
		this.simWorld = simWorld;
		this.image = new BufferedImage(width, height,
				BufferedImage.TYPE_INT_RGB);

		debugDraw = new DebugDrawImpl(image);
		debugDraw.setFlags(DebugDraw.e_shapeBit);
		debugDraw.getViewportTranform().setCamera(
				view.getCenter().getX() - (view.getWidth() / 2),
				view.getCenter().getY() - (view.getHeight() / 2),
				Math.min((float) (width / view.getWidth()),
						(float) (height / view.getHeight())));
		simWorld.getWorld().setDebugDraw(debugDraw);
	}

	public void refresh() {
		debugDraw.clear();
		simWorld.getWorld().drawDebugData();
	}

	public Image getImage() {
		return image;
	}

	public int getWidth() {
		return image.getWidth();
	}

	public int getHeight() {
		return image.getHeight();
	}

}
