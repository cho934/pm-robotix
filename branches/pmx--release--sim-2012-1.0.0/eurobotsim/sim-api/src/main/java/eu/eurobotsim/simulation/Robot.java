package eu.eurobotsim.simulation;

import eu.eurobotsim.avatar.Action;
import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Vec;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.world.GameMechanism;
import eu.eurobotsim.world.Interaction;

public class Robot {

	private Avatar avatar;

	private Psyche psyche;

	private GameMechanism gameMechanism;

	Robot(Avatar avatar, Psyche psyche, GameMechanism gameMechanism) {
		this.avatar = avatar;
		this.psyche = psyche;
		this.gameMechanism = gameMechanism;
	}

	public Avatar getAvatar() {
		return avatar;
	}

	public Psyche getPsyche() {
		return psyche;
	}

	public GameMechanism getGameMechanism() {
		return gameMechanism;
	}

	public void execute(Action action) {
		this.avatar.execute(action);
	}

	public void execute(Interaction interaction) {
		this.gameMechanism.execute(interaction, this);
	}
	
	public Point getPosition() {
		return this.avatar.getPosition();
	}
	
	public Vec getDirection() {
		return this.avatar.getDirection();
	}

}
