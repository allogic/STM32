CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OOCD = openocd

CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -Wextra -std=c99
LDFLAGS = -T linker_script.ld

OOCD_CFG = board/stm32f4discovery.cfg

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = $(BUILD_DIR)/output.elf

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) linker_script.ld
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

all: $(TARGET)

load: $(TARGET)
	$(OOCD) -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg  -c "program $(TARGET) verify reset exit"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all load clean
