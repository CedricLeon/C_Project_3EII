include(FetchContent)

FetchContent_Declare(
  cjson
  #fork du vrai projet pour target_include_directories()
  GIT_REPOSITORY https://github.com/CedricLeon/cJSON.git
  GIT_TAG        support-include-build
  GIT_SHALLOW    1
)

set(ENABLE_CJSON_TEST OFF CACHE BOOL "CJson : Enable building the tests" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "CJson : Build the shared libraries" FORCE)

FetchContent_MakeAvailable(cjson)