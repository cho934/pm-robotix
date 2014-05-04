package sketcher;

import java.awt.AlphaComposite;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import javax.imageio.ImageIO;

import sketcher.model.Object2D;

import com.mortennobel.imagescaling.AdvancedResizeOp;
import com.mortennobel.imagescaling.ResampleOp;

public class BgImageLayer implements Object2D {
    BufferedImage img;
    private Map<Integer, BufferedImage> cache = new HashMap<Integer, BufferedImage>();

    public BgImageLayer(String string) {
        // TODO Auto-generated constructor stub
        try {
            img = ImageIO.read(new File(string));
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    @Override
    public void renderBackground(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        // TODO Auto-generated method stub

    }

    float r = (3000f) / 1414f;

    @Override
    public void render(Graphics2D graphics, int offsetX, int offsetY, int zoom) {
        AffineTransform tr = new AffineTransform();

        graphics.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        graphics.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        int bOffsetX = (int) (94 * r);
        int bOffsetY = (int) (1024 * r);
        int x = -offsetX - (bOffsetX / zoom);
        int y = -offsetY - (bOffsetY / zoom);
        AlphaComposite ac = AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.90f);
        graphics.setComposite(ac);
        graphics.drawImage(getImageForZoom(zoom), x, y, null);

    }

    private BufferedImage getImageForZoom(int z) {
      //  if (z == 1) {
       //     return img;
       // }
        if (cache.get(z) == null) {
            int w = img.getWidth() / z;
            int h = img.getHeight() / z;

            w = (int) (r * w);
            h = (int) (r * h);

            ResampleOp resampleOp = new ResampleOp(w, h);
            resampleOp.setUnsharpenMask(AdvancedResizeOp.UnsharpenMask.Normal);
            BufferedImage im_transformed = resampleOp.filter(img, null);
            cache.put(z, im_transformed);
        }
        return cache.get(z);
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
