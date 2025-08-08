cmake_minimum_required(VERSION 3.10)
project(record_10s)

find_package(PkgConfig REQUIRED)

# --- Add for sysroot cross-compilation ---
if (DEFINED CMAKE_SYSROOT)
    set(ENV{PKG_CONFIG_SYSROOT            _DIR} ${CMAKE_SYSROOT})
    set(ENV{PKG_CONFIG_PATH} ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig)
endif()

pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(GST_BASE REQUIRED gstreamer-base-1.0)

include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})

add_executable(record_10s record_10s.cpp)
target_link_libraries(record_10s ${GST_LIBRARIES})
