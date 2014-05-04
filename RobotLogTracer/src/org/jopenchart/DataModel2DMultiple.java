package org.jopenchart;

import java.util.ArrayList;
import java.util.List;

public class DataModel2DMultiple extends DataModel implements DataModelListener {
    private final List<DataModel2D> models = new ArrayList<DataModel2D>();

    public DataModel2DMultiple() {

    }

    public DataModel2D getModel(int index) {
        return this.models.get(index);
    }

    public void addModel(DataModel2D model) {
        this.models.add(model);
        model.addDataModelListener(this);
    }

    public int getSize() {
        return this.models.size();
    }

    public Number getMaxXValue() {
        Number max = null;

        for (DataModel2D model : models) {
            Number b = model.getMaxXValue();
            if (max == null) {
                max = b;
            } else if (b != null && b.doubleValue() > max.doubleValue()) {
                max = b;
            }
        }
        return max;
    }

    public Number getMinXValue() {
        Number min = null;
        for (DataModel2D model : models) {
            Number b = model.getMinXValue();
            if (min == null) {
                min = b;
            } else if (b != null && b.doubleValue() < min.doubleValue()) {
                min = b;
            }
        }
        return min;
    }

    public Number getMaxYValue() {
        Number max = null;

        for (DataModel2D model : models) {
            Number b = model.getMaxYValue();
            if (max == null) {
                max = b;
            } else if (b != null && b.doubleValue() > max.doubleValue()) {
                max = b;
            }
        }
        return max;
    }

    public Number getMinYValue() {
        Number min = null;
        for (DataModel2D model : models) {
            Number b = model.getMinYValue();
            if (min == null) {
                min = b;
            } else if (b != null && b.doubleValue() < min.doubleValue()) {
                min = b;
            }
        }
        return min;
    }

    @Override
    public void dataChanged() {
        fireDataModelChanged();
    }

    public void removeAll() {
        this.models.clear();
    }

    @Override
    public synchronized int getState() {
        for (DataModel2D model : models) {
            if (model.getState() == LOADING) {
                return LOADING;
            }
        }
        return LOADED;
    }
}
