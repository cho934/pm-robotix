package simulateur;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

class Mouse extends MouseAdapter{
	
	private Displayer displayer ;
	private int mX,mY ;
	
	public Mouse(Displayer d){
		super() ;
		displayer = d ;
	}
	
    public void mousePressed(MouseEvent e) {
    	// Start element grabbing
    	mX = e.getX() ;
    	mY = e.getY() ;
    	displayer.em.select(e.getX()*3,e.getY()*3) ;
    	//Logger.log("press") ;
    	/*
      if (ellipse.contains(e.getX(), e.getY())) {
        selectedShape = ellipse;
        if (boundingRec != null)
          boundingRec = ellipse.getBounds2D();
        displayParameters(selectedShape);
      } else { 
        boundingRec = null;
        location.setText("");
      }
      canvas.repaint();
      x1 = e.getX();
      y1 = e.getY();
      */
    }
    public void mouseReleased(MouseEvent e) {
    	// Stop grabbing element
    	displayer.em.unselect() ;
    	//Logger.log("release") ;
    	/*
      if (ellipse.contains(e.getX(), e.getY())) {
        boundingRec = ellipse.getBounds2D();
        selectedShape = ellipse;

        displayParameters(selectedShape);
      }
      canvas.repaint();
      */
    }

    public void mouseClicked(MouseEvent e) {
    	displayer.em.select(e.getX()*3,e.getY()*3) ;
    	if(displayer.em.selected() != null){
    		if(e.getClickCount()==2 && e.getButton()==MouseEvent.BUTTON1){
    			displayer.em.selected().upper() ;
    		}
    		if(e.getClickCount()==2 && e.getButton()==MouseEvent.BUTTON3){
    			displayer.em.selected().lower() ;
    		}
    	}
    	/*
      if (ellipse.contains(e.getX(), e.getY())) {
        selectedShape = ellipse;
        boundingRec = ellipse.getBounds2D();

        displayParameters(selectedShape);
      } else {
        if (boundingRec != null)
          boundingRec = null;
        location.setText("");
      }
      canvas.repaint();
      */
    }
    	
    public void mouseDragged(MouseEvent e) {
    	int x = e.getX() ;
    	int y = e.getY() ;
    	displayer.em.moveSelected((x-mX)*3,(y-mY)*3) ;
    	mX = x ;
    	mY = y ;
    	displayer.repaint() ;
    	//Logger.log("drag") ;
       	/*
    	if (ellipse.contains(e.getX(), e.getY())) {
			boundingRec = null;
			selectedShape = ellipse;
            x2 = e.getX();
            y2 = e.getY();
            x = x + x2 - x1;
            y = y + y2 - y1;
            x1 = x2;
            y1 = y2;
          }
          if (selectedShape != null)
            displayParameters(selectedShape);
          canvas.repaint();
          */
    }

    public void mouseMoved(MouseEvent e) {
    	//Logger.log("move") ;
        	/*
          if (ellipse != null) { 
            if (ellipse.contains(e.getX(), e.getY())) {
              curCursor = Cursor
                  .getPredefinedCursor(Cursor.HAND_CURSOR);
            } else {
              curCursor = Cursor.getDefaultCursor();
            }
          }
          canvas.repaint();
          */
    }
}
