package eu.eurobotsim.micromouse;

import java.awt.Graphics;

import javax.swing.JApplet;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.Simulation;
import eu.eurobotsim.simulation.SimulationFactory;
import eu.eurobotsim.simulation.view.GenericView;

public class MicroMouseApplet extends JApplet {

	private GenericView genericView;

	public void init() {

		/* Création de la simulation à partir de sa description physique, et les "règles" */
		final Simulation world = new SimulationFactory().createSimulation(
				new MazeDef(), new MouseRunMechanism(), null);

		/* Ajout d'un robot à partide sa définition physique et de son cerveau */
		world.addRobot(new MicroMouse(), new Brain());

		int width = 400;
		int height = 400;

		PhysicalSimulation simWorld = world.getPhysicalSimulation();
		genericView = new GenericView(simWorld, width, height, new Rectangle(
				new Point(250, 250), 510, 510));
		genericView.refresh();

		/* Fait évoluer la simulation de 1/200ème de seconde */
		Thread simThread = new Thread() {
			public void run() {
				while (true) {
					world.step(1.0f / 200);
					try {
						Thread.currentThread().sleep((int) 1000 / 200);
					} catch (InterruptedException ex) {
						ex.printStackTrace();
					}
				}
			};
		};

		/* Rafraichi la vue, ne contraint en aucun cas le déroulement de la Simulation */
		SwingWorker<Object, Object> worker = new SwingWorker<Object, Object>() {
			@Override
			protected Object doInBackground() throws Exception {
				while (true) {
					SwingUtilities.invokeLater(new Runnable() {

						public void run() {
							genericView.refresh();
							repaint();
						}
					});
					try {
						Thread.currentThread().sleep((int) 1000 / 10);
					} catch (InterruptedException ex) {
						ex.printStackTrace();
					}
				}
			}
		};

		simThread.start();
		worker.execute();

		setSize(width, height);

	}

	@Override
	public void paint(Graphics g) {
		g.drawImage(genericView.getImage(), 0, 0, genericView.getWidth(),
				genericView.getHeight(), this);
	}

}
