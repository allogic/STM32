#ifndef STM32F4_TERM_H
#define STM32F4_TERM_H

#include <stdbool.h>
#include <stdint.h>

#define TERM_CHAR_BS        (8)
#define TERM_CHAR_LF        (10)
#define TERM_CHAR_CR        (13)
#define TERM_CHAR_ESC       (27)
#define TERM_CHAR_SPACE     (32)
#define TERM_CHAR_0         (48)
#define TERM_CHAR_1         (49)
#define TERM_CHAR_2         (50)
#define TERM_CHAR_3         (51)
#define TERM_CHAR_4         (52)
#define TERM_CHAR_5         (53)
#define TERM_CHAR_6         (54)
#define TERM_CHAR_7         (55)
#define TERM_CHAR_8         (56)
#define TERM_CHAR_9         (57)
#define TERM_CHAR_COLON     (58)
#define TERM_CHAR_SEMICOLON (59)
#define TERM_CHAR_AU        (65)
#define TERM_CHAR_BU        (66)
#define TERM_CHAR_CU        (67)
#define TERM_CHAR_DU        (68)
#define TERM_CHAR_EU        (69)
#define TERM_CHAR_FU        (70)
#define TERM_CHAR_GU        (71)
#define TERM_CHAR_HU        (72)
#define TERM_CHAR_IU        (73)
#define TERM_CHAR_JU        (74)
#define TERM_CHAR_KU        (75)
#define TERM_CHAR_LU        (76)
#define TERM_CHAR_MU        (77)
#define TERM_CHAR_NU        (78)
#define TERM_CHAR_OU        (79)
#define TERM_CHAR_PU        (80)
#define TERM_CHAR_QU        (81)
#define TERM_CHAR_RU        (82)
#define TERM_CHAR_SU        (83)
#define TERM_CHAR_TU        (84)
#define TERM_CHAR_UU        (85)
#define TERM_CHAR_VU        (86)
#define TERM_CHAR_WU        (87)
#define TERM_CHAR_XU        (88)
#define TERM_CHAR_YU        (89)
#define TERM_CHAR_ZU        (90)
#define TERM_CHAR_LSQBR     (91)
#define TERM_CHAR_AL        (97)
#define TERM_CHAR_BL        (98)
#define TERM_CHAR_CL        (99)
#define TERM_CHAR_DL        (100)
#define TERM_CHAR_EL        (101)
#define TERM_CHAR_FL        (102)
#define TERM_CHAR_GL        (103)
#define TERM_CHAR_HL        (104)
#define TERM_CHAR_IL        (105)
#define TERM_CHAR_JL        (106)
#define TERM_CHAR_KL        (107)
#define TERM_CHAR_LL        (108)
#define TERM_CHAR_ML        (109)
#define TERM_CHAR_NL        (110)
#define TERM_CHAR_OL        (111)
#define TERM_CHAR_PL        (112)
#define TERM_CHAR_QL        (113)
#define TERM_CHAR_RL        (114)
#define TERM_CHAR_SL        (115)
#define TERM_CHAR_TL        (116)
#define TERM_CHAR_UL        (117)
#define TERM_CHAR_VL        (118)
#define TERM_CHAR_WL        (119)
#define TERM_CHAR_XL        (120)
#define TERM_CHAR_YL        (121)
#define TERM_CHAR_ZL        (122)
#define TERM_CHAR_TILDE     (126)
#define TERM_CHAR_DEL       (127)

#define TERM_LINE_BUFFER_SIZE (32)
#define TERM_ARG_BUFFER_SIZE  (32)

#define TERM_ESC "\033"
#define TERM_CSI TERM_ESC "["

#define TERM_MOVE_CURSOR_BACK    TERM_CSI "D"
#define TERM_MOVE_CURSOR_FORWARD TERM_CSI "C"
#define TERM_MOVE_CURSOR_UP      TERM_CSI "A"
#define TERM_MOVE_CURSOR_DOWN    TERM_CSI "B"

#define TERM_STORE_CURSOR_POS   TERM_CSI "s"
#define TERM_RESTORE_CURSOR_POS TERM_CSI "u"

#define TERM_ERASE_FROM_CURSOR_TO_EOL TERM_CSI "0K"
#define TERM_ERASE_FROM_SOL_TO_CURSOR TERM_CSI "1K"
#define TERM_ERASE_LINE               TERM_CSI "2K"

#define TERM_CMD_BEGIN_TABLE cmd_t g_commands[] = {
#define TERM_CMD_TABLE_ENTRY(CMD, DELEGATE)
#define TERM_CMD_END_TABLE }; const uint32_t g_command_cnt = sizeof(g_commands) / sizeof(g_commands[0]);

typedef struct {
	uint8_t command[TERM_LINE_BUFFER_SIZE];
	void (*handler)(uint32_t argc, char** argv);
} cmd_t;

void term_init(void);

#endif
