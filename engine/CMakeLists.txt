cmake_minimum_required(VERSION 3.24)
project(HellzYeahRetroEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SDL3 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-3.2.20)
FetchContent_MakeAvailable(SDL3)

add_executable(HellzYeahRetroEngine
    src/main.cpp
    src/Engine.cpp
    src/World.cpp
)
target_include_directories(HellzYeahRetroEngine PRIVATE include)
target_link_libraries(HellzYeahRetroEngine PRIVATE SDL3::SDL3)

# Keep a normal main() entry point for the first test builds.
# This avoids the Windows GUI-subsystem WinMain requirement while the engine is in active development.
if(MSVC)
  target_compile_options(HellzYeahRetroEngine PRIVATE /W4)
endif()
