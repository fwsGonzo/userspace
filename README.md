## Userspace Linux platform

### Installation

* Get a modern compiler
    * gcc 7.3 or gcc 8.0
    * clang-8 or clang-9 from SVN trunk
* Install Botan from source, if you need it
    * git clone ...
    * ./configure --disable-shared
    * make -j32
    * sudo make install
* Create a userspace services that includes userspace.cmake
* Build the userspace service like a normal CMake project
    * mkdir -p build && cd build
    * cmake ..
    * make -j16
* Run the resulting binary as a normal linux program

### Options

* Apply your own CMake code to the 'service' target:
    * `target_link_libraries(service mylib)`
* CMake options:
    * Some options require enabling it in both the Linux platform CMake project and the service code CMake project for it to fully work.
    * ENABLE_LTO: Enable ThinLTO. Only works with clang. (enable both)
    * GPROF: Enable profiling with gprof (enable both)
    * SANITIZE: Enable asan and ub sanitizers (enable both)

### Testing it

Run one of the tests in /services with ./test.sh. If you get the error `RTNETLINK answers: File exists`, flush the interface with `sudo ip addr flush dev bridge43`. Where bridge43 is the interface name. You might have to do the same if the interface stops responding. If all else fails, restart the machine.
