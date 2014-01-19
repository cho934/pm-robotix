package simulateur;

import java.util.Random;

import various.Logger;
import various.RobotikException;

public class Cards {
	
	public static final int ERROR = -1 ;
	public static final int PAWN = 0 ;
	public static final int QUEEN = 1 ;
	public static final int KING = 2 ;
	
	private int[] selected = {-1,-1,-1} ;
	private Random random ;
	
	public Cards(){
		random = new Random() ;
		try {
			selected[0] = getCard() ;
			selected[1] = getCard() ;
			selected[2] = getCard() ;
		} catch (RobotikException e) {
			Logger.log(e) ;
		}
	}
	
	public int[] getCard(int k){
		int[] result = new int[5] ;
		try {
			result = card(selected[k]) ;
		} catch (RobotikException e) {
			Logger.log(e) ;
		}
		return result ;
	}
	
	private int[] card(int k) throws RobotikException{
		int[] result = new int[]{ERROR,ERROR,ERROR,ERROR,ERROR} ;
		if(k==0){result = new int[] {QUEEN,KING,PAWN,PAWN,PAWN,} ;}
		if(k==1){result = new int[] {QUEEN,PAWN,KING,PAWN,PAWN,} ;}
		if(k==2){result = new int[] {QUEEN,PAWN,PAWN,KING,PAWN,} ;}
		if(k==3){result = new int[] {QUEEN,PAWN,PAWN,PAWN,KING} ;}
		if(k==4){result = new int[] {KING,QUEEN,PAWN,PAWN,PAWN,} ;}
		if(k==5){result = new int[] {PAWN,QUEEN,KING,PAWN,PAWN,} ;}
		if(k==6){result = new int[] {PAWN,QUEEN,PAWN,KING,PAWN,} ;}
		if(k==7){result = new int[] {PAWN,QUEEN,PAWN,PAWN,KING} ;}
		if(k==8){result = new int[] {KING,PAWN,QUEEN,PAWN,PAWN,} ;}
		if(k==9){result = new int[] {PAWN,KING,QUEEN,PAWN,PAWN,} ;}
		if(k==10){result = new int[] {PAWN,PAWN,QUEEN,KING,PAWN,} ;}
		if(k==11){result = new int[] {PAWN,PAWN,QUEEN,PAWN,KING} ;}
		if(k==12){result = new int[] {KING,PAWN,PAWN,QUEEN,PAWN,} ;}
		if(k==13){result = new int[] {PAWN,KING,PAWN,QUEEN,PAWN,} ;}
		if(k==14){result = new int[] {PAWN,PAWN,KING,QUEEN,PAWN,} ;}
		if(k==15){result = new int[] {PAWN,PAWN,PAWN,QUEEN,KING} ;}
		if(k==16){result = new int[] {KING,PAWN,PAWN,PAWN,QUEEN} ;}
		if(k==17){result = new int[] {PAWN,KING,PAWN,PAWN,QUEEN} ;}
		if(k==18){result = new int[] {PAWN,PAWN,KING,PAWN,QUEEN} ;}
		if(k==19){result = new int[] {PAWN,PAWN,PAWN,KING,QUEEN} ;}
		if(result[0]==ERROR){
			throw new RobotikException("This card doesn't exist : "+k);
		}
		return result ;
	}
	
	private int getCard() throws RobotikException{
		int result = -1 ;
		if(selected[2]==-1){
			while(contains(result)){
				result = random.nextInt(20) ;
			}
		}else{
			throw new RobotikException("Trying to get a 4th card. Selected : "+selected.toString()) ;
		}
		return result ;
	}
	
	private boolean contains(int k){
		boolean result = false ;
		if(selected[0]==k){result = true ;}
		if(selected[1]==k){result = true ;}
		if(selected[2]==k){result = true ;}
		return result ;
	}

}
