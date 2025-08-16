#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(andy-drawing)

# Get the parent directory
get_filename_component(ANDY_DRAWING_PARENT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

find_package(SDL3 QUIET)

if(TARGET SDL3::SDL3)
    get_target_property(SDL3_INCLUDE_DIRS SDL3::SDL3 INTERFACE_INCLUDE_DIRECTORIES)
    set(FOUND_DRAWING_BACKEND TRUE)
    set(ANDY_DRAWING_BACKEND "sdl3")
    add_compile_definitions(
        ANDY_DRAWING_SDL3
    )
endif()

if(FOUND_DRAWING_BACKEND)
    add_library(andy-drawing OBJECT
        ${CMAKE_CURRENT_LIST_DIR}/src/image.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/${ANDY_DRAWING_BACKEND}/window.cpp
    )
else()
    add_library(andy-drawing INTERFACE)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Create an executable for each file in examples
file(GLOB EXAMPLES ${CMAKE_CURRENT_LIST_DIR}/examples/*.cpp)

if(FALSE)
    foreach(EXAMPLE ${EXAMPLES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)

        add_executable(${EXAMPLE_NAME} ${EXAMPLE})

        target_link_libraries(${EXAMPLE_NAME} andy-drawing)
    endforeach()
endif()