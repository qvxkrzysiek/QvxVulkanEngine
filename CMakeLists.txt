cmake_minimum_required(VERSION 3.27)
project(QVE)

INCLUDE(FetchContent)
FETCHCONTENT_DECLARE(GLFW GIT_REPOSITORY https://github.com/glfw/glfw.git)
FETCHCONTENT_MAKEAVAILABLE(GLFW)

find_package(Vulkan REQUIRED)
IF (Vulkan_FOUND)
    INCLUDE_DIRECTORIES(${Vulkan_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Vulkan_LIBRARY_DIRS})
ENDIF ()

include(FetchContent)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

set(CMAKE_CXX_STANDARD 17)

# Definiujemy cel QVE przed ustawieniem katalogów nagłówków
add_executable(QVE main.cpp
        qve_window.cpp
        qve_window.h
        first_app.cpp
        first_app.h
        qve_pipeline.cpp
        qve_pipeline.h
        qve_device.cpp
        qve_device.h
        qve_swap_chain.cpp
        qve_swap_chain.h)

# Dodajemy katalogi nagłówków po zdefiniowaniu celu
target_include_directories(QVE PRIVATE ${glm_SOURCE_DIR})

# Linkujemy biblioteki po zdefiniowaniu celu
TARGET_LINK_LIBRARIES(QVE glfw ${Vulkan_LIBRARIES})
