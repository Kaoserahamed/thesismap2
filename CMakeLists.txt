cmake_minimum_required(VERSION 3.20)
project(LastTrain LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

file(GLOB_RECURSE LASTTRAIN_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(LastTrain ${LASTTRAIN_SOURCES})

target_include_directories(LastTrain PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(MSVC)
    target_compile_options(LastTrain PRIVATE /W4)
else()
    target_compile_options(LastTrain PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(LastTrain PRIVATE raylib nlohmann_json::nlohmann_json)

target_compile_definitions(LastTrain PRIVATE
    $<$<CONFIG:Debug>:ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/">
    $<$<NOT:$<CONFIG:Debug>>:ASSET_DIR="assets/">
)

add_custom_command(TARGET LastTrain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:LastTrain>/assets"
)

enable_testing()
add_subdirectory(tests)
