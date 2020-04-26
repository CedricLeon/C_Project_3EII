cmake_minimum_required(VERSION 3.15)
project(C_Project C)

#Appel le cmake qui download CMocka avec les bonnes rules
#On aurait aussi pu utiliser add_subdirectory(Nom_de_sousDossier) qui appelle un autre CMakeLists.txt dans ce Nom_de_sousDossier
include(cmake/FetchCMocka.cmake)
include(cmake/FetchCJson.cmake)

# Creating STATIC Library for source files (allow to compile only once those files)
set(SOURCE_FILES
    src/patient.c
    src/patient.h
    src/date.c
    src/date.h
    src/medecin.c
    src/medecin.h
    src/Structures.h
    src/dossier_medical.h
    src/dossier_medical.c
    src/ordonnance.c
    src/ordonnance.h
    src/rendezvous.c
    src/rendezvous.h
    src/calendrier.c
    src/JsonSave.c
    src/JsonSave.h)

#Linking every librairies used into GPCalendarUtils
add_library(GPCalendarUtils STATIC ${SOURCE_FILES})
target_link_libraries(GPCalendarUtils PUBLIC cjson)
#target_link_libraries(GPCalendarUtils PUBLIC NOM_DE_LA_LIBRAIRIE_STATIC_DE_GTK)

#Normal executable
add_executable(GPCalendar
    src/main.c)
target_compile_features(GPCalendar PRIVATE c_std_99)
target_link_libraries(GPCalendar PRIVATE GPCalendarUtils)

#Testing executable
add_executable(GPCalendar_Tests
    src/tests_unitaires.c)
target_compile_features(GPCalendar_Tests PUBLIC c_std_99)
target_link_libraries(GPCalendar_Tests PRIVATE GPCalendarUtils)
target_link_libraries(GPCalendar_Tests PRIVATE cmocka-static)

#Permet de setup Ctest
#Dans la console : cd cmake-build-debug && ctest -C Release
enable_testing()
add_test(NAME GPCalendar_Tests COMMAND GPCalendar_Tests)