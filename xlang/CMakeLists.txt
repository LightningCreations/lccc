cmake_minimum_required(VERSION 3.15)
project(xlang CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/Config.hpp)

set(LCCC_XLANG_VERSION 0.1)

message(STATUS "Building xlang API Version ${LCCC_XLANG_VERSION}")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(LCCC_XLANG_PLUGINS_IMPL src/LinuxPlugins.cpp)
endif()

add_library(xlang-targets OBJECT src/Targets/X86.cpp src/Targets/X86.hpp src/Targets/TargetRegistry.cpp src/Targets/TargetRegistry.hpp)

set_target_properties(xlang-targets PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        )

target_include_directories(xlang-targets PRIVATE include ${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(xlang SHARED include/xlang++/Plugins.h include/xlang++/Visit.hpp include/xlang++/Target.hpp src/Visit.cpp include/xlang++/Layout.h include/xlang++/Properties.h
         src/IRWriter.cpp src/Layout.cpp ${LCCC_XLANG_PLUGINS_IMPL}
         src/Target.cpp)
target_include_directories(xlang PUBLIC include ${CMAKE_CURRENT_BINARY_DIR}/include)
target_compile_definitions(xlang PRIVATE BUILD_LIBXLANG)
target_link_libraries(xlang ${CMAKE_DL_LIBS} xlang-targets)

install(TARGETS xlang EXPORT xlang)
set_target_properties(xlang PROPERTIES
        SOVERSION ${LCCC_XLANG_VERSION})

add_executable(xlang-prg src/Main.cpp ${CMAKE_CURRENT_BINARY_DIR}/include/Config.hpp)


target_link_libraries(xlang-prg xlang dl)

set_target_properties(xlang-prg PROPERTIES OUTPUT_NAME xlang)

install(TARGETS xlang-prg)
