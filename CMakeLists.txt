project(BackTest)
cmake_minimum_required(VERSION 2.8.11)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-Wall")

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
    set(curl_directory "C:/curl/builds/libcurl-vc15-x64-release-dll-ipv6-sspi-winssl")
    include_directories("${curl_directory}/include")
    set(CURL_LIBRARIES "${curl_directory}/lib/libcurl.lib")
endif(CURL_FOUND)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
find_package(Qt5Widgets)
find_package(Qt5PrintSupport)

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
file(GLOB_RECURSE sources      src/BackTester/Brokers/*.cpp       src/BackTester/Brokers/*.h
                               src/BackTester/DataProviders/*.cpp src/BackTester/DataProviders/*.h
                               src/BackTester/Strategies/*.cpp    src/BackTester/Strategies/*.h
                               src/BackTester/Utilities/*.cpp     src/BackTester/Utilities/*.h
                               src/BackTester/Events/*.cpp        src/BackTester/Events/*.h
                               src/BackTester/Portfolios/*.cpp    src/BackTester/Portfolios/*.h
                               src/BackTester/*.cpp               src/BackTester/*.h)

file(GLOB_RECURSE sources_test src/test/*.cpp)

add_library (BackTester ${sources})
include_directories(src/BackTester/Brokers
                    src/BackTester/DataProviders
                    src/BackTester/Strategies
                    src/BackTester/Utilities
                    src/BackTester/Events
                    src/BackTester/Portfolios
                    src/BackTester)
target_link_libraries(BackTester Qt5::Widgets)

set(GUI_UI_FILES src/Gui/mainwindow.ui)

set(Q_CUSTOM_PLOT_FILES src/Gui/External/qcustomplot.h src/Gui/External/qcustomplot.cpp)
add_library(Gui src/Gui/mainwindow.cpp src/Gui/mainwindow.h ${GUI_UI_FILES} ${Q_CUSTOM_PLOT_FILES})
INCLUDE_DIRECTORIES(src/Gui src/Gui/External)
target_link_libraries (Gui Qt5::Widgets Qt5::PrintSupport)

add_executable(${PROJECT_NAME} src/main.cpp )
target_link_libraries(${PROJECT_NAME} Gui BackTester ${CURL_LIBRARIES} Qt5::Widgets)

add_executable(test_runner ${sources_test})
target_link_libraries(test_runner gtest_main BackTester ${CURL_LIBRARIES} Qt5::Widgets )

enable_testing()
