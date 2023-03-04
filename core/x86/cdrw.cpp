
#include "stdafx.h"
#include "cdrw.h"
#include "util.h"

#include <jni.h>
#include <stdio.h>

//---------------------------------------------------------------------------
void _ReleaseCashDrawerControl(JNI_ARGS)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(obj), "addr", "J");
	IOPOSCashDrawer_1_5* pI = (IOPOSCashDrawer_1_5*)env->GetLongField(obj, fid);
	if (pI != NULL) {
		env->SetLongField(obj, fid, 0L);
		if (pI->Release() != 0L) {
			// I am sorry :)
		}
	}
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetErrorCode)(JNI_ARGS) 
{
	jint ret = OPOS_SUCCESS;
	try {
		GET_CDRW(cdrw);
		ret = cdrw->ResultCode;
	}
	catch (_com_error) {
		ret = OPOS_E_FAILURE;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetErrorCodeExtended)(JNI_ARGS) 
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		ret = cdrw->ResultCodeExtended;
	}
	catch (_com_error) { }
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetCapStatus)(JNI_ARGS)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		if (VARIANT_TRUE == cdrw->CapStatus) {
			ret = 1;
		}
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetDrawerOpened)(JNI_ARGS)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		if (VARIANT_TRUE == cdrw->DrawerOpened) {
			ret = 1;
		}
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nOpenDrawer)(JNI_ARGS) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->OpenDrawer();
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nWaitForDrawerClose)(JNI_ARGS, jint beepTimeout, 
	jint beepFrequency, jint beepDuration, jint beepDelay) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->WaitForDrawerClose(beepTimeout, beepFrequency, 
			beepDuration, beepDelay);
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jstring, nGetCheckHealthText)(JNI_ARGS)
{
	jstring ret = JSTR_NULL;

	try {
		GET_CDRW(cdrw);
		_bstr_t value = cdrw->CheckHealthText;
		ret = BSTR2JSTR(env, value);
	}
	catch (_com_error) { }

	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetClaimed)(JNI_ARGS)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		if (VARIANT_TRUE == cdrw->Claimed) {
			ret = 1;
		}
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetDeviceEnabled)(JNI_ARGS)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		if (VARIANT_TRUE == cdrw->DeviceEnabled) {
			ret = 1;
		}
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nSetDeviceEnabled)(JNI_ARGS, jboolean enable)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->DeviceEnabled = (enable == 1) ? VARIANT_TRUE : VARIANT_FALSE;
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetFreezeEvents)(JNI_ARGS)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		if (VARIANT_TRUE == cdrw->FreezeEvents) {
			ret = 1;
		}
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nSetFreezeEvents)(JNI_ARGS, jboolean freezeEvents)
{
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->FreezeEvents = (freezeEvents == 1) ? VARIANT_TRUE : VARIANT_FALSE;
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jstring, nGetPhysicalDeviceDescription)(JNI_ARGS)
{
	jstring ret = JSTR_NULL;

	try {
		GET_CDRW(cdrw);
		_bstr_t value = cdrw->GetDeviceDescription();
		ret = BSTR2JSTR(env, value);
	}
	catch (_com_error) { }

	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jstring, nGetPhysicalDeviceName)(JNI_ARGS)
{
	jstring ret = JSTR_NULL;

	try {
		GET_CDRW(cdrw);
		_bstr_t value = cdrw->GetDeviceName();
		ret = BSTR2JSTR(env, value);
	}
	catch (_com_error) { }

	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nGetState)(JNI_ARGS) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		ret = cdrw->State;
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nClaim)(JNI_ARGS, jint timeout) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->ClaimDevice(timeout);
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nClose)(JNI_ARGS) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->Close();
		_ReleaseCashDrawerControl(env, obj);
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nCheckHealth)(JNI_ARGS, jint level) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->CheckHealth(level);
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nOpen)(JNI_ARGS, jstring logicalName) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		JSTR2BSTR(env, bstrLogicalName, logicalName);
		cdrw->Open(bstrLogicalName);
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
CDRW_FUNC(jint, nRelease)(JNI_ARGS) {
	jint ret = 0;
	try {
		GET_CDRW(cdrw);
		cdrw->ReleaseDevice();
	}
	catch (_com_error) { 
		ret = -1;
	}
	return ret;
}
//---------------------------------------------------------------------------
