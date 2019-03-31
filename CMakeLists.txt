cmake_minimum_required (VERSION 3.0.0 FATAL_ERROR)

# Project Settings
project (MainProject)

# setup sfml
set(SFML_VERSION "2.5.1")
set(SFML_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/SFML-${SFML_VERSION}")
set(SFML_INCLUDE_DIR "${SFML_ROOT_DIR}/include")
set(SFML_LIBRARIES_PATH "${SFML_ROOT_DIR}/lib")
# sfml libraries release
set(SFML_SYSTEM_LIB "${SFML_LIBRARIES_PATH}/libsfml-system.a")
set(SFML_GRAPHICS_LIB "${SFML_LIBRARIES_PATH}/libsfml-graphics.a")
set(SFML_WINDOW_LIB "${SFML_LIBRARIES_PATH}/libsfml-window.a")
set(SFML_LIBRARIES ${SFML_SYSTEM_LIB} ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB})
# (Windows only!) copy SFML DLL's for convenience
set(SFML_DLL_DIR "${SFML_ROOT_DIR}/bin")

# setup game sdk
set(SDK_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/libs/2DGameSDK")
set(SDK_INCLUDE_DIR "${SDK_ROOT_DIR}/include")
set(SDK_LIBRARIES_PATH "${SDK_ROOT_DIR}/lib")
set(SDK_LIB_NAME "lib2DGameSDK")
set(SDK_LIB "${SDK_LIBRARIES_PATH}/${SDK_LIB_NAME}.dll.a")
set(SDK_DLL_DIR "${SDK_ROOT_DIR}/bin")
set(SDK_LIBRARIES ${SDK_LIB})

# reference projects
add_subdirectory("${CMAKE_HOME_DIRECTORY}/Project_2DGameSDK")
add_subdirectory("${CMAKE_HOME_DIRECTORY}/Project_Prototype")