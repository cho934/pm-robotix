package simulateur.Elements;

import java.awt.Color;
import java.awt.Graphics;

import various.Constants;

public class Protect extends Element {
	
	private int demiWidth = 125 ;
	private int demiLength = 350 ;

	public Protect(int x, int y) {
		super(x, y);
		type = "PROTECT" ;
		hight = 70 ;
		setShape() ;
	}

	@Override
	public boolean amIThereImpl(int xx, int yy, int z) {
		boolean result = false;
		if(z<=hight){
			int x = Math.abs(X-xx) ;
			int y = Y-yy ;
			if(x<=demiLength && y<=demiWidth && y>=-demiWidth){
				if(y<=-5){
					result = true ;
				}else{
					if(x>=demiLength-20){
						result = true ;
					}
				}
			}
		}
		return result ;
	}
	
	@Override
	public boolean amIThereImpl(int xx, int yy) {
		boolean result = false;
		int x = Math.abs(X-xx) ;
		int y = Y-yy ;
		if(x<=demiLength && y<=demiWidth && y>=-demiWidth){
			if(y<=-5){
				result = true ;
			}else{
				if(x>=demiLength-20){
					result = true ;
				}
			}
		}
		return result ;
	}

	@Override
	public void setShape() {
		cylinder = (int) Math.sqrt(demiWidth*demiWidth + demiLength*demiLength) ;
	}
	
	public void draw(Graphics g) {
		Color c = g.getColor() ;
		g.setColor(Constants.COL_ELEMENT_PROTECT) ;
		g.fillRect((int)((X-demiLength)/3),(int)((Y+5)/3),(int)((2*demiLength)/3),(int)((120)/3));
		g.fillRect((int)((X-demiLength)/3),(int)((Y-125)/3),(int)((20)/3),(int)((150)/3));
		g.fillRect((int)((X+demiLength-20)/3),(int)((Y-125)/3),(int)((20)/3),(int)((150)/3));
		g.setColor(c) ;
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
