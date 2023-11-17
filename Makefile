CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
GDB = gdb-multiarch
OOCD = openocd

OOCD_CFG = board/stm32f4discovery.cfg

CFLAGS += -mcpu=cortex-m4
CFLAGS += -march=armv7e-m
CFLAGS += -mthumb
CFLAGS += -c
CFLAGS += -g
CFLAGS += -O0
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wno-shift-count-overflow
CFLAGS += -Wno-tautological-compare
CFLAGS += -Isrc
CFLAGS += -DPRINTF_INCLUDE_CONFIG_H

LDFLAGS += -mthumb
LDFLAGS += -T linker_script.ld
LDFLAGS += -Wl,-Map=$@.map
LDFLAGS += --specs=nosys.specs

GDBFLAGS += --eval-command="target extended-remote localhost:3333"
GDBFLAGS += --eval-command="set listsize 30"
GDBFLAGS += --eval-command="set print pretty on"
GDBFLAGS += --eval-command="set print array on"

SRC_DIR = src
BUILD_DIR = build

SRCS += $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/hal/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = $(BUILD_DIR)/output

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) linker_script.ld
	$(LD) $(LDFLAGS) -o $(TARGET).elf $(OBJS)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

all: $(TARGET)

load:
	$(OOCD) -f $(OOCD_CFG) -c "program $(TARGET).elf verify reset exit"

clean:
	rm -rf $(BUILD_DIR)

server:
	$(OOCD) -f $(OOCD_CFG)

debug:
	$(GDB) $(GDBFLAGS) $(TARGET).elf
