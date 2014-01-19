package eu.eurobotsim.view;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.imageio.ImageIO;

import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.view.GenericView;

public class Eurobot2012View extends GenericView {

	private static final Logger LOG = Logger.getLogger(Eurobot2012View.class.getName());
	private BufferedImage img;

	public Eurobot2012View(PhysicalSimulation simWorld, int width, int height,
			Rectangle view) {
		super(simWorld, width, height, view);
		try {
			img = ImageIO.read(new File("background.png"));
		} catch (IOException e) {
			LOG.log(Level.SEVERE, e.getMessage(), e);
		}
	}

	@Override
	protected void clear(Graphics2D g) {
		super.clear(g);
		g.drawImage(img, 0, 0, getWidth(), getHeight(), null);
	}

	@Override
	public void refresh() {
		super.refresh();
	}

}
