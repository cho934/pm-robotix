package eu.eurobotsim.simulation;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.worlddef.AvatarStartPosition;
import eu.eurobotsim.worlddef.WorldDef;
import junit.framework.TestCase;

public class SimulationFactoryTest extends TestCase {

    public void test1() throws Exception {
        SimulationFactory factory = new SimulationFactory();
        factory.createSimulation(new WorldDef() {

            public List<BuildingBlock> getBlocks() {
                return new ArrayList<BuildingBlock>();
            }

            @Override
            public List<AvatarStartPosition> getStartPositions() {
                return Arrays.asList(new AvatarStartPosition(null, null));
            }
        }, null, null);
    }

}
