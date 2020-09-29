cmake_minimum_required(VERSION 3.13)
project(ReflowData)

add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    ProfileConfigData.h
    ProfileConfigData.cpp
    ProfileMeasureData.h
    ProfileMeasureData.cpp
    ProfileSolderData.h
    ProfileSolderData.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
)
