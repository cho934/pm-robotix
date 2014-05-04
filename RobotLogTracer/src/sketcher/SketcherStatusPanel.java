package sketcher;

import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class SketcherStatusPanel extends JPanel implements MouseListener, MouseMotionListener {

    private SketcherMainPanel sketcherMainPanel;
    private JLabel label = new JLabel("");

    public SketcherStatusPanel(SketcherMainPanel sketcherMainPanel) {
        this.sketcherMainPanel = sketcherMainPanel;
        this.sketcherMainPanel.getRendererPanel().addMouseMotionListener(this);
        this.setLayout(new GridLayout(1, 1));
        this.add(label);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mousePressed(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseReleased(MouseEvent e) {
        // TODO Auto-generated method stub

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
    public void mouseDragged(MouseEvent e) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseMoved(MouseEvent e) {
        int z = this.sketcherMainPanel.getRendererPanel().getZoom();
        int x = this.sketcherMainPanel.getRendererPanel().getModelX(e.getX());
        int y = this.sketcherMainPanel.getRendererPanel().getModelY(e.getY());
        setStatus("Zoom: " + z + " Location: " + x + "," + y);

    }

    void setStatus(String status) {
        this.label.setText(status);
    }
}
