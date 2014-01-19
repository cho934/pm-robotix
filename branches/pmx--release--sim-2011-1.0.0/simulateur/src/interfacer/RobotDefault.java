package interfacer;

import java.awt.Graphics;

import simulateur.ElementsManager;
import simulateur.Elements.GameElement;
import simulateur.Elements.Robot;
import various.Constants;

public class RobotDefault extends Robot {
	
	private int demiSquare = 150 ;

	public RobotDefault(int x, int y, ElementsManager e, String col) {
		super(x, y, e, col);
	}

	@Override
	public boolean amIThereImpl(int x, int y, int z) {
		boolean result = false ;
		return result;
	}

	@Override
	public boolean amIThereImpl(int x, int y) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean detectConflict(GameElement e, int x, int y) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void draw(Graphics g) {
		int[] xPoints = new int[4] ;
		int[] yPoints = new int[4] ;
		xPoints[0] = (int) ((X + getRelativePoint(demiSquare,demiSquare)[0])/3) ;
		yPoints[0] = (int) ((Y + getRelativePoint(demiSquare,demiSquare)[1])/3) ;
		xPoints[1] = (int) ((X + getRelativePoint(-demiSquare,demiSquare)[0])/3) ;
		yPoints[1] = (int) ((Y + getRelativePoint(-demiSquare,demiSquare)[1])/3) ;
		xPoints[2] = (int) ((X + getRelativePoint(-demiSquare,-demiSquare)[0])/3) ;
		yPoints[2] = (int) ((Y + getRelativePoint(-demiSquare,-demiSquare)[1])/3) ;
		xPoints[3] = (int) ((X + getRelativePoint(demiSquare,-demiSquare)[0])/3) ;
		yPoints[3] = (int) ((Y + getRelativePoint(demiSquare,-demiSquare)[1])/3) ;
		g.setColor(Constants.COL_ROBOT) ;
		g.fillPolygon(xPoints, yPoints, 4) ;
		if(color.equals(ROBOT_COLOR_BLUE)){
			g.setColor(Constants.COL_ROBOT_BLUE) ;
			g.fillOval((int)((X-40)/3), (int)((Y-40)/3), (int)(80/3), (int)(80/3)) ;
		}else{
			g.setColor(Constants.COL_ROBOT_RED) ;
			g.fillOval((int)((X-40)/3), (int)((Y-40)/3), (int)(80/3), (int)(80/3)) ;
		}
	}
	
	private int[] getRelativePoint(int x,int y){
		int[] result = new int[2] ;
		result[0] = (int) Math.round(x*(Math.cos(2*Math.PI*(angle/360.))) - y*(Math.sin(2*Math.PI*(angle/360.)))) ;
		result[1] = (int) Math.round(x*(Math.sin(2*Math.PI*(angle/360.))) + y*(Math.cos(2*Math.PI*(angle/360.)))) ;
		return result ;
	}

	@Override
	public void setShape() {
	}

}
