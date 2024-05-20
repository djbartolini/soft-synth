cmake_minimum_required(VERSION 3.20)
project(soft-synth)
set(CMAKE_CXX_STANDARD 20)

# Set the path to your local libraries
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/")

# Find SDL2
find_package(SDL2 REQUIRED)

if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    message(STATUS "Found SDL2: ${SDL2_LIBRARIES}")
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()

# Find SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_PREFIX_PATH}/SDL2_image/include")
set(SDL2_IMAGE_LIBRARY "${CMAKE_PREFIX_PATH}/SDL2_image/lib/libSDL2_image.dylib")

if (EXISTS ${SDL2_IMAGE_INCLUDE_DIR} AND EXISTS ${SDL2_IMAGE_LIBRARY})
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    message(STATUS "Found SDL2_image: ${SDL2_IMAGE_LIBRARY}")
else()
    message(FATAL_ERROR "SDL2_image not found!")
endif()

# Find SDL2_mixer
set(SDL2_MIXER_INCLUDE_DIR "${CMAKE_PREFIX_PATH}/SDL2_mixer/include")
set(SDL2_MIXER_LIBRARY "${CMAKE_PREFIX_PATH}/SDL2_mixer/lib/libSDL2_mixer.dylib")

if (EXISTS ${SDL2_MIXER_INCLUDE_DIR} AND EXISTS ${SDL2_MIXER_LIBRARY})
    include_directories(${SDL2_MIXER_INCLUDE_DIR})
    message(STATUS "Found SDL2_mixer: ${SDL2_MIXER_LIBRARY}")
else()
    message(FATAL_ERROR "SDL2_mixer not found!")
endif()

# Add your executable
add_executable(soft-synth main.cpp)

# Link libraries to your executable
target_link_libraries(soft-synth PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
