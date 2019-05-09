cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)

option(PORTABLE "" OFF)
option(SAN_ADDR "" ON)
#option(ENABLE_S2N "" ON)
include(../../userspace.cmake)

os_add_executable(linux_udp "Linux userspace UDP test"
    service.cpp
  )

os_add_drivers(linux_udp ip4_reassembly)
