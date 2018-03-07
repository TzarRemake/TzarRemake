cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(TzarRemake)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
file(GLOB SOURCES
  "src/handlers/*.cpp"
  "src/handlers/*.h"
  "src/states/*.cpp"
  "src/states/*.h"
  "src/*.cpp"
  "src/*.h"
)

set(EXECUTABLE_NAME "TzarRemake")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Find any version 2.4.x of SFML
find_package(SFML 2.4 REQUIRED network audio graphics window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
