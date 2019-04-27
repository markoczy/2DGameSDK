#ifndef __GAMESDK_DLL_H__
#define __GAMESDK_DLL_H__

#ifdef DLLBUILD_GAMESDK
#define GAMESDK_DLL __declspec(dllexport)
#else
#define GAMESDK_DLL __declspec(dllimport)
#endif

#endif