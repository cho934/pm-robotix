package org.jopenchart;

import java.util.ArrayList;
import java.util.List;

public class DataModel2D extends DataModel {
    private final List<Number> lX = new ArrayList<Number>();
    private final List<Number> lY = new ArrayList<Number>();

    public DataModel2D() {

    }

    public void addAll(List<Number> dataX, List<Number> dataY) {
        if (dataX.size() != dataY.size()) {
            throw new IllegalArgumentException("x and y sizes don't match");
        }
        lX.addAll(dataX);
        lY.addAll(dataY);
    }

    public int getSize() {
        return lX.size();
    }

    public void setXValueAt(int index, Number value) {
        ensureCapacity(index);
        lX.set(index, value);
    }

    public void setYValueAt(int index, Number value) {
        ensureCapacity(index);
        lY.set(index, value);
    }

    private void ensureCapacity(int index) {
        for (int i = lX.size(); i <= index; i++) {
            lX.add(null);
            lY.add(null);
        }
    }

    public Number getXValueAt(int index) {
        ensureCapacity(index);
        return lX.get(index);
    }

    public Number getYValueAt(int index) {
        ensureCapacity(index);
        return lY.get(index);
    }

    public Number getMaxXValue() {
        Number max = 0;
        for (Number b : this.lX) {
            if (max == null) {
                max = b;
            } else if (b != null && b.doubleValue() > max.doubleValue()) {
                max = b;
            }
        }
        return max;
    }

    public Number getMaxYValue() {
        Number max = 0;
        for (Number b : this.lY) {
            if (max == null) {
                max = b;
            } else if (b != null && b.doubleValue() > max.doubleValue()) {
                max = b;
            }
        }
        return max;
    }

    public Number getMinXValue() {
        Number min = 0;
        for (Number b : this.lX) {
            if (min == null) {
                min = b;
            } else if (b != null && b.doubleValue() < min.doubleValue()) {
                min = b;
            }
        }
        return min;
    }

    public Number getMinYValue() {
        Number min = 0;
        for (Number b : this.lY) {
            if (min == null) {
                min = b;
            } else if (b != null && b.doubleValue() < min.doubleValue()) {
                min = b;
            }
        }
        return min;
    }

    public void clear() {
        for (int i = 0; i < this.getSize(); i++) {
            this.setXValueAt(i, null);
            this.setYValueAt(i, null);
        }
    }
}
