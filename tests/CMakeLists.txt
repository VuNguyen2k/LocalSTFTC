cmake_minimum_required(VERSION 3.19)
project(stftc_tests LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
  enable_language(OBJCXX OBJC)
  set(CMAKE_OSX_DEPLOYMENT_TARGET
      "10.15"
      CACHE STRING "Minimum OS X deployment version" FORCE
  )

  if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
  endif()
endif()

if(EMSCRIPTEN)
  message(FATAL_ERROR "EMSCRIPTEN is not supported")
endif()

if(APPLE)
  if((arm64 IN_LIST CMAKE_OSX_ARCHITECTURES) AND (x86_64 IN_LIST CMAKE_OSX_ARCHITECTURES)
  )# universal build
    set(OSX_ADDITIONAL_OPTION "CMAKE_SYSTEM_PROCESSOR osx-universal")
  else()
    set(OSX_ADDITIONAL_OPTION "CMAKE_SYSTEM_PROCESSOR ${CMAKE_OSX_ARCHITECTURES}")
  endif()
else()
  set(OSX_ADDITIONAL_OPTION "")
endif()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

add_executable(test_pffft ${CMAKE_CURRENT_SOURCE_DIR}/main_pffft.cpp)
target_include_directories(test_pffft PRIVATE ${INCLUDE_DIR} ${pffft_SOURCE_DIR})
target_link_libraries(test_pffft PRIVATE PFFFT)
set_target_properties(test_pffft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(test_fft ${CMAKE_CURRENT_SOURCE_DIR}/main_fft.cpp)
target_include_directories(test_fft PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_fft PRIVATE stftc)
set_target_properties(test_fft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(test_buffer ${CMAKE_CURRENT_SOURCE_DIR}/main_buffer.cpp)
target_include_directories(test_buffer PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_buffer PRIVATE stftc)
set_target_properties(test_buffer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(test_ola ${CMAKE_CURRENT_SOURCE_DIR}/main_ola.cpp)
target_include_directories(test_ola PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_ola PRIVATE stftc)
set_target_properties(test_ola PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(test_rtstft ${CMAKE_CURRENT_SOURCE_DIR}/main_rtstft.cpp)
target_include_directories(test_rtstft PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_rtstft PRIVATE stftc)
set_target_properties(test_rtstft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
