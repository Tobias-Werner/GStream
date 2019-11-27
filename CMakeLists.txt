cmake_minimum_required(VERSION 3.8)
project(STREAMS LANGUAGES CXX C VERSION 0)
set(CMAKE_CXX_STANDARD 11)

#############################################
#               Configuration               #
#############################################

# Calling flex and lemon to generate scanner- and parser-sources
set(UPDATE_PARSER false)
#set(UPDATE_PARSER true)

# Setting target architecture (LINUX64 = Desktop, ARM6 = Raspberry PI3)
set(DST_HARDWARE "LINUX64")
#set(DST_HARDWARE "ARM6")

#############################################

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wuninitialized -Wno-unused-parameter -fstandalone-debug")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wuninitialized -Wno-unused-parameter -O3")

find_package(Threads)

file(GLOB_RECURSE sources src/*.cpp include/*.h)
include_directories(include)

add_library(streams SHARED ${sources})
set_property(TARGET streams PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE test/include/catch)

IF (UPDATE_PARSER)
    add_custom_target(
            generateTokenizerAndParser ALL
            COMMAND /bin/bash ../tools/updateParserSources.sh
    )
    add_dependencies(streams generateTokenizerAndParser)
ENDIF ()

add_executable(libstream-tests test/src/tests.cpp)
target_link_libraries(libstream-tests LINK_PUBLIC sqlite3 ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} Catch streams)
add_dependencies(libstream-tests streams)

set(CMAKE_SYSTEM_NAME Linux)

IF (DST_HARDWARE STREQUAL LINUX64)
    set(triple x86_64-linux-gnu)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
ELSEIF (DST_HARDWARE STREQUAL ARM6)
    set(CMAKE_CROSSCOMPILING true)
    set(CMAKE_SYSROOT /home/tobias/raspbian-sdk/sysroot)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(triple arm-linux-gnueabihf)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)
ENDIF ()

install(TARGETS streams libstream-tests
        LIBRARY DESTINATION lib/${triple}
        RUNTIME DESTINATION bin)

add_custom_command(TARGET streams POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:streams> ../build/libstreams.so
        )

set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CPACK_PACKAGE_DESCRIPTION "A tiny, lightweight and fast SQLite extension for processing spatio-temporal datastreams on embedded systems.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A tiny, lightweight and fast SQLite extension for processing spatio-temporal datastreams on embedded systems.")
set(CPACK_PACKAGE_VENDOR "Jade HS")
set(CPACK_PACKAGE_CONTACT "tobias.werner@jade-hs.de")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tobias Werner")
set(CPACK_COMPONENTS_ALL Libraries ApplicationData)
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsqlite3-0 (>= 3.00)")

include(CPack)
