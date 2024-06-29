cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(library VERSION 0.1.0 LANGUAGES CXX)

# Version
configure_file(include/${PROJECT_NAME}/version.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.hpp LF)

# Sources
file(GLOB_RECURSE headers include/*.hpp)
file(GLOB_RECURSE sources src/${PROJECT_NAME}/*.[hc]pp)

# Library
add_library(${PROJECT_NAME} STATIC ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_include_directories(${PROJECT_NAME} PRIVATE src PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

# Dependencies
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

# Main
add_executable(main EXCLUDE_FROM_ALL src/main.cpp src/main.manifest)
target_link_libraries(main PRIVATE ${PROJECT_NAME})

# Tests
find_package(doctest CONFIG)
if(doctest_FOUND)
  add_executable(tests EXCLUDE_FROM_ALL src/test.cpp src/main.manifest)
  target_link_libraries(tests PRIVATE ${PROJECT_NAME} doctest::doctest)
endif()

# Benchmarks
find_package(benchmark CONFIG)
if(benchmark_FOUND)
  add_executable(benchmarks EXCLUDE_FROM_ALL src/benchmark.cpp src/main.manifest)
  target_link_libraries(benchmarks PRIVATE ${PROJECT_NAME} benchmark::benchmark)
endif()

# Install
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})

if(NOT DEFINED INSTALL_HEADERS OR INSTALL_HEADERS)
  install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ DESTINATION include)
endif()

install(EXPORT ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
configure_package_config_file(res/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME})

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
