cmake_minimum_required(VERSION 3.19)
project(STFTC LANGUAGES CXX C)
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

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)
option(BUILD_TESTS "Build tests" TRUE)
option(BUILD_PYTHON_BINDING "Build python binding for testing" TRUE)

if(BUILD_PYTHON_BINDING)
  set(PYFINDER_LOCATION ${PROJECT_BINARY_DIR}/PYFINFER.cmake)
  if(NOT (EXISTS ${PYFINDER_LOCATION}))
    message(STATUS "Downloading PYFINDER.cmake to ${PYFINDER_LOCATION}")
    file(DOWNLOAD
         https://raw.githubusercontent.com/pybind/pybind11/master/tools/FindPythonLibsNew.cmake
         ${PYFINDER_LOCATION}
    )
  endif()

  include(${PYFINDER_LOCATION})
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

CPMAddPackage(
  NAME fmt
  GIT_TAG 8.1.1
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # create an installable target
)

CPMAddPackage(
  NAME pffft
  GITHUB_REPOSITORY VuNguyen2k/pffft
  GIT_TAG 33ae794748cf67dc70368bdb38353fff8da50a61
  OPTIONS "PFFFT_USE_TYPE_DOUBLE OFF"
          "INSTALL_PFFFT OFF"
          "PFFFT_USE_BENCH_GREEN OFF"
          "PFFFT_USE_BENCH_KISS OFF"
          "PFFFT_USE_BENCH_POCKET OFF"
          "PFFFT_USE_FFTPACK OFF"
          ${OSX_ADDITIONAL_OPTION}
)

if(LINUX)
  target_compile_options(PFFFT PRIVATE "-fPIC")
endif()

if(BUILD_PYTHON_BINDING)
  CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11
    VERSION 2.10.0
  )
endif()

CPMAddPackage(NAME stftc SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

if(BUILD_TESTS)
  CPMAddPackage(NAME stftc_tests SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)
endif()
