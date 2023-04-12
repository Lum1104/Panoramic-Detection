#ifndef _IRAY_BASE_DEF_H_
#define _IRAY_BASE_DEF_H_

#include "windows.h"

namespace Iray
{
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE
#endif

#ifdef CHECK_FREE
#undef CHECK_FREE
#endif

#define CHECK_FREE(ptr) \
	if (ptr) {\
		::free(ptr); \
		ptr = NULL; \
	}


#define CHECK_DELETE(ptr) \
	if (ptr) {	\
		::delete(ptr); \
		ptr = NULL; \
	}

#ifndef EXPORT_DLL
#define EXPORT_API __declspec(dllimport)
#else
#define EXPORT_API __declspec(dllexport)
#endif

#define Irayfourcc(a, b, c, d)\
	((unsigned)(a) | ((unsigned)(b) << 8) | ((unsigned)(c) << 16) | ((unsigned)(d) << 24))

#define PIX_FMT_BIT14 Irayfourcc('B', 'T', '1', '4') // temperature data
#define PIX_FMT_BIT8  Irayfourcc('B', 'T', '0', '8') // grayImage data

}
#endif