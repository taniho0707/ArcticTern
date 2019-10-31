# suppress the warning "unused parameter" in HAL Driver
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")

include_directories(${CMAKE_SOURCE_DIR}/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F7xx/Include)

file(GLOB SRCS 
	*.cpp)

add_library(arcticutil STATIC ${SRCS})
