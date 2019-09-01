# ==================== INITIAL CONFIGURATION ====================

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Voice_for_VLC CXX)

include(FindPkgConfig)

set(CMAKE_CXX_STANDARD 17)

# ==================== SEARCHING FOR LIBPISTACHE ====================

pkg_check_modules(PISTACHE REQUIRED libpistache)

# ==================== SEARCHING FOR LIBVLC AND LIBVLCCORE ====================

pkg_check_modules(VLC REQUIRED libvlc)

pkg_check_modules(VLCCORE QUIET libvlccore vlccore)

# ==================== BUILDING THE EXECUTABLE ====================

file(GLOB DATABASE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/database/* )
file(GLOB EXCEPTIONS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/* )
file(GLOB NETWORK_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/network/* )
file(GLOB PLAYER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/player/* )
file(GLOB SYNCHRONIZATION_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/synchronization/* )
file(GLOB UTILS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/* )

add_executable(Voice_for_VLC ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp ${DATABASE_FILES} ${EXCEPTION_FILES} ${NETWORK_FILES} ${PLAYER_FILES} ${SYNCHRONIZATION_FILES} ${UTILS_FILES})

set(LIBS ${LIBS} ${VLC} ${PISTACHE} ${VLCCORE})

target_link_libraries(Voice_for_VLC ${LIBS})

# ==================== INSTALLATION ====================

install(TARGETS Voice_for_VLC DESTINATION /usr/local/bin)

