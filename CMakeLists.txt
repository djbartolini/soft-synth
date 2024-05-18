cmake_minimum_required(VERSION 3.20)
project(soft-synth)

set(CMAKE_CXX_STANDARD 20)

# Find package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Find Package
find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h)
find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_mixer.h)

add_executable(soft-synth        main.cpp
        )

target_include_directories(soft-synth PRIVATE lib/sdl2/include lib/sdl2_image/include lib/sdl2_mixer/include)

# Link libraries to your executable
target_link_libraries(soft-synth PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL_MIXER_LIBRARY})
