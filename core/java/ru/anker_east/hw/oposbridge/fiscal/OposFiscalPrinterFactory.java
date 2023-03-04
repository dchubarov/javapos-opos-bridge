/*
 * $Id: OposFiscalPrinterFactory.java,v 1.3 2009/04/13 15:22:10 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */
package ru.anker_east.hw.oposbridge.fiscal;

import jpos.JposException;
import jpos.config.JposEntry;
import jpos.loader.JposServiceInstance;
import jpos.loader.JposServiceInstanceFactory;

/**
 * 
 * @author Dmitry Chubarov
 */
public class OposFiscalPrinterFactory implements JposServiceInstanceFactory {

    /**
     * Constructs new FiscalPrinterFactory object.
     */
    public OposFiscalPrinterFactory() {
        
    }

    /* JposServiceInstanceFactory methods */
            
    private static final String OPOS_DEVICE_PROP_NAME = "OposDevice";
    private static final String SERVICE_VERSION_PROP_NAME = "ServiceVersion";
    private static final String TRACE_PROP_NAME = "Trace";
    
    public JposServiceInstance createInstance(String logicalName, JposEntry entry) throws JposException {
        String devName = logicalName;
        if (entry.hasPropertyWithName(OPOS_DEVICE_PROP_NAME)) {
            devName = (String)entry.getPropertyValue(OPOS_DEVICE_PROP_NAME);
        }
        
        int ver = 0;
        if (entry.hasPropertyWithName(SERVICE_VERSION_PROP_NAME)) {
            String tmp = (String)entry.getPropertyValue(SERVICE_VERSION_PROP_NAME);
            try {
                ver = Integer.parseInt(tmp);
            }
            catch (NumberFormatException e) { }
        }

        boolean trace = false;
        if (entry.hasPropertyWithName(TRACE_PROP_NAME)) {
            String tmp = (String)entry.getPropertyValue(TRACE_PROP_NAME);
            if (tmp.compareToIgnoreCase("true") == 0 ||
                    tmp.compareToIgnoreCase("yes") == 0 ||
                    tmp.compareToIgnoreCase("on") == 0)
                trace = true;
        }

        return new OposFiscalPrinterService(devName, ver, trace);
    }
}
