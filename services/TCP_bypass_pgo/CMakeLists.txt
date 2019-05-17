cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)

option(PORTABLE "" OFF)
option(PERFORMANCE "" ON)

include(../../userspace.cmake)

os_add_executable(tcpperf "Userspace TCP benchmark"
    main.cpp
    experiment.cpp
  )
set_source_files_properties("main.cpp" PROPERTIES COMPILE_FLAGS "-Wno-error=coverage-mismatch")
