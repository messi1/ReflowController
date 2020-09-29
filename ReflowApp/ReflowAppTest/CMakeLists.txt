cmake_minimum_required(VERSION 3.13)
project(ReflowAppTest)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        tst_Persistence.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        GTest::GTest
        ReflowAppLib::ReflowAppLib
)
