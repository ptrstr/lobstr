cmake_minimum_required(VERSION 3.0)
include(GNUInstallDirs)

# Check for iOS (to compile with Theos)
EXECUTE_PROCESS( COMMAND uname -p COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if (APPLE AND UNIX AND "${ARCHITECTURE}" STREQUAL "arm64")
  SET(CMAKE_OSX_SYSROOT /usr/SDK)
endif (APPLE AND UNIX AND "${ARCHITECTURE}" STREQUAL "arm64")

# Project intialization
project(lobstr VERSION 0.1.0 LANGUAGES C)

if (UNIX)
  SET(CMAKE_C_FLAGS "-Wall")
endif (UNIX)

# Get SOURCES an HEADERS (public ones)
file(GLOB SOURCES "lib/*.c")

# Add library
include_directories(include)
add_library(lobstr SHARED ${SOURCES})

set_target_properties(lobstr PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER include/lobstr.h)

# Linking
target_link_libraries(lobstr capstone)

install(TARGETS lobstr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
