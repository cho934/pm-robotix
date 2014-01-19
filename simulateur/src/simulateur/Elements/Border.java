package simulateur.Elements;

import java.awt.Color;
import java.awt.Graphics;
import various.Constants;

public class Border extends Element {
	
	private int demiWidth = 11 ;
	private int demiLength = 200 ;

	public Border(int x, int y) {
		super(x, y);
		type = "BORDER" ;
		hight = 70 ;
		setShape() ;
	}

	@Override
	public boolean amIThereImpl(int x, int y, int z) {
		boolean result = false ;
		if(z<hight){
			if(Math.abs(x-X)<demiLength){
				if(Math.abs(y-Y)<demiWidth){
					result = true ;
				}
			}
		}
		return result;
	}
	
	@Override
	public boolean amIThereImpl(int x, int y) {
		boolean result = false ;
		if(Math.abs(x-X)<demiLength){
			if(Math.abs(y-Y)<demiWidth){
				result = true ;
			}
		}
		return result;
	}

	@Override
	public void setShape() {
		cylinder = (int) Math.sqrt(demiWidth*demiWidth + demiLength*demiLength) ;
	}

	@Override
	public void draw(Graphics g) {
		Color c = g.getColor();
		g.setColor(Constants.COL_ELEMENT_BORDER);
		g.fillRect((int)((X-demiLength)/3),(int)((Y-demiWidth)/3),(int)((2*demiLength)/3),(int)((2*demiWidth)/3));
		g.setColor(c);
	}
	
	@Override
	public boolean detectConflict(GameElement ge, int newX, int newY){
		boolean result = false ;
		int grad = 0 ;
		while(!result && grad<360){
			int x = newX + (int) Math.round((ge.cylinder)*(Math.cos(2*Math.PI*(grad/360.)))) ;
			int y = newY + (int) Math.round((ge.cylinder)*(Math.sin(2*Math.PI*(grad/360.)))) ;
			if(!result){result = amIThere(x,y,ge.Z) ;}
			if(!result){result = amIThere(x,y,ge.Z+50) ;}
			grad += 5 ;
		}
		return result ;
	}

	@Override
	public String toStringImpl() {
		return type;
	}

}
