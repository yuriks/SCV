// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef __SCV_STDAFX_H__
#define __SCV_STDAFX_H__

#ifdef _WIN32
   #ifdef _MSC_VER
      #pragma warning(disable:4996)
      #pragma warning(disable:4706)
      #pragma warning(disable:4127)
      #pragma warning(disable:4018)
      #pragma warning(disable:4995)
      #ifndef _CRT_SECURE_NO_WARNINGS
         #define _CRT_SECURE_NO_WARNINGS
      #endif // _CRT_SECURE_NO_WARNINGS
   #endif // _MSC_VER

   #ifndef WIN32_LEAN_AND_MEAN
      #define WIN32_LEAN_AND_MEAN
   #endif // WIN32_LEAN_AND_MEAN

   #ifndef NOMINMAX
      #define NOMINMAX
   #endif // NOMINMAX

   #include <windows.h>
   #include <tchar.h>
   #include <strsafe.h>   
   #include <shobjidl.h>   
#else // UNIX
   #include <unistd.h>
   #include <dirent.h>   
   #include <errno.h>   
#endif // _WIN32

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
   TypeName(const TypeName&);              \
   TypeName& operator=(const TypeName&)

#ifndef _PI
   #define  _PI 3.141592653589793238462643f
#endif // _PI
#ifndef _PI2
   #define  _PI2 6.283185307179586476925286f
#endif // _PI2
#ifndef _SQRT2
   #define _SQRT2 1.4142135623730950488016887f
#endif // _SQRT2

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <list>
#include <map>

#include <cstdio>
#include <cassert>
#include <ctime>

#endif // __SCV_STDAFX_H__

