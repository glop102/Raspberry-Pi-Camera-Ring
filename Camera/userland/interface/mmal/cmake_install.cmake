# Install script for directory: /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/opt/vc")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/build/lib/libmmal.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmmal.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/interface/mmal" TYPE FILE FILES
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_buffer.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_clock.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_common.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_component.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_encodings.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_events.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_format.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_logging.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_metadata.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters_audio.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters_camera.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters_clock.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters_common.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_parameters_video.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_pool.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_port.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_queue.h"
    "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/mmal_types.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/core/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/util/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/vc/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/components/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/openmaxil/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/client/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/interface/mmal/test/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

