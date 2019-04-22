cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)

option(ENABLE_S2N "" ON)
option(STATIC_BUILD "" OFF)
option(STRIP_BINARY "" OFF)
include(../../userspace.cmake)

os_add_executable(linux_s2n "Linux userspace S2N test"
    service.cpp
    serial.cpp
  )
