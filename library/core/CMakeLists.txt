# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/main/c")
set (GRAPHICS_SOURCE_DIR "${SOURCE_DIR}/graphics")
set (MATH_SOURCE_DIR "${SOURCE_DIR}/math")
set (UTILS_SOURCE_DIR "${SOURCE_DIR}/utils")
set (GEOMETRY_SOURCE_DIR "${SOURCE_DIR}/geometry")

SET( SOURCES

    # Root source dir.
    ${SOURCE_DIR}/exogfx_jni.c

    # Graphics source dir.
    ${GRAPHICS_SOURCE_DIR}/gfx.c
    ${GRAPHICS_SOURCE_DIR}/context.c
    ${GRAPHICS_SOURCE_DIR}/ogles_renderer.c
    ${GRAPHICS_SOURCE_DIR}/ogles_fbo.c
    ${GRAPHICS_SOURCE_DIR}/ogles_presentation_filter.c
    ${GRAPHICS_SOURCE_DIR}/ogles_video_filter.c

    # Utils source dir.
    ${UTILS_SOURCE_DIR}/lib_loader.c
    ${UTILS_SOURCE_DIR}/ogles_util.c
    ${UTILS_SOURCE_DIR}/math_util.c
    ${UTILS_SOURCE_DIR}/map.c

    # Geometry source dir.
    ${GEOMETRY_SOURCE_DIR}/primitive.c
    ${GEOMETRY_SOURCE_DIR}/mesh_factory.c
    ${GEOMETRY_SOURCE_DIR}/plane.c

    # Math source dir.
    ${MATH_SOURCE_DIR}/mat4.c )

SET( HEADERS

     # Utils source dir.
     ${UTILS_SOURCE_DIR}/log_util.h
     ${UTILS_SOURCE_DIR}/ogles_util.h
     ${UTILS_SOURCE_DIR}/math_util.h
     ${UTILS_SOURCE_DIR}/lib_loader.h
     ${UTILS_SOURCE_DIR}/map.h

     # Geometry source dir.
     ${GEOMETRY_SOURCE_DIR}/primitive_type.h
     ${GEOMETRY_SOURCE_DIR}/primitive.h
     ${GEOMETRY_SOURCE_DIR}/mesh_factory.h
     ${GEOMETRY_SOURCE_DIR}/plane.h

     # Math source dir.
     ${MATH_SOURCE_DIR}/mat4.h

     # Graphics source dir.
     ${GRAPHICS_SOURCE_DIR}/gfx.h
     ${GRAPHICS_SOURCE_DIR}/context.h
     ${GRAPHICS_SOURCE_DIR}/ogles.h
     ${GRAPHICS_SOURCE_DIR}/ogles_func.h
     ${GRAPHICS_SOURCE_DIR}/ogles_fbo.h
     ${GRAPHICS_SOURCE_DIR}/ogles_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_presentation_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_video_filter.h )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_library( # Sets the name of the library.
             exogfx_jni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SOURCES} ${HEADERS})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( log-lib log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       exogfx_jni
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )