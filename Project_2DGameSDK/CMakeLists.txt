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
add_definitions(-DDLLBUILD_GAMESDK)

# find headers
file(GLOB_RECURSE HDRS 
    ./src/*.h
)
source_group("inc" FILES ${HDRS})

include_directories(
    ${SFML_INCLUDE_DIR}
)

set(LIBS_RELEASE)
foreach(lib; ${SFML_LIBRARIES})
    list(APPEND LIBS_RELEASE optimized ${lib})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME} ${LIBS_RELEASE})

# find shared headers in src/shared
file(GLOB_RECURSE SHARED_HDRS 
    ./src/shared/*.h
)

file(COPY ${SHARED_HDRS}
     DESTINATION ${CMAKE_HOME_DIRECTORY}/libs/${PROJECT_NAME}/include/${PROJECT_NAME})
