#pragma once
#include "kernel.h"
#include "keyboard.h"

void print_next_line();
void print_char(char ch);
uint32 strlen(const char *str);
uint32 digit_count(int num);
void itoa(int num, char *number);
void print_string(char *str);
void print_int(int num);

static uint32 vga_index = 0;
static uint32 next_line_index = 1;
static uint8 g_fore_color = WHITE, g_back_color = BLACK;
static int digit_ascii[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
char get_ascii_char(uint16 keycode);
