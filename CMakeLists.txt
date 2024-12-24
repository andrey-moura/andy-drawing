#Require a minimum version
cmake_minimum_required(VERSION 3.10)

set(UVA_DRAWING_BACKEND "NONE")

if(WIN32)
    set(UVA_DRAWING_BACKEND "win32")
elseif(LINUX)
    find_package(PkgConfig)

    if(PKG_CONFIG_FOUND)
        pkg_check_modules(GTK3 gtk+-3.0)

        if(GTK3_FOUND)
            set(UVA_DRAWING_BACKEND "gtk+-3.0")
        endif()

        include_directories(${GTK3_INCLUDE_DIRS})
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

include("${UVALANG_PARENT_DIRECTORY}/uva/CMakeLists.txt")

uva_library(core)

add_library(uva-drawing
    ${CMAKE_CURRENT_LIST_DIR}/src/memory_surface.${UVA_DRAWING_BACKEND}.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/software_renderer.${UVA_DRAWING_BACKEND}.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/texture_surface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/hardware_renderer.cpp
)

set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL)
find_package(GLEW)

if(OpenGL_FOUND)
    # Link to OpenGL
    target_link_libraries(uva-drawing OpenGL::GL)
else()
    message(STATUS "OpenGL not found")
endif()

if(GLEW_FOUND)
    # Link to glew
    target_link_libraries(uva-drawing ${GLEW_LIBRARIES})
else()
    message(STATUS "glew not found")
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Create an executable for each file in examples
file(GLOB EXAMPLES ${CMAKE_CURRENT_LIST_DIR}/examples/*.cpp)

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
endforeach()