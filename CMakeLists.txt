cmake_minimum_required (VERSION 3.0.0 FATAL_ERROR)

################################################################################
# Project Settings
################################################################################
project (MainProject)
message("Build start ${CMAKE_BUILD_TYPE}")

# Assume Debug builds as default
if (NOT CMAKE_BUILD_TYPE)
    message("Build not specified setting Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Show all warnings
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

################################################################################
# Setup sfml
################################################################################
set(SFML_VERSION "2.5.1")
set(SFML_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/SFML-${SFML_VERSION}")
set(SFML_INCLUDE_DIR "${SFML_ROOT_DIR}/include")
set(SFML_LIBRARIES_PATH "${SFML_ROOT_DIR}/lib")
# sfml libraries release
set(SFML_SYSTEM_LIB "${SFML_LIBRARIES_PATH}/libsfml-system.a")
set(SFML_GRAPHICS_LIB "${SFML_LIBRARIES_PATH}/libsfml-graphics.a")
set(SFML_WINDOW_LIB "${SFML_LIBRARIES_PATH}/libsfml-window.a")
set(SFML_LIBRARIES ${SFML_SYSTEM_LIB} ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB})
# sfml libraries debug
set(SFML_SYSTEM_LIB_D "${SFML_LIBRARIES_PATH}/libsfml-system-d.a")
set(SFML_GRAPHICS_LIB_D "${SFML_LIBRARIES_PATH}/libsfml-graphics-d.a")
set(SFML_WINDOW_LIB_D "${SFML_LIBRARIES_PATH}/libsfml-window-d.a")
set(SFML_LIBRARIES_D ${SFML_SYSTEM_LIB_D} ${SFML_GRAPHICS_LIB_D} ${SFML_WINDOW_LIB_D})
# (Windows only!) copy SFML DLL's for convenience
set(SFML_DLL_DIR "${SFML_ROOT_DIR}/bin")

################################################################################
# Setup Box2D
################################################################################
set(BOX2D_VERSION "2.3.1")
set(BOX2D_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/BOX2D-${BOX2D_VERSION}")
set(BOX2D_INCLUDE_DIR "${BOX2D_ROOT_DIR}/include")
set(BOX2D_LIBRARIES_PATH "${BOX2D_ROOT_DIR}/lib")
# Box2D libraries release
set(BOX2D_LIB "${BOX2D_LIBRARIES_PATH}/libBox2D.dll.a")
set(BOX2D_LIBRARIES ${BOX2D_LIB})
# (Windows only!) copy BOX2D DLL's for convenience
set(BOX2D_DLL_DIR "${BOX2D_ROOT_DIR}/bin")

################################################################################
# Setup  nlohmann json
################################################################################
set(JSON_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/nlohmann-json")
set(JSON_INCLUDE_DIR "${JSON_ROOT_DIR}/include")

################################################################################
# Setup game sdk
################################################################################
set(SDK_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/2DGameSDK")
set(SDK_INCLUDE_DIR "${SDK_ROOT_DIR}/include")
set(SDK_LIBRARIES_PATH "${SDK_ROOT_DIR}/lib")
set(SDK_LIB_NAME "lib2DGameSDK")
set(SDK_LIB "${SDK_LIBRARIES_PATH}/${SDK_LIB_NAME}.dll.a")
set(SDK_DLL_DIR "${SDK_ROOT_DIR}/bin")
set(SDK_LIBRARIES ${SDK_LIB})

################################################################################
# reference projects
################################################################################
add_subdirectory("${CMAKE_HOME_DIRECTORY}/Project_2DGameSDK")
add_subdirectory("${CMAKE_HOME_DIRECTORY}/Project_Prototype")