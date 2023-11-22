#ifndef STM32F4_TERM_H
#define STM32F4_TERM_H

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#define TERM_CTRL_NUL (0)
#define TERM_CTRL_SOH (1)
#define TERM_CTRL_STX (2)
#define TERM_CTRL_ETX (3)
#define TERM_CTRL_EOT (4)
#define TERM_CTRL_ENQ (5)
#define TERM_CTRL_ACK (6)
#define TERM_CTRL_BEL (7)
#define TERM_CTRL_BS  (8)
#define TERM_CTRL_TAB (9)
#define TERM_CTRL_LF  (10)
#define TERM_CTRL_VT  (11)
#define TERM_CTRL_FF  (12)
#define TERM_CTRL_CR  (13)
#define TERM_CTRL_SO  (14)
#define TERM_CTRL_SI  (15)
#define TERM_CTRL_DLE (16)
#define TERM_CTRL_DC1 (17)
#define TERM_CTRL_DC2 (18)
#define TERM_CTRL_DC3 (19)
#define TERM_CTRL_DC4 (20)
#define TERM_CTRL_NAK (21)
#define TERM_CTRL_SYN (22)
#define TERM_CTRL_ETB (23)
#define TERM_CTRL_CAN (24)
#define TERM_CTRL_EM  (25)
#define TERM_CTRL_SUB (26)
#define TERM_CTRL_ESC (27)
#define TERM_CTRL_FS  (28)
#define TERM_CTRL_GS  (29)
#define TERM_CTRL_RS  (30)
#define TERM_CTRL_US  (31)

#define TERM_CHAR_QUEUE_SIZE  (32)
#define TERM_LINE_BUFFER_SIZE (32)
#define TERM_ARG_BUFFER_SIZE  (32)

#define TERM_ESC "\033"
#define TERM_CSI "["

#define TERM_MOVE_CURSOR_LEFT  TERM_ESC TERM_CSI "D"
#define TERM_MOVE_CURSOR_RIGHT TERM_ESC TERM_CSI "C"
#define TERM_MOVE_CURSOR_UP    TERM_ESC TERM_CSI "A"
#define TERM_MOVE_CURSOR_DOWN  TERM_ESC TERM_CSI "B"

#define TERM_MOVE_CURSOR_LAST_ROW TERM_ESC TERM_CSI "999;1H"
#define TERM_MOVE_CURSOR_TO_PREV_SOL TERM_ESC TERM_CSI "1F"

#define TERM_STORE_CURSOR_POS   TERM_ESC TERM_CSI "s"
#define TERM_RESTORE_CURSOR_POS TERM_ESC TERM_CSI "u"

#define TERM_ERASE_FROM_CURSOR_TO_EOL TERM_ESC TERM_CSI "0K"
#define TERM_ERASE_FROM_SOL_TO_CURSOR TERM_ESC TERM_CSI "1K"
#define TERM_ERASE_LINE               TERM_ESC TERM_CSI "2K"

#define TERM_CLEAR_SCREEN TERM_ESC TERM_CSI "2J"

#define TERM_SCROLL_UP_ONE_LINE TERM_ESC TERM_CSI "1S"

#define TERM_CMD_BEGIN_TABLE cmd_t g_commands[] = {
#define TERM_CMD_TABLE_ENTRY(CMD, DELEGATE)
#define TERM_CMD_END_TABLE }; const uint32_t g_command_cnt = sizeof(g_commands) / sizeof(g_commands[0]);

typedef struct {
	uint8_t command[TERM_LINE_BUFFER_SIZE];
	void (*handler)(uint32_t argc, char** argv);
} cmd_t;

void term_init(void);
void term_update(void);

#endif
