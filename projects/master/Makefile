CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
GDB = gdb-multiarch
OOCD = openocd

LIB_DIR = ../../library
PRO_DIR = .
BUILD_DIR = ./build

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
CFLAGS += -I$(LIB_DIR)
CFLAGS += -I$(PRO_DIR)

LDFLAGS += -mthumb
LDFLAGS += -T $(LIB_DIR)/stm32f407.ld
LDFLAGS += -Wl,-Map=$@.map
LDFLAGS += --specs=nosys.specs

GDBFLAGS += --eval-command="target extended-remote localhost:3333"
GDBFLAGS += --eval-command="set listsize 30"
GDBFLAGS += --eval-command="set print pretty on"
GDBFLAGS += --eval-command="set print array on"

LIB_SRCS += $(wildcard $(LIB_DIR)/*.c)
LIB_SRCS += $(wildcard $(LIB_DIR)/container/*.c)
LIB_SRCS += $(wildcard $(LIB_DIR)/hal/*.c)

PRO_SRCS += $(wildcard $(PRO_DIR)/*.c)

OBJS += $(patsubst $(LIB_DIR)/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))
OBJS += $(patsubst $(PRO_DIR)/%.c, $(BUILD_DIR)/%.o, $(PRO_SRCS))

TARGET = $(BUILD_DIR)/output

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PRO_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
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
