project(001_Vulkan_Tutorial_Abstraction)

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

add_executable(001_Vulkan_Tutorial_Abstraction
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

target_include_directories(001_Vulkan_Tutorial_Abstraction
    PUBLIC 
        ${extern_dir}/vulkan/Include
        ${extern_dir}/glm
        ${extern_dir}/glfw/include
        ${extern_dir}/stb
        ${extern_dir}/tinyobjloader
)

target_link_libraries(001_Vulkan_Tutorial_Abstraction
    PUBLIC
        ${extern_dir}/vulkan/Lib/vulkan-1.lib
        ${extern_dir}/glfw/lib-vc2019/glfw3.lib
)

set_property(TARGET 001_Vulkan_Tutorial_Abstraction PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")