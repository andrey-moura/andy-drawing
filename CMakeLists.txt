#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(andy-drawing)

# Get the parent directory
get_filename_component(ANDY_DRAWING_PARENT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# Check if GTK3 is available
find_package(PkgConfig)

if(PkgConfig_FOUND)
    pkg_check_modules(GTK3 QUIET gtk+-3.0)
endif()

if(GTK3_FOUND)
    set(FOUND_DRAWING_BACKEND TRUE)
    set(ANDY_DRAWING_BACKEND "gtk3")
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_compile_definitions(
        ANDY_DRAWING_GTK3
    )
    set(ANDY_DRAWING_BACKEND_LIBRARIES ${GTK3_LIBRARIES})
endif()

if(FOUND_DRAWING_BACKEND)
    add_library(andy-drawing OBJECT
        ${CMAKE_CURRENT_LIST_DIR}/src/image.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/${ANDY_DRAWING_BACKEND}/window.cpp
    )
    target_link_libraries(andy-drawing PRIVATE ${ANDY_DRAWING_BACKEND_LIBRARIES})
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