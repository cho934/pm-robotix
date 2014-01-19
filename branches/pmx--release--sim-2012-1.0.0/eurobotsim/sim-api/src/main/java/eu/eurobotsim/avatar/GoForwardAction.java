package eu.eurobotsim.avatar;

public class GoForwardAction implements Action {

	private float speed;

	public GoForwardAction(float speed) {
		this.speed = speed;
	}

	public float getSpeed() {
		return speed;
	}

}
