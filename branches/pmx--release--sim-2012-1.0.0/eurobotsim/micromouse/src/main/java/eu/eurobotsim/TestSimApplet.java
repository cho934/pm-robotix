package eu.eurobotsim;

import java.awt.Graphics;

import javax.swing.JApplet;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import eu.eurobotsim.avatardef.Pong;
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
import eu.eurobotsim.worlddef.SquareWorld;
import eu.eurobotsim.worlddef.TreasureHunterMechanism;
import eu.eurobotsim.worlddef.TreasureIslandWorldDef;

public class TestSimApplet extends JApplet {

	private SimulationView worldView;

	private GenericView genericView;

	public void init() {

		final Simulation world = new SimulationFactory().createSimulation(
				new SquareWorld(), new TreasureHunterMechanism(), null);
		PhysicalSimulation simWorld = world.getPhysicalSimulation();

		world.addRobot(new Pong(), new FreezeAtFirstSight());

		int width = 400;
		int height = 400;
		Rectangle borders = new Rectangle(-210, -210, 420, 420);

		worldView = simWorld.createDebugView(width, height, borders);
		worldView.refresh();

		genericView = new Eurobot2012View(simWorld, width, height, borders);
		genericView.refresh();

		setSize(worldView.getWidth() * 2, worldView.getHeight());

		SwingWorker<Object, Object> worker = new SwingWorker<Object, Object>() {
			@Override
			protected Object doInBackground() throws Exception {
				for (int i = 0; i < 50000; i++) {
					world.step(1.0f / 20);
					SwingUtilities.invokeLater(new Runnable() {

						public void run() {
							worldView.refresh();
							genericView.refresh();
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
		g.drawImage(worldView.getImage(), 0, 0, worldView.getWidth(),
				worldView.getHeight(), this);
		g.drawImage(genericView.getImage(), worldView.getWidth(), 0,
				genericView.getWidth(), genericView.getHeight(), this);
	}

}
