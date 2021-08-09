project(003_Vulkan_Skybox)

file(GLOB source
    "*.h"
    "*.cpp"
)

add_executable(003_Vulkan_Skybox
    ${source}
)

set(extern_dir
    ${CMAKE_SOURCE_DIR}/extern
)

target_include_directories(003_Vulkan_Skybox
    PUBLIC 
        ${extern_dir}/vulkan/Include
        ${extern_dir}/glm
        ${extern_dir}/glfw/include
        ${extern_dir}/stb
        ${extern_dir}/tinyobjloader
        ${extern_dir}/tinyexr
)

target_link_libraries(003_Vulkan_Skybox
    PUBLIC
        ${extern_dir}/vulkan/Lib/vulkan-1.lib
        ${extern_dir}/glfw/lib-vc2019/glfw3.lib
)

set_property(TARGET 003_Vulkan_Skybox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")