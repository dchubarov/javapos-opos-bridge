
package ru.anker_east.hw.oposbridge.cash;

import jpos.JposConst;
import jpos.JposException;
import jpos.services.CashDrawerService112;
import jpos.services.EventCallbacks;

/**
 *
 * @author dch
 */
public class OposCashDrawerService implements CashDrawerService112 {

    private static final int SERVICE_VERSION = 1012000; // 1.12
    static {
        System.loadLibrary("OposBridgeWr32");
    }

    private long addr = 0L;
    private String oposDeviceName = null;

    public OposCashDrawerService(String oposDeviceName) {
        this.oposDeviceName = oposDeviceName;
    }

    private native int nGetErrorCode();
    private native int nGetErrorCodeExtended();
    
    public boolean getCapCompareFirmwareVersion() throws JposException {
        return false;
    }

    public boolean getCapUpdateFirmware() throws JposException {
        return false;
    }

    public void compareFirmwareVersion(String arg0, int[] arg1)
            throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public void updateFirmware(String arg0) throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public boolean getCapStatisticsReporting() throws JposException {
        return false;
    }

    public boolean getCapUpdateStatistics() throws JposException {
        return false;
    }

    public void resetStatistics(String arg0) throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public void retrieveStatistics(String[] arg0) throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public void updateStatistics(String arg0) throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public boolean getCapStatusMultiDrawerDetect() throws JposException {
        return false;
    }

    public int getCapPowerReporting() throws JposException {
        return JposConst.JPOS_PR_NONE;
    }

    public int getPowerNotify() throws JposException {
        return JposConst.JPOS_PN_DISABLED;
    }

    public void setPowerNotify(int arg0) throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    public int getPowerState() throws JposException {
        return JposConst.JPOS_PS_UNKNOWN;
    }

    private native int nGetCapStatus();
    
    public boolean getCapStatus() throws JposException {
        return checkResult(nGetCapStatus()) == 0 ? false : true;
    }

    private native int nGetDrawerOpened();

    public boolean getDrawerOpened() throws JposException {
        return checkResult(nGetDrawerOpened()) == 0 ? false : true;
    }

    private native int nOpenDrawer();
    
    public void openDrawer() throws JposException {
        checkResult(nOpenDrawer());
    }

    private native int nWaitForDrawerClose(int beepTimeout, int beepFrequency,
            int beepDuration, int beepDelay);
    
    public void waitForDrawerClose(int beepTimeout, int beepFrequency,
            int beepDuration, int beepDelay) throws JposException {
        checkResult(nWaitForDrawerClose(beepTimeout, beepFrequency,
                beepDuration, beepDelay));
    }

    private native String nGetCheckHealthText();
    
    public String getCheckHealthText() throws JposException {
        return nGetCheckHealthText();
    }

    private native int nGetClaimed();

    public boolean getClaimed() throws JposException {
        return checkResult(nGetClaimed()) == 0 ? false : true;
    }

    private native int nGetDeviceEnabled();
    
    public boolean getDeviceEnabled() throws JposException {
        return checkResult(nGetDeviceEnabled()) == 0 ? false : true;
    }

    private native int nSetDeviceEnabled(boolean enabled);

    public void setDeviceEnabled(boolean enabled) throws JposException {
        checkResult(nSetDeviceEnabled(enabled));
    }

    public String getDeviceServiceDescription() throws JposException {
        return this.getClass().getName();
    }

    public int getDeviceServiceVersion() throws JposException {
        return SERVICE_VERSION;
    }

    private native int nGetFreezeEvents();

    public boolean getFreezeEvents() throws JposException {
        return checkResult(nGetFreezeEvents()) == 0 ? false : true;
    }

    private native int nSetFreezeEvents(boolean freezeEvents);
    
    public void setFreezeEvents(boolean freezeEvents) throws JposException {
        checkResult(nSetFreezeEvents(freezeEvents));
    }

    private native String nGetPhysicalDeviceDescription();
    
    public String getPhysicalDeviceDescription() throws JposException {
        return nGetPhysicalDeviceDescription();
    }

    private native String nGetPhysicalDeviceName();
    
    public String getPhysicalDeviceName() throws JposException {
        return nGetPhysicalDeviceName();
    }

    private native int nGetState();
    
    public int getState() throws JposException {
        return checkResult(nGetState());
    }

    private native int nClaim(int timeout);
    
    public void claim(int timeout) throws JposException {
        checkResult(nClaim(timeout));
    }

    private native int nClose();
    
    public void close() throws JposException {
        checkResult(nClose());
    }

    private native int nCheckHealth(int level);
    
    public void checkHealth(int level) throws JposException {
        checkResult(nCheckHealth(level));
    }

    public void directIO(int command, int[] data, Object obj)
            throws JposException {
        // Unsupported
        throw new JposException(JposConst.JPOS_E_ILLEGAL);
    }

    private native int nOpen(String logicalName);
    
    public void open(String logicalName, EventCallbacks cb)
            throws JposException {
        checkResult(nOpen(oposDeviceName));
    }

    private native int nRelease();
    
    public void release() throws JposException {
        checkResult(nRelease());
    }

    public void deleteInstance() throws JposException {
        nClose();
    }

    // Implementation-specific

    private int checkResult(int result) throws JposException {
        if (result < 0) {
            int oposError = nGetErrorCode();
            if (oposError == JposConst.JPOS_E_EXTENDED) {
                throw new JposException(oposError, nGetErrorCodeExtended());
            }
            else {
                throw new JposException(oposError);
            }
        }
        return result;
    }
}
