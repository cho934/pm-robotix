package simulateur.Elements;

import java.awt.Color;
import java.awt.Graphics;

import simulateur.ElementsManager;
import various.Constants;


/**
 * Pawn is the most numerous element of the table.
 * Height : 50 mm
 * Diameter : 200 mm
 * Plus : 2mm Chamfer on both sides of the pawn
 * 
 * @author TriP
 *
 */
public class Pawn extends GameElement {

	/**
	 * CONSTRUCTOR [PAWN] Create a new PAWN, position it at it's initial place.
	 * @param x initial X position of the Pawn
	 * @param y initial Y position of the Pawn
	 */
	public Pawn(int x, int y, ElementsManager e) {
		super(x,y,e);
		type = "PAWN" ;
	}

	@Override
	public int getShape(int z) {
		int result = 0 ;
		if(z>1 && z<49){result=100 ;}
		if(z==0){result=98 ;}
		if(z==1){result=99 ;}
		if(z==49){result=99 ;}
		if(z==50){result=98 ;}
		return result ;
	}

	@Override
	protected int getHight() {
		return 50;
	}
	
	public void drawElement(Graphics g) {
		Color c = g.getColor() ;
		g.setColor(Constants.COL_ELEMENT_PAWN) ;
		g.fillOval((int)((X-cylinder)/3), (int)((Y-cylinder)/3), (int)((2*cylinder)/3), (int)((2*cylinder)/3)) ;
		g.setColor(Constants.COL_ELEMENT_BLACK) ;
		g.drawOval((int)((X-cylinder)/3), (int)((Y-cylinder)/3), (int)((2*cylinder)/3), (int)((2*cylinder)/3)) ;
		g.setColor(c) ;
	}

}
