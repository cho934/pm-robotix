package simulateur;

import interfacer.RobotDefault;

import java.awt.Graphics;
import java.util.LinkedList;

import simulateur.Elements.* ;
import various.Constants;
import various.RobotikException;

public class ElementsManager {
	
	private Board t ;
	private Element[] elements ;
	private Robot robotBlue ;
	private Robot robotRed ;
	private GameElement selected ;
	
	public ElementsManager(){
		
		t = new Board() ;
		elements = new Element[23] ;
		InitialPosits posits = new InitialPosits(Constants.INITIAL_POSIT) ;
		
		elements[0] = new Pawn(posits.p01x, posits.p01y, this) ;
		elements[1] = new Pawn(posits.p02x, posits.p02y, this) ;
		elements[2] = new Pawn(posits.p03x, posits.p03y, this) ;
		elements[3] = new Pawn(posits.p04x, posits.p04y, this) ;
		elements[4] = new Pawn(posits.p05x, posits.p05y, this) ;
		
		elements[5] = new Pawn(posits.p06x, posits.p06y, this) ;
		elements[6] = new Pawn(posits.p07x, posits.p07y, this) ;
		elements[7] = new Pawn(posits.p08x, posits.p08y, this) ;
		elements[8] = new Pawn(posits.p09x, posits.p09y, this) ;
		elements[9] = new Pawn(posits.p10x, posits.p10y, this) ;
		
		elements[10] = new Pawn(posits.p11x, posits.p11y, this) ;
		elements[11] = new Pawn(posits.p12x, posits.p12y, this) ;
		elements[12] = new Pawn(posits.p13x, posits.p13y, this) ;
		elements[13] = new Pawn(posits.p14x, posits.p14y, this) ;
		elements[14] = new Pawn(posits.p15x, posits.p15y, this) ;
		
		elements[15] = new Queen(posits.q1x, posits.q1y, this) ;
		elements[16] = new Queen(posits.q2x, posits.q2y, this) ;
		
		elements[17] = new King(posits.k1x, posits.k1y, this) ;
		elements[18] = new King(posits.k2x, posits.k2y, this) ;
		
		elements[19] = new Border(200,400) ;
		elements[20] = new Border(2800,400) ;
		
		elements[21] = new Protect(800,1975) ;
		elements[22] = new Protect(2200,1975) ;
		
		robotBlue = new RobotDefault(200,200,this,Robot.ROBOT_COLOR_BLUE) ;
		robotBlue.angle = 10 ;
		robotRed = new RobotDefault(2800,200,this,Robot.ROBOT_COLOR_RED) ;
	}
	
	/**
	 * Get Pawn by index
	 * @param i Pawn index, must be between 1 and 15
	 * @return the Pawn
	 * @throws RobotikException when index out of range
	 */
	public Pawn getPawn(int i) throws RobotikException{
		if(i<1 || i>15){
			throw new RobotikException("You tried to get pawn n°"+i+", must be in [1-15]") ;
		}
		return (Pawn) getElement(i-1) ;
	}
	
	/**
	 * Get Queen by index
	 * @param i Queen index, must be 1 or 2
	 * @return the Queen
	 * @throws RobotikException when index out of range
	 */
	public Queen getQueen(int i) throws RobotikException{
		if(i<1 || i>2){
			throw new RobotikException("You tried to get queen n°"+i+", must be 1 or 2") ;
		}
		return (Queen) getElement(i+14) ;
	}
	
	/**
	 * Get King by index
	 * @param i King index, must be 1 or 2
	 * @return the King
	 * @throws RobotikException when index out of range
	 */
	public King getKing(int i) throws RobotikException{
		if(i<1 || i>2){
			throw new RobotikException("You tried to get king n°"+i+", must be 1 or 2") ;
		}
		return (King) getElement(i+16) ;
	}
	
	/**
	 * Get Border by index
	 * @param i Border index, must be 1 or 2
	 * @return the Border
	 * @throws RobotikException when index out of range
	 */
	public Border getBorder(int i) throws RobotikException{
		if(i<1 || i>2){
			throw new RobotikException("You tried to get border n°"+i+", must be 1 or 2") ;
		}
		return (Border) getElement(i+18) ;
	}
	
	/**
	 * Get Protect by index
	 * @param i Protect index, must be 1 or 2
	 * @return the Protect
	 * @throws RobotikException when index out of range
	 */
	public Protect getProtect(int i) throws RobotikException{
		if(i<1 || i>2){
			throw new RobotikException("You tried to get protect n°"+i+", must be 1 or 2") ;
		}
		return (Protect) getElement(i+20) ;
	}
	
	/**
	 * Get Element by index
	 * @param i Element index, must be between 1 and 22
	 * @return the Element
	 * @throws RobotikException when index out of range
	 */
	public Element getElement(int i)  throws RobotikException{
		if(i<1 || i>22){
			throw new RobotikException("You tried to get elemnt n°"+i+", must be between 1 and 22") ;
		}
		return elements[i] ;
	}
	
	public Element[] getElements(){
		return elements ;
	}
	
	/**
	 * Verify if the targeted position is empty or not.
	 * Very greedy process ==> optimize !!!
	 */
	public boolean empty(int x, int y, int z){
		boolean result = false ;
		int index = 1 ;
		while(!result && index<=22){
			try {
				if(getElement(index).amIThere(x, y, z)){
					result = true ;
				}
			} catch (RobotikException e) {
				//Logger.log(e) ;
			}
			index++ ;
		}
		return result ;
	}
	
	public Board getBoard(){
		return t ;
	}
	
	public LinkedList<GameElement> getGameElements(int x, int y){
		LinkedList<GameElement> result = new LinkedList<GameElement>() ;
		GameElement ge = null ;
		int level = -1 ;
		for(int k=0 ; k<19 ; k++){
			ge = (GameElement) elements[k] ;
			if(ge.amIThere(x, y)){
				if(ge.level > level){
					result.add(ge) ;
				}
			}
		}
		return result ;
	}
	
	public boolean isConflict(GameElement ge, int newX, int newY){
		boolean result = false ;
		if(newX<ge.cylinder || newX>3000-ge.cylinder || newY<ge.cylinder || newY>2100-ge.cylinder){
			result = true ;
		}else{
			for(Element g:elements){
				if(g!=ge && !result){
					if(g.getCenterDistance(newX,newY)<=g.cylinder+ge.cylinder){
						result = g.detectConflict(ge,newX,newY) ;
					}
				}
			}
		}
		return result ;
	}
	
	public void draw(Graphics g){
		t.draw(g) ;
		int indexL = 0 ;
		int rest = elements.length ;
		while(rest>0 && indexL<5){
			for(Element e:elements){
				if(e.level == indexL){
					e.draw(g) ;
					rest-- ;
				}
			}
			indexL++ ;
		}
		robotBlue.draw(g) ;
		robotRed.draw(g) ;
	}
	
	public String getZone(int x, int y){
		return t.getZone(x,y) ;
	}
	
	public void moveSelected(int x, int y){
		if(selected != null){
			selected.move(x,y) ;
		}
	}
	
	public void select(int x, int y){
		LinkedList<GameElement> ges = getGameElements(x, y) ;
		int maxLevel = -1 ;
		for(GameElement ge:ges){
			//Logger.log(ge.toString()) ;
			if(ge.level>maxLevel){
				selected = ge ;
				maxLevel = ge.level ;
				//Logger.log("Selected") ;
			}
		}
	}
	
	public void unselect(){
		selected = null ;
	}
	
	public int getPoints(String col){
		int points = 0 ;
		GameElement ge ;
		for(int k=0 ; k<19 ; k++){
			ge = (GameElement) elements[k] ;
			points += ge.getPoints(col) ;
		}
		return points ;
	}
	
	public String toString(){
		String result = "" ;
		for(Element e:elements){
			if(e instanceof GameElement) {
				result+=e.type+" X="+e.X+" Y="+e.Y+" Z="+e.Z ;
				GameElement ge = (GameElement) e;
				result+=" L="+ge.level+" "+ge.aura;
				if(ge.isSub){result+=" SUB" ;}
			}
			result+="\n" ;
		}
		return result ;
	}
	
	public GameElement selected(){
		return selected ;
	}
}
