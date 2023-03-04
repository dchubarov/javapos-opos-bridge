/*
 * $Id: fprn.h,v 1.1 2009/01/23 10:17:06 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */
#ifndef __FPRN_H_INCLUDED__
#define __FPRN_H_INCLUDED__

#import "OPOSFiscalPrinter.ocx" no_namespace //, embedded_idl, no_dual_interfaces

#ifndef OPOS_H
#include <opos.h>
#endif

#ifndef OPOSFPTR_H
#include <oposfptr.h>
#endif

#define GET_FPRN(v) GET_FPRN_R(v, 1_6)

#define GET_FPRN_R(v, r)																		\
	jfieldID __fid = env->GetFieldID(env->GetObjectClass(obj), "addr", "J");					\
	IOPOSFiscalPrinter_1_6* __pI = (IOPOSFiscalPrinter_1_6*)env->GetLongField(obj, __fid);		\
	if (__pI == NULL) {																			\
		CoInitialize(NULL);																		\
		IOPOSFiscalPrinter_1_6Ptr __spI;														\
		HRESULT __hr = __spI.CreateInstance(L"OPOS.FiscalPrinter");								\
		if (FAILED(__hr)) {																		\
			_com_issue_error(__hr);																\
		}																						\
		__pI = __spI.Detach();																	\
		env->SetLongField(obj, __fid, (jlong)__pI);												\
	}																							\
	IOPOSFiscalPrinter_ ## r ## Ptr v(__pI);												    \
	if (!v) {																					\
		_com_issue_error(E_NOINTERFACE);														\
	}

/* For static version
#define GET_FPRN_R(v, r)												     \
	if (!g_piFiscalPrinter) {											     \
		IOPOSFiscalPrinter_1_6Ptr spi;                                       \
		HRESULT hr = spi.CreateInstance(L"OPOS.FiscalPrinter");              \
		if (FAILED(hr)) {													 \
			_com_issue_error(hr);											 \
		}																	 \
		g_piFiscalPrinter = spi.Detach();									 \
	}                                                                        \
	IOPOSFiscalPrinter_ ## r ## Ptr v(g_piFiscalPrinter);					 \
	if (!v) {																 \
		_com_issue_error(E_NOINTERFACE);									 \
	}
*/

#define FPRN_FUNC(ret, fn) \
	extern "C" JNIEXPORT ret JNICALL Java_ru_anker_1east_hw_oposbridge_fiscal_OposFiscalPrinterService_00024Wrapper_ ## fn

#define FPRN_PROPSET_BOOLEAN_R(prop, r) \
	FPRN_FUNC(jint, set ## prop)(JNI_ARGS, jboolean prop) {													 \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			fprn->prop = (prop == 0) ? VARIANT_FALSE : VARIANT_TRUE;										 \
			return OPOS_SUCCESS;																			 \
		}																									 \
		catch (_com_error) { }																				 \
		return OPOS_GENERIC_ERROR;																			 \
	}

#define FPRN_PROPGET_BOOLEAN_R(prop, r) \
	FPRN_FUNC(jboolean, get ## prop)(JNI_ARGS) {															 \
		jboolean ret = 0;																					 \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			if (fprn->prop == VARIANT_TRUE) {																 \
				ret = 1;																					 \
			}																								 \
		}																									 \
		catch (_com_error) { }																				 \
		return ret;																							 \
	}

#define FPRN_PROPSET_STRING_R(prop, r) \
	FPRN_FUNC(jint, set ## prop)(JNI_ARGS, jstring prop) {												     \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			JSTR2BSTR(env, bstr, prop);																		 \
			fprn->prop = bstr;																				 \
			return OPOS_SUCCESS;																			 \
		}																									 \
		catch (_com_error) { }																				 \
		return OPOS_GENERIC_ERROR;																			 \
	}

#define FPRN_PROPGET_STRING_R(prop, r) \
	FPRN_FUNC(jstring, get ## prop)(JNI_ARGS) {																 \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			return BSTR2JSTR(env, fprn->prop);																 \
		}																									 \
		catch (_com_error) { }																				 \
		return NULL;																						 \
	}

#define FPRN_PROPSET_INTEGER_R(prop, r) \
	FPRN_FUNC(jint, set ## prop)(JNI_ARGS, jint prop) {														 \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			fprn->prop = prop;																				 \
			return OPOS_SUCCESS;																			 \
		}																									 \
		catch (_com_error) { }																				 \
		return OPOS_GENERIC_ERROR;																			 \
	}

#define FPRN_PROPGET_INTEGER_R(prop, r) \
	FPRN_FUNC(jint, get ## prop)(JNI_ARGS) {																 \
		jint ret = -1;																						 \
		try {																								 \
			GET_FPRN_R(fprn, r);																			 \
			ret = fprn->prop;																				 \
		}																									 \
		catch (_com_error) { }																				 \
		return ret;																							 \
	}

#endif /* __FPRN_H_INCLUDED__ */
