cmake_minimum_required(VERSION 3.10)
project(HZRFN)

# Directory variables
set(SRC ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE ${SRC}/include)

configure_file(${PROJECT_SOURCE_DIR}/setup_info.h ${PROJECT_SOURCE_DIR}/setup_info.h)

# Headers
set(
    HEADER_FILES 
    ${INCLUDE}/engine/engine.h
    ${INCLUDE}/engine/window.h
    ${INCLUDE}/util/sdl_util.h
    ${INCLUDE}/game/entity/components/sprite.h
    ${INCLUDE}/game/entity/components/transform.h
    ${INCLUDE}/game/entity/entity_component.h
    ${INCLUDE}/game/entity_manager.h
    ${INCLUDE}/game/grid_map/grid_map.h
    ${INCLUDE}/util/vec2.h
    ${INCLUDE}/game/map_manager.h
    ${INCLUDE}/game/asset_manager.h
)

# Sources
set(
    SOURCE_FILES 
    ${SRC}/main/main.cpp
    ${SRC}/engine/engine.cpp
    ${SRC}/engine/window.cpp
    ${SRC}/util/sdl_util.cpp
    ${SRC}/game/entity/components/sprite.cpp
    ${SRC}/game/entity/components/transform.cpp
    ${SRC}/game/entity_manager.cpp
    ${SRC}/game/entity/entity_component.cpp
    ${SRC}/game/grid_map/grid_map.cpp
    ${SRC}/util/asset_util.cpp
    ${SRC}/game/map_manager.cpp
    ${SRC}/game/asset_manager.cpp

)

# Linkers
find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_image REQUIRED SDL2_image)

add_library(engineLib ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(engineLib PUBLIC ${INCLUDE})
add_executable(eng ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(eng PUBLIC ${INCLUDE})
target_link_libraries(eng PUBLIC SDL2 SDL2_image)
