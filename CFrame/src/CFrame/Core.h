#pragma once

#ifdef CF_PLATFORM_WINDOWS
	#ifdef CF_BUILD_DLL
		#define CFRAME_API //__declspec(dllexport)
	#else
		#define CFRAME_API //__declspec(dllimport)
	#endif
#else
	#error CFrame only supports Windows!
#endif