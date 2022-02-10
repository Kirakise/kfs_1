#pragma once


//Хачу как в плюсах
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

extern uint16* vga_buffer;

typedef struct s_screen{
  uint16 screen_str[BUFSIZE];
  uint32 next_line;
  uint16 vga_index;
  uint8 fore_color;
  uint8 back_color;
  char inp_buf[255];
  uint8 inp_ind;
}               t_screen;

extern t_screen screens[3];
extern uint8 curscreen;

#define NULL (void*)0

uint16 vga_entry(uint8 ch, uint8 fore_color, uint8 back_color);
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color);
void init_vga(uint8 fore_color, uint8 back_color);
void wait_for_io(uint32 timer);
void sleep(uint32 timer);
