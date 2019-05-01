#ifndef __GAMESDK_LOGGER_H__
#define __GAMESDK_LOGGER_H__

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
#define LOGD(a) std::cout << "Debug___@__" << __FUNCTION__ << ":" << a << std::endl;
#define DLOGD(a, b) std::cout << "Debug___@__" << __FUNCTION__ << ": " << a << " " << b << std::endl;
// define lower level
#ifndef GAMESDK_LOG_I
#define GAMESDK_LOG_I
#endif
#endif

#ifdef GAMESDK_LOG_I
#define LOGI(a) std::cout << "Info____@__" << __FUNCTION__ << ": " << a << std::endl;
#define DLOGI(a, b) std::cout << "Info____@__" << __FUNCTION__ << ": " << a << " " << b << std::endl;
// define lower level
#ifndef GAMESDK_LOG_W
#define GAMESDK_LOG_W
#endif
#endif

#ifdef GAMESDK_LOG_W
#define LOGW(a) std::cout << "!Warn!__@__" << __FUNCTION__ << ": " << a << std::endl;
#define DLOGW(a, b) std::cout << "!Warn!__@__" << __FUNCTION__ << ": " << a << " " << b << std::endl;
// define lower level
#ifndef GAMESDK_LOG_E
#define GAMESDK_LOG_E
#endif
#endif

#ifdef GAMESDK_LOG_E
#define LOGE(a) std::cout << "!!ERR!!_@__" << __FUNCTION__ << ": " << a << std::endl;
#define DLOGE(a, b) std::cout << "!!ERR!!_@__" << __FUNCTION__ << ": " << a << " " << b << std::endl;
#endif

#ifndef GAMESDK_LOG_D
#define LOGD(a)
#define DLOGD(a, b)
#endif

#ifndef GAMESDK_LOG_I
#define LOGI(a)
#define DLOGI(a, b)
#endif

#ifndef GAMESDK_LOG_W
#define LOGW(a)
#define DLOGW(a, b)
#endif

#ifndef GAMESDK_LOG_E
#define LOGE(a)
#define DLOGE(a, b)
#endif

#endif