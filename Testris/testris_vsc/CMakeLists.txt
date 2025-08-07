cmake_minimum_required(VERSION 3.12)

project(testris_vsc)

add_executable(testris_vsc
    src/main.cpp
    src/Game/engine/GameEngine.cpp
    src/Game/engine/RenderEngine.cpp
    src/Game/main/Block.cpp
    src/Game/main/GameBoard.cpp
)

if (NOT PNG AND WIN32 AND NOT MSVC)
    set(PNG_LIBRARY "C:/Program Files(x86)/libpng")
    set(PNG_PNG_INCLUDE_DIR "C:/Program Files(x86)/libpng/include")
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

target_include_directories(testris_vsc
    PUBLIC include/Game/engine
    PUBLIC include/Game/main
    PUBLIC ${SDL3_INCLUDE_DIRS}
    PUBLIC ${SDL3IMAGE_INCLUDE_DIRS}
)

if (WIN32 AND NOT MSVC)
    target_link_libraries(testris_vsc PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image mingw32)
else() #linux
    target_link_libraries(testris_vsc PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()