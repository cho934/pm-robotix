package eu.eurobotsim.geom;

import java.text.NumberFormat;

public class Vec {

	private float vx;

	private float vy;

	public Vec(float vx, float vy) {
		super();
		this.vx = vx;
		this.vy = vy;
	}

	public float getVx() {
		return vx;
	}

	public void setVx(float vx) {
		this.vx = vx;
	}

	public float getVy() {
		return vy;
	}

	public void setVy(float vy) {
		this.vy = vy;
	}

	public float getAngle() {
		double length = Math.sqrt(getVx() * getVx() + getVy() * getVy());
		return (float) Math.atan2(getVy() / length, getVx() / length);
	}

	@Override
	public String toString() {
		NumberFormat nf = NumberFormat.getNumberInstance();
		nf.setMinimumFractionDigits(2);
		nf.setMaximumFractionDigits(2);
		return "Vec[x=" + nf.format(getVx()) + ",y=" + nf.format(getVy())
				+ ",angle=" + nf.format((getAngle() / Math.PI * 180)) + "°="
				+ nf.format(getAngle()) + "]";
	}

}
