package eu.eurobotsim.psyche;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.avatar.Event;
import eu.eurobotsim.avatar.GoForwardAction;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.simulation.Robot;

public class Brain implements Psyche {

	private Robot robot;
	
	@Override
	public void start(Robot robot) {
		this.robot = robot;
		// Prise de décision
		takeDecision();
	}
	
	private void takeDecision() {
		// Envoi de l'action
		System.out.println("Position du robot " + robot.getPosition());
	}
	
	private void forward(float distance, float speed) {
		// TODO naramsda
		// envoyer
	}
	
	private void rotate(float angle, float angularSpeed) {
		// TODO naramsda
		// envoyer evenemnt quand termnié
	}

	@Override
	public void signalEvent(Avatar avatar, Event event) {
		
		// update state
		
		takeDecision();
		
	}

	@Override
	public void timeEllapsed(float dt) {
	}

}
