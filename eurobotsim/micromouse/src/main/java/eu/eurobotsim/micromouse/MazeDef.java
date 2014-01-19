package eu.eurobotsim.micromouse;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Vec;
import eu.eurobotsim.worlddef.AvatarStartPosition;
import eu.eurobotsim.worlddef.WorldDef;

public class MazeDef implements WorldDef {

	public List<AvatarStartPosition> getStartPositions() {
		return Arrays.asList(new AvatarStartPosition(new Point(50,50), new Vec(1,0)));
	}

	public List<BuildingBlock> getBlocks() {
		List<BuildingBlock> blocks = new ArrayList<BuildingBlock>();

		BuildingBlock t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(0, 0, 500, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(0, 100, 400, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(100, 200, 300, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(100, 300, 200, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(100, 400, 100, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(0, 500, 500, 1));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(0, 0, 1, 500));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(100, 300, 1, 100));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(300, 300, 1, 200));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(400, 200, 1, 300));
		blocks.add(t);

		t = new BuildingBlock(PartType.STATIC);
		t.setShape(new Rectangle(500, 0, 1, 500));
		blocks.add(t);

		return blocks;
	}

}
