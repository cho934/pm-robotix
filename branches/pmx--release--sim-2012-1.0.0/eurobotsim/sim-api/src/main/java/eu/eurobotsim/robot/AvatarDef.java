package eu.eurobotsim.robot;

import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;

/**
 * The AvatarDef is the definition of the body of the robot. The Avatar is build
 * by the Simulation according to the AvatarDef.
 * 
 * @author David Naramski
 * 
 */
public interface AvatarDef {

	List<BuildingBlock> getBlocks();

}
