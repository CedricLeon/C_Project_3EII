# ┌──────────────────────────────────────────────────────────────────┐
# │                       CMAKE PROPERTIES                           │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.15)
project(GPCalendar C)

# ┌──────────────────────────────────────────────────────────────────┐
# │                       Including Dependences                      │
# └──────────────────────────────────────────────────────────────────┘

# ─────────────────────────────── CMocka ─────────────────────────────
#Appel le cmake qui download CMocka avec les bonnes rules
#On aurait aussi pu utiliser add_subdirectory(Nom_de_sousDossier) qui appelle un autre CMakeLists.txt dans ce Nom_de_sousDossier
include(cmake/FetchCMocka.cmake)
# ─────────────────────────────── CJson ──────────────────────────────
include(cmake/FetchCJson.cmake)

# ─────────────────────────────── GTK3+ ──────────────────────────────
#Pour l'installation de GTK3+ c'est beaucoup plus difficile de réaliser un fetch_content comme avec CMocka ou cjson car gtk n'utilise pa cmake pour se build mais meson. De plus meson ne gère pas certaines double inclusion de librairies => le build fail
#Donc pour gérer GTK3+ dans ce cmake il faut que vous l'ayez installé (Cf README.md) il faut également avoir installé PkgConfig dont on se sert pour vérifier que c'est la bonne version de GTK qui est installée :
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#Ces lignes permettent aussi à CMake de trouver GTK3+ et ainsi de setup des varaiables comme :

# ${GTK3_INCLUDE_DIRS}      chemin du répertoire dans lequel se situe GTK3+, pour pouvoir faire : #include <gtk/gtk.h>
# ${GTK3_LIBRARIES}         nom de la librairie GTK3+ à linker au projet
# ${GTK3_LIBRARY_DIRS}
# ${GTK3_CFLAGS_OTHER}

# ┌──────────────────────────────────────────────────────────────────┐
# │             GPCalendarUtils : Project STATIC library             │
# └──────────────────────────────────────────────────────────────────┘

# Creating STATIC Library for source files (To compile only once those files)
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

add_library(GPCalendarUtils STATIC ${SOURCE_FILES})
target_include_directories(GPCalendarUtils PUBLIC include)       #target_include_directories permet de faire #include "GPCalendar/Model/date.c"
                                                                 #On aurait pu préciser include/GPCalendar/Model puisqu'on utilise dans cette librairie seulement des fichiers du Model, mais ça peut changer dans l'avenir
target_link_libraries(GPCalendarUtils PUBLIC cjson)              #Linking in the CJson library, because it's use in every executable

# ┌──────────────────────────────────────────────────────────────────┐
# │                          GPCalendar                              │
# └──────────────────────────────────────────────────────────────────┘

add_executable(GPCalendar
    src/App/main.c
    include/GPCalendar/View/callbacks.h
    src/View/callbacks.c
    include/GPCalendar/View/fonctionsGraphiques.h
    src/View/fonctionsGraphiques.c
    include/GPCalendar/View/time.h
    src/View/time.c
    )
target_compile_features(GPCalendar PUBLIC c_std_99)              #Précise que le projet est réalisé dans la norme du C_99
target_link_libraries(GPCalendar PUBLIC                          #Link à cet executable la librairie du projet et GTK3+
    GPCalendarUtils
    ${GTK3_LIBRARIES})
target_include_directories(GPCalendar PUBLIC                     #On précise les répertoires des fichiers utilisés
    src/View                                                     #Les .c de la View
    ${GTK3_INCLUDE_DIRS})                                        #La librairie de GTK3+

# ┌──────────────────────────────────────────────────────────────────┐
# │                       GPCalendar_Tests                           │
# └──────────────────────────────────────────────────────────────────┘

add_executable(GPCalendar_Tests
    tests/tests_unitaires.c)
target_compile_features(GPCalendar_Tests PUBLIC c_std_99)
target_link_libraries(GPCalendar_Tests PUBLIC
    GPCalendarUtils
    cmocka-static)                                              #La librairie STATIC de CMocka

enable_testing()                                                #Permet de setup Ctest
add_test(NAME GPCalendar_Tests COMMAND GPCalendar_Tests)        #Dans la console : cd cmake-build-debug && ctest -C Release