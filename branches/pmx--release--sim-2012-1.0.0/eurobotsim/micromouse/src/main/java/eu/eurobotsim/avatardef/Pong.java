package eu.eurobotsim.avatardef;

import java.util.ArrayList;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.robot.AvatarDef;

/**
 * Pong is a really simple robot with a single sensor around the body.
 * 
 * @author david
 * 
 */
public class Pong implements AvatarDef {

	public List<BuildingBlock> getBlocks() {
		List<BuildingBlock> blocks = new ArrayList<BuildingBlock>();

		BuildingBlock body = new BuildingBlock();
		body.setPartType(PartType.ROBOT);
		body.setShape(new Circle(new Point(0, 0), 40));
		blocks.add(body);

		BuildingBlock arrow = new BuildingBlock();
		arrow.setPartType(PartType.ROBOT);
		arrow.setShape(new Rectangle(new Point(0, 0), 1, 60));
		blocks.add(arrow);

		BuildingBlock sensor = new BuildingBlock();
		sensor.setPartType(PartType.SENSOR);
		sensor.setShape(new Circle(new Point(0, 0), 80));
		blocks.add(sensor);

		return blocks;
	}
}
