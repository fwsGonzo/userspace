cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)
include(../../userspace.cmake)

option(PORTABLE "" OFF)

os_add_executable(linux_tcp "Linux userspace TCP test"
    service.cpp
  )
