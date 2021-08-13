project(000_Vulkan_Tutorial)

file(GLOB SRC
    "*.cpp"
)

file(GLOB_RECURSE SHADERS
    "*.vert"
    "*.frag"
)

add_executable(000_Vulkan_Tutorial
    ${SRC}
    ${SHADERS}
)

source_group("Source Files"            FILES ${SRC})
source_group("GLSL Shaders"        FILES ${SHADERS})

set(extern_dir
    ${CMAKE_SOURCE_DIR}/extern
)

target_include_directories(000_Vulkan_Tutorial
    PUBLIC 
        ${extern_dir}/vulkan/Include
        ${extern_dir}/glm
        ${extern_dir}/glfw/include
        ${extern_dir}/stb
        ${extern_dir}/tinyobjloader
)

target_link_libraries(000_Vulkan_Tutorial
    PUBLIC
        ${extern_dir}/vulkan/Lib/vulkan-1.lib
        ${extern_dir}/glfw/lib-vc2019/glfw3.lib
)

set_property(TARGET 000_Vulkan_Tutorial PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")