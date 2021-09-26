get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME})

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

add_executable(${PROJECT_NAME}
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

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${extern_dir}/vulkan/Include
        ${extern_dir}/glm
        ${extern_dir}/glfw/include
        ${extern_dir}/stb
        ${extern_dir}/tinyobjloader
        ${extern_dir}/tinyexr
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${extern_dir}/vulkan/Lib/vulkan-1.lib
        ${extern_dir}/glfw/lib-vc2019/glfw3.lib
)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")