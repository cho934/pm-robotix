package eu.eurobotsim.world.view;

import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.simulation.view.Viewport;

import junit.framework.TestCase;

public class ViewportTest extends TestCase {

	public void test1() {
		Viewport port = new Viewport(new Rectangle(0, 0, 100, 100),
				new Rectangle(0, 0, 50, 50));
		assertEquals(5f, port.toCameraWidth(10));
		assertEquals(0f, port.toCameraWidth(0));
		assertEquals(50f, port.toCameraWidth(100));
		assertEquals(0f, port.toCameraX(0));
		assertEquals(25f, port.toCameraX(50));
	}

	public void test2() {
		Viewport port = new Viewport(new Rectangle(-100, -100, 200, 200),
				new Rectangle(0, 0, 50, 50));
		assertEquals(0f, port.toCameraX(-100));
		assertEquals(25f, port.toCameraX(0));
	}

	public void test3() {
		Viewport port = new Viewport(
				new Rectangle(new Point(10, 10), 200, 200), new Rectangle(
						new Point(30, 30), 200, 200));
		assertEquals(50f, port.toCameraX(30));
		assertEquals(20f, port.toCameraX(0));
		assertEquals(20f, port.toCameraWidth(20));
	}

	public void test4() {
		Viewport port = new Viewport(
				new Rectangle(new Point(10, 10), 200, 200), new Rectangle(
						new Point(30, 30), 400, 400));
		assertEquals(-170f, port.toCameraX(-90));
		assertEquals(30f, port.toCameraX(10));
	}

}
