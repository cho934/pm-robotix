package eu.eurobotsim.simulation;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.robot.AvatarDef;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.world.GameMechanism;

/**
 * The Simulation is a pair of PhysicalSimulation (physics engine) and
 * GameMechanism.
 * 
 * @author David Naramski
 * 
 */
public class Simulation {

	private PhysicalSimulation physicalSimulation;

	private GameMechanism gameMechanism;

	Simulation(PhysicalSimulation physicalSimulation,
			GameMechanism gameMechanism) {
		this.physicalSimulation = physicalSimulation;
		this.gameMechanism = gameMechanism;
	}

	/**
	 * Return the PhysicalSimulation that rules the Simulation
	 * 
	 * @return
	 */
	public PhysicalSimulation getPhysicalSimulation() {
		return physicalSimulation;
	}

	/**
	 * Return the GameMechanism that rules the Simulation
	 * 
	 * @return
	 */
	public GameMechanism getGameMechanism() {
		return gameMechanism;
	}

	/**
	 * Request the Simulation to simulate the next dt seconds and process all
	 * the simulated elements.
	 * 
	 * @param dt
	 */
	public void step(float dt) {
		physicalSimulation.step(dt);
		gameMechanism.step(dt);
	}

	public Robot addRobot(AvatarDef avatarDef, Psyche psyche) {
		Avatar avatar = physicalSimulation.createAvatar(avatarDef, psyche);
		Robot robot = new Robot(avatar, psyche, gameMechanism);
		psyche.start(robot);
		return robot;
	}

}
