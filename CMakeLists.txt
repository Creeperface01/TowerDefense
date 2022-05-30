cmake_minimum_required(VERSION 3.21)
project(tower_defense)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

#dir for library path aliases
set(ALIAS_DIR "${CMAKE_BINARY_DIR}/aliases")
file(MAKE_DIRECTORY ${ALIAS_DIR})

include(cmake/Utils.cmake)
include(cmake/DownloadProject.cmake)

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        )

# centurion
download_project(PROJ centurion
        GIT_REPOSITORY https://github.com/Creeperface01/centurion.git
        GIT_TAG v6.3.1
        )

file(GLOB_RECURSE CENTURION_SOURCES ${centurion_SOURCE_DIR}/src/*.hpp)

# nanogui
download_project(PROJ nanogui
        GIT_REPOSITORY https://github.com/Creeperface01/nanogui-sdl.git
        GIT_TAG tower_defense
        )

#git_project(PROJECT_NAME nanogui
#        GIT_REPOSITORY https://github.com/Creeperface01/nanogui-sdl.git
#        GIT_TAG tower_defense
#        CMAKE_ARGS "${CMAKE_ARGS};NANOGUI_BUILD_EXAMPLE=OFF"
#        )

file(GLOB_RECURSE NANOGUI_SOURCES
        ${nanogui_SOURCE_DIR}/sdlgui/*.h
        ${nanogui_SOURCE_DIR}/sdlgui/*.cpp
        ${nanogui_SOURCE_DIR}/sdlgui/*.c
        )

execute_process(
        COMMAND ln -s "${SDL2_INCLUDE_DIR}" "${ALIAS_DIR}"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE CMD_ERROR
        OUTPUT_FILE CMD_OUTPUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

#math
download_project(PROJ vector_math
        GIT_REPOSITORY https://github.com/Creeperface01/math.git
        GIT_TAG develop
        )

file(GLOB_RECURSE VECTOR_MATH_SOURCES ${vector_math_SOURCE_DIR}/include/*.hpp)

#pfd
download_project(PROJ pfd
        GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
        GIT_TAG main
        )

set(PFD_SOURCES ${pfd_SOURCE_DIR}/portable-file-dialogs.h)

# sources
include_directories(
        ${ALIAS_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${centurion_SOURCE_DIR}/src
        ${nanogui_SOURCE_DIR}
        ${vector_math_SOURCE_DIR}/include
        ${pfd_SOURCE_DIR}
)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${CENTURION_SOURCES}
        ${NANOGUI_SOURCES}
        ${VECTOR_MATH_SOURCES}
        ${PFD_SOURCES}
        )

target_link_libraries(${PROJECT_NAME} -lm
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        )
