cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)

option(STRIP_BINARY "" OFF)
option(STATIC_BUILD "" OFF) # avoid compiler bug
include(../../userspace.cmake)

os_add_executable(linux_liu "Linux userspace LiveUpdate test"
    service.cpp
  )
