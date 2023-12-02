cmake_minimum_required(VERSION 3.8...3.27)
project(
  alpp
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "C++ wrapper of OpenAL Soft")
option(BUILD_TESTS "Build sources in `/test` directory" ON)

set(${CMAKE_PROJECT_NAME}_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(${CMAKE_PROJECT_NAME}_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/device.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util.cc)

find_package(OpenAL REQUIRED)
if(NOT OpenAL_FOUND)
  message(FATAL_ERROR "Could not find OpenAL.")
endif()

add_library(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_SRCS})
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${${CMAKE_PROJECT_NAME}_INCLUDES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenAL::OpenAL)

if(BUILD_TESTS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()
