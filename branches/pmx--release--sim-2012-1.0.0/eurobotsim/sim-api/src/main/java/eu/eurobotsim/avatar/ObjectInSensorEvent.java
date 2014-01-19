package eu.eurobotsim.avatar;

import eu.eurobotsim.geom.BuildingBlock;

public class ObjectInSensorEvent implements Event {

	private BuildingBlock sensor;

	public ObjectInSensorEvent(BuildingBlock sensor) {
		this.sensor = sensor;
	}

	public BuildingBlock getSensor() {
		return sensor;
	}

}
