#ifndef STM32F4_TERM_H
#define STM32F4_TERM_H

#include <stdint.h>

#define TERM_CHAR_BS    (8)
#define TERM_CHAR_CR    (13)
#define TERM_CHAR_SPACE (32)
#define TERM_CHAR_DEL   (127)

#define TERM_CMD_BUFFER_SIZE (32)
#define TERM_ARG_BUFFER_SIZE (32)

#define TERM_ESC "\033"
#define TERM_CSI TERM_ESC "["

#define TERM_CSI_CUB(N) TERM_CSI #N "D"
#define TERM_CSI_CUF(N) TERM_CSI #N "C"
#define TERM_CSI_CCU(N) TERM_CSI #N "A"
#define TERM_CSI_CUD(N) TERM_CSI #N "B"

#define TERM_CSI_INS TERM_CSI "2~"
#define TERM_CSI_DEL TERM_CSI "3~"
#define TERM_CSI_END TERM_CSI "4~"
#define TERM_CSI_PGUP TERM_CSI "5~"
#define TERM_CSI_PGDN TERM_CSI "6~"
#define TERM_CSI_HOME TERM_CSI "7~"

#define TERM_CMD_BEGIN_TABLE cmd_t g_commands[] = {
#define TERM_CMD_TABLE_ENTRY(CMD, DELEGATE)
#define TERM_CMD_END_TABLE }; const uint32_t g_command_cnt = sizeof(g_commands) / sizeof(g_commands[0]);

typedef struct {
	uint8_t command[TERM_CMD_BUFFER_SIZE];
	void (*delegate)(uint32_t argc, char** argv);
} cmd_t;

void term_init(void);

#endif
