package sketcher;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import java.util.List;

import sketcher.model.Line;
import sketcher.model.Object2D;

public class UserInputHandler implements MouseListener, MouseMotionListener, KeyListener, MouseWheelListener {

    private SketcherRendererPanel panel;
    private int pressedX;
    private int pressedY;
    private int initialOffsetX;
    private int initialOffsetY;
    private SketcherToolBar toolbar;
    private Line object;
    private List<Object2D> selectedObjects = new ArrayList<Object2D>();
    private boolean[] pressed = new boolean[256];

    public UserInputHandler(SketcherRendererPanel sketcherRendererPanel) {
        this.panel = sketcherRendererPanel;
        this.toolbar = sketcherRendererPanel.getSketcherMainPanel().getTooBar();
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        int dx = pressedX - e.getX();
        int dy = pressedY - e.getY();
        System.out.println(e.getButton());
        if (toolbar.getMode() == SketcherToolBar.MODE_MOVE) {
            panel.setOffset(this.initialOffsetX + dx, this.initialOffsetY + dy);
        } else if (toolbar.getMode() == SketcherToolBar.MODE_DRAW) {
            int x2 = this.panel.getModelX(this.panel.snapToGridX(e.getX()));
            int y2 = this.panel.getModelY(this.panel.snapToGridY(e.getY()));
            this.object.setEnd(x2, y2);
            this.panel.repaint();
        }

    }

    @Override
    public void mouseMoved(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseClicked(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mousePressed(MouseEvent e) {
        panel.requestFocus();
        this.pressedX = e.getX();
        this.pressedY = e.getY();
        System.out.println("MousePressed" + e.getButton());
        if (e.getButton() == MouseEvent.BUTTON2) {
            toolbar.setMode(SketcherToolBar.MODE_MOVE);
        }
        // Mode handling
        if (toolbar.getMode() == SketcherToolBar.MODE_MOVE) {
            this.initialOffsetX = panel.getOffsetX();
            this.initialOffsetY = panel.getOffsetY();
        } else if (toolbar.getMode() == SketcherToolBar.MODE_DRAW) {
            int x1 = this.panel.getModelX(this.panel.snapToGridX(this.pressedX));
            int y1 = this.panel.getModelY(this.panel.snapToGridY(this.pressedY));

            this.object = new Line(x1, y1, x1, y1);
            this.object.setHighlight(true);
            this.panel.getSketcherMainPanel().getSketch().getLayers().get(0).add(object);
            this.panel.repaint();
        } else if (toolbar.getMode() == SketcherToolBar.MODE_SELECT) {
            int x1 = this.panel.getModelX(this.pressedX);
            int y1 = this.panel.getModelY(this.pressedY);
            int maxDistance = this.panel.getModelDistance(15);
            List<Object2D> list = this.panel.getSketcherMainPanel().getSketch().getNearestObjects(x1, y1, maxDistance);
            clearSelection();
            if (list.size() > 0) {

                addToSelection(list.get(0));
            }
            this.panel.repaint();
        }
    }

    private void addToSelection(Object2D obj) {
        if (!this.selectedObjects.contains(obj)) {
            ((Line) obj).setSelected(true);
            this.selectedObjects.add(obj);
        }
    }

    private void clearSelection() {
        for (Object2D obj : this.selectedObjects) {
            ((Line) obj).setSelected(false);
        }
        this.selectedObjects.clear();

    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON2) {
            toolbar.revertMode();
        }
        if (object != null) {
            this.object.setHighlight(false);
        }
        this.panel.repaint();

    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseExited(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void keyTyped(KeyEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void keyPressed(KeyEvent e) {
        System.out.println("Key presesd" + e.getKeyCode());
        if (e.getKeyCode() >= 0 && e.getKeyCode() < 256) {
            pressed[e.getKeyCode()] = true;
        }

    }

    @Override
    public void keyReleased(KeyEvent e) {
        System.out.println("Key released" + e.getKeyCode());
        if (e.getKeyCode() >= 0 && e.getKeyCode() < 256) {
            pressed[e.getKeyCode()] = false;
        }

    }

    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
       int i=e.getWheelRotation();
       panel.incrementZoom(i);
        
    }

}
