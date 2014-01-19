package eu.eurobotsim.worlddef;

import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Vec;

public class AvatarStartPosition {

	private Point position;
	
	private Vec orientation;

	public AvatarStartPosition(Point position, Vec orientation) {
		this.position = position;
		this.orientation = orientation;
	}
	
	public Point getPosition() {
		return position;
	}

	public void setPosition(Point position) {
		this.position = position;
	}

	public Vec getOrientation() {
		return orientation;
	}

	public void setOrientation(Vec orientation) {
		this.orientation = orientation;
	}
	
}
