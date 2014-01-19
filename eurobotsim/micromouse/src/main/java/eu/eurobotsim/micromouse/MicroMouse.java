package eu.eurobotsim.micromouse;

import java.util.ArrayList;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.robot.AvatarDef;

public class MicroMouse implements AvatarDef {

	public List<BuildingBlock> getBlocks() {
		List<BuildingBlock> blocks = new ArrayList<BuildingBlock>();

		BuildingBlock circle = new BuildingBlock();
		circle.setPartType(PartType.ROBOT);
		circle.setShape(new Circle(new Point(0, 0), 25));
		blocks.add(circle);

		BuildingBlock mouse = new BuildingBlock();
		mouse.setPartType(PartType.ROBOT);
		mouse.setShape(new Rectangle(new Point(-10, 0), 35, 35));
		blocks.add(mouse);

		return blocks;
	}

}
