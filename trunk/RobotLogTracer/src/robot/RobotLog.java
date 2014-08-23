package robot;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import sketcher.Layer;
import sketcher.model.Line;

public class RobotLog {
    private static final String LEFT_RESOLUTION = "leftresolution:";
    private static final String RIGHT_RESOLUTION = "rightresolution:";
    private static final String ENCODER_DISTANCE = "encoderdistance:";
    private double leftResolution;
    private double rightResolution;
    private double encoderDistance;
    private List<LogData> logs = new ArrayList<LogData>();

    public RobotLog(File file) throws IOException {
        System.out.println("Reading log file " + file.getAbsolutePath());
        BufferedInputStream bufferedInputStream = new BufferedInputStream(new FileInputStream(file));
        parse(bufferedInputStream);
        bufferedInputStream.close();
    }

    private void parse(InputStream in) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(in, "UTF8"));
        String line = r.readLine();
        try {
            do {
                parseLine(line);
                line = r.readLine();
            } while (line != null);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
    private void parseLine(String line) {
        if (line.length() < 2) {
            return;
        }
        char c0 = line.charAt(0);
        if (c0 == '/') {
            return;
        }
        if (Character.isDigit(c0)) {
            String[] strs = line.split(",");
            if (strs.length < 8) {
                throw new IllegalArgumentException("Invalid line:" + line);
            }
            LogData l = new LogData(Long.parseLong(strs[0]), Long.parseLong(strs[1]), Long.parseLong(strs[2]), Integer.parseInt(strs[3]), Integer.parseInt(strs[4]), Integer.parseInt(strs[5]),
                    Integer.parseInt(strs[6]), Integer.parseInt(strs[7]), Integer.parseInt(strs[8]), Double.parseDouble(strs[9]), Double.parseDouble(strs[10]), Double.parseDouble(strs[11]));
            logs.add(l);
        } else {
            line = line.toLowerCase();
            if (line.startsWith(LEFT_RESOLUTION)) {
                String v = line.substring(LEFT_RESOLUTION.length());
                leftResolution = Double.parseDouble(v);
            } else if (line.startsWith(RIGHT_RESOLUTION)) {
                String v = line.substring(RIGHT_RESOLUTION.length());
                rightResolution = Double.parseDouble(v);
            } else if (line.startsWith(ENCODER_DISTANCE)) {
                String v = line.substring(ENCODER_DISTANCE.length());
                encoderDistance = Double.parseDouble(v);
            } else {
                throw new IllegalArgumentException("Invalid line:" + line);
            }
        }

    }

    public Layer createPathLayer() {
        Layer l = new Layer();
        int size = logs.size() - 1;
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            LogData log2 = this.logs.get(i + 1);
            l.add(new Line((int) (log1.getX() * 1000), (int) (log1.getY() * 1000), (int) (log2.getX() * 1000), (int) (log2.getY() * 1000)));
        }
        return l;
    }

    public List<Number> getTimeInMs() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getTimeInMillis());
        }
        return result;
    }

    public List<Number> getLeftPower() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getLeftPower());
        }
        return result;
    }

    public List<Number> getRightPower() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getRightPower());
        }
        return result;
    }

    public List<Number> getOrder0() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getOrder0());
        }
        return result;
    }

    public List<Number> getOrder1() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getOrder1());
        }
        return result;
    }

    public List<Number> getCurrent0() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getCurrent0());
        }
        return result;
    }

    public List<Number> getCurrent1() {
        List<Number> result = new ArrayList<Number>();
        int size = logs.size();
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            result.add(log1.getCurrent1());
        }
        return result;
    }

    public double getLeftResolution() {
        return leftResolution;
    }

    public double getRightResolution() {
        return rightResolution;
    }

    public double getEncoderDistance() {
        return encoderDistance;
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub

    }

    public List<Number> getSpeed() {

        List<Number> result = new ArrayList<Number>();
        result.add(0);
        int size = logs.size() - 1;
        for (int i = 0; i < size; i++) {
            LogData log1 = this.logs.get(i);
            LogData log2 = this.logs.get(i + 1);
            double dx = log2.getX() - log1.getX();
            double dy = log2.getY() - log1.getY();
            double l = Math.sqrt(dx * dx + dy * dy);
            double dT = log2.getTimeInMillis() - log1.getTimeInMillis();

            double v = 100000 * l / dT;
            System.out.println("l:" + l + " dt:" + dT + " v:" + v);
            result.add(v);
        }
        return result;

    }
}
