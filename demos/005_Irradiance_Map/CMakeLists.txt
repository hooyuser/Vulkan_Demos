project(005_Irradiance_Map)

file(GLOB SRC
    "*.cpp"
)

file(GLOB HEADER
    "*.h"
)

file(GLOB_RECURSE SHADERS
    "*.vert"
    "*.frag"
)

add_executable(005_Irradiance_Map
    ${SRC}
    ${HEADER}
    ${SHADERS}
)

source_group("Source Files"            FILES ${SRC})
source_group("Header Files"            FILES ${HEADER})
source_group("GLSL Shaders"        FILES ${SHADERS})
set(extern_dir
    ${CMAKE_SOURCE_DIR}/extern
)

target_include_directories(005_Irradiance_Map
    PUBLIC 
        ${extern_dir}/vulkan/Include
        ${extern_dir}/glm
        ${extern_dir}/glfw/include
        ${extern_dir}/stb
        ${extern_dir}/tinyobjloader
        ${extern_dir}/tinyexr
)

target_link_libraries(005_Irradiance_Map
    PUBLIC
        ${extern_dir}/vulkan/Lib/vulkan-1.lib
        ${extern_dir}/glfw/lib-vc2019/glfw3.lib
)

set_property(TARGET 005_Irradiance_Map PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")