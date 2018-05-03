##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [2.26.0] date: [Tue Apr 24 22:02:25 JST 2018]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = ArcticTern


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# source path
SOURCES_DIR =  \
Drivers/STM32F7xx_HAL_Driver \
Drivers/CMSIS \
Drivers

# firmware library path
PERIFLIB_PATH = 

# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.c \
Src/stm32f7xx_hal_msp.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
Src/system_stm32f7xx.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
Src/stm32f7xx_it.c

# C++ sources
CPP_SOURCES = \
$(wildcard Src/*.cpp)

# ASM sources
ASM_SOURCES =  \
startup_stm32f765xx.s


######################################
# firmware library
######################################
PERIFLIB_SOURCES = 


#######################################
# binaries
#######################################
BINPATH = /usr/bin
PREFIX = arm-none-eabi-
CC = $(BINPATH)/$(PREFIX)g++
AS = $(BINPATH)/$(PREFIX)g++ -x assembler-with-cpp
CP = $(BINPATH)/$(PREFIX)objcopy
AR = $(BINPATH)/$(PREFIX)ar
SZ = $(BINPATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=softfp

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F765xx \
-D__FPU_PRESENT
# -DARM_MATH_CM4


# AS includes
AS_INCLUDES =  -x assembler-with-cpp

# C includes
C_INCLUDES =  \
-IInc \
-IDrivers/STM32F7xx_HAL_Driver/Inc \
-IDrivers/STM32F7xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F7xx/Include \
-IDrivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections \
-fmessage-length=0 -fexceptions -fno-rtti -funsigned-char -fpermissive -fno-use-cxa-atexit -std=c++17 -Wno-narrowing

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F765VITx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys \
-lgcc -lrdimon -lstdc++

LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -specs=rdimon.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -u _printf_float \
-Wl,-lgcc,-lc,-lm,-lrdimon,--gc-sections --static

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of C++ program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#######################################
# flash
#######################################
flash:
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo w > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@sleep 0.1
	@echo u > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@sleep 0.3
	-~/git/stm32flash-code/stm32flash -b 230400 -w build/ArcticTern.hex /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO02-if00-port0
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo r > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0

#######################################
# flash and debug
#######################################
debug:
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo w > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@sleep 0.1
	@echo u > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@sleep 0.3
	~/git/stm32flash-code/stm32flash -b 230400 -w build/ArcticTern.hex -g 0x0 /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO02-if00-port0
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo r > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	gtkterm --port /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO02-if00-port0 --speed 115200&
	@sleep 1
	@echo u > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo "Press [Enter] to Power OFF"
	@read
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0

#######################################
# run
#######################################
run:
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo r > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	gtkterm --port /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO02-if00-port0 --speed 115200&
	@sleep 1
	@echo u > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0
	@echo "Press [Enter] to Power OFF"
	@read
	@echo d > /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0

#######################################
# initialize for writing
#######################################
init:
	-sudo stty -F /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0 ospeed 115200
	-sudo stty -F /dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_MEJIRO01-if00-port0 ospeed 115200

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
