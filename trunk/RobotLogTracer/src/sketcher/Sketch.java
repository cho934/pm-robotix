package sketcher;

import java.awt.Graphics2D;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import sketcher.model.Object2D;

public class Sketch implements Object2D {
    private final List<Layer> layers = new ArrayList<Layer>();

    @Override
    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        for (Layer layer : layers) {
            layer.render(graphics, offsetX, offsetY, zoom);
        }

    }

    @Override
    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        for (Layer layer : layers) {
            layer.renderBackground(graphics, offsetX, offsetY, zoom);
        }

    }

    public void addLayer(Layer l) {
        this.layers.add(l);
    }

    public List<Layer> getLayers() {
        return layers;
    }

    public void saveAsSVG(File file) throws IOException {

        PrintWriter pr = new PrintWriter(file, "UTF-8");
        printSVG(pr);
        pr.flush();
        pr.close();
    }

    @Override
    public void printSVG(PrintWriter pr) {
        int w = this.getMaxX() - getMinX();
        int h = this.getMaxY() - getMinY();
        pr.println("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        pr.print("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"");
        pr.print(w);
        pr.print("\" height=\"");
        pr.print(h);
        pr.println("\">");
        pr.println("<title>Simple sketch</title>");
        for (Layer layer : layers) {
            layer.printSVG(pr);
        }
        pr.println("</svg>");

    }

    public int getMinX() {
        int min = Integer.MAX_VALUE;
        for (Layer layer : layers) {
            int m = layer.getMinX();
            if (m < min) {
                min = m;
            }
        }
        return min;
    }

    public int getMinY() {
        int min = Integer.MAX_VALUE;
        for (Layer layer : layers) {
            int m = layer.getMinY();
            if (m < min) {
                min = m;
            }
        }
        return min;
    }

    public int getMaxX() {
        int max = Integer.MIN_VALUE;
        for (Layer layer : layers) {
            int m = layer.getMaxX();
            if (m > max) {
                max = m;
            }
        }
        return max;
    }

    public int getMaxY() {
        int max = Integer.MIN_VALUE;
        for (Layer layer : layers) {
            int m = layer.getMaxY();
            if (m > max) {
                max = m;
            }
        }
        return max;
    }

    public List<Object2D> getNearestObjects(final int x1, final int y1, int maxDistance) {
        int maxSquared = maxDistance * maxDistance;
        List<Object2D> result = new ArrayList<Object2D>();
        List<Object2D> objs = new ArrayList<Object2D>();
        for (Layer layer : layers) {
            objs.addAll(layer.getAllObjects());
        }
        for (Object2D object2d : objs) {
            if (object2d.getDistanceSquared(x1, y1) < maxSquared) {
                result.add(object2d);
            }
        }
        Collections.sort(result, new Comparator<Object2D>() {

            @Override
            public int compare(Object2D o1, Object2D o2) {
                int d1 = o1.getDistanceSquared(x1, y1);
                int d2 = o2.getDistanceSquared(x1, y1);
                return d1 - d2;
            }
        });

        return result;
    }

    @Override
    public int getDistanceSquared(int x1, int y1) {
        int min = Integer.MAX_VALUE;
        for (Layer layer : layers) {
            int m = layer.getDistanceSquared(x1, y1);
            if (m < min) {
                min = m;
            }
        }
        return min;
    }

    @Override
    public void setSelected(boolean b) {
        // TODO Auto-generated method stub

    }
}
