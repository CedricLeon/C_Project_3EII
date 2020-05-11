# GPCalendar (Still developing)

GPCalendar is an application allowing physician in a structure like an hospital to manage easier their timetable. It is still under development. It also allowed better communication between patient and physician with easy access to personal data, easy to use historical of consultations, etc.

## Trucs à faire

- GPCalendar_Shell : gérer tout les cas où on tape des bêtises / "help" affiche les choix / "quit" pour quitter la fonction ou on est
- RDV_Valable()  : à tester
- Run code coverage et rajouter des tests pour atteindre 80% (demander Alexandre)

## Unit-Testing

For the moment (01/05/2020) unit-tested are implemented for the patient, physician, calendar, date and order functions.

If you want to run them you can execute the ````GPCalendar_Tests```` executable or execute the following commands :

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
#Make sure the project is already build, else :
cmake ..
cmake --build .
#And then
valgrind ./GPCalendar_Tests
````

You can also run it with your IDE like **Valgrind-MemoryCheck** in CLion.

## cJSON

cJSON is a GitHub Project which allow to easily use **JSON** format in C code. It is used to "save" the application. 

If you want to save or load one of your project you have to type the absolute path with the name of the file you want to load or the name of the file you want to create to save your project.

Example : - Load : ```C:\Documents\YourProject.json```

​				  - Save : ```C:\Documents\NomDeMonFichierDeSauvegarde.json```

## Build

GPCalendar is a cross platform application, built with CMake.

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

If you are especially using `CodeBlocks`, you can generate a CodeBlocks project with :

````bash
cmake -G "CodeBlocks - Unix Makefiles" .
````

(You can also see what other type of project you can build with CMake with `cmake -G`).

## CMake

If you don't have CMake you can run the following commands (Credits **OlivierLdff**) :

````bash
sudo apt-get install libssl-dev
wget https://github.com/Kitware/CMake/releases/download/v3.17.0-rc2/cmake-3.17.0-rc2.tar.gz
tar zxvf cmake-3.17.0-rc2.tar.gz
cd cmake-3.17.0-rc2
./configure
make -j2	#You can also run make without -j or -j2 but it will be slower
sudo make install
# Restart terminal
````

## GTK3+

### General Settings for CMake

GTK3+ isn't build with CMake like `CMocka` or `cJSON`, it's built with `meson`. Therefore it isn't possible to just fetch content of the GTK3+ git project in our CMakeLists.txt and then build normally the project.

To include GTK3+ in the project you have to download his libraries first :

````bash
sudo apt install libgtk-3-dev
````

You want the dev library. Be careful, the name of the package may have change. But you're looking for something like `libgtk-3`, `libgtk3.0` or `libgtk3-dev`.

Once it's done, be sure you have `PkgConfig`(it's a package manager that we are using in our CMakeLists.txt) :

````bash
sudo apt install pkg-config
````

And then you can normally run CMake (in your build repertory) with :

````bash
cmake ..
cmake --build .
````

As the GTK3+ dependences are only include in `./GPCalendar` you can build the Model and tests of the project without GTK3+ by only building and executing `./GPCalendar_Tests`.


### Manually Settings for CodeBlocks

#### Installation

GTK+ has been mostly conceived for Linux. Therefore, if you do not have it, I invite you to check out the openclassroom course on how to create a GTK+ interface on MacOs or Windows.
But If you have Linux, let's begin:

First you should download the different libraries. To do so, open your Linux shell and type:
````bash
sudo apt-get update
````
This allows you to update your different packages. Then you'll need to install the *devpackages* and make sure you do have the runtime so type:
````bash
sudo apt-get install libgtk-3-dev
````

#### How to build with your console
Open your Linux shell for instance and go to your folder:
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
I will show you now how to use and configure the Code :: Blocks software which is a portable, open source IDE and very practical for GTK+.

First, launch Code :: Blocks and open or create a new Project by going to: *File -> New Project -> Empty project*
Then you'll need to configure your compiler. Go to Project -> Build Options select the debug mode and select the compiler settings and in  *"add in other options"* type:

````bash
`pkg-config --cflags gtk+-3.0`
````
You'll have to do the same with the linker settings:
````bash
`pkg-config --libs gtk+-3.0`
````
Repeat these two lines for the Release and Projectname mode (usually at the top left of the window).



## Terminal Window

GPCalendar is an application which have a graphical interface (generate with GTK3+).

But it can also work from a shell with some switch case to choose what action you want to do.

```bash
case 1 :
	Create a Patient
case 2 :
	Create a Medecin
case 3 :
	Create a RendezVous beetween a Patient and a Physician
case 4 : 
	Check hospital data
case 5 :
	Cancel a RendezVous
case 6 : 
	Delete a Patient
case 7 :
	Delete a Medecin
case 8 :
	Save the Project (all Patients, all Medecins and the hospital calendar)

```

