package robot;

public class LogData {

    private long timeInMillis;
    private long lEncoder;
    private long rEncoder;
    private int lPower;
    private int rPower;
    private int order0;
    private int order1;
    private int current0;
    private int current1;
    private double x;
    private double y;
    private double theta;

    public LogData(long timeInMillis, long lEncoder, long rEncoder, int lPower, int rPower, int order0, int order1, int current0, int current1, double x, double y, double theta) {
        this.timeInMillis = timeInMillis;
        this.lEncoder = lEncoder;
        this.rEncoder = rEncoder;
        this.lPower = lPower;
        this.rPower = rPower;
        this.order0 = order0;
        this.order1 = order1;
        this.current0 = current0;
        this.current1 = current1;
        this.x = x;
        this.y = -y;
        this.theta = theta;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getTheta() {
        return theta;
    }

    public int getLeftPower() {
        return lPower;
    }

    public int getRightPower() {
        return rPower;
    }

    public int getOrder0() {
        return order0;
    }

    public int getOrder1() {
        return order1;
    }

    public int getCurrent0() {
        return current0;
    }

    public int getCurrent1() {
        return current1;
    }

    public long getTimeInMillis() {
        return timeInMillis;
    }
}
