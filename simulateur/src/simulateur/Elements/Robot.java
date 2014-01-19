package simulateur.Elements;

import simulateur.ElementsManager;

public abstract class Robot extends Element {
	
	public static final String ROBOT_COLOR_BLUE = "BLUE" ;
	public static final String ROBOT_COLOR_RED = "RED" ;
	
	private ElementsManager em ;
	public String type = "Not Initialized" ;
	public String color ;
	public int angle = 0 ;

	public Robot(int x, int y, ElementsManager e, String col) {
		super(x, y) ;
		color = col ;
		em = e ;
	}

	@Override
	public String toStringImpl() {
		String result = color+" ROBOT" ;
		return result ;
	}

}
