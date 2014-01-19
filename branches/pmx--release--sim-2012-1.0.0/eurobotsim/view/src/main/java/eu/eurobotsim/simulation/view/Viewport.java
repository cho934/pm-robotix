package eu.eurobotsim.simulation.view;

import eu.eurobotsim.geom.Rectangle;

public class Viewport {

	private Rectangle worldView;

	private Rectangle cameraView;

	private float scaleX;

	private float scaleY;

	public Viewport(Rectangle worldView, Rectangle cameraView) {
		this(worldView, cameraView, true);
	}

	public Viewport(Rectangle worldView, Rectangle cameraView,
			boolean keepAspectRatio) {
		this.worldView = worldView;
		this.cameraView = cameraView;

		System.out.println("World : " + worldView);
		System.out.println("Camera : " + cameraView);

		float worldViewAspect = worldView.getWidth() / worldView.getHeight();
		float cameraViewAspect = cameraView.getWidth() / cameraView.getHeight();


		float widthScale = cameraView.getWidth() / worldView.getWidth();
		float heightScale =  cameraView.getHeight() / worldView.getHeight();

		if (!keepAspectRatio) {
			scaleX = widthScale;
			scaleY = heightScale;
		} else {
			if (worldViewAspect > cameraViewAspect) {
				/* The world view is larger */
				scaleX = widthScale;
				scaleY = scaleX;
			} else {
				/* The world view is taller */
				scaleX = heightScale;
				scaleY = scaleX;
			}
		}
		System.out.println("Scale X : " + scaleX + " - Scale Y : " + scaleY);
	}

	public float toCameraX(float x) {

		return (x - worldView.getCenter().getX()) * scaleX
				+ cameraView.getCenter().getX();

	}

	public float toCameraY(float y) {
		return (y - worldView.getCenter().getY()) * scaleY
				+ cameraView.getCenter().getY();
	}

	public float toCameraWidth(float width) {
		return width * scaleX;
	}

	public float toCameraHeight(float height) {
		return height * scaleY;
	}

}
