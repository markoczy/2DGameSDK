#ifndef __GAMESDK_CONFIG_H__
#define __GAMESDK_CONFIG_H__

// Include DLL Imports/Exports
#include <2DGameSDK/dll/gamesdk_dll.h>

// Include Logger when building DLL
#ifdef DLLBUILD_GAMESDK
#include <2DGameSDK/dll/gamesdk_logger.h>
#endif

#endif