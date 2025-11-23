cmake_minimum_required(VERSION 3.10)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Ray Tracer")

# Add WIN32 here to suppress console window
add_executable(CMakeTarget
    "src/CApp.cpp"
    "src/headers/CApp.h"
    "src/main.cpp"
    "src/image.cpp"
    "src/scene.cpp"
    "src/ray.cpp"
    "src/camera.cpp"
    "src/objectbase.cpp"
    "src/objsphere.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# Find SDL2 installed by vcpkg
find_package(SDL2 CONFIG REQUIRED)

# Important: Link both SDL2::SDL2main and SDL2::SDL2
target_link_libraries(CMakeTarget PRIVATE SDL2::SDL2main SDL2::SDL2)

# --- Cross-platform optimization flags ---
if(MSVC)
    # Use /O2 (maximize speed) for Release builds with MSVC
    set_target_properties(CMakeTarget PROPERTIES
        COMPILE_FLAGS_RELEASE "/O2"
    )
else()
    # Use -Ofast for GCC/Clang Release builds
    target_compile_options(CMakeTarget PRIVATE
        $<$<CONFIG:Release>:-Ofast>
    )
endif()
