cmake_minimum_required(VERSION 3.28.3)
project(space_invaders C)

set(CMAKE_C_STANDARD 23)

add_executable(space_invaders 
        main.c 
        game.c
        textureManager.c
        tank.c
        bubak.c
        bubakGroup.c
        dynamic_array.c
        projectile.c
        shield.c
        ufo.c
        scoreManager.c
        ui.c)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(space_invaders PRIVATE -fsanitize=address)
    target_link_options(space_invaders PRIVATE -fsanitize=address)
endif()


find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(space_invaders PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(space_invaders PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(space_invaders PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

find_package(SDL2_mixer CONFIG REQUIRED)
target_link_libraries(space_invaders PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)