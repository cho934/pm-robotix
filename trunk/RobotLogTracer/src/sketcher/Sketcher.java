package sketcher;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import robot.RobotLog;

public class Sketcher {
    JFrame f = new JFrame();

    public Sketcher() {

        SketcherMainPanel contentPane = new SketcherMainPanel();
        try {
            Layer sbg = new Layer();
            // sbg.add(new SVGObject2D());
            sbg.add(new BgImageLayer("table2014.png"));
            contentPane.getSketch().addLayer(sbg);
            RobotLog r = new RobotLog(new File("out.txt"));
            contentPane.getSketch().addLayer(r.createPathLayer());

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        f.setContentPane(contentPane);
        f.setSize(1024, 768);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setTitle("Sketcher");

    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {
                try {
                    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }

                Sketcher s = new Sketcher();
                s.setVisible(true);

            }
        });

    }

    public void setVisible(boolean b) {
        f.setVisible(b);

    }
}
