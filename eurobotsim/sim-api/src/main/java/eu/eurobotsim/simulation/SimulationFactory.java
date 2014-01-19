package eu.eurobotsim.simulation;

import java.lang.reflect.Constructor;
import java.util.Properties;

import eu.eurobotsim.world.GameMechanism;
import eu.eurobotsim.worlddef.WorldDef;

/**
 * The Simulation implementation is plugable. The SimulationFactory discovers
 * which implementation to use and instanciates one Simulation.
 * 
 * @author David Naramski
 * 
 */
public class SimulationFactory {

	/**
	 * Create a definition with the WorldDef. It will first look for a system
	 * property eu.eurobotsim.simulation.factory, it can be defined by
	 * System.setProperty("eu.eurobotsim.simulation.factory",*impl*); or
	 * -Deu.eurobotsim.simulation.factory=*impl*. If it doesn't find the
	 * property, the factory will look for a file
	 * "simulation_factory.properties" in the classpath. *impl* is the fully
	 * qualified name of the implementation of the Simulation.
	 * 
	 * @param worldDef
	 * @param gameMechanism
	 * @param properties
	 * @return
	 */
	public Simulation createSimulation(WorldDef worldDef,
			GameMechanism gameMechanism, Properties properties) {
		try {
			String factoryClass = null;
			String config = System
					.getProperty("eu.eurobotsim.simulation.factory");
			if (config != null) {
				factoryClass = config;
			} else {
				Properties props = null;
				if (properties == null) {
					props = new Properties();
					props.load(this.getClass().getResourceAsStream(
							"/simulation_factory.properties"));
				} else {
					props = properties;
				}
				factoryClass = props.getProperty("eu.eurobotsim.simulation.factory");
			}
			Class<?> c = Class.forName(factoryClass);
			Constructor<?> cons = c.getConstructor(WorldDef.class);
			Object instance = cons.newInstance(worldDef);
			Simulation world = new Simulation((PhysicalSimulation) instance,
					gameMechanism);
			return world;
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
