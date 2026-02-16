cmake_minimum_required(VERSION 3.10)
project("StudentRegistrationApp" VERSION 1.0 LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output")

# 2. Define Resources (Windows Icon)
if(WIN32)
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/app.rc")
endif()
# 3. Define the Executable
# Combining all sources and resources into one target
add_executable(${PROJECT_NAME}
    src/main1.cpp 
    ${APP_ICON_RESOURCE}
)

# 4. Include and Link setup
target_include_directories(${PROJECT_NAME} PRIVATE include src)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)

# 5. Post-Build Sync (Assets and DLLs)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/src/records"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/records"
    
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/raylib.dll"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raylib.dll"
    
    COMMENT "Syncing assets and DLLs to output folder..."
)