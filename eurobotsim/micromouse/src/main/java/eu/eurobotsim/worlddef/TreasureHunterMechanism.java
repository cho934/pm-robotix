package eu.eurobotsim.worlddef;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import eu.eurobotsim.avatar.InteractionFinishedEvent;
import eu.eurobotsim.simulation.Robot;
import eu.eurobotsim.world.GameMechanism;
import eu.eurobotsim.world.GetCoinInteraction;
import eu.eurobotsim.world.Interaction;

public class TreasureHunterMechanism implements GameMechanism {

	private float ellapsedTime = 0;

	private List<TimedInteraction> interactions = new ArrayList<TreasureHunterMechanism.TimedInteraction>();

	@Override
	public void start() {
		ellapsedTime = 0;
	}

	@Override
	public void step(float time) {
		ellapsedTime += time;
		Iterator<TimedInteraction> it = interactions.iterator();
		while (it.hasNext()) {
			TimedInteraction i = it.next();
			if (i.time <= ellapsedTime) {
				System.out.println("Interaction finished " + it);
				it.remove();
				i.robot.getPsyche().signalEvent(i.robot.getAvatar(),
						new InteractionFinishedEvent());
			}
		}
	}

	@Override
	public void execute(Interaction interaction, Robot robot) {
		if (interaction instanceof GetCoinInteraction) {
			TimedInteraction i = new TimedInteraction();
			i.interaction = interaction;
			i.time = ellapsedTime + 3;
			System.out.println("Ajout d'interaction pour " + i.time);
			i.robot = robot;
			interactions.add(i);
		}
	}

	static class TimedInteraction {
		float time;
		Interaction interaction;
		Robot robot;
	}

}
