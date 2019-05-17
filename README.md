## Userspace Linux platform

### Installation

* Get a modern compiler
    * gcc 7.3 or later
    * clang-8 or later
* Create userspace services that includes userspace.cmake
* Build the userspace service like a normal CMake project
    * mkdir -p build && cd build
    * cmake ..
    * make -j16
* Run the resulting binary as a normal linux program
* You can avoid having to run with sudo with bridge permissions

### Options

* Apply your own CMake code to the 'service' target:
    * `target_link_libraries(service mylib)`
* CMake options:
    * See the top of userspace.cmake
* For PGO training you will have to automate the process yourself

### Testing it

Run one of the test services in /services with one of the scripts. If you get the error `RTNETLINK answers: File exists`, flush the interface with `sudo ip addr flush dev bridge43`. Where bridge43 is the interface name. You might have to do the same if the interface stops responding. If all else fails, restart your machine.
