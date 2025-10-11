# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 4.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (TextBasedAdventure1 VERSION 1.0
DESCRIPTION "A text-based adventure game."
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PROJECT_INCLUDES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/project" ${CMAKE_PROJECT_INCLUDES_PATH})
set(SOURCES "src/main.cpp")

add_library (TextIO STATIC 
"src/text_io/text_io.cpp" 
"include/project/text_io.h")
target_include_directories(TextIO PUBLIC SOURCES)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE TextIO)

# Include sub-projects.
add_subdirectory ("apps")
add_subdirectory ("docs")
add_subdirectory ("scripts")
add_subdirectory ("src")
add_subdirectory ("tests")
