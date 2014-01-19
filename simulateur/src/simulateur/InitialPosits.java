package simulateur;

public class InitialPosits {
	
	public static final int RANDOM = 0 ;
	public static final int POSIT1 = 1 ;
	
	// Default posit 1
	public int[] P1_green = {Cards.PAWN,Cards.KING,Cards.PAWN,Cards.QUEEN,Cards.PAWN} ;
	public int[] P1_line1 = {Cards.KING,Cards.PAWN,Cards.PAWN,Cards.PAWN,Cards.QUEEN} ;
	public int[] P1_line2 = {Cards.PAWN,Cards.QUEEN,Cards.PAWN,Cards.KING,Cards.PAWN} ;
	
	// PAWNS Positions
	public int p01x=200, p02x=200, p03x=200, p04x=800, p05x=800 ;
	public int p01y, p02y, p03y, p04y, p05y ;
	public int p06x=1150, p07x=1150, p08x=1500, p09x=1850, p10x=1850 ;
	public int p06y, p07y, p08y=1050, p09y, p10y ;
	public int p11x=2200, p12x=2200, p13x=2800, p14x=2800, p15x=2800 ;
	public int p11y, p12y, p13y, p14y, p15y ;
	
	// QUEENS Positions
	public int q1x=200, q2x=2800 ;
	public int q1y, q2y ;
	
	// KINGS Positions
	public int k1x=200, k2x=2800 ;
	public int k1y, k2y ;
	
	public InitialPosits(int method){
		if(method==RANDOM){
			setRandom() ;
		}
		if(method==POSIT1){
			setPosit1() ;
		}
	}
	
	private void setRandom(){
		Cards cards = new Cards() ;
		setGreen(cards.getCard(0)) ;
		setLine1(cards.getCard(1)) ;
		setLine2(cards.getCard(2)) ;
	}
	
	private void setLine1(int[] card){
		int y = 350 ;
		for(int k=0 ; k<5 ; k++){
			if(card[k]==Cards.KING){
				p04y = y ;
				p12y = y ;
			}
			if(card[k]==Cards.QUEEN){
				p05y = y ;
				p11y = y ;
			}
			y += 350 ;
		}
	}
	
	private void setLine2(int[] card){
		int y = 350 ;
		for(int k=0 ; k<5 ; k++){
			if(card[k]==Cards.KING){
				p06y = y ;
				p10y = y ;
			}
			if(card[k]==Cards.QUEEN){
				p07y = y ;
				p09y = y ;
			}
			y += 350 ;
		}
	}
	
	private void setGreen(int[] card){
		int y = 690 ;
		int index = 1 ;
		for(int k=0 ; k<5 ; k++){
			if(card[k]==Cards.KING){
				k1y = y ;
				k2y = y ;
			}
			if(card[k]==Cards.QUEEN){
				q1y = y ;
				q2y = y ;
			}
			if(card[k]==Cards.PAWN){
				if(index==3){
					p03y = y ;
					p13y = y ;
				}
				if(index==2){
					p02y = y ;
					p14y = y ;
					index = 3 ;
				}
				if(index==1){
					p01y = y ;
					p15y = y ;
					index = 2 ;
				}
			}
			y += 280 ;
		}
	}
	
	private void setPosit1(){
		setGreen(P1_green) ;
		setLine1(P1_line1) ;
		setLine2(P1_line2) ;
	}
}