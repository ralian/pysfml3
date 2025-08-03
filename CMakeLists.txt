cmake_minimum_required(VERSION 3.24)
project(pysfml VERSION 3.0.0 LANGUAGES CXX)
cmake_policy(VERSION 3.24...3.31)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES ON)

# Find required packages
#set(PYBIND11_FINDPYTHON ON)
#set(PYBIND11_PYTHON_VERSION 3.13)
find_package(pybind11 REQUIRED PATHS "C:/Program Files (x86)/pybind11/share/cmake/pybind11/")
find_package(SFML 3 REQUIRED COMPONENTS Window Graphics System PATHS "C:/Program Files (x86)/SFML/lib/cmake/SFML") # 

# Create the Python module
pybind11_add_module(pysfml3 
    src/pysfml.cpp
    src/Event.cpp
    src/Font.cpp
    src/Keyboard.cpp
    src/Mouse.cpp
    src/Text.cpp
    src/system_bindings.cpp
    src/window_bindings.cpp
    src/graphics_bindings.cpp
)

# Link SFML libraries
target_link_libraries(pysfml3 PRIVATE 
    SFML::System 
    SFML::Window
    SFML::Graphics
)

# Include directories
target_include_directories(pysfml3 PRIVATE 
    include/
    #${SFML_INCLUDE_DIR}
    ${pybind11_INCLUDE_DIR}
)

# Compiler-specific options
target_compile_definitions(pysfml3 PRIVATE VERSION_INFO=${PROJECT_VERSION})

# Set properties for the module
set_target_properties(pysfml3 PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(pysfml3 PRIVATE SFML_STATIC)
endif() 
