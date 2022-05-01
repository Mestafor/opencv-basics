cmake_minimum_required (VERSION 3.16.3)

# # C++ 2017
# target_compile_features(myapp cxx_std_17)
# # C++ 2014
# target_compile_features(myapp cxx_std_14)
# # C++ 2011
# target_compile_features(myapp cxx_std_11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

if (WIN32)
    # set(CMAKE_GENERATOR "Ninja") # set your generator
    message("Win32 used, generator is set to ${CMAKE_GENERATOR}")
endif (WIN32)

# Download all submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodule during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        message("GIT_SUBMOD_RESULT: ${GIT_SUBMOD_RESULT} ${GIT_EXECUTABLE}")
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "`git submodule update --init --recursive` failed with ${GIT_SUBMOD_RESULT}, please check submodules")
        endif()
    endif()
endif()

project(openCV_tutor)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(openCV_main src/main.cpp)
target_link_libraries(openCV_main ${OpenCV_LIBS})

add_executable(openCV_basics src/1-basics.cpp)
target_link_libraries(openCV_basics ${OpenCV_LIBS})

add_executable(openCV_resize src/2-resize.cpp)
target_link_libraries(openCV_resize ${OpenCV_LIBS})

add_executable(openCV_draw src/3-draw.cpp)
target_link_libraries(openCV_draw ${OpenCV_LIBS})

add_executable(openCV_warp src/3-warp.cpp)
target_link_libraries(openCV_warp ${OpenCV_LIBS})

add_executable(openCV_color-detection src/4-color-detection.cpp)
target_link_libraries(openCV_color-detection ${OpenCV_LIBS})

add_executable(openCV_shapes-detection src/5-shapes-detection.cpp)
target_link_libraries(openCV_shapes-detection ${OpenCV_LIBS})

add_executable(openCV_face-detection src/6-face-detection.cpp)
target_link_libraries(openCV_face-detection ${OpenCV_LIBS})

add_executable(openCV_motion-detection src/7-motion-detection.cpp)
target_link_libraries(openCV_motion-detection ${OpenCV_LIBS})
