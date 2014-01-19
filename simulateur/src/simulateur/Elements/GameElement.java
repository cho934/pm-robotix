package simulateur.Elements;

import java.awt.Color;
import java.awt.Graphics;
import java.util.LinkedList;

import simulateur.Board;
import simulateur.ElementsManager;
import various.Constants;
import various.Logger;


public abstract class GameElement extends Element {
	
	/**
	 * profile of the cylinder element
	 */
	protected int[] profile ;
	
	public static final String POINT_BLUE = "B" ;
	public static final String POINT_RED = "R" ;
	public static final String POINT_BLUE_B = "BB" ;
	public static final String POINT_RED_B = "RR" ;
	public GameElement sub = null ;
	public String aura = "" ;
	public boolean isSub = false ;
	
	private ElementsManager em ;

	/**
	 * ABSTRACT CONSTRUCTOR Create a new Cylinder Element, position it at it's initial place.
	 * @param x initial X position of the CylinderElement
	 * @param y initial Y position of the CylinderElement
	 */
	public GameElement(int x, int y, ElementsManager e) {
		super(x, y);
		em = e ;
		setShape() ;
		checkPosition() ;
	}

	@Override
	public void setShape(){
		hight = getHight() ;
		cylinder = 0 ;
		int temp = 0 ;
		profile = new int[hight+1] ;
		for(int i = 0 ; i <= hight ; i++){
			temp = getShape(i) ;
			if(temp>cylinder){
				cylinder = temp ;
			}
			profile[i] = temp ;
		}
	}

	@Override
	public boolean amIThereImpl(int x, int y, int z) {
		return (getCenterDistance(x,y)<radius(z-Z)) ;
	}
	
	@Override
	public boolean amIThereImpl(int x, int y) {
		return (getCenterDistance(x,y)<cylinder) ;
	}
	
	/**
	 * Get radius of the element, at the specified height
	 * @param z height of the radius to get
	 * @return radius
	 */
	private int radius(int z){
		int radius = 0 ;
		if(z < profile.length){
			radius = profile[z] ;
		}
		return radius ;
	}


	/**
	 * Get height of the Element
	 * @return hight
	 */
	protected abstract int getHight() ;
	
	/**
	 * Get radius of the element for the specified height.
	 * This method has to return a correct value for each mm step between 0 and element's height
	 * @param i height (mm) of the targeted radius
	 * @return radius (mm)
	 */
	protected abstract int getShape(int z) ;
	
	public void draw(Graphics g){
		Color c = g.getColor() ;
		if(isComplete() && !isSub){
			g.setColor(Constants.COL_ELEMENT_WHITE) ;
			if(aura.equals(POINT_RED_B)){
				g.setColor(Constants.COL_ELEMENT_AURA_G) ;
				g.fillOval((int)((X-cylinder-15)/3), (int)((Y-cylinder-15)/3), (int)((2*cylinder+30)/3), (int)((2*cylinder+30)/3)) ;
			}
			if(aura.equals(POINT_RED) || aura.equals(POINT_RED_B)){
				g.setColor(Constants.COL_ELEMENT_AURA_R) ;
				g.fillOval((int)((X-cylinder-10)/3), (int)((Y-cylinder-10)/3), (int)((2*cylinder+20)/3), (int)((2*cylinder+20)/3)) ;
			}
			if(aura.equals(POINT_BLUE_B)){
				g.setColor(Constants.COL_ELEMENT_AURA_G) ;
				g.fillOval((int)((X-cylinder-15)/3), (int)((Y-cylinder-15)/3), (int)((2*cylinder+30)/3), (int)((2*cylinder+30)/3)) ;
			}
			if(aura.equals(POINT_BLUE) || aura.equals(POINT_BLUE_B)){
				g.setColor(Constants.COL_ELEMENT_AURA_B) ;
				g.fillOval((int)((X-cylinder-10)/3), (int)((Y-cylinder-10)/3), (int)((2*cylinder+20)/3), (int)((2*cylinder+20)/3)) ;
			}
			if(level==1){
				g.fillOval((int)((X-10)/3), (int)((Y+cylinder+10)/3), (int)(20/3), (int)(20/3)) ;
			}
			if(level==2){
				g.fillOval((int)((X-30)/3), (int)((Y+cylinder+10)/3), (int)(20/3), (int)(20/3)) ;
				g.fillOval((int)((X+10)/3), (int)((Y+cylinder+10)/3), (int)(20/3), (int)(20/3)) ;
			}
		}
		drawElement(g) ;
		g.setColor(c) ;
	}
	
	
	public boolean isComplete(){
		if(level==0){
			return true ;
		}else{
			if(sub==null){
				return false ;
			}else{
				return sub.isComplete() ;
			}
		}
	}
	
	public void checkPosition(){
		String posit1 = em.getZone(X+cylinder,Y) ;
		String posit2 = em.getZone(X-cylinder,Y) ;
		String posit3 = em.getZone(X,Y+cylinder) ;
		String posit4 = em.getZone(X,Y-cylinder) ;
		if(posit1.equals(posit2) && posit2.equals(posit3) && posit3.equals(posit4)){
			String Naura = aura ;
			boolean interesting = false ;
			if(posit1.equals(Board.ZONE_BLUE)){
				Naura = POINT_BLUE ;
				interesting = true ;
			}
			if(posit1.equals(Board.ZONE_BLUE_BONUS)){
				Naura = POINT_BLUE_B ;
				interesting = true ;
			}
			if(posit1.equals(Board.ZONE_RED)){
				Naura = POINT_RED ;
				interesting = true ;
			}
			if(posit1.equals(Board.ZONE_RED_BONUS)){
				Naura = POINT_RED_B ;
				interesting = true ;
			}
			if(!Naura.equals(aura) && interesting){
				//Logger.log("Element "+type+" on "+posit1) ;
				aura = Naura ;
			}
			if(!Naura.equals(aura)){
				//Logger.log("Element "+type+" on "+posit1) ;
			}
			if(interesting){
				aura = Naura ;
			}else{
				aura = "" ;
			}
		}else{
			if(!aura.equals("")){
				aura = "" ;
				if(type!=null){
					//Logger.log("Element "+type+" is no more a point") ;
				}
			}
		}
	}
	
	public void move(int x, int y){
		if(conflict(X+x,Y+y)){return ;}
		LinkedList<GameElement> geList = em.getGameElements(X+x,Y+y) ;
		for(GameElement ge:geList){
			if(ge.getCenterDistance(X,Y)<=10 && ge!=this){
				Logger.log("Detected : "+ge.toString()) ;
				if(ge.level==level-1 && !ge.isSub){
					ge.setSup(this) ;
				}
				if(ge.level==level+1 && ge.sub==null){
					setSup(ge) ;
				}
			}
		}
		if(!isSub){
			moveAndSub(X+x,Y+y) ;
		}
	}
	
	public void setSup(GameElement ge){
		if(ge.sub==null){
			Logger.log("setSup:"+toString()+"\nsub:"+ge.toString()) ;
			ge.sub = this ;
			isSub = true ;
			em.select(X,Y) ;
		}
	}
	
	public boolean conflict(int x, int y){
		boolean result = em.isConflict(this,x,y) ;
		if(sub!=null && !result){
			result = sub.conflict(x,y) ;
		}
		return result ;
	}
	
	public void moveAndSub(int x, int y){
		X = x ;
		Y = y ;
		if(sub != null){
			sub.moveAndSub(X,Y) ;
		}
		checkPosition() ;
	}
	
	public void upper(){
		if(level<2){
			level++ ;
			Z = level*50 ;
			sub = null ;
			isSub = false ;
		}
	}
	
	public void lower(){
		if(level>0 && sub==null){
			level-- ;
			Z = level*50 ;
			isSub = false ;
		}
	}
	
	public int getPoints(String col){
		int points = 0 ;
		if(!isSub  && isComplete()){
			if(col.equals("RED")){
				if(aura.equals(POINT_RED) || aura.equals(POINT_RED_B)){
					if(type.equals("PAWN")){
						points = 10 ;
					}
					if(type.equals("QUEEN")){
						points = 20*(level+1) ;
					}
					if(type.equals("KING")){
						points = 30*(level+1) ;
					}
				}
				if(aura.equals(POINT_RED_B)){
					points += 30 ;
				}
			}else{
				if(aura.equals(POINT_BLUE) || aura.equals(POINT_BLUE_B)){
					if(type.equals("PAWN")){
						points = 10 ;
					}
					if(type.equals("QUEEN")){
						points = 20*(level+1) ;
					}
					if(type.equals("KING")){
						points = 30*(level+1) ;
					}
				}
				if(aura.equals(POINT_RED_B)){
					points += 30 ;
				}
			}
		}
		return points ;
	}
	
	@Override
	public String toStringImpl() {
		String result = "GameElement("+type+")" ;
		result += "\nPosit : X="+X+" Y="+Y ;
		result += "\nLevel="+level ;
		if(isComplete()){result += " [Complete Tower]" ;}
		if(sub!=null){result+=sub.toString() ;}
		return result;
	}
	
	@Override
	public boolean detectConflict(GameElement ge, int newX, int newY){
		boolean result = false ;
		if(level==ge.level){
			if(getCenterDistance(newX,newY)<(cylinder+ge.cylinder)){
				result = true ;
			}
		}
		return result ;
	}
	
	public abstract void drawElement(Graphics g) ;
}
