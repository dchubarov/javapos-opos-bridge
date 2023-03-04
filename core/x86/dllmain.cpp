/*
 * $Id: dllmain.cpp,v 1.1 2009/01/23 10:17:06 dch Exp $
 * 
 * Copyright (c) 2008 Anker-East Ltd (http://www.anker-east.ru).
 * All rights reserved.
 * 
 */

#include "stdafx.h"

#include <ole2.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	HRESULT hr = S_OK;

	switch (dwReason)	{
		case DLL_PROCESS_ATTACH:
			hr = CoInitialize(NULL);
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			CoUninitialize();
			break;
	}

	return SUCCEEDED(hr) ? TRUE : FALSE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
