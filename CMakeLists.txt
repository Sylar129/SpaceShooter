
cmake_minimum_required(VERSION 3.16.0)
project(SpaceShooter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

include(FetchContent)

FetchContent_Declare(
    SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.18.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(SDL3)
include_directories(AFTER ${SDL3_SOURCE_DIR}/include)

FetchContent_Declare(
    SDL3_image
    URL https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-3.2.4.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(SDLIMAGE_VENDORED OFF)
FetchContent_MakeAvailable(SDL3_image)
include_directories(AFTER ${SDL3_image_SOURCE_DIR}/include)

add_executable(${TARGET}
                src/main.cpp
                src/game.cpp
                src/scene_main.cpp
                src/environment.cpp
                src/texture.cpp
                src/player.cpp)

target_link_libraries(${TARGET}
                        SDL3::SDL3
                        SDL3_image::SDL3_image)
