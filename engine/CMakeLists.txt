cmake_minimum_required(VERSION 3.24)
project(HellzYeahRetroEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SDL3 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-3.2.20)
FetchContent_MakeAvailable(SDL3)

add_executable(HellzYeahRetroEngine
    src/main.cpp
    src/Engine.cpp
    src/World.cpp
)
target_include_directories(HellzYeahRetroEngine PRIVATE include)
target_link_libraries(HellzYeahRetroEngine PRIVATE SDL3::SDL3)
if(WIN32)
  set_target_properties(HellzYeahRetroEngine PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
