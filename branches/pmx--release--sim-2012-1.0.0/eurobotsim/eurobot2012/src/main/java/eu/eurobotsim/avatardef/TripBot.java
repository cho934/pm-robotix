package eu.eurobotsim.avatardef;

import java.util.ArrayList;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.robot.AvatarDef;

public class TripBot implements AvatarDef {

	public List<BuildingBlock> getBlocks() {
		List<BuildingBlock> blocks = new ArrayList<BuildingBlock>();
//*
		BuildingBlock body = new BuildingBlock();
		body.setPartType(PartType.ROBOT);
		body.setShape(new Circle(new Point(0, 0), 190));
		blocks.add(body);

		BuildingBlock arrow = new BuildingBlock();
		arrow.setPartType(PartType.ROBOT);
		arrow.setShape(new Rectangle(new Point(50, 0), 100, 190));
		blocks.add(arrow);

		BuildingBlock sensor = new BuildingBlock();
		sensor.setPartType(PartType.SENSOR);
		sensor.setShape(new Circle(new Point(0, 0), 300));
		blocks.add(sensor);
//*/
/*
		BuildingBlock contour = new BuildingBlock();
		contour.setPartType(PartType.SENSOR);
		contour.setShape(new Circle(new Point(0, 0), 190));
		blocks.add(contour);
		
		BuildingBlock body = new BuildingBlock();
		body.setPartType(PartType.ROBOT);
		body.setShape(new Rectangle(new Point(0, 0), 200, 300));
		blocks.add(body);
		
		BuildingBlock fork = new BuildingBlock();
		fork.setPartType(PartType.ROBOT);
		fork.setShape(new Rectangle(new Point(125, 0), 50, 50));
		blocks.add(fork);
		
		fork = new BuildingBlock();
		fork.setPartType(PartType.ROBOT);
		fork.setShape(new Rectangle(new Point(125, -75), 50, 50));
		blocks.add(fork);
		
		fork = new BuildingBlock();
		fork.setPartType(PartType.ROBOT);
		fork.setShape(new Rectangle(new Point(125, 75), 50, 50));
		blocks.add(fork);
//*/
		return blocks;
	}

}
