package sketcher;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Rectangle2D;

import javax.swing.JPanel;

import sketcher.model.Line;

public class SketcherRendererPanel extends JPanel {

    int zooms[] = new int[] { 1, 5, 10, 25, 50, 100, 150, 200 };
    private int zoomIndex = -1;
    private int zoom;
    // offset du coin en haut à gauche, en pixel
    private int offsetX = -200;
    private int offsetY = -500;
    private int GRID = 50;
    SketcherMainPanel sketcherMainPanel;

    SketcherRendererPanel(SketcherMainPanel sketcherMainPanel) {
        this.sketcherMainPanel = sketcherMainPanel;

        this.setBackground(Color.WHITE);
        UserInputHandler inputHandler = new UserInputHandler(this);
        this.addMouseListener(inputHandler);
        this.addMouseMotionListener(inputHandler);
        this.addMouseWheelListener(inputHandler);
        this.addKeyListener(inputHandler);
        this.setFocusable(true);

        this.requestFocus();
        this.setFocusCycleRoot(true);
        this.setZoomIndex(1);
    }

    @Override
    public boolean isFocusOwner() {
        return true;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        int width = this.getWidth();
        int height = this.getHeight();
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
        Color thinLineColor = new Color(230, 240, 240);
        Color crossColor = new Color(180, 210, 210);
        g.setColor(thinLineColor);
        int startX = -this.offsetX % GRID;
        int startY = -this.offsetY % GRID;
        // Lignes verticales
        for (int x = startX; x < width; x += GRID) {
            g.drawLine(x, 0, x, height);
        }
        // Lignes horizontales
        for (int y = startY; y < height; y += GRID) {
            g.drawLine(0, y, width, y);
        }

        //
        g.setColor(crossColor);
        int c = (zoomIndex % 3);
        int GRID_MARK = 2;
        if (c == 0) {
            GRID_MARK = 5;
        } else if (c == 2) {
            GRID_MARK = 10;
        }

        System.out.println("SketcherRendererPanel.paintComponent() z:" + zoom + " " + GRID_MARK);
        int startX2 = -this.offsetX % (GRID * GRID_MARK);
        int startY2 = -this.offsetY % (GRID * GRID_MARK);
        for (int x = startX2; x < width; x += GRID * GRID_MARK) {
            g.drawLine(x, 0, x, height);
        }

        for (int y = startY2; y < height; y += GRID * GRID_MARK) {
            g.drawLine(0, y, width, y);
        }

        g.setColor(crossColor);
        int h = 3;
        for (int x = startX; x < width; x += GRID) {
            for (int y = startY; y < height; y += GRID) {
                g.drawLine(x - h, y, x + h, y);
                g.drawLine(x, y - h, x, y + h);
            }
        }
        Sketch s = sketcherMainPanel.getSketch();
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        s.renderBackground(g2, offsetX, offsetY, zoom);
        s.render(g2, offsetX, offsetY, zoom);

        // Legend
        g2.setColor(Color.DARK_GRAY);
        int xLegend = 5;

        String str = String.valueOf(zoom * GRID);
        Rectangle2D rect = g2.getFontMetrics().getStringBounds(str, g2);
        int yLegend = this.getHeight() - 10;

        g2.drawString(str, 2 * xLegend - (int) ((rect.getWidth() - GRID)) / 2f, yLegend - 6);
        g2.drawLine(10, yLegend, 10 + GRID, yLegend);
        g2.drawLine(10, yLegend - 5, 10, yLegend);
        g2.drawLine(10 + GRID, yLegend - 5, 10 + GRID, yLegend);
    }

    public int getOffsetX() {
        return offsetX;
    }

    public int getOffsetY() {
        return offsetY;
    }

    public void setOffset(int newOffsetX, int newOffsetY) {
        if (newOffsetX != this.offsetX || newOffsetY != this.offsetY) {
            this.offsetX = newOffsetX;
            this.offsetY = newOffsetY;
            repaint();
        }
    }

    public SketcherMainPanel getSketcherMainPanel() {
        return sketcherMainPanel;
    }

    public int getModelX(int x) {
        return (x + offsetX) * zoom;
    }

    public int getModelY(int y) {
        return (y + offsetY) * zoom;
    }

    public int getModelDistance(int distance) {
        return distance * zoom;
    }

    /**
     * x: mouse position
     * */
    public int snapToGridX(int x) {
        int rx = -offsetX + GRID * Math.round((x + offsetX) / (GRID * 1f));
        return rx;
    }

    public int snapToGridY(int y) {
        int ry = -offsetY + GRID * Math.round((y + offsetY) / (GRID * 1f));
        return ry;
    }

    public int getZoom() {
        return zoom;
    }

    public void incrementZoom(int inc) {
        setZoomIndex(this.zoomIndex + inc);
    }

    private void setZoomIndex(int newZoomIndex) {
        System.out.println("SketcherRendererPanel.setZoomIndex()" + newZoomIndex);
        if (newZoomIndex < 0) {
            newZoomIndex = 0;
        } else if (newZoomIndex >= zooms.length) {
            newZoomIndex = zooms.length - 1;
        }
        if (this.zoomIndex != newZoomIndex) {
            this.zoomIndex = newZoomIndex;
            this.zoom = zooms[newZoomIndex];
            repaint();
        }

    }
}
