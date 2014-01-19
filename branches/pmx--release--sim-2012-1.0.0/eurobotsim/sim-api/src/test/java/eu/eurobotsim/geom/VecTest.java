package eu.eurobotsim.geom;

import junit.framework.TestCase;

public class VecTest extends TestCase {

	public void test1() throws Exception {
		Vec v = new Vec(1, 0);
		assertEquals(0.0f, v.getAngle());
	}

	public void test2() throws Exception {
		Vec v = new Vec(0, 1);
		assertEquals((float) Math.PI / 2, v.getAngle());
	}

	public void test3() throws Exception {
		Vec v = new Vec(-1, 0);
		assertEquals((float) Math.PI, v.getAngle());
	}

	public void test4() throws Exception {
		Vec v = new Vec(0, -1);
		assertEquals((float) - Math.PI / 2, v.getAngle());
	}

}
