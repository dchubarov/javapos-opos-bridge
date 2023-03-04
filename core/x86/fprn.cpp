/*
 * $Id: fprn.cpp,v 1.2 2009/03/23 14:23:25 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */

#include "stdafx.h"
#include "fprn.h"
#include "util.h"

#include <jni.h>
#include <stdio.h>

//---------------------------------------------------------------------------
void _ReleaseControlObject(JNI_ARGS)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(obj), "addr", "J");
	IOPOSFiscalPrinter_1_6* pI = (IOPOSFiscalPrinter_1_6*)env->GetLongField(obj, fid);
	if (pI != NULL) {
		env->SetLongField(obj, fid, 0L);
		if (pI->Release() != 0L) {
			// I am sorry :)
		}
		CoUninitialize();
	}
}
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ResultCode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ResultCodeExtended, 1_6)
//---------------------------------------------------------------------------
FPRN_FUNC(jint, deleteInstance)(JNI_ARGS)
{
	//_ReleaseControlObject(env, obj);
	return OPOS_SUCCESS;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, release)(JNI_ARGS)
{
	try {		
		GET_FPRN(fprn);
		return fprn->ReleaseDevice();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, open)(JNI_ARGS, jstring deviceName)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDeviceName, deviceName);
		return fprn->Open(bstrDeviceName);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, directIO)(JNI_ARGS, jint command, jintArray data, jobject str)
{
	try {
		GET_FPRN(fprn);
		
		jboolean isCopy = 1;
		jint* pData = (data == NULL) ? NULL : env->GetIntArrayElements(data, &isCopy);
		
		bstr_t bstr;

		jint result = fprn->DirectIO(command, pData, &bstr.GetBSTR());
		if (result == OPOS_SUCCESS) {
			if (data != NULL) {
				env->SetIntArrayRegion(data, 0, env->GetArrayLength(data), pData);
			}

			// TODO: handle returned string (bstr)

		}

		if (isCopy) {

		}

		return result;
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, checkHealth)(JNI_ARGS, jint level)
{
	try {
		GET_FPRN(fprn);
		return fprn->CheckHealth(level);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, close)(JNI_ARGS)
{
	long result = OPOS_SUCCESS;

	try {
		GET_FPRN(fprn);
		fprn->Close();
	}
	catch (_com_error) {
		//result = OPOS_GENERIC_ERROR;
	}

	//_ReleaseControlObject(env, obj);
	return result;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, claim)(JNI_ARGS, jint timeout)
{
	try {
		GET_FPRN(fprn);
		return fprn->ClaimDevice(timeout);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, getState)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->State;
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_S_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jstring, getPhysicalDeviceName)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		_bstr_t value = fprn->GetDeviceName();
		return BSTR2JSTR(env, value);
	}
	catch (_com_error) {
		// ignore
	}

	return JSTR_NULL;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jstring, getPhysicalDeviceDescription)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		_bstr_t value = fprn->GetDeviceDescription();
		return BSTR2JSTR(env, value);
	}
	catch (_com_error) {
		// ignore
	}

	return JSTR_NULL;
}
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(FreezeEvents, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(FreezeEvents, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(DeviceEnabled, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(DeviceEnabled, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(Claimed, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(CheckHealthText, 1_6)
//---------------------------------------------------------------------------
FPRN_FUNC(jint, verifyItem)(JNI_ARGS, jstring itemName, jint vatID)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrItemName, itemName);
		return fprn->VerifyItem(bstrItemName, vatID);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setVatValue)(JNI_ARGS, jint vatID, jstring vatValue)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrVatValue, vatValue);
		return fprn->SetVatValue(vatID, bstrVatValue);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setVatTable)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->SetVatTable();
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setTrailerLine)(JNI_ARGS, jint lineNumber, 
	jstring text, jboolean doubleWidth)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrText, text);
		return fprn->SetTrailerLine(
			lineNumber, 
			bstrText, 
			(doubleWidth == 0) ? VARIANT_FALSE : VARIANT_TRUE);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setStoreFiscalID)(JNI_ARGS, jstring ID)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrID, ID);
		return fprn->SetStoreFiscalID(bstrID);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setPOSID)(JNI_ARGS, jstring POSID, jstring cashierID)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrPOSID, POSID);
		JSTR2BSTR(env, bstrCashierID, cashierID);
		return fprn->SetPOSID(bstrPOSID, bstrCashierID);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setHeaderLine)(JNI_ARGS, jint lineNumber, 
	jstring text, jboolean doubleWidth)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrText, text);
		return fprn->SetHeaderLine(
			lineNumber, 
			bstrText, 
			(doubleWidth == 0) ? VARIANT_FALSE : VARIANT_TRUE);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setDate)(JNI_ARGS, jstring date)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDate, date);
		return fprn->SetDate(bstrDate);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, resetPrinter)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->ResetPrinter();
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printZReport)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->PrintZReport();
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printXReport)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->PrintXReport();
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printReport)(JNI_ARGS, jint reportType, 
	jstring startNum, jstring endNum)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrStartNum, startNum);
		JSTR2BSTR(env, bstrEndNum, endNum);
		return fprn->PrintReport(reportType, bstrStartNum, bstrEndNum);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecVoidItem)(JNI_ARGS, jstring description, jlong amount,
	jint quantity, jint adjustmentType, jlong adjustment, jint vatInfo)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount, cyAdjustment;
		cyAmount.int64 = amount;
		cyAdjustment.int64 = adjustment;
		return fprn->PrintRecVoidItem(bstrDescription, cyAmount, quantity, adjustmentType, cyAdjustment, vatInfo);
	}
	catch (_com_error) {
		// ignore
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecVoid)(JNI_ARGS, jstring description)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		return fprn->PrintRecVoid(bstrDescription);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecTotal)(JNI_ARGS, jlong total, jlong payment, 
	jstring description)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyTotal, cyPayment;
		cyTotal.int64 = total;
		cyPayment.int64 = payment;
		return fprn->PrintRecTotal(cyTotal, cyPayment, bstrDescription);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecSubtotalAdjustment)(JNI_ARGS, jint adjustmentType,
	jstring description, jlong amount)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecSubtotalAdjustment(adjustmentType, bstrDescription, cyAmount);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecSubtotal)(JNI_ARGS, jlong amount)
{
	try {
		GET_FPRN(fprn);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecSubtotal(cyAmount);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecRefund)(JNI_ARGS, jstring description, jlong amount, jint vatInfo)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecRefund(bstrDescription, cyAmount, vatInfo);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecNotPaid)(JNI_ARGS, jstring description, jlong amount)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecNotPaid(bstrDescription, cyAmount);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecMessage)(JNI_ARGS, jstring message)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrMessage, message);
		return fprn->PrintRecMessage(bstrMessage);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemAdjustment)(JNI_ARGS, jint adjustmentType,
	jstring description, jlong amount, jint vatInfo)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecItemAdjustment(adjustmentType, bstrDescription, cyAmount, vatInfo);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItem)(JNI_ARGS, jstring description, jlong price,
	jint quantity, jint vatInfo, jlong unitPrice, jstring unitName)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		JSTR2BSTR(env, bstrUnitName, unitName);
		CURRENCY cyPrice, cyUnitPrice;
		cyPrice.int64 = price;
		cyUnitPrice.int64 = unitPrice;
		return fprn->PrintRecItem(bstrDescription, cyPrice, quantity, vatInfo, cyUnitPrice, bstrUnitName);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printPowerLossReport)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->PrintPowerLossReport();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printPeriodicTotalsReport)(JNI_ARGS, jstring date1, jstring date2)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDate1, date1);
		JSTR2BSTR(env, bstrDate2, date2);
		return fprn->PrintPeriodicTotalsReport(bstrDate1, bstrDate2);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printNormal)(JNI_ARGS, jint station, jstring data)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrData, data);
		return fprn->PrintNormal(station, bstrData);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printFixedOutput)(JNI_ARGS, jint documentType, 
	jint lineNumber, jstring data)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrData, data);
		return fprn->PrintFixedOutput(documentType, lineNumber, bstrData);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printFiscalDocumentLine)(JNI_ARGS, jstring documentLine)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDocumentLine, documentLine);
		return fprn->PrintFiscalDocumentLine(bstrDocumentLine);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printDuplicateReceipt)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->PrintDuplicateReceipt();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, getVatEntry)(JNI_ARGS, jint vatID, 
	jint optArgs, jintArray vatRate)
{
	try {
		GET_FPRN(fprn);
		jboolean isCopy = 1;
		jint result;
		jint* piVatRate = env->GetIntArrayElements(vatRate, &isCopy);
		result = fprn->GetVatEntry(vatID, optArgs, piVatRate);
		env->SetIntArrayRegion(vatRate, 0, env->GetArrayLength(vatRate), piVatRate);
		if (isCopy) {
			// TODO: free piVatRate
		}
		return result;
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, getTotalizer)(JNI_ARGS, jint vatID, 
	jint optArgs, jobjectArray data)
{
	try {
		GET_FPRN(fprn);
		bstr_t bstrData;
		jint result = fprn->GetTotalizer(vatID, optArgs, &bstrData.GetBSTR());
		if (result == OPOS_SUCCESS) {
			env->SetObjectArrayElement(data, 0, BSTR2JSTR(env, bstrData));
		}

		return result;
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, getDate)(JNI_ARGS, jobjectArray data)
{
	try {
		GET_FPRN(fprn);

		bstr_t bstrDate;
		jint result = fprn->GetDate(&bstrDate.GetBSTR());

		if (result == OPOS_SUCCESS) {
			env->SetObjectArrayElement(data, 0, BSTR2JSTR(env, bstrDate));
		}

		return result;
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, getData)(JNI_ARGS, jint dataItem, 
	jintArray optArgs, jobjectArray data)
{
	try {
		GET_FPRN(fprn);
		jint lOptArgs = 0;

		env->GetIntArrayRegion(optArgs, 0, 1, &lOptArgs);
		bstr_t bstrData;
		jint result = fprn->GetData(dataItem, &lOptArgs, &bstrData.GetBSTR());

		if (result == OPOS_SUCCESS) {
			env->SetIntArrayRegion(optArgs, 0, 1, &lOptArgs);
			env->SetObjectArrayElement(data, 0, BSTR2JSTR(env, bstrData));
		}

		return result;
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endTraining)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndTraining();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endRemoval)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndRemoval();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endNonFiscal)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndNonFiscal();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endItemList)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndItemList();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endInsertion)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndInsertion();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endFixedOutput)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndFixedOutput();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endFiscalReceipt)(JNI_ARGS, jboolean printHeader)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndFiscalReceipt((printHeader == 0) ? VARIANT_FALSE : VARIANT_TRUE);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, endFiscalDocument)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->EndFiscalDocument();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, clearOutput)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->ClearOutput();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, clearError)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->ClearError();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginTraining)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginTraining();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginRemoval)(JNI_ARGS, jint timeout)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginRemoval(timeout);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginNonFiscal)(JNI_ARGS)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginNonFiscal();
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginItemList)(JNI_ARGS, jint vatID)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginItemList(vatID);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginInsertion)(JNI_ARGS, jint timeout)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginInsertion(timeout);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginFixedOutput)(JNI_ARGS, jint station, jint documentType)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginFixedOutput(station, documentType);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginFiscalReceipt)(JNI_ARGS, jboolean printHeader)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginFiscalReceipt((printHeader == 0) ? VARIANT_FALSE : VARIANT_TRUE);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, beginFiscalDocument)(JNI_ARGS, jint documentAmount)
{
	try {
		GET_FPRN(fprn);
		return fprn->BeginFiscalDocument(documentAmount);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(TrainingModeActive, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(SlipSelection, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(SlipSelection, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(SlpNearEnd, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(SlpEmpty, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(ReservedWord, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(RemainingFiscalMemory, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(RecNearEnd, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(RecEmpty, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(QuantityLength, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(QuantityDecimalPlaces, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(PrinterState, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(PredefinedPaymentLines, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(NumVatRates, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(NumTrailerLines, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(NumHeaderLines, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(MessageLength, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(JrnNearEnd, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(JrnEmpty, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(FlagWhenIdle, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(FlagWhenIdle, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(ErrorString, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ErrorStation, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ErrorState, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ErrorOutID, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ErrorLevel, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(DuplicateReceipt, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(DuplicateReceipt, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(DescriptionLength, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(DayOpened, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CoverOpen, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(CountryCode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(CheckTotal, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CheckTotal, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_BOOLEAN_R(AsyncMode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(AsyncMode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(AmountDecimalPlaces, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(PowerState, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(PowerNotify, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(PowerNotify, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(OutputID, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapXReport, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapValidateJournal, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapTrainingMode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSubtotal, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSubPercentAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSubAmountAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpValidation, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpPresent, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpNearEndSensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpFullSlip, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpFiscalDocument, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSlpEmptySensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetVatTable, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetTrailer, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetStoreFiscalID, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetPOSID, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetHeader, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapReservedWord, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapRemainingFiscalMemory, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapRecPresent, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapRecNearEndSensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapRecEmptySensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapReceiptNotPaid, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPredefinedPaymentLines, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(CapPowerReporting, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPowerLossReport, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPositiveAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPercentAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapOrderAdjustmentFirst, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapNonFiscalMode, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapJrnPresent, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapJrnNearEndSensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapJrnEmptySensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapItemList, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapIndependentHeader, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapHasVatTable, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapFixedOutput, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapDuplicateReceipt, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapDoubleWidth, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapCoverSensor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapCheckTotal, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapAmountNotPaid, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapAmountAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapAdditionalLines, 1_6)
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecTaxID)(JNI_ARGS, jstring taxID)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrTaxID, taxID);
		return fprn->PrintRecTaxID(bstrTaxID);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecSubtotalAdjustVoid)(JNI_ARGS, 
	jint adjustmentType, jlong amount)
{
	try {
		GET_FPRN(fprn);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecSubtotalAdjustVoid(adjustmentType, cyAmount);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecRefundVoid)(JNI_ARGS, jstring description,
	jlong amount, jint vatInfo)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecRefundVoid(bstrDescription, cyAmount, vatInfo);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecPackageAdjustVoid)(JNI_ARGS, 
	jint adjustmentType, jstring vatAdjustment)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrVatAdjustment, vatAdjustment);
		return fprn->PrintRecPackageAdjustVoid(adjustmentType, bstrVatAdjustment);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecPackageAdjustment)(JNI_ARGS, jint adjustmentType,
	jstring description, jstring vatAdjustment)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		JSTR2BSTR(env, bstrVatAdjustment, vatAdjustment);
		return fprn->PrintRecPackageAdjustment(adjustmentType, bstrDescription, bstrVatAdjustment);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemFuelVoid)(JNI_ARGS, jstring description, 
	jlong price, jint vatInfo, jlong specialTax)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyPrice, cySpecialTax;
		cyPrice.int64 = price;
		cySpecialTax.int64 = specialTax;
		return fprn->PrintRecItemFuelVoid(bstrDescription, cyPrice, vatInfo, cySpecialTax);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemFuel)(JNI_ARGS, jstring description,
	jlong price, jint quantity, jint vatInfo, jlong unitPrice, 
	jstring unitName, jlong specialTax, jstring specialTaxName)
{
	try {
		GET_FPRN(fprn);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyPrice; 
		cyPrice.int64 = price;
		CURRENCY cyUnitPrice; 
		cyUnitPrice.int64 = unitPrice;
		JSTR2BSTR(env, bstrUnitName, unitName);
		CURRENCY cySpecialTax;
		cySpecialTax.int64 = specialTax;
		JSTR2BSTR(env, bstrSpecialTaxName, specialTaxName);

		return fprn->PrintRecItemFuel(bstrDescription, cyPrice, quantity, 
			vatInfo, cyUnitPrice, bstrUnitName, cySpecialTax, bstrSpecialTaxName);
	}
	catch (_com_error) {
		// do nothing
	}

	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecCash)(JNI_ARGS, jlong amount)
{
	try {
		GET_FPRN(fprn);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;

		return fprn->PrintRecCash(cyAmount);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, setCurrency)(JNI_ARGS, jint newCurrency)
{
	try {
		GET_FPRN(fprn);
		fprn->SetCurrency(newCurrency);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(TotalizerType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(TotalizerType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_STRING_R(PreLine, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(PreLine, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_STRING_R(PostLine, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(PostLine, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(MessageType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(MessageType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(FiscalReceiptType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(FiscalReceiptType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(FiscalReceiptStation, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(FiscalReceiptStation, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(DateType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(DateType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_INTEGER_R(ContractorId, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ContractorId, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_STRING_R(ChangeDue, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(ChangeDue, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_STRING_R(AdditionalTrailer, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(AdditionalTrailer, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPSET_STRING_R(AdditionalHeader, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_STRING_R(AdditionalHeader, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_INTEGER_R(ActualCurrency, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapTotalizerType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapSetCurrency, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPostPreLine, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPackageAdjustment, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapOnlyVoidLastItem, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapMultiContractor, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapFiscalReceiptType, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapFiscalReceiptStation, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapEmptyReceiptIsVoidable, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapChangeDue, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapAdditionalTrailer, 1_6)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapAdditionalHeader, 1_6)
//---------------------------------------------------------------------------
// 1.8
//---------------------------------------------------------------------------
FPRN_FUNC(jint, updateStatistics)(JNI_ARGS, jstring statisticsBuffer)
{
	try {
		GET_FPRN_R(fprn, 1_8);
		JSTR2BSTR(env, bstrStatisticsBuffer, statisticsBuffer);
		return fprn->UpdateStatistics(bstrStatisticsBuffer);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, retrieveStatistics)(JNI_ARGS, jobjectArray statisticsBuffer)
{
	try {
		GET_FPRN_R(fprn, 1_8);
		bstr_t bstrBuffer;
		jint result = fprn->RetrieveStatistics(&bstrBuffer.GetBSTR());

		if (result == OPOS_SUCCESS) {
			env->SetObjectArrayElement(statisticsBuffer, 0, BSTR2JSTR(env, bstrBuffer));
		}

		return result;
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, resetStatistics)(JNI_ARGS, jstring statisticsBuffer)
{
	try {
		GET_FPRN_R(fprn, 1_8);
		JSTR2BSTR(env, bstrStatisticsBuffer, statisticsBuffer);
		return fprn->ResetStatistics(bstrStatisticsBuffer);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapUpdateStatistics, 1_8)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapStatisticsReporting, 1_8)
//---------------------------------------------------------------------------
// 1.9
//---------------------------------------------------------------------------
FPRN_FUNC(jint, updateFirmware)(JNI_ARGS, jstring firmwareFileName)
{
	try {
		GET_FPRN_R(fprn, 1_9);
		JSTR2BSTR(env, bstrFirmwareFileName, firmwareFileName);
		return fprn->UpdateFirmware(bstrFirmwareFileName);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, compareFirmwareVersion)(JNI_ARGS, 
	jstring firmwareFileName, jintArray result)
{
	try {
		GET_FPRN_R(fprn, 1_9);
		JSTR2BSTR(env, bstrFirmwareFileName, firmwareFileName);
		jint ret, compareResult;
		ret = fprn->CompareFirmwareVersion(bstrFirmwareFileName, &compareResult);

		if (ret == OPOS_SUCCESS) {
			env->SetIntArrayRegion(result, 0, 1, &compareResult);
		}

		return ret;
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapUpdateFirmware, 1_9)
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapCompareFirmwareVersion, 1_9)
//---------------------------------------------------------------------------
//	1.11
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemAdjustmentVoid)(JNI_ARGS, jint adjustmentType,
	jstring description, jlong amount, jint vatInfo)
{
	try {
		GET_FPRN_R(fprn, 1_11);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		return fprn->PrintRecItemAdjustmentVoid(adjustmentType, bstrDescription, 
			cyAmount, vatInfo);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemVoid)(JNI_ARGS, jstring description, jlong price,
	jint quantity, jint vatInfo, jlong unitPrice, jstring unitName)
{
	try {
		GET_FPRN_R(fprn, 1_11);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyPrice;
		cyPrice.int64 = price;
		CURRENCY cyUnitPrice;
		cyUnitPrice.int64 = unitPrice;
		JSTR2BSTR(env, bstrUnitName, unitName);

		return fprn->PrintRecItemVoid(bstrDescription, cyPrice, quantity, 
			vatInfo, cyUnitPrice, bstrUnitName);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_PROPGET_BOOLEAN_R(CapPositiveSubtotalAdjustment, 1_11)
//---------------------------------------------------------------------------
//	1.12
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemRefundVoid)(JNI_ARGS, jstring description,
	jlong amount, jint quantity, jint vatInfo, jlong unitAmount, 
	jstring unitName)
{
	try {
		GET_FPRN_R(fprn, 1_12);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		CURRENCY cyUnitAmount;
		cyUnitAmount.int64 = unitAmount;
		JSTR2BSTR(env, bstrUnitName, unitName);

		return fprn->PrintRecItemRefundVoid(bstrDescription, cyAmount, quantity,
			vatInfo, cyUnitAmount, bstrUnitName);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
FPRN_FUNC(jint, printRecItemRefund)(JNI_ARGS, jstring description,
	jlong amount, jint quantity, jint vatInfo, jlong unitAmount, 
	jstring unitName)
{
	try {
		GET_FPRN_R(fprn, 1_12);
		JSTR2BSTR(env, bstrDescription, description);
		CURRENCY cyAmount;
		cyAmount.int64 = amount;
		CURRENCY cyUnitAmount;
		cyUnitAmount.int64 = unitAmount;
		JSTR2BSTR(env, bstrUnitName, unitName);

		return fprn->PrintRecItemRefund(bstrDescription, cyAmount, quantity,
			vatInfo, cyUnitAmount, bstrUnitName);
	}
	catch (_com_error) {
		// do nothing
	}
	return OPOS_GENERIC_ERROR;
}
//---------------------------------------------------------------------------
