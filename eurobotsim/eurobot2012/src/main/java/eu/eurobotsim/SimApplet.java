package eu.eurobotsim;

import java.awt.Graphics;

import javax.swing.JApplet;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import eu.eurobotsim.avatardef.TripBot;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.psyche.Brain;
import eu.eurobotsim.psyche.FreezeAtFirstSight;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.Robot;
import eu.eurobotsim.simulation.Simulation;
import eu.eurobotsim.simulation.SimulationFactory;
import eu.eurobotsim.simulation.SimulationView;
import eu.eurobotsim.simulation.view.GenericView;
import eu.eurobotsim.view.Eurobot2012View;
import eu.eurobotsim.worlddef.TreasureHunterMechanism;
import eu.eurobotsim.worlddef.TreasureIslandWorldDef;

public class SimApplet extends JApplet {

	//private SimulationView worldView;

	private GenericView genericView;

	public void init() {

		/* Création de simulation */
		final Simulation world = new SimulationFactory().createSimulation(
				new TreasureIslandWorldDef(), new TreasureHunterMechanism(),
				null);

		/* Ajouter un robot, le simulation appelle la méthode START du cerveau */
		//Robot robot = world.addRobot(new TripBot(), new FreezeAtFirstSight());
		Robot robot = world.addRobot(new TripBot(), new Brain());

		int width = 1000;
		int height = 700;
		Rectangle borders = new Rectangle(new Point(0, 0), 3000, 2100);

		PhysicalSimulation simWorld = world.getPhysicalSimulation();
/*
		worldView = simWorld.createDebugView(width, height, borders);
		worldView.refresh();
*/
		genericView = new Eurobot2012View(simWorld, width, height, borders);
		genericView.refresh();

		//setSize(worldView.getWidth() * 2, worldView.getHeight());
		setSize(genericView.getWidth(), genericView.getHeight());

		SwingWorker<Object, Object> worker = new SwingWorker<Object, Object>() {
			@Override
			protected Object doInBackground() throws Exception {
				for (int i = 0; i < 50000; i++) {
					world.step(1.0f / 20);
					SwingUtilities.invokeLater(new Runnable() {

						public void run() {
							//worldView.refresh();
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
		/*
		g.drawImage(worldView.getImage(), 0, 0, worldView.getWidth(),
				worldView.getHeight(), this);
		*/
		g.drawImage(genericView.getImage(), 0, 0,
				genericView.getWidth(), genericView.getHeight(), this);
				
	}

}
