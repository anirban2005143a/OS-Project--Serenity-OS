cmake_minimum_required(VERSION 3.16)
project(SameBoyPort)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SerenityOS_SOURCE_DIR $ENV{SERENITY_SOURCE_DIR})
include(${SerenityOS_SOURCE_DIR}/Meta/CMake/code_generators.cmake)
add_custom_target(all_generated)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sameboy_core)

# Add emulator source files
set(SOURCES
    src/main.cpp
    sameboy_core/apu.c
    sameboy_core/apu.h
    sameboy_core/camera.c
    sameboy_core/camera.h
    sameboy_core/cheats.c
    sameboy_core/cheat_search.c
    sameboy_core/cheat_search.h
    sameboy_core/cheats.h
    sameboy_core/debugger.c
    sameboy_core/debugger.h
    sameboy_core/defs.h
    sameboy_core/display.c
    sameboy_core/display.h
    sameboy_core/gb.c
    sameboy_core/gb.h
    sameboy_core/graphics/agb_border.inc
    sameboy_core/graphics/cgb_border.inc
    sameboy_core/graphics/dmg_border.inc
    sameboy_core/graphics/mgb_border.inc
    sameboy_core/graphics/sgb_animation_logo.inc
    sameboy_core/graphics/sgb_border.inc
    sameboy_core/joypad.c
    sameboy_core/joypad.h
    sameboy_core/mbc.c
    sameboy_core/mbc.h
    sameboy_core/memory.c
    sameboy_core/memory.h
    sameboy_core/model.h
    sameboy_core/printer.c
    sameboy_core/printer.h
    sameboy_core/random.c
    sameboy_core/random.h
    sameboy_core/rewind.c
    sameboy_core/rewind.h
    sameboy_core/rumble.c
    sameboy_core/rumble.h
    sameboy_core/save_state.c
    sameboy_core/save_state.h
    sameboy_core/sgb.c
    sameboy_core/sgb.h
    sameboy_core/sm83_cpu.c
    sameboy_core/sm83_cpu.h
    sameboy_core/sm83_disassembler.c
    sameboy_core/symbol_hash.c
    sameboy_core/symbol_hash.h
    sameboy_core/timing.c
    sameboy_core/timing.h
    sameboy_core/workboy.c
    sameboy_core/workboy.h
)


add_executable(SameBoyPort ${SOURCES})
target_link_libraries(SameBoyPort gui main)
install(TARGETS SameBoyPort RUNTIME DESTINATION bin)
