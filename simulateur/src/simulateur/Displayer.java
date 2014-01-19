package simulateur;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JTextArea;

public class Displayer extends Canvas{
	private static final long serialVersionUID = -4872652025549356306L;
	
	JFrame main ;
	JFrame infos ;
	JTextArea text ;
	ElementsManager em ;
	
	public Displayer(){
		em = new ElementsManager() ;
		// Main window creation
		main = new JFrame("PMX-ROBOTIX Simulator") ;
		main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
		main.setPreferredSize(new Dimension(1005,733)) ;
		main.setLocation(20,20) ;
		main.setResizable(false) ;
		Mouse mouse = new Mouse(this) ;
		addMouseListener(mouse) ;
		addMouseMotionListener(mouse) ;
		main.getContentPane().add(this) ;
		main.pack() ;
		main.setVisible(true) ;
		
		// Infos window creation
		infos = new JFrame("PMX-ROBOTIX Infos") ;
		infos.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
		infos.setPreferredSize(new Dimension(400,733)) ;
		text = new JTextArea() ;
		text.setText("EORGJORZEG") ;
		text.setEditable(false) ;
		infos.add(text) ;
		infos.setLocation(1045,20) ;
		infos.pack() ;
		infos.setVisible(true) ;
	}
	
	public void setInfoText(String s){
		text.setText(s) ;
	}
	
	public void updateInfos(){
		String toDisplay = " -- Main Infos --\n" ;
		toDisplay += "RED  Points : "+getPoints("RED")+"\n" ;
		toDisplay += "BLUE Points : "+getPoints("BLUE")+"\n" ;
		toDisplay += " -- GameElements --\n" ;
		toDisplay += em.toString() ;
		setInfoText(toDisplay) ;
	}
	
	public void paint(Graphics g){
		em.draw(g) ;
		updateInfos() ;
		main.repaint() ;
	}
	
	public String getZone(int x, int y){
		return em.getBoard().getZone(x*3,y*3) ;
	}
	
	public int getPoints(String col){
		return em.getPoints(col) ;
	}

}
