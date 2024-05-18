-- CMaker

-- Define your project details
local cmake_version = "3.20"
local project_name = "soft-synth"
local cxx_standard = "20"

local executable = "sound.cpp"

-- Dependencies
local dep_SDL = "SDL2"
local dep_version_SDL = "2.30.2"
local include_directories_SDL = "lib/sdl2/include"
local lib_directories_SDL = "${SDL2_LIBRARIES}"
local link_SDL = "sdl2"

local dep_SDL_image = "sdl2_image"
local dep_version_SDL_image = "2.8.2_1"
local include_directories_SDL_image = "/lib/sdl2_image/include"
local lib_directories_SDL_image = "${SDL_IMAGE_LIBRARY}"
local link_SDL_image = "sdl2_image"

local dep_SDL_mixer = "sdl2_mixer"
local dep_version_SDL_mixer = "2.8.0"
local include_directories_SDL_mixer = "/lib/sdl2_mixer/include"
local lib_directories_SDL_mixer = "${SDL_MIXER_LIBRARY}"
local link_SDL_mixer = "sdl2_mixer"


-- CMake Content
local cmake_content = [[
cmake_minimum_required(VERSION ]] .. cmake_version .. [[)
project(]] .. project_name .. [[)

set(CMAKE_CXX_STANDARD ]] .. cxx_standard .. [[)

# Find Package
find_package(]] .. dep_SDL .. [[ ]] .. dep_SDL_image .. [[ ]] .. dep_SDL_mixer .. [[ REQUIRED)

add_executable(]] .. project_name .. [[
        main.cpp
        ]] .. executable .. [[)

target_include_directories(]] .. project_name .. [[ PRIVATE ]] .. include_directories_SDL .. [[ ]] .. include_directories_SDL_image .. [[ ]] .. include_directories_SDL_mixer .. [[)

# Link libraries to your executable
target_link_libraries(]] .. project_name .. [[ PRIVATE ]] .. link_SDL .. [[ ]] .. link_SDL_image .. [[ ]] .. lib_directories_SDL_mixer .. [[)
]]

-- Write file
local file = io.open("CMakeLists.txt", "w")

if file then
  file:write(cmake_content)
  file:close()
  print("CMakeLists.txt created successfully!")
else
  print("Failed to create CMakeLists.txt")
end
