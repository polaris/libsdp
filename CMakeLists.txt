cmake_minimum_required(VERSION 3.12)

project(libsdp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CXX_FLAGS)
set(CXX_FLAGS_RELEASE)
set(CXX_FLAGS_DEBUG)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    message(STATUS "Configuring compiler options for Clang")
    list(APPEND CXX_FLAGS "-Weverything" "-Werror" "-pedantic" "-Wno-c++98-compat" "-Wno-c++98-compat-pedantic" "-Wno-disabled-macro-expansion" "-Wno-padded")
    list(APPEND CXX_FLAGS_RELEASE "-O3")
    list(APPEND CXX_FLAGS_DEBUG "")
elseif(CMAKE_CXX_COMPILER_ID MATCHES GCC)
    message(STATUS "Configuring compiler options for GCC")
    list(APPEND CXX_FLAGS "-Wall" "-Wextra" "-Werror" "-pedantic")
    list(APPEND CXX_FLAGS_RELEASE "-O3")
    list(APPEND CXX_FLAGS_DEBUG "")
else()
    message(WARNING "Unexpected compiler: ${CMAKE_CXX_COMPILER_ID}; Supported: Clang and GCC")
endif()

# libsdp
add_library(sdp include/sdp/sdp.hpp src/sdp.cpp)
target_include_directories(sdp SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS})
target_include_directories(sdp PUBLIC include)
target_compile_options(sdp
        PRIVATE
            ${CXX_FLAGS}
            "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
            "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>")
set_target_properties(sdp
        PROPERTIES
            POSITION_INDEPENDENT_CODE 1
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON)

# test driver
add_executable(test test/test.cpp)
target_include_directories(test SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS})
target_link_libraries(test PRIVATE sdp ${CONAN_LIBS})
target_compile_options(test
        PRIVATE
            ${CXX_FLAGS}
            "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
            "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>")
set_target_properties(test
        PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON)
