package eu.eurobotsim.micromouse;

import eu.eurobotsim.simulation.Robot;
import eu.eurobotsim.world.GameMechanism;
import eu.eurobotsim.world.Interaction;

public class MouseRunMechanism implements GameMechanism {

	float ellapsed = 0;

	public void execute(Interaction interaction, Robot robot) {
	}

	public void start() {
		ellapsed = 0;
	}

	public void step(float dt) {
		System.out.println(this.ellapsed += dt);
	}

}
