cmake_minimum_required(VERSION 3.13)
project(ReflowController)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

option(WARNING_AS_ERRORS "Treat any warning as compile time error" OFF)
option(STATIC_ANALYZERS "Run static analyzers (clang-tidy, cppcheck) during compilation" ON)

find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
find_package(GTest)

if(STATIC_ANALYZERS)
  find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};-quiet")

  find_program(CPPCHECK_COMMAND NAMES cppcheck)
  set(CMAKE_CXX_CPPCHECK "${CPPCHECK_COMMAND};--quiet")

  if(WARNING_AS_ERRORS)
    list(APPEND CMAKE_CXX_CLANG_TIDY "-warnings-as-errors=*")
  endif(WARNING_AS_ERRORS)
endif(STATIC_ANALYZERS)

if(WARNING_AS_ERRORS)
  set(COMPILE_WARNING_AS_ERROR "-Werror")
endif(WARNING_AS_ERRORS)


add_subdirectory(ReflowApp)
add_subdirectory(ReflowApp/ReflowAppLib)
add_subdirectory(ReflowApp/ReflowAppTest)
add_subdirectory(ReflowController/)
add_subdirectory(ReflowController/ReflowControllerTest)
add_subdirectory(ReflowData)
add_subdirectory(ReflowData/ReflowDataTest)
