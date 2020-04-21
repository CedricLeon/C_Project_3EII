# GPCalendar (Still developing)

GPCalendar is an application allowing physician in a structure like an hospital to manage easier their timetable. It is still under development. It also allowed better communication between patient and physician with easy access to personal data, easy to use historical of consultations, etc.

## Unit-Testing

For the moment (21/04/2020) unit-tested are implemented for the patient, physician and calendar functions.

If you want to run them you can execute the ````Tests_exec```` executable or do the following commands :

````bash
cd cmake-build-debug
ctest -C Release
````

## Build

GPCalendar is (normally) a cross platform application and is build with CMake.

To build the application, make sure you have CMake and clone the git repertory. Then create the source build folder and access it. 

````bash
git clone https://gitlab.insa-rennes.fr/cleonard/C_Project.git
cd C_Project && mkdir build && cd build
````

You can now run the Cmake commands to build the project 

````bash
cmake ..
cmake --build .
````

#### Cmake

If you don't have Cmake you can run the following commands (Credits OlivierLdff) :

````bash
sudo apt-get install libssl-dev
wget https://github.com/Kitware/CMake/releases/download/v3.17.0-rc2/cmake-
3.17.0-rc2.tar.gz
tar zxvf cmake-3.17.0-rc2.tar.gz
cd cmake-3.17.0-rc2.tar.gz
./configure
make -j
sudo make install
# Restart terminal
````



