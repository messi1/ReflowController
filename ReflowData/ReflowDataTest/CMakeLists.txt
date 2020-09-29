cmake_minimum_required(VERSION 3.13)
project(ReflowDataTest)

add_definitions(-DGTEST_LANGUAGE_CXX11)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_test(${PROJECT_NAME} COMMAND ${PROJECT_NAME} --filenames-as-tags -o report-backend.xml -r junit)

target_sources(${PROJECT_NAME}
    PRIVATE
        tst_ProfileConfigData.h
        tst_ProfileMeasureData.h
        tst_ProfileSolderData.h
        main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        GTest::GTest
        ReflowData::ReflowData
)

