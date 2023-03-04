
#ifndef __CDRW_H_INCLUDED__
#define __CDRW_H_INCLUDED__

#import "OPOSCashDrawer.ocx" no_namespace

#ifndef OPOS_H
#include <opos.h>
#endif

#ifndef OPOSCASH_H
#include <oposcash.h>
#endif

#define CDRW_FUNC(ret, fn) \
	extern "C" JNIEXPORT ret JNICALL Java_ru_anker_1east_hw_oposbridge_cash_OposCashDrawerService_ ## fn

#define GET_CDRW(v) GET_CDRW_R(v, 1_5)

#define GET_CDRW_R(v, r)																				\
	jfieldID __fid = env->GetFieldID(env->GetObjectClass(obj), "addr", "J");					\
	IOPOSCashDrawer_1_5* __pI = (IOPOSCashDrawer_1_5*)env->GetLongField(obj, __fid);			\
	if (__pI == NULL) {																			\
		IOPOSCashDrawer_1_5Ptr __spI;															\
		HRESULT __hr = __spI.CreateInstance(L"OPOS.CashDrawer");								\
		if (FAILED(__hr)) {																		\
			_com_issue_error(__hr);																\
		}																						\
		__pI = __spI.Detach();																	\
		env->SetLongField(obj, __fid, (jlong)__pI);												\
	}																							\
	IOPOSCashDrawer_ ## r ## Ptr v(__pI);														\
	if (!v) {																					\
		_com_issue_error(E_NOINTERFACE);														\
	}

#endif /* !__CDRW_H_INCLUDED__ */