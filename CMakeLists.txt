# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 4.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project
project (TextBasedAdventure1 VERSION 1.0
DESCRIPTION "A text-based adventure game."
LANGUAGES CXX)

# --- Clang-Tidy Integration --------------------------------------------------
# Enable compile_commands.json generation (used by clang-tidy and IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# User toggle (can be overridden: -DENABLE_CLANG_TIDY=OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis during compilation" ON)
# User toggle (can be overridden: -DENABLE_CLANG_TIDY_WARNINGS_AS_ERRORS=ON)
option(ENABLE_CLANG_TIDY_WARNINGS_AS_ERRORS "Enable warnings as errors" OFF)

if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy clang-tidy.exe)
  file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}" PROJECT_ROOT_PATH)
  set(CLANG_TIDY_CHECKS "modernize-*,readability-*,bugprone-*,performance-*,-modernize-use-trailing-return-type")
  # Only analyze files under project src/ or include/
  set(CLANG_TIDY_HEADER_FILTER "^${PROJECT_ROOT_PATH}/(src|include)/")
  if (CLANG_TIDY_EXE)
    if (ENABLE_CLANG_TIDY_WARNINGS_AS_ERRORS)
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE};-checks=${CLANG_TIDY_CHECKS};-header-filter=${CLANG_TIDY_HEADER_FILTER};--extra-arg=/EHsc;-warnings-as-errors=*")
    else()
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE};-checks=${CLANG_TIDY_CHECKS};-header-filter=${CLANG_TIDY_HEADER_FILTER};--extra-arg=/EHsc")
    endif()
  endif()
endif()
# ------------------------------------------------------------------------------

# Set C++ standard and project-wide include paths
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PROJECT_INCLUDES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/project" ${CMAKE_PROJECT_INCLUDES_PATH})
set(SOURCES "src/main.cpp")

# Text Input/Output Library
add_library (TextIO STATIC 
"src/text_io/text_io.cpp" 
"include/project/text_io.h")
target_include_directories(TextIO PUBLIC SOURCES)

# Finite State Machine (FSM) Library
set(FSM_HEADERS
#state machines
  "include/project/fsm/InterfaceStateMachine.h"
  "include/project/fsm/BaseStateMachine.h"
  "include/project/fsm/GameStateMachine.h"
#states
  "include/project/fsm/InterfaceState.h"
  "include/project/fsm/BaseState.h"
  "include/project/fsm/InitializeState.h"
  "include/project/fsm/SendOutputToUserState.h"
  #"include/project/fsm/RequestUserInputState.h"
  #"include/project/fsm/ProcessUserInputState.h"
  #"include/project/fsm/CheckForSavedGamesState.h"
  #"include/project/fsm/NoSaveGameFoundState.h"
  #"include/project/fsm/SaveGameFoundState.h"
  #"include/project/fsm/CreateNewGameState.h"
  #"include/project/fsm/LoadSavedGameState.h"
  #"include/project/fsm/HandleErrorState.h"
  "include/project/fsm/ValidateGameState.h"
  #"include/project/fsm/StartGameState.h"
  #"include/project/fsm/UpdateWorldAndEntitiesState.h"
  #"include/project/fsm/SaveGameState.h"
)
set(FSM_SOURCES
#state machines
 "src/fsm/BaseStateMachine.cpp"
 "src/fsm/GameStateMachine.cpp"
#states
 "src/fsm/BaseState.cpp"
 "src/fsm/InitializeState.cpp"
 "src/fsm/SendOutputToUserState.cpp"
 #"src/fsm/RequestUserInputState.cpp"
 #"src/fsm/ProcessUserInputState.cpp"
 #"src/fsm/CheckForSavedGamesState.cpp"
 #"src/fsm/NoSaveGameFoundState.cpp"
 #"src/fsm/SaveGameFoundState.cpp"
 #"src/fsm/CreateNewGameState.cpp"
 #"src/fsm/LoadSavedGameState.cpp"
 #"src/fsm/HandleErrorState.cpp"
 "src/fsm/ValidateGameState.cpp"
 #"src/fsm/StartGameState.cpp"
 #"src/fsm/UpdateWorldAndEntitiesState.cpp"
 #"src/fsm/SaveGameState.cpp"
)
add_library (FSM STATIC ${FSM_SOURCES} ${FSM_HEADERS})
target_include_directories(FSM PUBLIC SOURCES)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE TextIO)
target_link_libraries(${PROJECT_NAME} PRIVATE FSM)

# Include sub-projects.
add_subdirectory ("apps")
add_subdirectory ("docs")
add_subdirectory ("scripts")
add_subdirectory ("src")
add_subdirectory ("tests")
