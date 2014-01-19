package eu.eurobotsim.simulation.trip;

import java.util.ArrayList;
import java.util.List;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Representation;
import eu.eurobotsim.robot.AvatarDef;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.SimulationView;
import eu.eurobotsim.worlddef.WorldDef;

public class TripSimulationImpl implements PhysicalSimulation {

	public TripSimulationImpl(WorldDef worldDef) {
		
	}
	
	@Override
	public Avatar createAvatar(AvatarDef avatarDef, Psyche psyche) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void step(float dt) {
		// TODO Auto-generated method stub
	}

	@Override
	public SimulationView createDebugView(int width, int height,
			Rectangle simulationView) {
		// NON MANDATORY
		return null;
	}

	@Override
	public List<Representation> getRepresentation() {
		// NON MANDATORY
		return new ArrayList<Representation>();
	}

}
