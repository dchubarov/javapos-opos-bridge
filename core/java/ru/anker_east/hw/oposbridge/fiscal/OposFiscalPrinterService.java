/*
 * $Id: OposFiscalPrinterService.java,v 1.4 2009/04/13 15:22:10 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */
package ru.anker_east.hw.oposbridge.fiscal;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import jpos.JposConst;
import jpos.JposException;
import jpos.services.EventCallbacks;

/**
 *
 * @author Dmitry Chubarov
 */
public class OposFiscalPrinterService
        implements jpos.services.FiscalPrinterService112 {

    private static final int DEFAULT_SERVICE_VERSION = 1012000; // 1.12    

    private static final String TRACE_FILE_NAME = "fptr-trace.log";
    
    private Wrapper wrapper;
    private EventCallbacks eventsCallback;
    private String oposDeviceName;
    private int serviceVersion;
    private boolean trace;
    private PrintWriter traceWriter;

    static {
        // load native methods
        System.loadLibrary("OposBridgeWr32");
    }

    public OposFiscalPrinterService(String oposDeviceName, int serviceVersion, boolean trace) {
        this.wrapper = new Wrapper();
        this.oposDeviceName = oposDeviceName;
        this.eventsCallback = null;
        
        this.serviceVersion = 
            (serviceVersion < 1006000 || serviceVersion > 1012000) ? 
                DEFAULT_SERVICE_VERSION : serviceVersion;

        this.trace = trace;
        this.traceWriter = null;
    }

    private void throwJposException(int result) throws JposException {
        if (result != JposConst.JPOS_SUCCESS) {
            if (result == JposConst.JPOS_E_EXTENDED) {
                throw new JposException(result, wrapper.getResultCodeExtended());
            }
            else {
                throw new JposException(result);
            }
        }
    }

    private void traceMsg(String msg) {
        if (trace) {
            if (traceWriter == null) {
                try {
                    traceWriter = new PrintWriter(
                            new FileWriter(TRACE_FILE_NAME, true), true);

                    traceWriter.println("**** SESSION START ****");
                    
                }
                catch (IOException e) {
                    trace = false;
                    return;
                }
            }

            traceWriter.println((new Date(System.currentTimeMillis())).toString() + " - " + msg);
        }
    }
    
    // JavaPOS Release 1.12
    
    public void printRecItemRefund(String description, long amount, int quantity, int vatInfo, long unitAmount, String unitName) throws JposException {
        traceMsg("printRecItemRefund(description=\"" + description
                + "\", amount=" + amount + ", quantity=" + quantity
                + ", vatInfo=" + vatInfo + ", unitAmount=" + unitAmount
                + ", unitName=\"" + unitName + "\")");
        
        int result = wrapper.printRecItemRefund(description, amount, quantity, vatInfo, unitAmount, unitName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecItemRefundVoid(String description, long amount, int quantity, int vatInfo, long unitAmount, String unitName) throws JposException {
        traceMsg("printRecItemRefundVoid(description=\"" + description
                + "\", amount=" + amount + ", quantity=" + quantity
                + ", vatInfo=" + vatInfo + ", unitAmount=" + unitAmount
                + ", unitName=\"" + unitName + "\")");
        
        int result = wrapper.printRecItemRefundVoid(description, amount, quantity, vatInfo, unitAmount, unitName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    // JavaPOS Release 1.11
    
    public boolean getCapPositiveSubtotalAdjustment() throws JposException {
        return wrapper.getCapPositiveSubtotalAdjustment();
    }

    public void printRecItemVoid(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName) throws JposException {
        traceMsg("printRecItemVoid(description=\"" + description
                + "\", price=" + price + ", quantity=" + quantity
                + ", vatInfo=" + vatInfo + ", unitPrice=" + unitPrice
                + ", unitName=\"" + unitName + "\")");

        int result = wrapper.printRecItemVoid(description, price, quantity, vatInfo, unitPrice, unitName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecItemAdjustmentVoid(int adjustmentType, String description, long amount, int vatInfo) throws JposException {
        traceMsg("printRecItemAdjustmentVoid(adjustmentType=" + adjustmentType
                + ", description=\"" + description + "\", amount=" + amount
                + ", vatInfo=" + vatInfo + ")");

        int result = wrapper.printRecItemAdjustmentVoid(adjustmentType, description, amount, vatInfo);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    // JavaPOS Release 1.10 - nothing new added
    
    // JavaPOS Release 1.9
    
    public boolean getCapCompareFirmwareVersion() throws JposException {
        return wrapper.getCapCompareFirmwareVersion();
    }

    public boolean getCapUpdateFirmware() throws JposException {
        return wrapper.getCapUpdateFirmware();
    }

    public void compareFirmwareVersion(String firmwareFileName, int[] compareResult) throws JposException {
        int result = wrapper.compareFirmwareVersion(firmwareFileName, compareResult);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void updateFirmware(String firmwareFileName) throws JposException {
        int result = wrapper.updateFirmware(firmwareFileName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }
    
    // JavaPOS Release 1.8

    public boolean getCapStatisticsReporting() throws JposException {
        return wrapper.getCapStatisticsReporting();
    }

    public boolean getCapUpdateStatistics() throws JposException {
        return wrapper.getCapUpdateStatistics();
    }

    public void resetStatistics(String statisticsBuffer) throws JposException {
        int result = wrapper.resetStatistics(statisticsBuffer);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void retrieveStatistics(String[] statisticsBuffer) throws JposException {
        int result = wrapper.retrieveStatistics(statisticsBuffer);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void updateStatistics(String statisticsBuffer) throws JposException {
        int result = wrapper.updateStatistics(statisticsBuffer);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }
    
    // JavaPOS Release 1.7

    public int getAmountDecimalPlaces() throws JposException {
        return getAmountDecimalPlace();
    }
    
    // JavaPOS Release 1.6

    public boolean getCapAdditionalHeader() throws JposException {
        return wrapper.getCapAdditionalHeader();
    }

    public boolean getCapAdditionalTrailer() throws JposException {
        return wrapper.getCapAdditionalTrailer();
    }

    public boolean getCapChangeDue() throws JposException {
        return wrapper.getCapChangeDue();
    }

    public boolean getCapEmptyReceiptIsVoidable() throws JposException {
        return wrapper.getCapEmptyReceiptIsVoidable();
    }

    public boolean getCapFiscalReceiptStation() throws JposException {
        return wrapper.getCapFiscalReceiptStation();
    }

    public boolean getCapFiscalReceiptType() throws JposException {
        return wrapper.getCapFiscalReceiptType();
    }

    public boolean getCapMultiContractor() throws JposException {
        return wrapper.getCapMultiContractor();
    }

    public boolean getCapOnlyVoidLastItem() throws JposException {
        return wrapper.getCapOnlyVoidLastItem();
    }

    public boolean getCapPackageAdjustment() throws JposException {
        return wrapper.getCapPackageAdjustment();
    }

    public boolean getCapPostPreLine() throws JposException {
        return wrapper.getCapPostPreLine();
    }

    public boolean getCapSetCurrency() throws JposException {
        return wrapper.getCapSetCurrency();
    }

    public boolean getCapTotalizerType() throws JposException {
        return wrapper.getCapTotalizerType();
    }

    public int getActualCurrency() throws JposException {
        int result = wrapper.getActualCurrency();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public String getAdditionalHeader() throws JposException {
        String result = wrapper.getAdditionalHeader();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setAdditionalHeader(String additionalHeader) throws JposException {
        traceMsg("setAdditionalHeader(additionalHeader=\""
                + additionalHeader + "\")");

        int result = wrapper.setAdditionalHeader(additionalHeader);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getAdditionalTrailer() throws JposException {
        String result = wrapper.getAdditionalTrailer();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setAdditionalTrailer(String additionalTrailer) throws JposException {
        traceMsg("setAdditionalTrailer(additionalTraler=\""
                + additionalTrailer + "\")");

        int result = wrapper.setAdditionalTrailer(additionalTrailer);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getChangeDue() throws JposException {
        String result = wrapper.getChangeDue();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setChangeDue(String changeDue) throws JposException {
        traceMsg("setChangeDue(changeDue=\"" + changeDue + "\")");
        
        int result = wrapper.setChangeDue(changeDue);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getContractorId() throws JposException {
        int result = wrapper.getContractorId();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setContractorId(int contractorId) throws JposException {
        traceMsg("setContractorId(contractorId=" + contractorId + ")");
        
        int result = wrapper.setContractorId(contractorId);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getDateType() throws JposException {
        int result = wrapper.getDateType();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setDateType(int dateType) throws JposException {
        traceMsg("setDateType(dateType=" + dateType + ")");
        
        int result = wrapper.setDateType(dateType);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getFiscalReceiptStation() throws JposException {
        int result = wrapper.getFiscalReceiptStation();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setFiscalReceiptStation(int fiscalReceiptStation) throws JposException {
        traceMsg("setFiscalReceiptStation(fiscalReceiptStation="
                + fiscalReceiptStation + ")");
        
        int result = wrapper.setFiscalReceiptStation(fiscalReceiptStation);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getFiscalReceiptType() throws JposException {
        int result = wrapper.getFiscalReceiptType();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setFiscalReceiptType(int fiscalReceiptType) throws JposException {
        traceMsg("setFiscalReceiptType(fiscalReceiptType="
                + fiscalReceiptType + ")");
        
        int result = wrapper.setFiscalReceiptType(fiscalReceiptType);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getMessageType() throws JposException {
        int result = wrapper.getMessageType();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setMessageType(int messageType) throws JposException {
        traceMsg("setMessageType(messageType=" + messageType + ")");
        
        int result = wrapper.setMessageType(messageType);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getPostLine() throws JposException {
        String result = wrapper.getPostLine();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setPostLine(String postLine) throws JposException {
        traceMsg("setPostLine(postLine=\"" + postLine + "\")");
        
        int result = wrapper.setPostLine(postLine);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getPreLine() throws JposException {
        String result = wrapper.getPreLine();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setPreLine(String preLine) throws JposException {
        traceMsg("setPreLine(preLine=\"" + preLine + "\")");
        
        int result = wrapper.setPreLine(preLine);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getTotalizerType() throws JposException {
        int result = wrapper.getTotalizerType();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setTotalizerType(int totalizerType) throws JposException {
        traceMsg("setTotalizerType(totalizerType=" + totalizerType + ")");
        
        int result = wrapper.setTotalizerType(totalizerType);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setCurrency(int newCurrency) throws JposException {
        traceMsg("setCurrency(newCurrency=" + newCurrency + ")");
        
        int result = wrapper.setCurrency(newCurrency);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecCash(long amount) throws JposException {
        traceMsg("printRecCash(amount=" + amount + ")");
        
        int result = wrapper.printRecCash(amount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecItemFuel(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName, long specialTax, String specialTaxName) throws JposException {
        traceMsg("printRecItemFuel(description=\"" + description
                + "\", price=" + price + ", quantity=" + quantity
                + ", vatInfo=" + vatInfo + ", unitPrice=" + unitPrice
                + ", unitName=\"" + unitName + "\")");

        int result = wrapper.printRecItemFuel(description, price, quantity, vatInfo, unitPrice, unitName, specialTax, specialTaxName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecItemFuelVoid(String description, long price, int vatInfo, long specialTax) throws JposException {
        traceMsg("printRecItemFuelVoid(description=\"" + description
                + "\", price=" + price + ", vatInfo=" + vatInfo
                + ", specialTax=" + specialTax + ")");

        int result = wrapper.printRecItemFuelVoid(description, price, vatInfo, specialTax);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecPackageAdjustment(int adjustmentType, String description, String vatAdjustment) throws JposException {
        traceMsg("printRecPackageAdjustment(adjustmentType=" + adjustmentType
                + ", descrition=\"" + description + "\", vatAdjustment=\""
                + vatAdjustment + "\")");
        
        int result = wrapper.printRecPackageAdjustment(adjustmentType, description, vatAdjustment);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecPackageAdjustVoid(int adjustmentType, String vatAdjustment) throws JposException {
        traceMsg("printRecPackageAdjustVoid(adjustmentType=" + adjustmentType
                + ", vatAdjustment=\"" + vatAdjustment + "\")");

        int result = wrapper.printRecPackageAdjustVoid(adjustmentType, vatAdjustment);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecRefundVoid(String description, long amount, int vatInfo) throws JposException {
        traceMsg("printRecRefundVoid(description=\"" + description
                + "\", amount=" + amount + ", vatInfo=" + vatInfo + ")");

        int result = wrapper.printRecRefundVoid(description, amount, vatInfo);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecSubtotalAdjustVoid(int adjustmentType, long amount) throws JposException {
        traceMsg("printRecSubtotalAdjustVoid(adjustmentType=" + adjustmentType
                + ", amount=" + amount + ")");

        int result = wrapper.printRecSubtotalAdjustVoid(adjustmentType, amount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void printRecTaxID(String taxID) throws JposException {
        traceMsg("printRecTaxID(taxID=\"" + taxID + "\")");
        
        int result = wrapper.printRecTaxID(taxID);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }
    
    // JavaPOS Release 1.5 - nothing new added
    
    // JavaPOS Release 1.4 - nothing new added
    
    // JavaPOS Release 1.3 - nothing new added

    public boolean getCapAdditionalLines() throws JposException {
        return wrapper.getCapAdditionalLines();
    }

    public boolean getCapAmountAdjustment() throws JposException {
        return wrapper.getCapAmountAdjustment();
    }

    public boolean getCapAmountNotPaid() throws JposException {
        return wrapper.getCapAmountNotPaid();
    }

    public boolean getCapCheckTotal() throws JposException {
        return wrapper.getCapCheckTotal();
    }

    public boolean getCapCoverSensor() throws JposException {
        return wrapper.getCapCoverSensor();
    }

    public boolean getCapDoubleWidth() throws JposException {
        return wrapper.getCapDoubleWidth();
    }

    public boolean getCapDuplicateReceipt() throws JposException {
        return wrapper.getCapDuplicateReceipt();
    }

    public boolean getCapFixedOutput() throws JposException {
        return wrapper.getCapFixedOutput();
    }

    public boolean getCapHasVatTable() throws JposException {
        return wrapper.getCapHasVatTable();
    }

    public boolean getCapIndependentHeader() throws JposException {
        return wrapper.getCapIndependentHeader();
    }

    public boolean getCapItemList() throws JposException {
        return wrapper.getCapItemList();
    }

    public boolean getCapJrnEmptySensor() throws JposException {
        return wrapper.getCapJrnEmptySensor();
    }

    public boolean getCapJrnNearEndSensor() throws JposException {
        return wrapper.getCapJrnNearEndSensor();
    }

    public boolean getCapJrnPresent() throws JposException {
        return wrapper.getCapJrnPresent();
    }

    public boolean getCapNonFiscalMode() throws JposException {
        return wrapper.getCapNonFiscalMode();
    }

    public boolean getCapOrderAdjustmentFirst() throws JposException {
        return wrapper.getCapOrderAdjustmentFirst();
    }

    public boolean getCapPercentAdjustment() throws JposException {
        return wrapper.getCapPercentAdjustment();
    }

    public boolean getCapPositiveAdjustment() throws JposException {
        return wrapper.getCapPositiveAdjustment();
    }

    public boolean getCapPowerLossReport() throws JposException {
        return wrapper.getCapPowerLossReport();
    }

    public int getCapPowerReporting() throws JposException {
        return wrapper.getCapPowerReporting();
    }

    public boolean getCapPredefinedPaymentLines() throws JposException {
        return wrapper.getCapPredefinedPaymentLines();
    }

    public boolean getCapReceiptNotPaid() throws JposException {
        return wrapper.getCapReceiptNotPaid();
    }

    public boolean getCapRecEmptySensor() throws JposException {
        return wrapper.getCapRecEmptySensor();
    }

    public boolean getCapRecNearEndSensor() throws JposException {
        return wrapper.getCapRecNearEndSensor();
    }

    public boolean getCapRecPresent() throws JposException {
        return wrapper.getCapRecPresent();
    }

    public boolean getCapRemainingFiscalMemory() throws JposException {
        return wrapper.getCapRemainingFiscalMemory();
    }

    public boolean getCapReservedWord() throws JposException {
        return wrapper.getCapReservedWord();
    }

    public boolean getCapSetHeader() throws JposException {
        return wrapper.getCapSetHeader();
    }

    public boolean getCapSetPOSID() throws JposException {
        return wrapper.getCapSetPOSID();
    }

    public boolean getCapSetStoreFiscalID() throws JposException {
        return wrapper.getCapSetStoreFiscalID();
    }

    public boolean getCapSetTrailer() throws JposException {
        return wrapper.getCapSetTrailer();
    }

    public boolean getCapSetVatTable() throws JposException {
        return wrapper.getCapSetVatTable();
    }

    public boolean getCapSlpEmptySensor() throws JposException {
        return wrapper.getCapSlpEmptySensor();
    }

    public boolean getCapSlpFiscalDocument() throws JposException {
        return wrapper.getCapSlpFiscalDocument();
    }

    public boolean getCapSlpFullSlip() throws JposException {
        return wrapper.getCapSlpFullSlip();
    }

    public boolean getCapSlpNearEndSensor() throws JposException {
        return wrapper.getCapSlpNearEndSensor();
    }

    public boolean getCapSlpPresent() throws JposException {
        return wrapper.getCapSlpPresent();
    }

    public boolean getCapSlpValidation() throws JposException {
        return wrapper.getCapSlpValidation();
    }

    public boolean getCapSubAmountAdjustment() throws JposException {
        return wrapper.getCapSubAmountAdjustment();
    }

    public boolean getCapSubPercentAdjustment() throws JposException {
        return wrapper.getCapSubPercentAdjustment();
    }

    public boolean getCapSubtotal() throws JposException {
        return wrapper.getCapSubtotal();
    }

    public boolean getCapTrainingMode() throws JposException {
        return wrapper.getCapTrainingMode();
    }

    public boolean getCapValidateJournal() throws JposException {
        return wrapper.getCapValidateJournal();
    }

    public boolean getCapXReport() throws JposException {
        return wrapper.getCapXReport();
    }

    public int getOutputID() throws JposException {
        int result = wrapper.getOutputID();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getPowerNotify() throws JposException {
        int result = wrapper.getPowerNotify();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setPowerNotify(int powerNotify) throws JposException {
        traceMsg("setPowerNotify(powerNotify=" + powerNotify + ")");
        
        int result = wrapper.setPowerNotify(powerNotify);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getPowerState() throws JposException {
        int result = wrapper.getPowerState();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getAmountDecimalPlace() throws JposException {
        int result = wrapper.getAmountDecimalPlaces();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public boolean getAsyncMode() throws JposException {
        return wrapper.getAsyncMode();
    }

    public void setAsyncMode(boolean asyncMode) throws JposException {
        traceMsg("setAsyncMode(asyncMode=" + asyncMode + ")");
        
        int result = wrapper.setAsyncMode(asyncMode);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public boolean getCheckTotal() throws JposException {
        return wrapper.getCheckTotal();
    }

    public void setCheckTotal(boolean checkTotal) throws JposException {
        traceMsg("setCheckTotal(checkTotal=" + checkTotal + ")");
        
        int result = wrapper.setCheckTotal(checkTotal);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public int getCountryCode() throws JposException {
        int result = wrapper.getCountryCode();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public boolean getCoverOpen() throws JposException {
        return wrapper.getCoverOpen();
    }

    public boolean getDayOpened() throws JposException {
        return wrapper.getDayOpened();
    }

    public int getDescriptionLength() throws JposException {
        int result = wrapper.getDescriptionLength();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public boolean getDuplicateReceipt() throws JposException {
        return wrapper.getDuplicateReceipt();
    }

    public void setDuplicateReceipt(boolean duplicateReceipt) throws JposException {
        traceMsg("setDuplicateReceipt(duplicateReceipt="
                + duplicateReceipt + ")");
        
        int result = wrapper.setDuplicateReceipt(duplicateReceipt);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public int getErrorLevel() throws JposException {
        int result = wrapper.getErrorLevel();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getErrorOutID() throws JposException {
        int result = wrapper.getErrorOutID();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getErrorState() throws JposException {
        int result = wrapper.getErrorState();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getErrorStation() throws JposException {
        int result = wrapper.getErrorStation();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public String getErrorString() throws JposException {
        String result = wrapper.getErrorString();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public boolean getFlagWhenIdle() throws JposException {
        return wrapper.getFlagWhenIdle();
    }

    public void setFlagWhenIdle(boolean flagWhenIdle) throws JposException {
        traceMsg("setFlagWhenIdle(flagWhenIdle=" + flagWhenIdle + ")");

        int result = wrapper.setFlagWhenIdle(flagWhenIdle);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public boolean getJrnEmpty() throws JposException {
        return wrapper.getJrnEmpty();
    }

    public boolean getJrnNearEnd() throws JposException {
        return wrapper.getJrnNearEnd();
    }

    public int getMessageLength() throws JposException {
        int result = wrapper.getMessageLength();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getNumHeaderLines() throws JposException {
        int result = wrapper.getNumHeaderLines();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getNumTrailerLines() throws JposException {
        int result = wrapper.getNumTrailerLines();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getNumVatRates() throws JposException {
        int result = wrapper.getNumVatRates();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public String getPredefinedPaymentLines() throws JposException {
        String result = wrapper.getPredefinedPaymentLines();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getPrinterState() throws JposException {
        int result = wrapper.getPrinterState();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getQuantityDecimalPlaces() throws JposException {
        int result = wrapper.getQuantityDecimalPlaces();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getQuantityLength() throws JposException {
        int result = wrapper.getQuantityLength();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public boolean getRecEmpty() throws JposException {
        return wrapper.getRecEmpty();
    }

    public boolean getRecNearEnd() throws JposException {
        return wrapper.getRecNearEnd();
    }

    public int getRemainingFiscalMemory() throws JposException {
        int result = wrapper.getRemainingFiscalMemory();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public String getReservedWord() throws JposException {
        String result = wrapper.getReservedWord();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;        
    }

    public boolean getSlpEmpty() throws JposException {
        return wrapper.getSlpEmpty();
    }

    public boolean getSlpNearEnd() throws JposException {
        return wrapper.getSlpNearEnd();
    }

    public int getSlipSelection() throws JposException {
        int result = wrapper.getSlipSelection();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void setSlipSelection(int slipSelection) throws JposException {
        traceMsg("setSlipSelection(slipSelection=" + slipSelection + ")");
        
        int result = wrapper.setSlipSelection(slipSelection);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public boolean getTrainingModeActive() throws JposException {
        return wrapper.getTrainingModeActive();
    }

    public void beginFiscalDocument(int documentAmount) throws JposException {
        traceMsg("beginFiscalDocument(documentAmount=" + documentAmount + ")");
        
        int result = wrapper.beginFiscalDocument(documentAmount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginFiscalReceipt(boolean printHeader) throws JposException {
        traceMsg("beginFiscalReceipt(printHeader=" + printHeader + ")");
        
        int result = wrapper.beginFiscalReceipt(printHeader);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginFixedOutput(int station, int documentType) throws JposException {
        traceMsg("beginFixedOutput(station=" + station
                + ", documentType=" + documentType + ")");

        int result = wrapper.beginFixedOutput(station, documentType);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginInsertion(int timeout) throws JposException {
        traceMsg("beginInsertion(timeout=" + timeout + ")");
        
        int result = wrapper.beginInsertion(timeout);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginItemList(int vatID) throws JposException {
        traceMsg("beginItemList(vatID=" + vatID + ")");
        
        int result = wrapper.beginItemList(vatID);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginNonFiscal() throws JposException {
        traceMsg("beginNonFiscal()");
        
        int result = wrapper.beginNonFiscal();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginRemoval(int timeout) throws JposException {
        traceMsg("beginRemoval(timeout=" + timeout + ")");
        
        int result = wrapper.beginRemoval(timeout);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void beginTraining() throws JposException {
        traceMsg("beginTraining()");
        
        int result = wrapper.beginTraining();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void clearError() throws JposException {
        traceMsg("clearError()");
        
        int result = wrapper.clearError();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void clearOutput() throws JposException {
        traceMsg("clearOutput()");
        
        int result = wrapper.clearOutput();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endFiscalDocument() throws JposException {
        traceMsg("endFiscalDocument()");

        int result = wrapper.endFiscalDocument();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endFiscalReceipt(boolean printHeader) throws JposException {
        traceMsg("endFiscalReceipt(printHeader=" + printHeader + ")");
        
        int result = wrapper.endFiscalReceipt(printHeader);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endFixedOutput() throws JposException {
        traceMsg("endFixedOutput()");

        int result = wrapper.endFixedOutput();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endInsertion() throws JposException {
        traceMsg("endInsertion()");
        
        int result = wrapper.endInsertion();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endItemList() throws JposException {
        traceMsg("endItemList()");

        int result = wrapper.endItemList();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endNonFiscal() throws JposException {
        traceMsg("endNonFiscal()");

        int result = wrapper.endNonFiscal();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endRemoval() throws JposException {
        traceMsg("endRemoval()");

        int result = wrapper.endRemoval();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void endTraining() throws JposException {
        traceMsg("endTraining()");

        int result = wrapper.endTraining();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void getData(int dataItem, int[] optArgs, String[] data) throws JposException {
        int result = wrapper.getData(dataItem, optArgs, data);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void getDate(String[] Date) throws JposException {
        int result = wrapper.getDate(Date);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void getTotalizer(int vatID, int optArgs, String[] data) throws JposException {
        int result = wrapper.getTotalizer(vatID, optArgs, data);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void getVatEntry(int vatID, int optArgs, int[] vatRate) throws JposException {
        int result = wrapper.getVatEntry(vatID, optArgs, vatRate);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printDuplicateReceipt() throws JposException {
        traceMsg("printDuplicateReceipt()");

        int result = wrapper.printDuplicateReceipt();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printFiscalDocumentLine(String documentLine) throws JposException {
        traceMsg("printFiscalDocumentLine(documentLine=\"" 
                + documentLine + "\")");
        
        int result = wrapper.printFiscalDocumentLine(documentLine);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printFixedOutput(int documentType, int lineNumber, String data) throws JposException {
        traceMsg("printFixedOutput(documentType=" + documentType
                + ", lineNumber=" + lineNumber + ", data=\"" + data + "\")");

        int result = wrapper.printFixedOutput(documentType, lineNumber, data);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printNormal(int station, String data) throws JposException {
        traceMsg("printNormal(station=" + station + ", data=\"" + data + "\")");
        
        int result = wrapper.printNormal(station, data);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printPeriodicTotalsReport(String date1, String date2) throws JposException {
        traceMsg("printPeriodicTotalsReport(date1=" + date1 
                + ", date2=" + date2 + ")");
        
        int result = wrapper.printPeriodicTotalsReport(date1, date2);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printPowerLossReport() throws JposException {
        traceMsg("printPowerLossReport()");
        
        int result = wrapper.printPowerLossReport();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecItem(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName) throws JposException {
        traceMsg("printRecItem(description=\"" + description + "\", price="
                + price + ", quantity=" + quantity + ", vatInfo=" + vatInfo
                + ", unitPrice=" + unitPrice + ", unitName=\""
                + unitName + "\")");
        
        int result = wrapper.printRecItem(description, price, quantity, vatInfo, unitPrice, unitName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecItemAdjustment(int adjustmentType, String description, long amount, int vatInfo) throws JposException {
        traceMsg("printRecItemAdjustment(adjustmentType=" + adjustmentType
                + ", description=\"" + description + "\", amount=" + amount
                + ", vatInfo=" + vatInfo + ")");

        int result = wrapper.printRecItemAdjustment(adjustmentType, description, amount, vatInfo);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecMessage(String message) throws JposException {
        traceMsg("printRecMessage(message=\"" + message + "\")");
        
        int result = wrapper.printRecMessage(message);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecNotPaid(String description, long amount) throws JposException {
        traceMsg("printRecNotPaid(description=\"" + description + "\", amount="
                + amount + ")");
        
        int result = wrapper.printRecNotPaid(description, amount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecRefund(String description, long amount, int vatInfo) throws JposException {
        traceMsg("printRecRefund(description=\"" + description + "\", amount="
                + amount + ", vatInfo=" + vatInfo + ")");

        int result = wrapper.printRecRefund(description, amount, vatInfo);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecSubtotal(long amount) throws JposException {
        traceMsg("printRecSubtotal(amount=" + amount + ")");
        
        int result = wrapper.printRecSubtotal(amount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecSubtotalAdjustment(int adjustmentType, String description, long amount) throws JposException {
        traceMsg("printRecSubtotalAdjustment(adjustmentType=" + adjustmentType
                + ", description=\"" + description + "\", amout="
                + amount + ")");

        int result = wrapper.printRecSubtotalAdjustment(adjustmentType, description, amount);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecTotal(long total, long payment, String description) throws JposException {
        traceMsg("printRecTotal(total=" + total + ", payment=" + payment
                + ", description=\"" + description + "\")");

        int result = wrapper.printRecTotal(total, payment, description);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecVoid(String description) throws JposException {
        traceMsg("printRecVoid(description=\"" + description + "\")");
        
        int result = wrapper.printRecVoid(description);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printRecVoidItem(String description, long amount, int quantity, int adjustmentType, long adjustment, int vatInfo) throws JposException {
        traceMsg("printRecVoidItem(description=\"" + description
                + "\", amount=" + amount + ", quantity=" + quantity
                + ", adjustmentType=" + adjustmentType + ", adjustment="
                + adjustment + ", vatInfo=" + vatInfo + ")");
        
        int result = wrapper.printRecVoidItem(description, amount, quantity, adjustmentType, adjustment, vatInfo);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printReport(int reportType, String startNum, String endNum) throws JposException {
        traceMsg("printReport(reportType=" + reportType + ", startNum=\""
                + startNum + "\", endNum=\"" + endNum + "\")");

        int result = wrapper.printReport(reportType, startNum, endNum);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printXReport() throws JposException {
        traceMsg("printXReport()");

        int result = wrapper.printXReport();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void printZReport() throws JposException {
        traceMsg("printZReport()");
        
        int result = wrapper.printZReport();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void resetPrinter() throws JposException {
        traceMsg("resetPrinter()");

        int result = wrapper.resetPrinter();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setDate(String date) throws JposException {
        traceMsg("setDate(date=\"" + date + "\")");
        
        int result = wrapper.setDate(date);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setHeaderLine(int lineNumber, String text, boolean doubleWidth) throws JposException {
        traceMsg("setHeaderLine(lineNumber=" + lineNumber + ", text=\"" + text
                + "\", doubleWidth=" + doubleWidth + ")");
        
        int result = wrapper.setHeaderLine(lineNumber, text, doubleWidth);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setPOSID(String POSID, String cashierID) throws JposException {
        traceMsg("setPOSID(POSID=\"" + POSID + "\", cashierID=\""
                + cashierID + "\")");

        int result = wrapper.setPOSID(POSID, cashierID);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setStoreFiscalID(String ID) throws JposException {
        traceMsg("setStoreFiscalID(ID=\"" + ID + "\")");
        
        int result = wrapper.setStoreFiscalID(ID);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setTrailerLine(int lineNumber, String text, boolean doubleWidth) throws JposException {
        traceMsg("setTrailerLine(lineNumber=" + lineNumber + ", text=\""
                + text + "\", doubleWidth=" + doubleWidth + ")");

        int result = wrapper.setTrailerLine(lineNumber, text, doubleWidth);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setVatTable() throws JposException {
        traceMsg("setVatTable()");
        
        int result = wrapper.setVatTable();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void setVatValue(int vatID, String vatValue) throws JposException {
        traceMsg("setVatValue(vatID=" + vatID
                + ", vatValue=\"" + vatValue + "\")");

        int result = wrapper.setVatValue(vatID, vatValue);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void verifyItem(String itemName, int vatID) throws JposException {
        traceMsg("verifyItem(itemName=\"" + itemName
                + "\", vatID=" + vatID + ")");
        
        int result = wrapper.verifyItem(itemName, vatID);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }
    
    // BaseService

    public String getCheckHealthText() throws JposException {
        String result = wrapper.getCheckHealthText();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;        
    }

    public boolean getClaimed() throws JposException {
        return wrapper.getClaimed();
    }

    public boolean getDeviceEnabled() throws JposException {
        return wrapper.getDeviceEnabled();
    }

    public void setDeviceEnabled(boolean deviceEnabled) throws JposException {
        traceMsg("setDeviceEnabled(deviceEnabled=" + deviceEnabled + ")");
        
        int result = wrapper.setDeviceEnabled(deviceEnabled);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getDeviceServiceDescription() throws JposException {
        // TODO: getDeviceServiceDescription
        return this.getClass().getName();
    }

    public int getDeviceServiceVersion() throws JposException {
        return serviceVersion;
    }

    public boolean getFreezeEvents() throws JposException {
        return wrapper.getFreezeEvents();
    }

    public void setFreezeEvents(boolean freezeEvents) throws JposException {
        int result = wrapper.setFreezeEvents(freezeEvents);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public String getPhysicalDeviceDescription() throws JposException {
        String result = wrapper.getPhysicalDeviceDescription();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;        
    }

    public String getPhysicalDeviceName() throws JposException {
        String result = wrapper.getPhysicalDeviceName();
        if (result == null) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public int getState() throws JposException {
        int result = wrapper.getState();
        if (result < 0) {
            throwJposException(JposConst.JPOS_E_FAILURE);
        }
        return result;
    }

    public void claim(int timeout) throws JposException {
        traceMsg("claim(timeout=" + timeout + ")");
        
        int result = wrapper.claim(timeout);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void close() throws JposException {
        traceMsg("close()");
        
        eventsCallback = null;
        int result = wrapper.close();
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void checkHealth(int level) throws JposException {
        traceMsg("checkHealth(level=" + level + ")");
        
        int result = wrapper.checkHealth(level);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }

    public void directIO(int command, int[] data, Object object) throws JposException {
        traceMsg("directIO(command=" + command + ", ...)");
        
        int result = wrapper.directIO(command, data, object);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }        
    }

    public void open(String logicalName, EventCallbacks cb) throws JposException {
        traceMsg("open(logicalName=\"" + logicalName + "\", ...)");
        
        this.eventsCallback = cb;
        int result = wrapper.open(oposDeviceName);
        if (result != JposConst.JPOS_SUCCESS) {
            throwJposException(result);
        }
    }
    
    public void release() throws JposException {
        traceMsg("release()");
        
        // Workaround the problem specific to PRIM family OPOS driver that
        // causes JRE to crash due to system access violation error then
        // release() called without preceding call to claim().
        if (getClaimed()) {
            int result = wrapper.release();
            if (result != JposConst.JPOS_SUCCESS) {
                throwJposException(result);
            }
        }
    }

    public void deleteInstance() throws JposException {        
        wrapper.deleteInstance();
    }
    
    
    private class Wrapper {
        // address of native COM object
        private long addr = 0;

        // OPOS-specific
        public native int getResultCode();
        public native int getResultCodeExtended();
        
        // base
        public native int deleteInstance();
        public native int open(String logicalName);
        public native int directIO(int command, int[] data, Object object);
        public native int close();
        public native int claim(int timeout);
        public native int getState();
        public native String getPhysicalDeviceName();
        public native String getPhysicalDeviceDescription();
        public native int setFreezeEvents(boolean freezeEvents);
        public native boolean getFreezeEvents();
        public native int release();
        public native int checkHealth(int level);
        public native int setDeviceEnabled(boolean deviceEnabled);
        public native boolean getDeviceEnabled();
        public native boolean getClaimed();
        public native String getCheckHealthText();
        // 1.3
        public native int verifyItem(String itemName, int vatID);
        public native int setVatValue(int vatID, String vatValue);
        public native int setVatTable();
        public native int setTrailerLine(int lineNumber, String text, boolean doubleWidth);
        public native int setStoreFiscalID(String ID);
        public native int setPOSID(String POSID, String cashierID);
        public native int setHeaderLine(int lineNumber, String text, boolean doubleWidth);
        public native int setDate(String date);
        public native int resetPrinter();
        public native int printZReport();
        public native int printXReport();
        public native int printReport(int reportType, String startNum, String endNum);
        public native int printRecVoidItem(String description, long amount, int quantity, int adjustmentType, long adjustment, int vatInfo);
        public native int printRecVoid(String description);
        public native int printRecTotal(long total, long payment, String description);
        public native int printRecSubtotalAdjustment(int adjustmentType, String description, long amount);
        public native int printRecSubtotal(long amount);
        public native int printRecRefund(String description, long amount, int vatInfo);
        public native int printRecNotPaid(String description, long amount);
        public native int printRecMessage(String message);
        public native int printRecItemAdjustment(int adjustmentType, String description, long amount, int vatInfo);
        public native int printRecItem(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName);
        public native int printPowerLossReport();
        public native int printPeriodicTotalsReport(String date1, String date2);
        public native int printNormal(int station, String data);
        public native int printFixedOutput(int documentType, int lineNumber, String data);
        public native int printFiscalDocumentLine(String documentLine);
        public native int printDuplicateReceipt();
        public native int getVatEntry(int vatID, int optArgs, int[] vatRate);
        public native int getTotalizer(int vatID, int optArgs, String[] data);
        public native int getDate(String[] Date);
        public native int getData(int dataItem, int[] optArgs, String[] data);
        public native int endTraining();
        public native int endRemoval();
        public native int endNonFiscal();
        public native int endItemList();
        public native int endInsertion();
        public native int endFixedOutput();
        public native int endFiscalReceipt(boolean printHeader);
        public native int endFiscalDocument();
        public native int clearOutput();
        public native int clearError();
        public native int beginTraining();
        public native int beginRemoval(int timeout);
        public native int beginNonFiscal();
        public native int beginItemList(int vatID);
        public native int beginInsertion(int timeout);
        public native int beginFixedOutput(int station, int documentType);
        public native int beginFiscalReceipt(boolean printHeader);
        public native int beginFiscalDocument(int documentAmount);
        public native boolean getTrainingModeActive();
        public native int setSlipSelection(int slipSelection);
        public native int getSlipSelection();
        public native boolean getSlpNearEnd();
        public native boolean getSlpEmpty();
        public native String getReservedWord();
        public native int getRemainingFiscalMemory();
        public native boolean getRecNearEnd();
        public native boolean getRecEmpty();
        public native int getQuantityLength();
        public native int getQuantityDecimalPlaces();
        public native int getPrinterState();
        public native String getPredefinedPaymentLines();
        public native int getNumVatRates();
        public native int getNumTrailerLines();
        public native int getNumHeaderLines();
        public native int getMessageLength();
        public native boolean getJrnNearEnd();
        public native boolean getJrnEmpty();
        public native int setFlagWhenIdle(boolean flagWhenIdle);
        public native boolean getFlagWhenIdle();
        public native String getErrorString();
        public native int getErrorStation();
        public native int getErrorState();
        public native int getErrorOutID();
        public native int getErrorLevel();
        public native int setDuplicateReceipt(boolean duplicateReceipt);
        public native boolean getDuplicateReceipt();
        public native int getDescriptionLength();
        public native boolean getDayOpened();
        public native boolean getCoverOpen();
        public native int getCountryCode();
        public native int setCheckTotal(boolean checkTotal);
        public native boolean getCheckTotal();
        public native int setAsyncMode(boolean asyncMode);
        public native boolean getAsyncMode();
        public native int getAmountDecimalPlaces();
        public native int getPowerState();
        public native int setPowerNotify(int powerNotify);
        public native int getPowerNotify();
        public native int getOutputID();
        public native boolean getCapAdditionalLines();
        public native boolean getCapAmountAdjustment();
        public native boolean getCapAmountNotPaid();
        public native boolean getCapCheckTotal();
        public native boolean getCapCoverSensor();
        public native boolean getCapDoubleWidth();
        public native boolean getCapDuplicateReceipt();
        public native boolean getCapFixedOutput();
        public native boolean getCapHasVatTable();
        public native boolean getCapIndependentHeader();
        public native boolean getCapItemList();
        public native boolean getCapJrnEmptySensor();
        public native boolean getCapJrnNearEndSensor();
        public native boolean getCapJrnPresent();
        public native boolean getCapNonFiscalMode();
        public native boolean getCapOrderAdjustmentFirst();
        public native boolean getCapPercentAdjustment();
        public native boolean getCapPositiveAdjustment();
        public native boolean getCapPowerLossReport();
        public native int getCapPowerReporting();
        public native boolean getCapPredefinedPaymentLines();
        public native boolean getCapReceiptNotPaid();
        public native boolean getCapRecEmptySensor();
        public native boolean getCapRecNearEndSensor();
        public native boolean getCapRecPresent();
        public native boolean getCapRemainingFiscalMemory();
        public native boolean getCapReservedWord();
        public native boolean getCapSetHeader();
        public native boolean getCapSetPOSID();
        public native boolean getCapSetStoreFiscalID();
        public native boolean getCapSetTrailer();
        public native boolean getCapSetVatTable();
        public native boolean getCapSlpEmptySensor();
        public native boolean getCapSlpFiscalDocument();
        public native boolean getCapSlpFullSlip();
        public native boolean getCapSlpNearEndSensor();
        public native boolean getCapSlpPresent();
        public native boolean getCapSlpValidation();
        public native boolean getCapSubAmountAdjustment();
        public native boolean getCapSubPercentAdjustment();
        public native boolean getCapSubtotal();
        public native boolean getCapTrainingMode();
        public native boolean getCapValidateJournal();
        public native boolean getCapXReport();
        // 1.6
        public native int printRecTaxID(String taxID);
        public native int printRecSubtotalAdjustVoid(int adjustmentType, long amount);
        public native int printRecRefundVoid(String description, long amount, int vatInfo);
        public native int printRecPackageAdjustVoid(int adjustmentType, String vatAdjustment);
        public native int printRecPackageAdjustment(int adjustmentType, String description, String vatAdjustment);
        public native int printRecItemFuelVoid(String description, long price, int vatInfo, long specialTax);
        public native int printRecItemFuel(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName, long specialTax, String specialTaxName);
        public native int printRecCash(long amount);
        public native int setCurrency(int newCurrency);
        public native int setTotalizerType(int totalizerType);
        public native int getTotalizerType();
        public native int setPreLine(String preLine);
        public native String getPreLine();
        public native int setPostLine(String preLine);
        public native String getPostLine();
        public native int setMessageType(int messageType);
        public native int getMessageType();
        public native int setFiscalReceiptType(int fiscalReceiptType);
        public native int getFiscalReceiptType();
        public native int setFiscalReceiptStation(int fiscalReceiptStation);
        public native int getFiscalReceiptStation();
        public native int setDateType(int dateType);
        public native int getDateType();
        public native int setContractorId(int contractorId);
        public native int getContractorId();
        public native int setChangeDue(String changeDue);
        public native String getChangeDue();
        public native int setAdditionalTrailer(String additionalTrailer);
        public native String getAdditionalTrailer();
        public native int setAdditionalHeader(String additionalHeader);
        public native String getAdditionalHeader();
        public native int getActualCurrency();
        public native boolean getCapAdditionalHeader();
        public native boolean getCapAdditionalTrailer();
        public native boolean getCapChangeDue();
        public native boolean getCapEmptyReceiptIsVoidable();
        public native boolean getCapFiscalReceiptStation();
        public native boolean getCapFiscalReceiptType();
        public native boolean getCapMultiContractor();
        public native boolean getCapOnlyVoidLastItem();
        public native boolean getCapPackageAdjustment();
        public native boolean getCapPostPreLine();
        public native boolean getCapSetCurrency();
        public native boolean getCapTotalizerType();
        // 1.8
        public native int updateStatistics(String statisticsBuffer);
        public native int retrieveStatistics(String[] statisticsBuffer);
        public native int resetStatistics(String statisticsBuffer);
        public native boolean getCapUpdateStatistics();
        public native boolean getCapStatisticsReporting();
        // 1.9
        public native int updateFirmware(String firmwareFileName);
        public native int compareFirmwareVersion(String firmwareFileName, int[] result);
        public native boolean getCapUpdateFirmware();
        public native boolean getCapCompareFirmwareVersion();
        // 1.11
        public native int printRecItemAdjustmentVoid(int adjustmentType, String description, long amount, int vatInfo);
        public native int printRecItemVoid(String description, long price, int quantity, int vatInfo, long unitPrice, String unitName);
        public native boolean getCapPositiveSubtotalAdjustment();
        // 1.12
        public native int printRecItemRefundVoid(String description, long amount, int quantity, int vatInfo, long unitAmount, String unitName);
        public native int printRecItemRefund(String description, long amount, int quantity, int vatInfo, long unitAmount, String unitName);
    }
}
