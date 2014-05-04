package sketcher;

import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.geom.AffineTransform;
import java.awt.geom.Dimension2D;

import org.apache.batik.bridge.BridgeExtension;
import org.apache.batik.bridge.ExternalResourceSecurity;
import org.apache.batik.bridge.ScriptSecurity;
import org.apache.batik.bridge.UserAgent;
import org.apache.batik.gvt.event.EventDispatcher;
import org.apache.batik.gvt.text.Mark;
import org.apache.batik.util.ParsedURL;
import org.w3c.dom.Element;
import org.w3c.dom.svg.SVGAElement;
import org.w3c.dom.svg.SVGDocument;

class PrintingUserAgent implements UserAgent {

    /**
     * Returns the default size of this user agent (400x400).
     */
    public Dimension2D getViewportSize() {
        return new Dimension(400, 400);
    }

    /**
     * Displays the specified error message using the <tt>ErrorHandler</tt>.
     */
    public void displayError(String message) {
        System.err.println(message);
    }

    /**
     * Displays the specified error using the <tt>ErrorHandler</tt>.
     */
    public void displayError(Exception e) {
        e.printStackTrace(System.err);
    }

    /**
     * Displays the specified message using the <tt>ErrorHandler</tt>.
     */
    public void displayMessage(String message) {
        System.err.println(message);
    }

    /**
     * Returns the pixel to millimeter conversion factor specified in the <tt>TranscodingHints</tt>
     * or 0.3528 if any.
     */
    public float getPixelToMM() {
        return 0.26458333333333333333333333333333f; // 96dpi
    }

    /**
     * Returns the user language specified in the <tt>TranscodingHints</tt> or "en" (english) if
     * any.
     */
    public String getLanguages() {
        return "en";
    }

    /**
     * Returns the user stylesheet specified in the <tt>TranscodingHints</tt> or null if any.
     */
    public String getUserStyleSheetURI() {
        return null;
    }

    /**
     * Returns the XML parser to use from the TranscodingHints.
     */
    public String getXMLParserClassName() {
        return "org.apache.crimson.parser.XMLReaderImpl";
    }

    /**
     * Unsupported operation.
     */
    public EventDispatcher getEventDispatcher() {
        return null;
    }

    /**
     * Unsupported operation.
     */
    public void openLink(SVGAElement elt) {
    }

    /**
     * Unsupported operation.
     */
    public void setSVGCursor(Cursor cursor) {
    }

    /**
     * Unsupported operation.
     */
    public void runThread(Thread t) {
    }

    /**
     * Unsupported operation.
     */
    public AffineTransform getTransform() {
        return null;
    }

    @Override
    public void checkLoadExternalResource(ParsedURL arg0, ParsedURL arg1) throws SecurityException {
        // TODO Auto-generated method stub

    }

    @Override
    public void checkLoadScript(String arg0, ParsedURL arg1, ParsedURL arg2) throws SecurityException {
        // TODO Auto-generated method stub

    }

    @Override
    public void deselectAll() {
        // TODO Auto-generated method stub

    }

    @Override
    public String getAlternateStyleSheet() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public float getBolderFontWeight(float arg0) {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public SVGDocument getBrokenLinkDocument(Element arg0, String arg1, String arg2) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public String getDefaultFontFamily() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ExternalResourceSecurity getExternalResourceSecurity(ParsedURL arg0, ParsedURL arg1) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public float getLighterFontWeight(float arg0) {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public String getMedia() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public float getMediumFontSize() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public float getPixelUnitToMillimeter() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public ScriptSecurity getScriptSecurity(String arg0, ParsedURL arg1, ParsedURL arg2) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void handleElement(Element arg0, Object arg1) {
        // TODO Auto-generated method stub

    }

    @Override
    public boolean hasFeature(String arg0) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean isXMLParserValidating() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void registerExtension(BridgeExtension arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void setTextSelection(Mark arg0, Mark arg1) {
        // TODO Auto-generated method stub

    }

    @Override
    public void setTransform(AffineTransform arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void showAlert(String arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public boolean showConfirm(String arg0) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public String showPrompt(String arg0) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public String showPrompt(String arg0, String arg1) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean supportExtension(String arg0) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public java.awt.Point getClientAreaLocationOnScreen() {
        // TODO Auto-generated method stub
        return null;
    }
}