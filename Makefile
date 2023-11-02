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

OUTPUT_BIN = $(BUILD_DIR)/output.bin

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_BIN): $(OBJS) linker_script.ld
	$(LD) $(LDFLAGS) -o $(OUTPUT_BIN) $(OBJS)
	$(OBJCOPY) -O binary $(OUTPUT_BIN) $(OUTPUT_BIN)

all: $(OUTPUT_BIN)

load: $(OUTPUT_BIN)
	$(OOCD) -f /ucrt64/share/openocd/scripts/board/stm32f4discovery.cfg  -c "program $(OUTPUT_BIN) verify reset exit"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all load clean