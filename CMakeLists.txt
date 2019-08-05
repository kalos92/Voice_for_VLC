cmake_minimum_required(VERSION 3.14)
project(Voice_for_VLC CXX)

set(CMAKE_CXX_STANDARD 17)

find_library(CPPREST_LIB cpprest)
find_package(OpenSSL 1.0.0 REQUIRED)

FIND_PATH(LIBVLC_INCLUDE_DIR vlc/vlc.h
        HINTS "$ENV{LIBVLC_INCLUDE_PATH}"
        PATHS
        "/usr/include"
        "/usr/include/vlc"
        "/usr/local/include"
        "/usr/local/include/vlc"
        )
FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc
        HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
        PATHS
        "$ENV{LIB_DIR}/lib"
        )
FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc)
FIND_LIBRARY(LIBVLCCORE_LIBRARY NAMES vlccore libvlccore
        HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
        PATHS
        "$ENV{LIB_DIR}/lib"
        )
FIND_LIBRARY(LIBVLCCORE_LIBRARY NAMES vlccore libvlccore)

IF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLCCORE_LIBRARY)
    SET(LIBVLC_FOUND TRUE)
ENDIF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLCCORE_LIBRARY)

IF (LIBVLC_FOUND)
    IF (NOT LIBVLC_FIND_QUIETLY)
        MESSAGE(STATUS "Found LibVLC include-dir path: ${LIBVLC_INCLUDE_DIR}")
        MESSAGE(STATUS "Found LibVLC library path:${LIBVLC_LIBRARY}")
        MESSAGE(STATUS "Found LibVLCcore library path:${LIBVLCCORE_LIBRARY}")
    ENDIF (NOT LIBVLC_FIND_QUIETLY)
ELSE (LIBVLC_FOUND)
    IF (LIBVLC_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find LibVLC")
    ENDIF (LIBVLC_FIND_REQUIRED)
ENDIF (LIBVLC_FOUND)
FIND_PATH(LIBVLC_INCLUDE_DIR PATHS "${CMAKE_INCLUDE_PATH}/vlc" NAMES vlc.h)

add_subdirectory(src/exceptions)
add_subdirectory(src/network)
add_subdirectory(src/player)
add_subdirectory(src/synchronization)
add_subdirectory(src/utils)
add_subdirectory(src/database)

add_executable(Voice_for_VLC src/Main.cpp)

set(CMAKE_CXX_FLAGS "-pthread")
set(JSON_BuildTests OFF CACHE INTERNAL "")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${LIBVLC_INCLUDE_DIR})
set(LIBS ${LIBS} ${OpenCV_LIBS})
set(LIBS ${LIBS} ${LIBVLC_LIBRARY})

target_link_libraries(Voice_for_VLC ${LIBS})

