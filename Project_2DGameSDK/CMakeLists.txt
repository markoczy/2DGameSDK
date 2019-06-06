# Project Settings
project (2DGameSDK)

set(2DGameSDK_VERSION_MAJOR 1)
set(2DGameSDK_VERSION_MINOR 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/bin")

# find sources
file(GLOB_RECURSE SRCS 
    ./src/*.cpp
)
source_group("src" FILES ${SRCS})
add_definitions(-DDLLBUILD_GAMESDK -DGAMESDK_LOG_E)

# find headers
file(GLOB_RECURSE HDRS 
    ./src/*.h
)
source_group("inc" FILES ${HDRS})

include_directories(
    ${SFML_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
    # include shared headers
    ${PROJECT_SOURCE_DIR}/include
)

set(LIBS_DEBUG)
foreach(lib; ${SFML_LIBRARIES_D})
    list(APPEND LIBS_DEBUG debug ${lib})
endforeach()

set(LIBS_RELEASE)
foreach(lib; ${SFML_LIBRARIES})
    list(APPEND LIBS_RELEASE optimized ${lib})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS})

if ("${CMAKE_BUILD_TYPE}" MATCHES Debug)
    target_link_libraries(${PROJECT_NAME} ${LIBS_DEBUG})
else ()
    target_link_libraries(${PROJECT_NAME} ${LIBS_RELEASE})
endif ("${CMAKE_BUILD_TYPE}" MATCHES Debug)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# find shared headers in src/shared
file(GLOB_RECURSE SHARED_HDRS 
    ./src/include/*.h
)

file(COPY ./include/${PROJECT_NAME} DESTINATION ${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/include)

# file(COPY ${SHARED_HDRS}
#      DESTINATION ${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/include/${PROJECT_NAME})
