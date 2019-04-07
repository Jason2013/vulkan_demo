cmake_minimum_required(VERSION 3.12)

project(Vulkan_Demo)

set(VULKAN_DIR ${CMAKE_SOURCE_DIR}/external/vulkan/1.1.82.0)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)
set(GLM_DIR ${CMAKE_SOURCE_DIR}/external/glm)
set(TINYGLTF_DIR ${CMAKE_SOURCE_DIR}/external/tinygltf)

include_directories(
    ${VULKAN_DIR}/Include
    ${GLFW_DIR}/include
    ${GLM_DIR}
    ${TINYGLTF_DIR}
    ${TINYGLTF_DIR}/examples/common
    )

link_libraries(${VULKAN_DIR}/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,Lib,Lib32>/vulkan-1.lib
    ${GLFW_DIR}/lib/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/$<IF:$<CONFIG:Debug>,Debug,Release>/glfw3.lib
    )

set(TARGET_NAME vulkan_demo)

add_executable(${TARGET_NAME}
    main.cpp
    )

target_compile_options(${TARGET_NAME} PRIVATE
    /std:c++17
    )

set(GLSL_COMPILER ${VULKAN_DIR}/Bin/glslangValidator)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders"
    # COMMAND glslangValidator -V -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/vert.spv ${CMAKE_CURRENT_SOURCE_DIR}/../25_shader_textures.vert
    # COMMAND glslangValidator -V -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/frag.spv ${CMAKE_CURRENT_SOURCE_DIR}/../25_shader_textures.frag
    COMMAND ${GLSL_COMPILER} -V -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/vert.spv ${CMAKE_CURRENT_SOURCE_DIR}/main.vert
    COMMAND ${GLSL_COMPILER} -V -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/frag.spv ${CMAKE_CURRENT_SOURCE_DIR}/main.frag
    # COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/textures"
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/uvtemplate.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures/uvtemplate.bmp
    # COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/models"
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/chalet.obj ${CMAKE_CURRENT_BINARY_DIR}/models/chalet.obj
    )
