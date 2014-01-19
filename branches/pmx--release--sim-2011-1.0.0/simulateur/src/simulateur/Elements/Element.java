package simulateur.Elements;

import java.awt.Graphics;

/**
 * Abstract class of any gameElement.
 * @author TriP
 *
 */
public abstract class Element {
	
	/**
	 * X position of the element center (mm)
	 */
	public int X ;
	
	/**
	 * Y position of the element center (mm)
	 */
	public int Y ;
	
	/**
	 * Z height of the element's base
	 */
	public int Z ;
	
	public int level = 0 ;
	
	/**
	 * Maximum high of the element
	 */
	public int hight ;
	
	/**
	 * Maximum distance of any point to the central axe
	 */
	public int cylinder ;
	
	public String type ;
	
	/**
	 * ABSTRACT CONSTRUCTOR Create a new Element, position it at it's initial place.
	 * @param x initial X position of the Element
	 * @param y initial Y position of the Element
	 */
	public Element(int x, int y){
		X = x ;
		Y = y ;
		Z = 0 ;
	}
	
	public String toString(){
		return toStringImpl() ;
	}
	
	/**
	 * Verify element's presence on the (x,y) given target, on the ground
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @return true if the element is present at the target spot on the ground
	 */
	public boolean amIThere(int x, int y){
		boolean result = false ;
		if(getCenterDistance(x,y) <= cylinder){
			result = amIThereImpl(x,y) ;
		}
		return result ;
	}
	
	/**
	 * Verify element's presence on the (x,y,z) given target
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @param z Z position of the target
	 * @return true if the element is present at the target spot
	 */
	public boolean amIThere(int x, int y, int z){
		boolean result = false ;
		if(z<=hight+Z && z>=Z){
			if(getCenterDistance(x,y) <= cylinder){
				result = amIThereImpl(x,y,z) ;
			}
		}
		return result ;
	}
	
	/**
	 * Get distance from the central axe
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @return distance
	 */
	public int getCenterDistance(int x, int y){
		return (int) getDistance(x,y,X,Y) ;
	}
	
	/**
	 * Get distance from the central axe
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @return distance
	 */
	public double getDistance(int x1, int y1, int x2, int y2){
		return Math.sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) ;
	}
	
	/**
	 * Complex implementation of the element's checking process
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @param z Z position of the target
	 * @return true if the element is present at the target spot
	 */
	public abstract boolean amIThereImpl(int x, int y, int z) ;
	
	/**
	 * Complex implementation of the element's checking process
	 * @param x X position of the target
	 * @param y Y position of the target
	 * @return true if the element is present at the target spot
	 */
	public abstract boolean amIThereImpl(int x, int y) ;
	
	/**
	 * setup the element's shape
	 */
	public abstract void setShape() ;
	
	public abstract void draw(Graphics g) ;
	
	public abstract String toStringImpl() ;
	
	public abstract boolean detectConflict(GameElement e, int x, int y) ;
	
}
