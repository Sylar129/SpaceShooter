
cmake_minimum_required(VERSION 3.16.0)
project(SpaceShooter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
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
    SDL2
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.32.8.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(SDL2)
include_directories(AFTER ${SDL2_SOURCE_DIR}/include)

FetchContent_Declare(
    SDL2_image
    URL https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.8.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(SDL2IMAGE_VENDORED OFF)
FetchContent_MakeAvailable(SDL2_image)
include_directories(AFTER ${SDL2_image_SOURCE_DIR}/include)

add_executable(${TARGET}
                src/main.cpp
                src/game.cpp
                src/scene_main.cpp
                src/texture.cpp
                src/player.cpp)

target_link_libraries(${TARGET}
                        SDL2::SDL2
                        SDL2_image::SDL2_image)
