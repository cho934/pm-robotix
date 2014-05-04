package sketcher;

import java.awt.Graphics2D;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import sketcher.model.Object2D;

public class Layer implements Object2D {
    private final List<Object2D> objects = new ArrayList<Object2D>();

    @Override
    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        for (Object2D obj : objects) {
            obj.render(graphics, offsetX, offsetY, zoom);
        }

    }

    @Override
    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        for (Object2D obj : objects) {
            obj.renderBackground(graphics, offsetX, offsetY, zoom);
        }

    }

    public void add(Object2D obj) {
        objects.add(obj);

    }

    @Override
    public void printSVG(PrintWriter pr) {
        for (Object2D layer : objects) {
            layer.printSVG(pr);
        }

    }

    public int getMinX() {
        int min = Integer.MAX_VALUE;
        for (Object2D obj : objects) {
            int m = obj.getMinX();
            if (m < min) {
                min = m;
            }
        }
        return min;
    }

    public int getMinY() {
        int min = Integer.MAX_VALUE;
        for (Object2D obj : objects) {
            int m = obj.getMinY();
            if (m < min) {
                min = m;
            }
        }
        return min;
    }

    public int getMaxX() {
        int max = Integer.MIN_VALUE;
        for (Object2D obj : objects) {
            int m = obj.getMaxX();
            if (m > max) {
                max = m;
            }
        }
        return max;
    }

    public int getMaxY() {
        int max = Integer.MIN_VALUE;
        for (Object2D obj : objects) {
            int m = obj.getMaxY();
            if (m > max) {
                max = m;
            }
        }
        return max;
    }

    public List<Object2D> getAllObjects() {
        return objects;
    }

    @Override
    public int getDistanceSquared(int x1, int y1) {
        // FIXME:
        return Integer.MAX_VALUE;
    }

    @Override
    public void setSelected(boolean b) {
        // TODO Auto-generated method stub

    }

}
