package eu.eurobotsim.geom;

public class Representation {

	private BuildingBlock block;
	
	private Vec orientation;
	
	private Point position;

	public BuildingBlock getBlock() {
		return block;
	}

	public void setBlock(BuildingBlock block) {
		this.block = block;
	}

	public Vec getOrientation() {
		return orientation;
	}

	public void setOrientation(Vec orientation) {
		this.orientation = orientation;
	}

	public Point getPosition() {
		return position;
	}

	public void setPosition(Point position) {
		this.position = position;
	}
	
}
