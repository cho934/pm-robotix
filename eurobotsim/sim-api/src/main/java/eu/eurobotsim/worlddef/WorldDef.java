package eu.eurobotsim.worlddef;

import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;

public interface WorldDef {

	List<AvatarStartPosition> getStartPositions();

	List<BuildingBlock> getBlocks();

}
