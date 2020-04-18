cmake_minimum_required(VERSION 3.15)
project(C_Project C)

#
find_library(CMOCKA_LIBRARY cmocka)

#Normal executable
set(SOURCE_FILES patient.c patient.h date.c date.h medecin.c medecin.h Structures.h dossier_medical.h ordonnance.c ordonnance.h rendezvous.c rendezvous.h calendrier.c)
add_executable(NormalExec_CProject ${SOURCE_FILES})
target_link_libraries(NormalExec_CProject ${CMOCKA_LIBRARY})
target_compile_features(NormalExec_CProject PUBLIC c_std_99)


#Testing executable
set(SOURCE_FILES_TEST ${SOURCE_FILES} tests_unitaires.c tests_unitaires.h )
add_executable(Tests_exec ${SOURCE_FILES_TEST})
target_link_libraries(Tests_exec ${CMOCKA_LIBRARY})
target_compile_definitions(Tests_exec PUBLIC c_std_99)

#Permet de setup Ctest
#Dans la console : cd cmake-build-debug && ctest -C Release
enable_testing()
add_test(NAME Tests_exec COMMAND Tests_exec)