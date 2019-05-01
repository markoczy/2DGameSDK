# Project Settings
project (Prototype)
set(Prototype_VERSION_MAJOR 1)
set(Prototype_VERSION_MINOR 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# find sources
file(GLOB_RECURSE SRCS 
    ./src/*.cpp
)
source_group("src" FILES ${SRCS})

# find headers
file(GLOB_RECURSE HDRS 
    ./src/*.h
)
source_group("inc" FILES ${HDRS})

include_directories(
    ${SFML_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
    ${SDK_INCLUDE_DIR}
)

set(LIBS_DEBUG)
foreach(lib; ${SFML_LIBRARIES_D} ${SDK_LIBRARIES})
    list(APPEND LIBS_DEBUG debug ${lib})
endforeach()

set(LIBS_RELEASE)
foreach(lib; ${SFML_LIBRARIES} ${SDK_LIBRARIES})
    list(APPEND LIBS_RELEASE optimized ${lib})
endforeach()


add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
# add_dependencies (${PROJECT_NAME} 2DGameSDK)

if ("${CMAKE_BUILD_TYPE}" MATCHES Debug)
    target_link_libraries(${PROJECT_NAME} ${LIBS_DEBUG})
else ()
    target_link_libraries(${PROJECT_NAME} ${LIBS_RELEASE})
endif ("${CMAKE_BUILD_TYPE}" MATCHES Debug)



# (Windows only!) copy SFML DLL's for convenience
if ("${CMAKE_BUILD_TYPE}" MATCHES Debug)
    configure_file("${SFML_DLL_DIR}/sfml-system-d-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
    configure_file("${SFML_DLL_DIR}/sfml-window-d-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
    configure_file("${SFML_DLL_DIR}/sfml-graphics-d-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
else ()
    configure_file("${SFML_DLL_DIR}/sfml-system-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
    configure_file("${SFML_DLL_DIR}/sfml-window-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
    configure_file("${SFML_DLL_DIR}/sfml-graphics-2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" COPYONLY)
endif ("${CMAKE_BUILD_TYPE}" MATCHES Debug)

# POST BUILD: copy resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")
        
# (Windows only!) POST BUILD: copy 2DGameSDK DLL to output dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DLL_DIR}/${SDK_LIB_NAME}.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")