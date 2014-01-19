package eu.eurobotsim.geom;

public class Rectangle implements Shape {

	private Point center;

	private float width;

	private float height;

	public Rectangle(Point center, float width, float height) {
		this.center = center;
		this.width = width;
		this.height = height;
	}

	public Rectangle(float x, float y, float width, float height) {
		this.center = new Point(x + width / 2, y + height / 2);
		this.width = width;
		this.height = height;
	}

	public Point getCenter() {
		return center;
	}

	public void setCenter(Point center) {
		this.center = center;
	}

	public float getWidth() {
		return width;
	}

	public void setWidth(float width) {
		this.width = width;
	}

	public float getHeight() {
		return height;
	}

	public void setHeight(float height) {
		this.height = height;
	}

	@Override
	public String toString() {
		return "Rectangle[center=" + getCenter() + ",width=" + getWidth()
				+ ",height=" + getHeight() + ",extends=("
				+ (getCenter().getX() - getWidth() / 2) + ","
				+ (getCenter().getY() - getHeight() / 2) + ")-("
				+ (getCenter().getX() + getWidth() / 2) + ","
				+ (getCenter().getY() + getHeight() / 2) + ")]";
	}

}
