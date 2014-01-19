package eu.eurobotsim.avatar;

public class RotateAction implements Action {

	private float angularVelocity;

	public RotateAction(float angularVelocity) {
		this.angularVelocity = angularVelocity;
	}

	public float getAngularVelocity() {
		return angularVelocity;
	}

}
