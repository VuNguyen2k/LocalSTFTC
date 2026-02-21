cmake_minimum_required(VERSION 3.19)
project(stftc_windows LANGUAGES CXX C)
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

file(GLOB stftc_windows_SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(stftc_windows STATIC ${stftc_windows_SOURCE_FILES})

target_include_directories(stftc_windows PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(stftc_windows PUBLIC fmt::fmt)
