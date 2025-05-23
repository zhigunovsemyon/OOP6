# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OOP6" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
file(GLOB CXX_FILES "src/*.cc")


if(WIN32)
	set(SDL2_PATH "c:\\sdl2\\")
	set(LINKED_LIB SDL2::Main)
    set(SUBSYSTEM_LINKER_OPTIONS $<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)
else()
	set(LINKED_LIB SDL2)
endif(WIN32)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package (SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

if (WIN32)
	add_definitions("/W3 /WX") #W4 даёт странные ошибки, Wall цепляет ошибки из SDL
else()
	add_definitions("-Wall -Wextra -Werror -Wconversion -Wsign-conversion")
endif(WIN32)

add_executable (${PROJECT_NAME} ${CXX_FILES}) 
target_link_options(${PROJECT_NAME} PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_link_libraries (${PROJECT_NAME} ${LINKED_LIB})
