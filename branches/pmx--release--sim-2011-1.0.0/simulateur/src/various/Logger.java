package various;

public class Logger {
	
	private static Logger log ;
	
	private Logger(){
	}
	
	public static void log(RobotikException e){
		if(log==null){
			log = new Logger() ;
		}
		log.receive(e) ;
	}
	
	public static void log(String l){
		if(log==null){
			log = new Logger() ;
		}
		log.receive(l) ;
	}
	
	public void receive(RobotikException e){
		receive(e.toString()) ;
		e.printStackTrace() ;
	}
	
	public void receive(String l){
		Throwable t = new Throwable() ;
		display(t.getStackTrace()[2].getClassName()+" : "+l) ;
	}
	
	public void display(String l){
		if(Constants.SYSOUT){
			System.out.println(l) ;
		}
	}
}
