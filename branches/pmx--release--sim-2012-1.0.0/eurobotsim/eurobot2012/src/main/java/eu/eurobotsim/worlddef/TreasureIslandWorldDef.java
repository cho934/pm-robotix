package eu.eurobotsim.worlddef;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Vec;

public class TreasureIslandWorldDef implements WorldDef {

	@Override
	public List<BuildingBlock> getBlocks() {
		List<BuildingBlock> blocks = new ArrayList<BuildingBlock>();

		BuildingBlock top = new BuildingBlock();
		top.setPartType(PartType.STATIC);
		top.setShape(new Rectangle(new Point(0, -1050), 3000, 2));
		blocks.add(top);

		BuildingBlock left = new BuildingBlock();
		left.setPartType(PartType.STATIC);
		left.setShape(new Rectangle(new Point(-1500, 0), 2, 2100));
		blocks.add(left);

		BuildingBlock bottom = new BuildingBlock();
		bottom.setPartType(PartType.STATIC);
		bottom.setShape(new Rectangle(new Point(0, 1050), 3000, 2));
		blocks.add(bottom);

		BuildingBlock right = new BuildingBlock();
		right.setPartType(PartType.STATIC);
		right.setShape(new Rectangle(new Point(1500, 0), 2, 2100));
		blocks.add(right);
		
		BuildingBlock blueBorder = new BuildingBlock();
		blueBorder.setPartType(PartType.STATIC);
		blueBorder.setShape(new Rectangle(new Point(-1300, -550), 400, 18));
		blocks.add(blueBorder);
		
		BuildingBlock redBorder = new BuildingBlock();
		redBorder.setPartType(PartType.STATIC);
		redBorder.setShape(new Rectangle(new Point(1300, -550), 400, 18));
		blocks.add(redBorder);

		return blocks;
	}

	@Override
	public List<AvatarStartPosition> getStartPositions() {
		return Arrays.asList(new AvatarStartPosition(new Point(0, 0), new Vec(
				1, 0)));
	}

}
