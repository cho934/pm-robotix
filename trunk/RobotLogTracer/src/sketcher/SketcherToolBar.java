package sketcher;

import java.awt.Cursor;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

public class SketcherToolBar extends JPanel {
    public static final int MODE_MOVE = 0;
    public static final int MODE_SELECT = 1;
    public static final int MODE_DRAW = 2;
    private int mode = -1;
    JToggleButton bMove = new JToggleButton("Move");
    JToggleButton bSelect = new JToggleButton("Select");
    JToggleButton bDraw = new JToggleButton("Draw");
    JButton bSave = new JButton("Save");
    ButtonGroup gr = new ButtonGroup();
    private SketcherMainPanel sketcherMainPanel;
    private int oldMode;

    public SketcherToolBar(final SketcherMainPanel sketcherMainPanel) {
        this.setLayout(new FlowLayout());
        this.sketcherMainPanel = sketcherMainPanel;
        gr.add(bMove);
        gr.add(bSelect);
        gr.add(bDraw);
        this.add(bMove);
        this.add(bSelect);
        this.add(bDraw);
        this.add(bSave);
       
        bMove.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {

                setMode(MODE_MOVE);

            }
        });
        bSelect.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                setMode(MODE_SELECT);
            }
        });
        bDraw.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {

                setMode(MODE_DRAW);
            }
        });
        bSave.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    sketcherMainPanel.getSketch().saveAsSVG(new File("out.svg"));
                } catch (IOException e1) {
                    e1.printStackTrace();
                }

            }
        });
    }

    public int getMode() {
        return mode;
    }

    public void setMode(int mode) {
        if (this.mode == mode) {
            return;
        }
        this.oldMode = this.mode;
        this.mode = mode;
        if (mode == MODE_DRAW) {
            bDraw.setSelected(true);
            sketcherMainPanel.getRendererPanel().setCursor(new Cursor(Cursor.HAND_CURSOR));
        } else if (mode == MODE_MOVE) {
            bMove.setSelected(true);
            sketcherMainPanel.getRendererPanel().setCursor(new Cursor(Cursor.MOVE_CURSOR));
        } else if (mode == MODE_SELECT) {
            sketcherMainPanel.getRendererPanel().setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            bSelect.setSelected(true);
        }
    }

    public void revertMode() {
        this.setMode(this.oldMode);
    }

    public void init() {
        this.setMode(MODE_DRAW);
        
    }
}
