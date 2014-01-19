package eu.eurobotsim.simulation.jbox2d;

import org.jbox2d.collision.shapes.CircleShape;
import org.jbox2d.collision.shapes.PolygonShape;
import org.jbox2d.collision.shapes.Shape;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.BodyDef;
import org.jbox2d.dynamics.BodyType;
import org.jbox2d.dynamics.Fixture;
import org.jbox2d.dynamics.World;

import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;

public abstract class BuildingBlockUtils {

	static Fixture createFixture(World world, BuildingBlock block, Point point) {

		BodyDef def = new BodyDef();

		switch (block.getPartType()) {
		case ROBOT:
		case SENSOR:
			def.type = BodyType.DYNAMIC;
			def.allowSleep = false;
			break;
		case STATIC:
		default:
			def.type = BodyType.STATIC;
			break;
		}

		Shape shape = null;

		if (block.getShape() instanceof Circle) {
			Circle circle = (Circle) block.getShape();
			CircleShape s = new CircleShape();
			s.m_radius = circle.getRadius() / 1000;
			def.position.x = (circle.getCenter().getX() + point.getX()) / 1000;
			def.position.y = (circle.getCenter().getY() + point.getY()) / 1000;
			shape = s;
		} else if (block.getShape() instanceof Rectangle) {
			Rectangle rectangle = (Rectangle) block.getShape();
			PolygonShape s = new PolygonShape();
			s.setAsBox(rectangle.getWidth() / 2 / 1000,
					rectangle.getHeight() / 2 / 1000);
			def.position.x = (rectangle.getCenter().getX() + point.getX()) / 1000;
			def.position.y = (rectangle.getCenter().getY() + point.getY()) / 1000;
			shape = s;
		}

		Body body = world.createBody(def);
		body.setUserData(block);

		Fixture fixture = null;

		switch (block.getPartType()) {
		case ROBOT:
			body.m_mass = 0;
			body.m_torque = 0;
			body.m_angularDamping = 0;
			body.m_I = 0;
			body.m_invI = 0;
			body.m_invMass = 0;
			body.resetMassData();
			fixture = body.createFixture(shape, 1);
			body.setSleepingAllowed(false);
			break;
		case SENSOR:
			body.m_mass = 0;
			body.m_torque = 0;
			body.m_angularDamping = 0;
			body.m_I = 0;
			body.m_invI = 0;
			body.m_invMass = 0;
			body.resetMassData();
			fixture = body.createFixture(shape, 1);
			fixture.m_isSensor = true;
			break;
		case STATIC:
			fixture = body.createFixture(shape, 1);
			fixture.m_restitution = 1;
			break;
		default:
			break;
		}

		return fixture;
	}

}
