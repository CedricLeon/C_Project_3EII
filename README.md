# GPCalendar (Still developing)

GPCalendar is an application allowing physician in a structure like an hospital to manage easier their timetable. It is still under development. It also allowed better communication between patient and physician with easy access to personal data, easy to use historical of consultations, etc.

## Unit-Testing

For the moment (21/04/2020) unit-tested are implemented for the patient, physician and calendar functions.

If you want to run them you can execute the ````Tests_exec```` executable or do the following commands :

````bash
cd cmake-build-debug
ctest -C Release
````

## Valgrind

If you want to run Valgrind on GPCalendar, make sure you have it installed :

````bash
sudo apt-get install valgrind
````

And then run it in build :

````bash
cd build
#Make sure the project is already build else :
cmake ..
cmake --build .
#And then
valgrind ./Tests_exec
````

You can also run it with your IDE like Valgrind-MemoryCheck in CLion.

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

## GTK3+

#### Installation

GTK+ has been mostly conceived for linux. Therefore, if you do not have it I invite you to check out the openclassroom course on how to creat a GTK+ interface on MacOs or Windows.
But If you have linux, let's begin:

First you should download the different librairies. To do so open your linux shell and type:
````bash
sudo apt-get update
````
This allows you to update your different packages. Then you'll need to install the devpackages and make sure you do have the runtime so type:
````bash
sudo apt-get install libgtk3.0-dev
sudo apt-get install libgtk3.0-0
````

#### How to build with your console
Open your linux shell for instance and go to your folder:
````bash
cd /home/the_path_to_your_folder/
````
Then you'll have to build your code doing:
````bash
gcc $(pkg-config --libs --cflags gtk+-3.0) main.c -o executable_name
````
The main.c corresponds to the name of our file (source code of the program) and executable_name is the name you want to give to your program.
Finally you need to run it:
````bash
./executable_name
````

#### How to build with your IDE 
I will show you now  how to use and configure the Code :: Blocks software which is a portable, open source IDE and very practical for GTK +.

First, launch Code :: Blocks and open or create a new Project by going to: File -> New Project -> Empty project
Then you'll need to configure your compiler. Go to Project -> Build Options select the debug mode and select the compiler settings and in "" add in other options" type:
````bash
`pkg-config --cflags gtk+-3.0`
````
You'll have to do the same with the linker settings:
````bash
`pkg-config --libs gtk+-3.0`
````
Repeat these two lines for the Release and Projectname mode (usually at the top left of the window).