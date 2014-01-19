package eu.eurobotsim.simulation.jbox2d;

import java.util.ArrayList;
import java.util.List;

import org.jbox2d.common.Vec2;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.Fixture;
import org.jbox2d.dynamics.World;
import org.jbox2d.dynamics.contacts.Contact;
import org.jbox2d.dynamics.joints.WeldJointDef;

import eu.eurobotsim.avatar.Action;
import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.avatar.GoForwardAction;
import eu.eurobotsim.avatar.ObjectInSensorEvent;
import eu.eurobotsim.avatar.RotateAction;
import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.PartType;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Vec;
import eu.eurobotsim.robot.AvatarDef;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.worlddef.AvatarStartPosition;

public class AvatarImpl implements Avatar {

	private Psyche psyche;

	private Fixture avatarBody;

	private float speed;

	private float angularVelocity;

	List<Fixture> fixtureList = new ArrayList<Fixture>();

	public AvatarImpl(Psyche psyche) {
		this.psyche = psyche;
	}

	public void init(World world, AvatarDef avatar, AvatarStartPosition start) {

		List<BuildingBlock> blocks = avatar.getBlocks();

		Fixture first = BuildingBlockUtils.createFixture(world, blocks.get(0),
				start.getPosition());
		fixtureList.add(first);

		Fixture lastFixture = first;
		for (int i = 1; i < blocks.size(); i++) {
			Fixture next = BuildingBlockUtils.createFixture(world,
					blocks.get(i), start.getPosition());
			fixtureList.add(next);

			WeldJointDef jointDef = new WeldJointDef();
			jointDef.initialize(lastFixture.getBody(), next.getBody(),
					lastFixture.getBody().getPosition());
			world.createJoint(jointDef);
			lastFixture = next;
		}

		avatarBody = first;
	}

	public void execute(Action action) {

		if (action instanceof GoForwardAction) {
			GoForwardAction a = (GoForwardAction) action;
			speed = a.getSpeed() / 1000;
		} else if (action instanceof RotateAction) {
			RotateAction a = (RotateAction) action;
			angularVelocity = a.getAngularVelocity();
		}

		update();

	}

	private void update() {
		Body b = avatarBody.getBody();
		Vec2 d = b.getWorldVector(new Vec2(1, 0));
		b.setLinearVelocity(d.mul(speed));
		b.setAngularVelocity(angularVelocity);
	}

	public Psyche getPsyche() {
		return psyche;
	}

	private BuildingBlock blockForFixture(Fixture fixture) {
		for (Fixture f : fixtureList) {
			if (f == fixture) {
				return (BuildingBlock) f.getBody().getUserData();
			}
		}
		return null;
	}

	private void signalContact(Contact contact, boolean begin) {
		BuildingBlock bA = blockForFixture(contact.m_fixtureA);
		BuildingBlock bB = blockForFixture(contact.m_fixtureB);
		if (bA != null && bA.getPartType() == PartType.SENSOR) {
			/*
			 * With this verification, we ensure to not detect collision with
			 * the robot himself
			 */
			if (bB == null) {
				psyche.signalEvent(this, new ObjectInSensorEvent(bA));
			}
		}
		if (bB != null && bB.getPartType() == PartType.SENSOR) {
			if (bA == null) {
				psyche.signalEvent(this, new ObjectInSensorEvent(bB));
			}
		}
	}

	public void beginContact(Contact contact) {
		signalContact(contact, true);
	}

	public void endContact(Contact contact) {
		signalContact(contact, false);
	}

	public void timeEllapsed(float millis) {
		getPsyche().timeEllapsed(millis);
		update();
	}

	public Point getPosition() {
		Vec2 p = avatarBody.getBody().getPosition();
		return new Point(p.x * 1000, p.y * 1000);
	}

	public Vec getDirection() {
		Vec2 v = avatarBody.getBody().getWorldVector(new Vec2(1, 0));
		return new Vec(v.x, v.y);
	}

}
