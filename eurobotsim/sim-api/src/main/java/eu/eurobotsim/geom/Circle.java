package eu.eurobotsim.geom;

public class Circle implements Shape {

	private Point center;

	private float radius;

	public Circle(Point center, float radius) {
		this.center = center;
		this.radius = radius;
	}

	public Point getCenter() {
		return center;
	}

	public void setCenter(Point center) {
		this.center = center;
	}

	public float getRadius() {
		return radius;
	}

	public void setRadius(float radius) {
		this.radius = radius;
	}

}
