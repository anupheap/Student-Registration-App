cmake_minimum_required(VERSION 3.10)
project("StudentRegistrationApp" VERSION 1.0 LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output")


if(WIN32)
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/app.rc")
endif()

add_executable(${PROJECT_NAME}
    src/main1.cpp 
    ${APP_ICON_RESOURCE}
)
message(STATUS "(1).    Added Executable.\n")

target_include_directories(${PROJECT_NAME} PRIVATE include src)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)
message(STATUS "(2).    Linked Libraries: raylib, opengl32, gdi32, winmm.\n")


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/raylib.dll"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raylib.dll"
    
    COMMENT "Syncing assets and DLLs to output folder..."
)

message(STATUS "(3).    Post-build commands set to sync assets and DLLs.\n")

file(REMOVE_RECURSE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/records")

file(
    COPY "${CMAKE_SOURCE_DIR}/src/records"
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

message(STATUS "(4).    Records Database Created and or Overwritten.\n")

message(STATUS "Build Configured Successfully. Initiating Build Process...\n")
