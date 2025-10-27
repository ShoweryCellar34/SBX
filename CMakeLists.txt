cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)

add_subdirectory(vendors/Phantom-Renderer)

set(GLFW_BUILD_DOCS     false    CACHE BOOL   "Build the GLFW documentation")
set(GLFW_INSTALL        false    CACHE BOOL   "Generate instilation target")
set(GLFW_USE_HYBRID_HPG true     CACHE BOOL   "Force use of high-performance GPU on hybrid systems")
set(GLFW_LIBRARY_TYPE   "STATIC" CACHE STRING "Library type override for GLFW (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")
add_subdirectory(vendors/glfw)

project(SH34-SBX LANGUAGES C)
set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE SBX_C_SOURCE "source/*.c")
add_executable(SBX ${SBX_C_SOURCE})
target_link_libraries(SBX PUBLIC PR glfw)
target_include_directories(SBX PUBLIC "headers")

if(MSVC)
    target_compile_definitions(SBX PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(GCC)
    target_compile_options(SBX PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address,undefined)
endif()
