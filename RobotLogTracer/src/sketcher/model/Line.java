package sketcher.model;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.io.PrintWriter;

public class Line implements Object2D {
    int x1, y1, x2, y2; // en mm
    Color color = Color.BLACK;
    private boolean highlight;
    private boolean selected;

    public Line(int x1, int y1, int x2, int y2) {
        super();
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
      System.out.println("Line "+x1+","+y1+" ->"+x2+","+y2);
    }

    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        int x1OnScreen = (x1) / zoom - offsetX;
        int y1OnScreen = (y1) / zoom - offsetY;
        int x2OnScreen = (x2) / zoom - offsetX;
        int y2OnScreen = (y2) / zoom - offsetY;

        if (selected) {
            graphics.setColor(new Color(255, 255, 128, 168));
            graphics.setStroke(new BasicStroke(6, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
            graphics.drawLine(x1OnScreen, y1OnScreen, x2OnScreen, y2OnScreen);
        }
        if (highlight) {
            int radius = 6;
            graphics.setColor(new Color(230, 170, 170, 128));
            graphics.fillOval(x1OnScreen - radius, y1OnScreen - radius, radius * 2, radius * 2);
            if (x1OnScreen != x2OnScreen || y1OnScreen != y2OnScreen) {
                graphics.fillOval(x2OnScreen - radius, y2OnScreen - radius, radius * 2, radius * 2);
            }
        }
    }

    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom) {

        int x1OnScreen = (x1) / zoom - offsetX;
        int y1OnScreen = (y1) / zoom - offsetY;
        int x2OnScreen = (x2) / zoom - offsetX;
        int y2OnScreen = (y2) / zoom - offsetY;

        graphics.setColor(color);
        graphics.setStroke(new BasicStroke(1));
        graphics.drawLine(x1OnScreen, y1OnScreen, x2OnScreen, y2OnScreen);

        if (x1OnScreen == x2OnScreen && y1OnScreen == y2OnScreen) {
            int radius = 3;
            graphics.drawLine(x1OnScreen - radius, y1OnScreen, x2OnScreen + radius, y2OnScreen);
            graphics.drawLine(x1OnScreen, y1OnScreen - radius, x2OnScreen, y2OnScreen + radius);
        }
        System.out.println("Line "+x1OnScreen+","+y1OnScreen+" ->"+x2OnScreen+","+y2OnScreen);
    }

    public void setEnd(int x, int y) {
        this.x2 = x;
        this.y2 = y;
    }

    public void setHighlight(boolean b) {
        this.highlight = b;

    }

    @Override
    public void printSVG(PrintWriter pr) {
        pr.print("<line x1=\"");
        pr.print(x1);
        pr.print("\" y1=\"");
        pr.print(y1);
        pr.print("\" x2=\"");
        pr.print(x2);
        pr.print("\" y2=\"");
        pr.print(y2);
        pr.println("\" stroke=\"black\" />");
    }

    @Override
    public int getMinX() {
        return Math.min(x1, x2);
    }

    @Override
    public int getMinY() {
        return Math.min(y1, y2);
    }

    @Override
    public int getMaxX() {
        return Math.max(x1, x2);
    }

    @Override
    public int getMaxY() {
        return Math.max(y1, y2);
    }

    @Override
    public int getDistanceSquared(int x, int y) {

        int dx = x1 - x2;
        int dy = y1 - y2;
        int lenSquared = dx * dx + dy * dy;

        if (lenSquared == 0) {
            // the line is a point
            int d1x = x1 - x;
            int d1y = y1 - y;
            return d1x * d1x - d1y * d1y;
        }

        int px2 = x2 - x1;
        int py2 = y2 - y1;
        int px = x - x1;
        int py = y - y1;
        double dotprod = px * px2 + py * py2;
        // dotprod is the length of the px,py vector
        // projected on the x1,y1=>x2,y2 vector times the
        // length of the x1,y1=>x2,y2 vector
        double projlenSq = dotprod * dotprod / (px2 * px2 + py2 * py2);
        if (projlenSq < 0) {
            // Distance to x1
            int d1x = x1 - x;
            int d1y = y1 - y;
            return d1x * d1x - d1y * d1y;

        } else if (projlenSq > lenSquared) {
            // Distance to x1
            int d2x = x2 - x;
            int d2y = y2 - y;
            return d2x * d2x - d2y * d2y;
        } else {
            // Distance to line is now the length of the relative point
            // vector minus the length of its projection onto the line
            double lenSq = px * px + py * py - projlenSq;
            if (lenSq < 0) {
                lenSq = 0;
            }
            return (int) Math.round(lenSq);
        }

    }

    @Override
    public void setSelected(boolean b) {
        this.selected = b;

    }
}
