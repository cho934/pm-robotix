package simulateur.Elements;

import java.awt.Color;
import java.awt.Graphics;

import simulateur.ElementsManager;
import various.Constants;


/**
 * King is composed on a pawn topped by an other cylinder (Pawn)
 * BASE
 * Height : 50 mm
 * Diameter : 200 mm
 * Plus : 2mm Chamfer on both sides of the pawn
 * TOP
 * Height : 180 mm
 * Diameter : 160 mm
 * Plus : located on the center of the base
 * 
 * @author TriP
 *
 */
public class King extends GameElement {

	/**
	 * CONSTRUCTOR [KING] Create a new KING, position it at it's initial place.
	 * @param x initial X position of the King
	 * @param y initial Y position of the King
	 */
	public King(int x, int y, ElementsManager e) {
		super(x,y,e);
		type = "KING" ;
	}

	@Override
	protected int getHight() {
		return 230;
	}

	@Override
	protected int getShape(int z) {
		int result = 0 ;
		if(z>1 && z<49){result=100 ;}
		if(z==0){result=98 ;}
		if(z==1){result=99 ;}
		if(z==49){result=99 ;}
		if(z==50){result=98 ;}
		if(z>50 && z<=230){result=80 ;}
		return result ;
	}

	@Override
	public void drawElement(Graphics g) {
		Color c = g.getColor() ;
		g.setColor(Constants.COL_ELEMENT_PAWN) ;
		g.fillOval((int)((X-cylinder)/3), (int)((Y-cylinder)/3), (int)((2*cylinder)/3), (int)((2*cylinder)/3)) ;
		g.setColor(Constants.COL_ELEMENT_KING) ;
		g.fillOval((int)((X-cylinder+25)/3), (int)((Y-cylinder+25)/3), (int)((2*cylinder-50)/3), (int)((2*cylinder-50)/3)) ;
		g.setColor(Constants.COL_ELEMENT_BLACK) ;
		g.drawOval((int)((X-cylinder)/3), (int)((Y-cylinder)/3), (int)((2*cylinder)/3), (int)((2*cylinder)/3)) ;
		g.setColor(c) ;
	}

}
