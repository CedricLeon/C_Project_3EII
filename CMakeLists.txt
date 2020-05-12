cmake_minimum_required(VERSION 3.15)
project(C_Project C)

#Appel le cmake qui download CMocka avec les bonnes rules
#On aurait aussi pu utiliser add_subdirectory(Nom_de_sousDossier) qui appelle un autre CMakeLists.txt dans ce Nom_de_sousDossier
include(cmake/FetchCMocka.cmake)
include(cmake/FetchCJson.cmake)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# ${GTK3_INCLUDE_DIRS}
# ${GTK3_LIBRARY_DIRS}
# ${GTK3_CFLAGS_OTHER}
# ${GTK3_LIBRARIES}
# #include <gtk/gtk.h>

# Creating STATIC Library for source files (allow to compile only once those files)
set(SOURCE_FILES
    src/Model/patient.c
    include/GPCalendar/Model/patient.h
    src/Model/date.c
    include/GPCalendar/Model/date.h
    src/Model/medecin.c
    include/GPCalendar/Model/medecin.h
    include/GPCalendar/Model/Structures.h
    include/GPCalendar/Model/dossier_medical.h
    src/Model/dossier_medical.c
    src/Model/ordonnance.c
    include/GPCalendar/Model/ordonnance.h
    src/Model/rendezvous.c
    include/GPCalendar/Model/rendezvous.h
    src/Model/calendrier.c
    src/Model/JsonSave.c
    include/GPCalendar/Model/JsonSave.h)

#Linking every librairies used into GPCalendarUtils
add_library(GPCalendarUtils STATIC ${SOURCE_FILES})
#nécessaire pour pouvoir faire #include "date.c" par exemple
target_include_directories(GPCalendarUtils PUBLIC include)
target_link_libraries(GPCalendarUtils PUBLIC cjson)

#Normal executable
add_executable(GPCalendar
    src/App/main.c
    include/GPCalendar/View/callbacks.h
    src/View/callbacks.c
    include/GPCalendar/View/fonctionsGraphiques.h
    src/View/fonctionsGraphiques.c
    include/GPCalendar/View/time.h
    src/View/time.c
    )
target_compile_features(GPCalendar PUBLIC c_std_99)
target_link_libraries(GPCalendar PUBLIC
    GPCalendarUtils
    ${GTK3_LIBRARIES})
target_include_directories(GPCalendar PUBLIC
    src/View
    ${GTK3_INCLUDE_DIRS})

#Testing executable
add_executable(GPCalendar_Tests
    tests/tests_unitaires.c)
target_compile_features(GPCalendar_Tests PUBLIC c_std_99)
target_link_libraries(GPCalendar_Tests PUBLIC
    GPCalendarUtils
    cmocka-static)

#Permet de setup Ctest
#Dans la console : cd cmake-build-debug && ctest -C Release
enable_testing()
add_test(NAME GPCalendar_Tests COMMAND GPCalendar_Tests)