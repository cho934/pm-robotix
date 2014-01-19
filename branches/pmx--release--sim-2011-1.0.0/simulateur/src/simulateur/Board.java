package simulateur;

import java.awt.Color;
import java.awt.Graphics;

import various.Constants;

public class Board {
	
	public static final String ZONE_BLACK = "Black" ;
	public static final String ZONE_START_BLUE = "Start Blue" ;
	public static final String ZONE_START_RED = "Start Red" ;
	public static final String ZONE_GREEN = "Green" ;
	public static final String ZONE_BLUE = "Blue" ;
	public static final String ZONE_RED = "Red" ;
	public static final String ZONE_BLUE_BONUS = "Blue Bonus" ;
	public static final String ZONE_RED_BONUS = "Red Bonus" ;
	
	public Board(){
	}

	public void draw(Graphics g) {
		Color c = g.getColor() ;
		setRect(-10,-10,3020,2120,Constants.COL_BOARD_BLACK,g) ;
		setRect(0,0,400,400,Constants.COL_BOARD_RED,g) ;
		setRect(2600,0,400,400,Constants.COL_BOARD_BLUE,g) ;
		setRect(0,400,400,1700,Constants.COL_BOARD_GREEN,g) ;
		setRect(2600,400,400,1700,Constants.COL_BOARD_GREEN,g) ;
		setRect(400, 0, 50, 2100, Constants.COL_BOARD_BLACK, g) ;
		setRect(2550, 0, 50, 2100, Constants.COL_BOARD_BLACK, g) ;
		for(int i=0 ; i<3 ; i++){
			for(int j=0 ; j<3 ; j++){
				setRect(450+i*700,j*700,350,350,Constants.COL_BOARD_BLUE,g) ;
				setRect(450+i*700,350+j*700,350,350,Constants.COL_BOARD_RED,g) ;
				setRect(800+i*700,j*700,350,350,Constants.COL_BOARD_RED,g) ;
				setRect(800+i*700,350+j*700,350,350,Constants.COL_BOARD_BLUE,g) ;
			}
		}
		g.setColor(Constants.COL_BOARD_BLACK) ;
		g.fillOval((int)(925/3),(int)(475/3),(int)(100/3),(int)(100/3)) ;
		g.fillOval((int)(925/3),(int)(1175/3),(int)(100/3),(int)(100/3)) ;
		g.fillOval((int)(1275/3),(int)(1875/3),(int)(100/3),(int)(100/3)) ;
		g.fillOval((int)(1625/3),(int)(1875/3),(int)(100/3),(int)(100/3)) ;
		g.fillOval((int)(1975/3),(int)(1175/3),(int)(100/3),(int)(100/3)) ;
		g.fillOval((int)(1975/3),(int)(475/3),(int)(100/3),(int)(100/3)) ;
		g.setColor(c) ;
	}
	
	public String getZone(int x, int y){
		String result = "" ;
		if((x>=400 && x<450) || (x>=2550 && x<2600)){
			result = ZONE_BLACK ;
		}else{
			if(x<400 || x>=2600){
				if(y<400){
					if(x<400){
						result = ZONE_START_RED ;
					}else{
						result = ZONE_START_BLUE ;
					}
				}else{
					result = ZONE_GREEN ;
				}
			}else{
				int xx = (int)((x-450)/350) ;
				int yy = (int)(y/350) ;
				if(((int)((xx+yy)/2))*2 == xx+yy){
					result = ZONE_BLUE ;
				}else{
					result = ZONE_RED ;
				}
				if(xx==1 && yy==1){result = ZONE_BLUE_BONUS ;}
				if(xx==1 && yy==3){result = ZONE_BLUE_BONUS ;}
				if(xx==2 && yy==5){result = ZONE_RED_BONUS ;}
				if(xx==3 && yy==5){result = ZONE_BLUE_BONUS ;}
				if(xx==4 && yy==1){result = ZONE_RED_BONUS ;}
				if(xx==4 && yy==3){result = ZONE_RED_BONUS ;}
			}
		}
		return result ;
	}
	
	private void setRect(int x, int y, int xx, int yy, Color col, Graphics g){
		g.setColor(col) ;
		g.fillRect((int)(x/3),(int)(y/3),(int)(xx/3),(int)(yy/3)) ;
	}
	
}
