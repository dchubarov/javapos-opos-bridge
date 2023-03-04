/*
 * $Id: util.h,v 1.1 2009/01/23 10:17:06 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */
#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__

#define JSTR2BSTR(env, bs, js)												 \
	_bstr_t bs;																 \
	if (TRUE) {																 \
		jboolean isCopy = 1;												 \
		bs = (const wchar_t*)env->GetStringChars(js, &isCopy);				 \
		if (isCopy) {														 \
			/* TODO: free jstring (how?) */									 \
		}																	 \
	}

#define BSTR2JSTR(env, bs)													 \
	env->NewString((const jchar*)(wchar_t*)bs, bs.length())

#define JSTR_NULL NULL

#define OPOS_GENERIC_ERROR OPOS_E_FAILURE;

#define JNI_ARGS \
	JNIEnv* env, jobject obj

/* Static version
#define JNI_ARGS \
	JNIEnv* env, jclass clazz
*/

#endif /* !__UTIL_H_INCLUDED__ */
