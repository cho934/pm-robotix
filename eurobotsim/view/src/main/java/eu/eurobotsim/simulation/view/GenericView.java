package eu.eurobotsim.simulation.view;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;

import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Representation;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.SimulationView;

public class GenericView implements SimulationView {

	private PhysicalSimulation simWorld;

	private BufferedImage image;

	private Viewport viewport;

	/**
	 * 
	 * @param simWorld
	 *            The physical simulation
	 * @param width
	 *            The width of the image
	 * @param height
	 *            The height of the image
	 * @param worldView
	 *            The limits of the view in the world.
	 */
	public GenericView(PhysicalSimulation simWorld, int width, int height,
			Rectangle worldView) {

		this.simWorld = simWorld;
		this.image = new BufferedImage(width, height,
				BufferedImage.TYPE_INT_RGB);

		this.viewport = new Viewport(worldView, new Rectangle(0, 0, width,
				height));

	}

	protected void clear(Graphics2D g) {
		g.setColor(Color.white);
		g.fillRect(0, 0, image.getWidth(), image.getHeight());
	}

	public void refresh() {

		Graphics2D g = (Graphics2D) image.getGraphics();
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		clear(g);

		g.setColor(Color.red);

		for (Representation r : simWorld.getRepresentation()) {

			AffineTransform oldT = g.getTransform();

			AffineTransform tt = AffineTransform.getTranslateInstance(0, 0);
			tt.translate(viewport.toCameraX(r.getPosition().getX()),
					viewport.toCameraY(r.getPosition().getY()));
			tt.rotate(r.getOrientation().getVx(), r.getOrientation().getVy());
			tt.translate((float) -viewport.toCameraX(0),
					(float) -viewport.toCameraY(0));
			g.setTransform(tt);

			Shape s = null;

			if (r.getBlock().getShape() instanceof Circle) {
				Circle c = (Circle) r.getBlock().getShape();
				s = createShape(c);
			} else if (r.getBlock().getShape() instanceof Rectangle) {
				Rectangle rect = (Rectangle) r.getBlock().getShape();
				s = createShape(rect);
			}

			if (s != null) {
				g.draw(s);
			}

			g.setTransform(oldT);
		}
	}

	private Shape createShape(Rectangle rect) {
		Rectangle2D rect2d = new Rectangle2D.Float(viewport.toCameraX(-rect
				.getWidth() / 2), viewport.toCameraY(-rect.getHeight() / 2),
				viewport.toCameraWidth(rect.getWidth()),
				viewport.toCameraHeight(rect.getHeight()));
		return rect2d;
	}

	private Shape createShape(Circle circle) {
		Ellipse2D circle2d = new Ellipse2D.Float((viewport.toCameraX(-circle
				.getRadius())), viewport.toCameraY(-circle.getRadius()),
				viewport.toCameraWidth(circle.getRadius() * 2),
				viewport.toCameraHeight(circle.getRadius() * 2));
		return circle2d;
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
