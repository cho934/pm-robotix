package sketcher.model;

import java.awt.Graphics2D;
import java.io.PrintWriter;

public interface Object2D {
    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom);

    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom);

    public void printSVG(PrintWriter pr);

    public int getMinX();

    public int getMinY();

    public int getMaxX();

    public int getMaxY();

    public int getDistanceSquared(int x1, int y1);

    public void setSelected(boolean b);
}
