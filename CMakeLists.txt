cmake_minimum_required(VERSION 3.15)

set(OPENGL_EXAMPLE_PROJECT_NAME opengl_example)
project(${OPENGL_EXAMPLE_PROJECT_NAME})

set(CMAKE_CXX_COMPILER c++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(OPENGL_EXAMPLE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(OPENGL_EXAMPLE_LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/libs)
set(OPENGL_EXAMPLE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# 设置源码编译依赖库
set(OPENGL_EXAMPLE_LIBRARIES glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 从源码编译依赖库
foreach(LIBRARY ${OPENGL_EXAMPLE_LIBRARIES})
    add_subdirectory(${OPENGL_EXAMPLE_LIBRARIES_DIR}/${LIBRARY})
endforeach(LIBRARY)

# 从系统查找依赖库
find_package(OpenGL REQUIRED) # xcode

# 从src编译依赖库
add_library(GLAD ${OPENGL_EXAMPLE_SOURCE_DIR}/glad.c)

# 指定头文件路径
include_directories(${OPENGL_EXAMPLE_INCLUDE_DIR})

# 遍历编译可执行文件
FILE(GLOB SRC_CPP_LIST ${OPENGL_EXAMPLE_SOURCE_DIR}/*/*.cpp)
foreach(src_cpp ${SRC_CPP_LIST})
    # 获取cpp文件前缀
    get_filename_component(exe_name ${src_cpp} NAME_WE)
    # 获取cpp文件路径以及上一级目录
    get_filename_component(exe_dir ${src_cpp} DIRECTORY)
    get_filename_component(par_dir ${exe_dir} NAME)
    # 设置可执行文件全名
    set(full_exe_name ${par_dir}_${exe_name})
    # 生成可执行文件
    add_executable(${full_exe_name} ${src_cpp})
    # 链接相关依赖库
    target_link_libraries(${full_exe_name} OpenGL::GL ${OPENGL_EXAMPLE_LIBRARIES} GLAD)
endforeach()
