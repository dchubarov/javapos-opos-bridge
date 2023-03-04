
package ru.anker_east.hw.oposbridge.cash;

import jpos.JposException;
import jpos.config.JposConfigException;
import jpos.config.JposEntry;
import jpos.loader.JposServiceInstance;
import jpos.loader.JposServiceInstanceFactory;

/**
 *
 * @author dch
 */
public class OposCashDrawerServiceInstanceFactory 
        implements JposServiceInstanceFactory {

    private static final String OPOS_DEVICE_PROP = "OposDevice";

    public JposServiceInstance createInstance(String logicalName,
            JposEntry entry) throws JposException {

        String prop = (String) entry.getPropertyValue(OPOS_DEVICE_PROP);
        if (prop == null || prop.isEmpty()) {
            throw new JposConfigException("OposDevice property must" +
                    " be defined in jpos.xml");
        }

        return new OposCashDrawerService(prop);
    }
}
