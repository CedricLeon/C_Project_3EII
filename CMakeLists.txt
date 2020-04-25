cmake_minimum_required(VERSION 3.15)
project(C_Project C)

#Appel le cmake qui download CMocka avec les bonnes rules
#On aurait aussi pu utiliser add_subdirectory(Nom_de_sousDossier) qui appelle un autre CMakeLists.txt dans ce Nom_de_sousDossier
include(cmake/FetchCMocka.cmake)

set(SOURCE_FILES
    src/patient.c
    src/patient.h
    src/date.c
    src/date.h
    src/medecin.c
    src/medecin.h
    src/Structures.h
    src/dossier_medical.h
    src/ordonnance.c
    src/ordonnance.h
    src/rendezvous.c
    src/rendezvous.h
    src/calendrier.c)

#Normal executable
add_executable(NormalExec_CProject
    ${SOURCE_FILES}
    src/main.c)
target_compile_features(NormalExec_CProject PRIVATE c_std_99)
target_link_libraries(NormalExec_CProject PRIVATE cmocka-static)

#Testing executable
add_executable(Tests_exec
    ${SOURCE_FILES}
    src/tests_unitaires.c
    src/tests_unitaires.h)
target_link_libraries(Tests_exec cmocka-static)
target_compile_features(Tests_exec PUBLIC c_std_99)

#Permet de setup Ctest
#Dans la console : cd cmake-build-debug && ctest -C Release
enable_testing()
add_test(NAME Tests_exec COMMAND Tests_exec)