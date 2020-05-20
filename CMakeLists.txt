cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(library VERSION 0.1.0 LANGUAGES CXX)

# Options
option(DISABLE_BENCHMARK "Disable benchmark" OFF)
option(DISABLE_TESTS "Disable tests" OFF)
option(DISABLE_MAIN "Disable main (used for development)" OFF)

# Version
configure_file(include/${PROJECT_NAME}/version.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.hpp LF)

# Sources
file(GLOB_RECURSE headers include/*.hpp)
file(GLOB_RECURSE sources src/${PROJECT_NAME}/*.[hc]pp)

# Library
add_library(${PROJECT_NAME} STATIC ${headers} ${sources})
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE src PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Dependencies
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

# Install
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})

if(NOT DEFINED INSTALL_HEADERS OR INSTALL_HEADER)
  install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
endif()

install(EXPORT ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)

configure_package_config_file(res/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION lib/cmake/${PROJECT_NAME})

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Benchmark
if(NOT DISABLE_BENCHMARK)
  file(GLOB_RECURSE benchmark_sources src/benchmark/*.[hc]pp)
  add_executable(benchmark EXCLUDE_FROM_ALL ${benchmark_sources})
  target_link_libraries(benchmark PRIVATE ${PROJECT_NAME})

  find_package(benchmark CONFIG REQUIRED)
  target_link_libraries(benchmark PRIVATE benchmark::benchmark_main)
endif()

# Tests
if(NOT DISABLE_TESTS)
  file(GLOB_RECURSE tests_sources src/tests/*.[hc]pp)
  add_executable(tests EXCLUDE_FROM_ALL ${tests_sources})
  target_link_libraries(tests PRIVATE ${PROJECT_NAME})

  find_package(Catch2 CONFIG REQUIRED)
  target_link_libraries(tests PRIVATE Catch2::Catch2)

  include(CTest)
  include(Catch)
  catch_discover_tests(tests)
endif()

# Main
if(NOT DISABLE_MAIN)
  add_executable(main EXCLUDE_FROM_ALL src/main.cpp src/main.manifest)
  target_link_libraries(main PRIVATE ${PROJECT_NAME})
endif()
