package eu.eurobotsim.geom;

public class BuildingBlock {

	private PartType partType;

	private Shape shape;

	public BuildingBlock() {
	}

	public BuildingBlock(PartType partType) {
		this.partType = partType;
	}

	public PartType getPartType() {
		return partType;
	}

	public void setPartType(PartType partType) {
		this.partType = partType;
	}

	public Shape getShape() {
		return shape;
	}

	public void setShape(Shape shape) {
		this.shape = shape;
	}

}
