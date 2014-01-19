package eu.eurobotsim.simulation.jbox2d.view;

import java.awt.Rectangle;

public class Viewport {

	private Rectangle worldView;

	private Rectangle cameraView;

	public Viewport(Rectangle worldView, Rectangle cameraView) {
		this.worldView = worldView;
		this.cameraView = cameraView;
	}

	public Viewport(int worldX, int worldY, int worldWidth, int worldHeight,
			int cameraX, int cameraY, int cameraWidth, int cameraHeight) {
		this(new Rectangle(worldX, worldY, worldWidth, worldHeight),
				new Rectangle(cameraX, cameraY, cameraWidth, cameraHeight));
	}

	public int toCameraX(float x) {
		float width = (float) cameraView.width / worldView.width;
		int offset_x = worldView.x - cameraView.x;
		return (int) ((x - offset_x) * width);
	}

	public int toCameraY(float y) {
		float heigth = (float) cameraView.height / worldView.height;
		int offset_y = worldView.y - cameraView.y;
		return (int) ((y - offset_y) * heigth);
	}

	public int toCameraWidth(float width) {
		float widthCoeff = (float) cameraView.width / worldView.width;
		return (int) (width * widthCoeff);
	}

	public int toCameraHeight(float height) {
		float heigthCoeff = (float) cameraView.height / worldView.height;
		return (int) (height * heigthCoeff);
	}

}
