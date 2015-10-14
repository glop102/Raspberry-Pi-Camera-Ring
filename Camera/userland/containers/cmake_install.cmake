# Install script for directory: /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers

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
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/build/lib/libcontainers.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcontainers.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/mp4/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/mpeg/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/mpga/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/binary/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/mkv/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/wav/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/asf/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/flash/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/rtp/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/rtsp/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/rcv/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/rv9/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/qsynth/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/simple/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/raw/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/dummy/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/metadata/id3/cmake_install.cmake")
  INCLUDE("/home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/test/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

