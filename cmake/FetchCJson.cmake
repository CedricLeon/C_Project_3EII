include(FetchContent)

FetchContent_Declare(
  cjson
  GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
  GIT_TAG        master
  GIT_SHALLOW    1
)

set(ENABLE_CJSON_TEST OFF CACHE BOOL "CJson : Enable building the tests" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "CJson : Build the shared libraries" FORCE)
#set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build the shared libraries" FORCE)
#set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
#set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cjson)