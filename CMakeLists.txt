cmake_minimum_required(VERSION 3.16)
project(AtomModel LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

add_executable(atom
    src/main.cpp
    external/glad/src/glad.c
)

target_include_directories(atom PRIVATE
    include
    external/glad/include
    external/stb
)

target_link_libraries(atom PRIVATE glfw glm::glm)

if(WIN32)
    target_link_libraries(atom PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(atom PRIVATE "-framework OpenGL")
else()
    target_link_libraries(atom PRIVATE GL)
endif()

# Kopiuj shadery i tekstury obok pliku wykonywalnego
add_custom_command(TARGET atom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:atom>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:atom>/textures
)
