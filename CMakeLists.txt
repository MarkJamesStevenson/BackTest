project(BackTest)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in.txt
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

find_package(CURL)
if(CURL_FOUND)
    message("found curl")
else ()
    message("giving a few hints to find curl")
    set(curl_directory "C:/libcurl/curl")
    include_directories("${curl_directory}/include")
    set(CURL_LIBRARIES "${curl_directory}/builds/libcurl-vc14-x64-release-dll-ipv6-sspi-winssl/lib/libcurl.lib")
endif(CURL_FOUND)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
 
# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
                      "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate
file(GLOB_RECURSE sources      src/BackTester/*.cpp src/BackTester/*.h)
file(GLOB_RECURSE sources_test src/test/*.cpp)

add_library (BackTester ${sources})
#target_include_directories (BackTester PUBLIC ${sources})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} BackTester ${CURL_LIBRARIES})

add_executable(test_runner ${sources_test})
target_link_libraries(test_runner gtest_main BackTester ${CURL_LIBRARIES})

enable_testing()
