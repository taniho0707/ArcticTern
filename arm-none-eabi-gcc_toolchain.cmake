set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_EXE_LINKER arm-none-eabi-g++)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

unset(CMAKE_C_FLAGS CACHE)
set(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 \
                    -fsingle-precision-constant -ffunction-sections -fdata-sections \
                    -g3 -Wall -Wextra \
                    -DSTM32F765xx -DUSE_HAL_DRIVER -DARM_MATH_CM7 " CACHE STRING "" FORCE)

unset(CMAKE_AS_FLAGS CACHE)
set(CMAKE_AS_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp" CACHE STRING "" FORCE)

unset(CMAKE_CXX_FLAGS CACHE)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-use-cxa-atexit -fno-exceptions -fno-rtti" CACHE STRING "" FORCE)

# If you implement systemcall manually, delete "--specs=nosys.specs" option
unset(CMAKE_EXE_LINKER_FLAGS CACHE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -L ${CMAKE_SOURCE_DIR} -T STM32F765VITx_FLASH.ld \
                        -lc -lm --specs=nosys.specs -Xlinker --gc-sections -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE STRING "" FORCE)
