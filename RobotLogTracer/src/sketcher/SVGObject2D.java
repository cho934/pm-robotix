package sketcher;

import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.io.File;
import java.io.PrintWriter;
import java.net.MalformedURLException;

import org.apache.batik.bridge.UserAgentAdapter;
import org.apache.batik.bridge.svg12.SVG12BridgeContext;
import org.apache.batik.gvt.GraphicsNode;
import org.apache.batik.swing.JSVGCanvas;

import sketcher.model.Object2D;

public class SVGObject2D implements Object2D {
    GraphicsNode root;
    private static final String SAX_PARSER = "org.apache.crimson.parser.XMLReaderImpl";
    /**
     * RenderContext used to render the node
     */
    private static SVG12BridgeContext rc = new SVG12BridgeContext(new UserAgentAdapter());
    JSVGCanvas svgCanvas;

    SVGObject2D() {
        // String parser = XMLResourceDescriptor.getXMLParserClassName();
        // SVGDocumentFactory documentFactory = new SAXSVGDocumentFactory(parser);
        // Document doc = null;
        File file = new File("table2014.svg");
        // try {
        // doc = documentFactory.createSVGDocument(file.toURL().toString());
        // } catch (Exception e) {
        // e.printStackTrace();
        // }
        // BridgeContext ctx = new BridgeContext(new PrintingUserAgent());
        // GVTBuilder builder = new GVTBuilder();
        // root = builder.build(ctx, doc);
        svgCanvas = new JSVGCanvas();
        try {
            svgCanvas.setURI(file.toURL().toString());
        } catch (MalformedURLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    @Override
    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        // TODO Auto-generated method stub

    }

    @Override
    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        if (svgCanvas != null) {
            int RATIO = 10;
            int w = (3400 * RATIO / zoom);
            int h = (4400 * RATIO / zoom);

            System.out.println("render SVG " + w + "x" + h);
            // graphics.scale(zoom, zoom);
            AffineTransform f = new AffineTransform();
            f.setToScale(zoom, zoom);
            // graphics.setTransform(f);

            // svgCanvas.paint(graphics);
            svgCanvas.setProgressivePaint(false);
            svgCanvas.setDisableInteractions(true);
            svgCanvas.setDoubleBuffered(false);
            svgCanvas.setSize(w, h);

            svgCanvas.printAll(graphics);

        }
    }

    @Override
    public void printSVG(PrintWriter pr) {
        // TODO Auto-generated method stub

    }

    @Override
    public int getMinX() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public int getMinY() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public int getMaxX() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public int getMaxY() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public int getDistanceSquared(int x1, int y1) {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public void setSelected(boolean b) {
        // TODO Auto-generated method stub

    }
}
