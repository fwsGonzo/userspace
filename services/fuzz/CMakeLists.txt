cmake_minimum_required(VERSION 2.8.9)
project (service C CXX)

#option(LIBCPP "" ON)
option(LIBFUZZER "" ON)
option(SANITIZE "" ON)
option(ENABLE_LTO "" OFF) # disable LTO because so much issues with LLD
option(STATIC_BUILD "" OFF) # asan doesnt support static builds
option(STRIP_BINARY "" OFF) # we need to see symbol names

include(../../userspace.cmake)

os_add_executable(fuzzer "Linux userspace IP-stack fuzzer"
    service.cpp fuzzy_packet.cpp fuzzy_stack.cpp fuzzy_webserver.cpp http.cpp
  )
