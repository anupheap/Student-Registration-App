cmake_minimum_required(VERSION 3.10)
project(StudentGroupingApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Output Directory
# Forces the .exe to be placed in project_root/output/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output")

include_directories(include)
include_directories(src)
link_directories(lib)

# Define Executables
add_executable(${PROJECT_NAME} WIN32 src/main1.cpp)

# Link Libraries
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)

# Copy Assets and DLLs to the output folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    # Copy the entire assets folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    
    # Copy raylib.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/raylib.dll"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raylib.dll"
    
    COMMENT "Syncing assets and DLLs to output folder..."
)