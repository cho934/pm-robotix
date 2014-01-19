package eu.eurobotsim;

import java.awt.Graphics;
import java.util.Properties;

import javax.swing.JApplet;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import eu.eurobotsim.avatardef.TripBot;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.psyche.FreezeAtFirstSight;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.Simulation;
import eu.eurobotsim.simulation.SimulationFactory;
import eu.eurobotsim.simulation.SimulationView;
import eu.eurobotsim.simulation.view.GenericView;
import eu.eurobotsim.view.Eurobot2012View;
import eu.eurobotsim.worlddef.TreasureHunterMechanism;
import eu.eurobotsim.worlddef.TreasureIslandWorldDef;

public class Tripplet extends JApplet {

	private SimulationView worldView;

	private GenericView genericView;

	int width = 400;
	int height = 400;

	public void init() {

		Properties props = new Properties();
		props.put("eu.eurobotsim.simulation.factory",
				"eu.eurobotsim.simulation.trip.TripSimulationImpl");

		final Simulation world = new SimulationFactory().createSimulation(
				new TreasureIslandWorldDef(), new TreasureHunterMechanism(),
				props);
		PhysicalSimulation simWorld = world.getPhysicalSimulation();

		world.addRobot(new TripBot(), new FreezeAtFirstSight());

		Rectangle borders = new Rectangle(new Point(0, 0), 3010, 3010);

		worldView = simWorld.createDebugView(width, height, borders);
		if(worldView != null) {
			worldView.refresh();
		}

		genericView = new Eurobot2012View(simWorld, width, height, borders);
		if(genericView != null) {
			genericView.refresh();
		}

		setSize(width * 2, height);

		SwingWorker<Object, Object> worker = new SwingWorker<Object, Object>() {
			@Override
			protected Object doInBackground() throws Exception {
				for (int i = 0; i < 50000; i++) {
					world.step(1.0f / 20);
					SwingUtilities.invokeLater(new Runnable() {

						public void run() {
							if(worldView != null) {
								worldView.refresh();
							}
							if(genericView != null) {
								genericView.refresh();
							}
							repaint();
						}
					});
					Thread.currentThread().sleep((int) 1000 / 20);
				}
				return null;
			}
		};

		worker.execute();

	}

	@Override
	public void paint(Graphics g) {
		if(worldView != null && worldView.getImage() != null) {
			g.drawImage(worldView.getImage(), 0, 0, worldView.getWidth(),
					worldView.getHeight(), this);
		}

		if(genericView != null && genericView.getImage()  != null) {
			g.drawImage(genericView.getImage(), width, 0,
					genericView.getWidth(), genericView.getHeight(), this);
		}
	}

}
