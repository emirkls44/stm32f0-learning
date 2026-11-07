# Builds every example from the command line (used by CI):
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
#   cmake --build build
# Each folder is also a normal STM32CubeIDE project and can be imported on its own.
cmake_minimum_required(VERSION 3.20)
project(stm32f0_learning C ASM)

set(MCU_FLAGS -mcpu=cortex-m0 -mthumb -mfloat-abi=soft)

function(add_stm32f0_example dir)
    set(root ${CMAKE_SOURCE_DIR}/${dir})
    file(GLOB app_sources ${root}/Core/Src/*.c)
    file(GLOB hal_sources ${root}/Drivers/STM32F0xx_HAL_Driver/Src/*.c)
    file(GLOB startup     ${root}/Core/Startup/*.s)
    file(GLOB linker      ${root}/*_FLASH.ld)

    add_executable(${dir}.elf ${app_sources} ${hal_sources} ${startup})
    target_include_directories(${dir}.elf PRIVATE
        ${root}/Core/Inc
        ${root}/Drivers/STM32F0xx_HAL_Driver/Inc
        ${root}/Drivers/CMSIS/Device/ST/STM32F0xx/Include
        ${root}/Drivers/CMSIS/Include)
    target_compile_definitions(${dir}.elf PRIVATE USE_HAL_DRIVER STM32F051x8)
    target_compile_options(${dir}.elf PRIVATE ${MCU_FLAGS} -Os -g -ffunction-sections -fdata-sections
        $<$<COMPILE_LANGUAGE:C>:-std=gnu11>)
    set_source_files_properties(${app_sources} PROPERTIES COMPILE_OPTIONS "-Wall")
    target_link_options(${dir}.elf PRIVATE ${MCU_FLAGS} -T${linker} --specs=nano.specs
        -Wl,--gc-sections)
endfunction()

file(GLOB example_dirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/[0-9][0-9]-*)
foreach(dir ${example_dirs})
    add_stm32f0_example(${dir})
endforeach()
