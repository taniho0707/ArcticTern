cmake_minimum_required(VERSION 3.1.0)

project(arctictern)

# to compile startup file
enable_language(ASM)

set(CMAKE_C_FLAGS_DEBUG "-O0 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_subdirectory(Drivers/STM32F7xx_HAL_Driver)
add_subdirectory(util)
add_subdirectory(middleware)

include_directories(
		Inc
		util
		middleware
		Drivers/CMSIS/Include
		Drivers/CMSIS/Device/ST/STM32F7xx/Include
		Drivers/STM32F7xx_HAL_Driver/Inc)

file(GLOB SRCS 
	Src/*.c
	Src/*.cpp
	startup_stm32f765xx.s)

# to link cmsis dsp libray, add a path to the static library
link_directories(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Lib/GCC)

set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME}.elf)
add_executable(${EXECUTABLE_NAME} ${SRCS})

target_link_libraries(${EXECUTABLE_NAME}
		hal
		libarm_cortexM7lfsp_math.a
		arcticutil
		arcticmiddleware)

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -Obinary ${EXECUTABLE_NAME} ${CMAKE_PROJECT_NAME}.bin)

# display the size of the output binary after a build is finished
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND arm-none-eabi-size --format=berkeley "${EXECUTABLE_NAME}")
