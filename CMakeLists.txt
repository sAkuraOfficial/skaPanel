cmake_minimum_required(VERSION 3.10)
project(lvgl)

# Set policy to allow to run the target_link_libraries cmd on targets that are build
# in another directory.
# Currently, the linking is not handled by env_support/cmake/os.cmake
# This means that if a driver is enabled and it requires linking an external library
# it needs to be handled in the top-level project.

cmake_policy(SET CMP0079 NEW)

# Uncomment if the program needs debugging
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99) # LVGL officially supports C99 and above
set(CMAKE_CXX_STANDARD 17) #C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-write-strings -Wwrite-strings")

set(LV_BUILD_SET_CONFIG_OPTS ON CACHE BOOL
    "create CMAKE variables from lv_conf_internal.h" FORCE)

add_subdirectory(lvgl)

if (CONFIG_LV_USE_EVDEV)
    message("Including EVDEV support")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(EVDEV REQUIRED libevdev)

    list(APPEND PKG_CONFIG_LIB ${EVDEV_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${EVDEV_INCLUDE_DIRS})
    list(APPEND LV_LINUX_BACKEND_SRC src/backend/indev_backends/evdev.c)

endif()

if (CONFIG_LV_USE_FREETYPE)
    message("Including Freetype support")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBFREETYPE REQUIRED freetype2)

    list(APPEND PKG_CONFIG_LIB ${LIBFREETYPE_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${LIBFREETYPE_INCLUDE_DIRS})

endif()

if (CONFIG_LV_USE_LINUX_FBDEV)

    # FBDEV has no dependencies
    message("Including FBDEV support")
    list(APPEND LV_LINUX_BACKEND_SRC src/backend/display_backends/fbdev.c)

endif()


set(LV_USE_FFMPEG 1)
if(LV_USE_FFMPEG)
    message("Including FFMPEG support")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(FFMPEG REQUIRED libavformat libavcodec libavutil libswscale libswresample)
    pkg_check_modules(ALSA REQUIRED alsa) #sudo apt update && sudo apt install libasound2-dev pkg-config

    list(APPEND PKG_CONFIG_LIB ${FFMPEG_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${FFMPEG_INCLUDE_DIRS})
    list(APPEND PKG_CONFIG_LIB ${ALSA_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${ALSA_INCLUDE_DIRS})
endif()

add_subdirectory(3rd/cpr)
add_subdirectory(3rd/json)
find_package(OpenSSL REQUIRED)


file(GLOB LV_LINUX_SRC src/backend/*.c)
set(LV_LINUX_INC src/backend)

target_include_directories(lvgl PUBLIC ${PKG_CONFIG_INC})

add_library(lvgl_linux STATIC ${LV_LINUX_SRC} ${LV_LINUX_BACKEND_SRC})

# If LVGL is configured to use LV_CONF_PATH or Kconfig
# Set the exactly the same definitions on the lvgl_linux target
set_target_properties(lvgl_linux PROPERTIES COMPILE_DEFINITIONS "${LVGL_COMPILER_DEFINES}")
target_include_directories(lvgl_linux PUBLIC
    ${LV_LINUX_INC} ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/backend ${LVGL_CONF_INC_DIR})

# Link LVGL with external dependencies - Modern CMake/CMP0079 allows this
target_link_libraries(lvgl PUBLIC ${PKG_CONFIG_LIB} m pthread)

#-----------------------------------------------------------------

# 收集src/libs目录下所有的C++源文件和头文件
file(GLOB_RECURSE MY_LIBS_SRC 
    "src/libs/*.cpp"
    "src/libs/*.c"
    "src/libs/*.h"
    "src/libs/*.hpp"
    "src/components/*.cpp"
    "src/components/*.c"
    "src/components/*.h"
    "src/components/*.hpp"
    "src/base/*.cpp"
    "src/base/*.hpp"

)

#-----------------------------------------------------------------

add_executable(lvglsim src/main.cpp src/base/base.cpp ${MY_LIBS_SRC} ${LV_LINUX_SRC} ${LV_LINUX_BACKEND_SRC})
# target_link_libraries(lvglsim lvgl_linux lvgl )
target_link_libraries(lvglsim PRIVATE 
    lvgl_linux 
    lvgl 
    cpr::cpr
    OpenSSL::SSL 
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)
target_include_directories(lvglsim PRIVATE src/libs src)

if (CONFIG_LV_USE_DRAW_G2D)
    target_link_libraries(lvglsim g2d)
endif()

# Install the lvgl_linux library and its headers
install(DIRECTORY src/backend/
    DESTINATION include/lvgl
    FILES_MATCHING
    PATTERN "backends*" EXCLUDE
    PATTERN "*.h")

install(TARGETS lvgl_linux
    ARCHIVE DESTINATION lib
)

add_custom_target(run COMMAND ${EXECUTABLE_OUTPUT_PATH}/lvglsim DEPENDS lvglsim)
