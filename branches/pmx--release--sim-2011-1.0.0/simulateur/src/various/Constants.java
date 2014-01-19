package various;

import java.awt.Color;

import simulateur.InitialPosits;

public final class Constants {
	
	// Debug settings
	public static final boolean SYSOUT = true ;
	
	// Initial position of game elements
	public static final int INITIAL_POSIT = InitialPosits.RANDOM ;
	
	// Colors
	// Board
	public static final Color COL_BOARD_BLACK = new Color(0,0,0) ;
	public static final Color COL_BOARD_RED = new Color(100,0,0) ;
	public static final Color COL_BOARD_BLUE = new Color(0,0,100) ;
	public static final Color COL_BOARD_GREEN = new Color(0,100,0) ;
	// Elements
	public static final Color COL_ELEMENT_PROTECT = new Color(200,200,110) ;
	public static final Color COL_ELEMENT_BORDER = new Color(200,200,110) ;
	public static final Color COL_ELEMENT_PAWN = new Color(180,180,0) ;
	public static final Color COL_ELEMENT_QUEEN = new Color(255,255,255) ;
	public static final Color COL_ELEMENT_KING = new Color(0,0,0) ;
	public static final Color COL_ELEMENT_AURA_G = new Color(255,255,0) ;
	public static final Color COL_ELEMENT_AURA_R = new Color(255,0,0) ;
	public static final Color COL_ELEMENT_AURA_B = new Color(0,200,255) ;
	public static final Color COL_ELEMENT_WHITE = new Color(255,255,255) ;
	public static final Color COL_ELEMENT_BLACK = new Color(0,0,0) ;
	// Robots
	public static final Color COL_ROBOT = new Color(100,100,100) ;
	public static final Color COL_ROBOT_RED = new Color(255,0,0) ;
	public static final Color COL_ROBOT_BLUE = new Color(0,0,255) ;
}
