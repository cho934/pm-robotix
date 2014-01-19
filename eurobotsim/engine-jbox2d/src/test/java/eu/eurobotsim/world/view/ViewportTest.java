package eu.eurobotsim.world.view;

import java.awt.Rectangle;

import eu.eurobotsim.simulation.jbox2d.view.Viewport;


import junit.framework.TestCase;

public class ViewportTest extends TestCase {

	public void test1() {
		Viewport port = new Viewport(new Rectangle(0, 0, 100, 100),
				new Rectangle(0, 0, 50, 50));
		assertEquals(0, port.toCameraX(0));
		assertEquals(25, port.toCameraX(50));
	}

	public void test2() {
		Viewport port = new Viewport(new Rectangle(-100, -100, 200, 200),
				new Rectangle(0, 0, 50, 50));
		assertEquals(25, port.toCameraX(0));
		assertEquals(0, port.toCameraX(-100));
	}

}
