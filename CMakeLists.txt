cmake_minimum_required(VERSION 3.5)
project(TMP)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
add_subdirectory(depends)
add_executable(TMP main.cpp core/res/core.qrc
    core/FboNode.cpp core/FboNode.h
    core/TMRenderer.cpp core/TMRenderer.h
    core/meshObject.cpp core/meshObject.h
    core/manager/ShaderManager.cpp core/manager/ShaderManager.h
    core/manager/CameraManager.cpp core/manager/CameraManager.h
    core/utils/Select.cpp core/utils/Select.h)
include_directories(core depends/easylog depends/glm-0.9.7.1)
target_link_libraries(TMP Qt5::Core Qt5::Quick easylog)

