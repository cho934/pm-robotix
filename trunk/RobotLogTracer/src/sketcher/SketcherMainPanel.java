package sketcher;

import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JPanel;
import javax.swing.JSeparator;

import sketcher.model.Line;

public class SketcherMainPanel extends JPanel {
    SketcherToolBar tools;
    SketcherRendererPanel rendererPanel;
    SketcherStatusPanel statusPanel;
    private Sketch s = new Sketch();

    SketcherMainPanel() {
        Layer l = new Layer();
        l.add(new Line(0, 0, 1000, 1000));
        l.add(new Line(0, 0, 0, 1000));
        s.addLayer(l);

        this.setLayout(new GridBagLayout());
        tools = new SketcherToolBar(this);
        rendererPanel = new SketcherRendererPanel(this);
        statusPanel = new SketcherStatusPanel(this);
        tools.init();

        GridBagConstraints c = new GridBagConstraints();
        c.gridx = 0;
        c.gridy = 0;
        c.weightx = 1;
        c.weighty = 0;
        c.fill = GridBagConstraints.BOTH;

        this.add(tools, c);
        c.gridy++;
        this.add(new JSeparator(JSeparator.HORIZONTAL), c);

        c.gridy++;
        c.weighty = 1;
        this.add(rendererPanel, c);

        c.gridy++;
        c.weighty = 0;
        this.add(new JSeparator(JSeparator.HORIZONTAL), c);
        c.gridy++;
        this.add(statusPanel, c);

    }

    public SketcherToolBar getTooBar() {
        return tools;
    }

    public SketcherRendererPanel getRendererPanel() {
        return rendererPanel;
    }

    public SketcherStatusPanel getStatusPanel() {
        return statusPanel;
    }

    public Sketch getSketch() {

        return s;
    }
}
