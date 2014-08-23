package robot;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.text.DecimalFormat;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

import org.jopenchart.Axis;
import org.jopenchart.AxisLabel;
import org.jopenchart.Chart;
import org.jopenchart.ChartPanel;
import org.jopenchart.DataModel2D;
import org.jopenchart.DataModel2DMultiple;
import org.jopenchart.linechart.LineXYChart;

import sketcher.Sketcher;
import ch.ethz.ssh2.Connection;
import ch.ethz.ssh2.SCPClient;

public class RobotSpeedGraphPanel extends JPanel {
	RobotSpeedGraphPanel(RobotLog l) {
		JTabbedPane tab = new JTabbedPane();
		// Tab 1
		JPanel tab1 = new JPanel();
		tab1.setLayout(new GridLayout(2, 1));
		ChartPanel panelLeft = new ChartPanel(createLeftChar(l));
		ChartPanel panelRight = new ChartPanel(createRightChar(l));
		tab1.add(new JScrollPane(panelLeft));
		tab1.add(new JScrollPane(panelRight));
		tab.addTab("Puissance moteur", tab1);
		// Tab 2
		JPanel tab2 = new JPanel();
		tab2.setLayout(new GridLayout(2, 1));
		ChartPanel panel0 = new ChartPanel(createOrderChart(l, 0));
		final ChartPanel panel1 = new ChartPanel(createOrderChart(l, 1)) {
			@Override
			public String getToolTipTextFrom(Number n) {
				if (n == null) {
					return null;
				}
				// axisX.getLabels().get(chart.getHighlight().getIndexOnModel()).getLabel()
				// + " " +
				// m.getYear() + ": " + n.longValue() + " €";
				String s = "v:" + n;
				System.out.println(s);
				repaint();
				return s;
			}

		};
		tab2.add(new JScrollPane(panel0));
		tab2.add(new JScrollPane(panel1));
		tab.addTab("Ordres", tab2);

		this.setLayout(new GridLayout(1, 1));
		this.add(tab);
	}

	private Chart createRightChar(RobotLog l) {
		return createPowerChart(l, true);
	}

	private Chart createLeftChar(RobotLog l) {
		return createPowerChart(l, false);
	}

	private Chart createPowerChart(RobotLog l, boolean right) {
		LineXYChart cLeft = new LineXYChart();
		cLeft.setColor(new Color(0, 155, 100));
		// c.setBackgroundRenderer(new SolidAreaRenderer(Color.pink));
		Axis axis = new Axis("y");
		axis.addLabel(new AxisLabel("-100%", -100));
		axis.addLabel(new AxisLabel("0", 0));
		axis.addLabel(new AxisLabel("100%", -100));
		cLeft.setLeftAxis(axis);

		Axis axisX = new Axis("x");
		axisX.addLabel(new AxisLabel("Début", 1));

		axisX.addLabel(new AxisLabel("Fin", 12));
		cLeft.setBottomAxis(axisX);

		cLeft.setDimension(new Dimension(600, 200));

		DataModel2DMultiple models = new DataModel2DMultiple();
		// Left
		DataModel2D mLeft = new DataModel2D();
		if (right) {
			mLeft.addAll(l.getTimeInMs(), l.getRightPower());
		} else {
			mLeft.addAll(l.getTimeInMs(), l.getLeftPower());
		}
		models.addModel(mLeft);

		// m.addAll(time, y);
		cLeft.setDataModel(models);
		cLeft.setLowerYRange(-100);
		cLeft.setHigherYRange(100);
		return cLeft;
	}

	private Chart createOrderChart(RobotLog l, int order) {
		LineXYChart cLeft = new LineXYChart();
		cLeft.setColor(new Color(0, 155, 100));

		Axis axisX = new Axis("x");
		axisX.addLabel(new AxisLabel("Début", 1));

		axisX.addLabel(new AxisLabel("Fin", 12));
		cLeft.setBottomAxis(axisX);

		cLeft.setDimension(new Dimension(600, 200));

		DataModel2DMultiple models = new DataModel2DMultiple();
		// Left
		DataModel2D mLeft = new DataModel2D();
		if (order == 0) {
			List<Number> order0 = l.getOrder0();
			System.out.println(order0);
			mLeft.addAll(l.getTimeInMs(), order0);
		} else {
			mLeft.addAll(l.getTimeInMs(), l.getOrder1());
		}
		models.addModel(mLeft);

		// Speed
		DataModel2D mSpeed = new DataModel2D();
		if (order == 0) {
			List<Number> current0 = l.getCurrent0();
			System.out.println(current0);
			mSpeed.addAll(l.getTimeInMs(), current0);
		} else {
			mSpeed.addAll(l.getTimeInMs(), l.getCurrent1());
		}
		models.addModel(mSpeed);

		// m.addAll(time, y);
		cLeft.setDataModel(models);
		double lY = cLeft.getLowerYRange().doubleValue();
		double hY = cLeft.getHigherYRange().doubleValue();
		if (lY < 0) {
			lY = -lY;
		}
		if (hY < 0) {
			hY = -hY;
		}
		double mY = Math.max(lY, hY);
		DecimalFormat df = new DecimalFormat("#.##");
		if (order == 0) {
			cLeft.setLowerYRange(-mY);
			cLeft.setHigherYRange(mY);
			Axis axis = new Axis("y");

			axis.addLabel(new AxisLabel("-" + df.format(mY), 0));
			axis.addLabel(new AxisLabel("0", 5));
			axis.addLabel(new AxisLabel("+" + df.format(mY), 10));
			cLeft.setLeftAxis(axis);

		} else {
			Axis axis = new Axis("y");

			axis.addLabel(new AxisLabel(df.format(cLeft.getLowerYRange()
					.doubleValue()), cLeft.getLowerYRange().doubleValue()));
			axis.addLabel(new AxisLabel(df.format(cLeft.getHigherYRange()
					.doubleValue()), cLeft.getHigherYRange().doubleValue()));
			cLeft.setLeftAxis(axis);
		}
		System.out.println("RobotSpeedGraphPanel.createOrderChart()");
		return cLeft;
	}

	public static void main(String[] args) throws IOException {
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				try {
					// File file = new File("out.txt"); //pour EV3
					File file = new File(
							"/home/pmx/workspace/EV3/LinuxX86/log.txt"); // pour
																			// simu
					File out = new File("out.txt");
					final FileChannel sourceChannel = new FileInputStream(file)
							.getChannel();
					final FileChannel destinationChannel = new FileOutputStream(
							out).getChannel();

					long maxCount = sourceChannel.size();
					try {
						final long size = sourceChannel.size();
						long position = 0;
						while (position < size) {
							position += sourceChannel.transferTo(position, 2,
									destinationChannel);
						}
					} finally {
						sourceChannel.close();
						destinationChannel.close();
					}

					// downloadLog(file, false); //true si EV3
					UIManager.setLookAndFeel(UIManager
							.getSystemLookAndFeelClassName());
					Sketcher s = new Sketcher();
					s.setVisible(true);
					JFrame f = new JFrame();

					f.setContentPane(new RobotSpeedGraphPanel(
							new RobotLog(file)));

					f.setSize(660, 500);
					f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					f.setLocationRelativeTo(null);
					f.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

			private void downloadLog(File file, boolean ev3)
					throws IOException, FileNotFoundException {

				Connection connection;
				if (ev3)
					connection = new Connection("192.168.2.240");
				else
					connection = new Connection("192.168.7.253");
				connection.connect();
				if (ev3)
					connection.authenticateWithPassword("root", "");
				else
					connection.authenticateWithPassword("root", "pmx");
				System.err.println("connected");
				SCPClient cl = new SCPClient(connection);

				FileOutputStream fileOutputStream = new FileOutputStream(file);
				if (ev3) {
					cl.get("/mnt/card/log.txt", fileOutputStream);
				} else {
					cl.get("/pmx/log.txt", fileOutputStream);
				}
				fileOutputStream.close();
				System.err.println("Log retrieved to " + file.getAbsolutePath());
				if (!file.exists()) {
					System.err.println("Log retrieved to "
							+ file.getAbsolutePath() + " MISSING");
				}
			}
		});

	}
}
