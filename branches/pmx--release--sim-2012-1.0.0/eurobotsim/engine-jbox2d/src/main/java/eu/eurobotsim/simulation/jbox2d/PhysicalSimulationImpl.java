package eu.eurobotsim.simulation.jbox2d;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.jbox2d.callbacks.ContactImpulse;
import org.jbox2d.callbacks.ContactListener;
import org.jbox2d.collision.AABB;
import org.jbox2d.collision.Manifold;
import org.jbox2d.common.Vec2;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.World;
import org.jbox2d.dynamics.contacts.Contact;

import eu.eurobotsim.avatar.Avatar;
import eu.eurobotsim.geom.BuildingBlock;
import eu.eurobotsim.geom.Circle;
import eu.eurobotsim.geom.Point;
import eu.eurobotsim.geom.Rectangle;
import eu.eurobotsim.geom.Representation;
import eu.eurobotsim.geom.Vec;
import eu.eurobotsim.robot.AvatarDef;
import eu.eurobotsim.robot.Psyche;
import eu.eurobotsim.simulation.PhysicalSimulation;
import eu.eurobotsim.simulation.SimulationView;
import eu.eurobotsim.simulation.jbox2d.view.DebugWorldView;
import eu.eurobotsim.worlddef.AvatarStartPosition;
import eu.eurobotsim.worlddef.WorldDef;

public class PhysicalSimulationImpl implements PhysicalSimulation {

	private World world;

	private List<AvatarImpl> avatars = new ArrayList<AvatarImpl>();

	private List<AvatarStartPosition> startPositions;

	public PhysicalSimulationImpl(WorldDef worldDef) {

		startPositions = new ArrayList<AvatarStartPosition>();
		startPositions.addAll(worldDef.getStartPositions());

		/* First we need to get the limits of the world */
		float left = 0, right = 0, top = 0, bottom = 0;
		for (BuildingBlock b : worldDef.getBlocks()) {
			if (b.getShape() instanceof Circle) {
				Circle c = (Circle) b.getShape();
				left = Math.min(left, c.getCenter().getX() - c.getRadius());
				right = Math.max(right, c.getCenter().getX() + c.getRadius());
				top = Math.min(top, c.getCenter().getY() - c.getRadius());
				bottom = Math.max(bottom, c.getCenter().getY() + c.getRadius());
			} else if (b.getShape() instanceof Rectangle) {
				Rectangle r = (Rectangle) b.getShape();
				left = Math.min(left, r.getCenter().getX() - r.getWidth() / 2);
				right = Math
						.max(right, r.getCenter().getX() + r.getWidth() / 2);
				top = Math.min(top, r.getCenter().getY() - r.getHeight() / 2);
				bottom = Math.max(bottom, r.getCenter().getY() + r.getHeight()
						/ 2);
			}
		}

		System.out.println("The world is contained in (" + left + "," + top
				+ ") (" + right + "," + bottom + ")");
		AABB env = new AABB();
		env.lowerBound.set(left / 1000, top / 1000);
		env.upperBound.set(right / 1000, bottom / 1000);

		Vec2 gravity = new Vec2(0.0f, 0.0f);
		world = new World(gravity, false);
		world.setContinuousPhysics(true);

		world.setContactListener(new ContactListener() {

			public void preSolve(Contact contact, Manifold oldManifold) {
			}

			public void postSolve(Contact contact, ContactImpulse impulse) {
			}

			public void endContact(Contact contact) {
				synchronized (avatars) {
					Iterator<AvatarImpl> a = avatars.iterator();
					while (a.hasNext())
						a.next().endContact(contact);
				}
			}

			public void beginContact(Contact contact) {
				synchronized (avatars) {
					Iterator<AvatarImpl> a = avatars.iterator();
					while (a.hasNext())
						a.next().beginContact(contact);
				}
			}
		});

		init(worldDef);
	}

	private void init(WorldDef worldDef) {

		List<BuildingBlock> blocks = worldDef.getBlocks();

		for (int i = 0; i < blocks.size(); i++) {
			BuildingBlockUtils.createFixture(world, blocks.get(i), new Point(0,
					0));
		}

	}

	public Avatar createAvatar(AvatarDef avatarDef, Psyche psyche) {
		AvatarStartPosition start = startPositions.remove(0);

		AvatarImpl impl = new AvatarImpl(psyche);
		impl.init(world, avatarDef, start);
		avatars.add(impl);
		return impl;
	}

	public List<Body> getBodyList() {
		List<Body> list = new ArrayList<Body>();
		Body body = world.getBodyList();
		while (body != null) {
			list.add(body);
			body = body.getNext();
		}
		return list;
	}

	public void step(float dt) {
		world.clearForces();
		world.step(dt, 10, 10);
		synchronized (avatars) {
			Iterator<AvatarImpl> a = avatars.iterator();
			while (a.hasNext()) {
				a.next().timeEllapsed(dt);
			}
		}
	}

	public World getWorld() {
		return world;
	}

	public List<Representation> getRepresentation() {
		List<Body> bodylist = getBodyList();
		List<Representation> list = new ArrayList<Representation>();
		for (Body b : bodylist) {
			Vec2 position = b.getPosition();
			Vec2 orientation = b.getWorldVector(new Vec2(1, 0));
			BuildingBlock block = (BuildingBlock) b.getUserData();
			Representation r = new Representation();
			r.setBlock(block);
			r.setPosition(new Point(position.x * 1000, position.y * 1000));
			r.setOrientation(new Vec(orientation.x, orientation.y));
			list.add(r);
		}
		return list;
	}

	@Override
	public SimulationView createDebugView(int width, int height, Rectangle view) {
		return new DebugWorldView(this, width, height, new Rectangle(
				new Point(view.getCenter().getX() / 1000, view.getCenter()
						.getY() / 1000), view.getWidth() / 1000,
				view.getHeight() / 1000));
	}

}
