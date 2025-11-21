# CMakeList.txt : CMake project for Ray Tracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Ray Tracer")

# Add source to this project's executable.
add_executable (CMakeTarget "CApp.cpp" "CApp.h" "main.cpp" "image.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
# Find SDL2 installed by vcpkg
find_package(SDL2 CONFIG REQUIRED)

# Link SDL2 to your executable
target_link_libraries(CMakeTarget PRIVATE SDL2::SDL2 SDL2::SDL2main)
