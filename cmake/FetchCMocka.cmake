#Fichier Cmake réalisé par Oliv' en Live permettant d'utiliser CMocka dans un project
#Ce .cmake effectue un git clone de CMocka et permet d'utiliser sa librairie static, on préfère utiliser la static car ainsi le .exe de notre appli générer est indépendant (Les fonctions de CMocka utilisées sont comprises dans le Cmake et non dans un .dll ou un .so qu'on doit trimbaler à côté de notre .exe)

#Ajouter include(cmake/FetchCMocka.cmake) pour inclure ce fichier dans le CMakeLists.txt

#On include le module FetchContent de CMake
include(FetchContent)

#FetchContent permet de ne pas forcément avoir Cmocka pour build le projet.
#En effet, c'est Cmake qui va s'occuper de download la librairie cmocka et de le build s'il ne le trouve pas dans le dossier build par exemple
FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

#Ici on vient set certaines variables de Cmocka du cache, la plus importante est la première, effectivement on utilise cmocka-static, qui est CMocka compiler sous forme de librairie static, il faut donc activer la variable CMake lui indiquant de compiler cette librairie static
#Le reste des variables sert surtout à ne pas compiler trop de choses comme les examples etc ...
set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)


#Enfin on vient "activer" ce qu'à fait FetchContent
#cette ligne est équivalente à git clone https://git.cryptomilk.org/projects/cmocka.git build/cmocka.src
FetchContent_MakeAvailable(cmocka)