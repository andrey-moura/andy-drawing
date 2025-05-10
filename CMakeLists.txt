#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(uva-drawing)

# Get the parent directory
get_filename_component(UVA_DRAWING_PARENT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

add_library(uva-drawing OBJECT
    ${CMAKE_CURRENT_LIST_DIR}/src/image.cpp
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

macro(os_specific_target_properties target)
    if(LINUX)
        target_link_libraries(${target} ${GTK3_LIBRARIES} cairo)
    endif()
endmacro()

os_specific_target_properties(uva-drawing)

# Create an executable for each file in examples
file(GLOB EXAMPLES ${CMAKE_CURRENT_LIST_DIR}/examples/*.cpp)

if(FALSE)
    foreach(EXAMPLE ${EXAMPLES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)

        add_executable(${EXAMPLE_NAME} ${EXAMPLE})

        target_link_libraries(${EXAMPLE_NAME} uva-drawing)
        
        os_specific_target_properties(${EXAMPLE_NAME})
    endforeach()
endif()