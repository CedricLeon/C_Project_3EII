cmake_minimum_required(VERSION 3.15)
project(C_Project C)

include_directories(/usr/local/include)
find_library(CMOCKA_LIBRARY libcmocka.so.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -lcmocka")

#Normal executable
set(SOURCE_FILES patient.c patient.h date.c date.h medecin.c medecin.h Structures.h dossier_medical.h ordonnance.h rendezvous.c rendezvous.h calendrier.c)
add_executable(NormalExec_CProject ${SOURCE_FILES})
target_link_libraries(NormalExec_CProject ${CMOCKA_LIBRARY})

#Testing executable
set(SOURCE_FILES_TEST tests_unitaires.c tests_unitaires.h patient.c patient.h date.c date.h medecin.c medecin.h Structures.h dossier_medical.h ordonnance.c ordonnance.h rendezvous.c rendezvous.h main.c calendrier.c)
add_executable(Tests_exec ${SOURCE_FILES_TEST})
target_link_libraries(Tests_exec ${CMOCKA_LIBRARY})