/**
 * @file gamesdk_dll.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Holds all configurations of the DLL build for project 2DGameSDK
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GAMESDK_DLL_H__
#define __GAMESDK_DLL_H__

// Include debug logging for dll build
//
// =======================================
// Preprocessor defines for DLL build:
//
// - GAMESDK_LOG_D: Debug-Fatal
// - GAMESDK_LOG_I: Info-Fatal
// - GAMESDK_LOG_W: Warn-Fatal
// - GAMESDK_LOG_E: Error-Fatal
//
// > Fatal Logs cannot be disabled
// =======================================
//
#ifdef DLLBUILD_GAMESDK
#include <2DGameSDK/dll/logger/gamesdk_logger.h>
#endif

// define DLL Exports
#ifdef DLLBUILD_GAMESDK
#define GAMESDK_DLL __declspec(dllexport)
#else
#define GAMESDK_DLL __declspec(dllimport)
#endif

#endif