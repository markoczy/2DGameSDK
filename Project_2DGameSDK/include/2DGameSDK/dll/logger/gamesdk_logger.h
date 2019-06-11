/**
 * @file gamesdk_logger.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Holds the preprocessor defines for internal logging functions of the
 * project 2DGameSDK
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAMESDK_LOGGER_H__
#define __GAMESDK_LOGGER_H__

#include <iomanip>
#include <iostream>

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

#ifdef GAMESDK_LOG_D
#define LOGD(a) std::cout << "DEBUG   " << __FUNCTION__ << "(" << __LINE__ << ") " << a << std::endl;
// define lower level
#ifndef GAMESDK_LOG_I
#define GAMESDK_LOG_I
#endif
#endif

#ifdef GAMESDK_LOG_I
#define LOGI(a) std::cout << "INFO    " << __FUNCTION__ << "(" << __LINE__ << ") " << a << std::endl;
// define lower level
#ifndef GAMESDK_LOG_W
#define GAMESDK_LOG_W
#endif
#endif

#ifdef GAMESDK_LOG_W
#define LOGW(a) std::cout << "WARN    " << __FUNCTION__ << "(" << __LINE__ << ") " << a << std::endl;
// define lower level
#ifndef GAMESDK_LOG_E
#define GAMESDK_LOG_E
#endif
#endif

#ifdef GAMESDK_LOG_E
#define LOGE(a) std::cout << "ERROR   " << __FUNCTION__ << "(" << __LINE__ << ") " << a << std::endl;
#endif

#ifndef GAMESDK_LOG_D
#define LOGD(a)
#endif

#ifndef GAMESDK_LOG_I
#define LOGI(a)
#endif

#ifndef GAMESDK_LOG_W
#define LOGW(a)
#endif

#ifndef GAMESDK_LOG_E
#define LOGE(a)
#endif

#endif