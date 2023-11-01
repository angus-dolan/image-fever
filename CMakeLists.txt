cmake_minimum_required(VERSION 3.16)
project(ImageFever LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6.0 COMPONENTS graphics REQUIRED)

# OpenCV
set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/opencv2")
find_package(OpenCV REQUIRED)

# Executable
add_executable(ImageFever main.cpp gui.cpp preload_images.cpp process_images.cpp shared_state.cpp)

# Link
target_link_libraries(ImageFever PRIVATE sfml-graphics ${OpenCV_LIBS})

target_compile_definitions(ImageFever PRIVATE CMAKE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(ImageFever PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET ImageFever POST_BUILD
            COMMENT "Copying SFML DLLs"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.6.0/bin" $<TARGET_FILE_DIR:ImageFever>
            VERBATIM)
endif()

install(TARGETS ImageFever)