#include "../inc/kernel.h"
#include "../inc/keyboard.h"
#include "../srcs/utils.c"

uint16 vga_entry(uint8 ch, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;
  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for (i = 0; i < BUFSIZE; i++)
    (*buffer)[i] = vga_entry(0, fore_color, back_color);
}


void init_vga(uint8 fore_color, uint8 back_color)
{
  uint16 *ptr;
  vga_buffer = (uint16 *)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  for (int i = 0; i < 3; i++)
  {
    ptr = screens[i].screen_str;
    clear_vga_buffer(&ptr, fore_color, back_color);
    screens[i].next_line = 1;
    screens[i].vga_index = 0;
  }
}

void switch_to_screen(int screen_num){
  if (curscreen == screen_num || screen_num > 3)
    return ;
  for (int i = 0; i < BUFSIZE; i++)
    screens[curscreen].screen_str[i] = vga_buffer[i];
  screens[curscreen].next_line = next_line_index;
  screens[curscreen].vga_index = vga_index;
  next_line_index = screens[screen_num].next_line;
  vga_index = screens[screen_num].vga_index;
  for (int i = 0; i < BUFSIZE; i++)
    vga_buffer[i] = screens[screen_num].screen_str[i];
  g_back_color = screens[screen_num].back_color;
  g_fore_color = screens[screen_num].fore_color;
}

void input()
{
  char ch;
  char keycode;
  do {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER)
      print_next_line();
    else{
      if (keycode == KEY_F1)
        switch_to_screen(0);
      else if (keycode == KEY_F2)
        switch_to_screen(1);
      else if (keycode == KEY_F2)
        switch_to_screen(2);
      else {
        ch = get_ascii_char(keycode);
        if (ch)
          print_char(ch);
      }
    }
  } while (ch > 0);
}

void kernel_entry(void)
{
  init_vga(WHITE, BLACK);
  screens[0].fore_color = WHITE;
  screens[0].back_color = BLACK;
  screens[0].fore_color = RED;
  screens[0].back_color = WHITE;
  screens[0].fore_color = BLACK;
  screens[0].back_color = WHITE;
  switch_to_screen(0);
  print_string("42");
  while (1)
    input();
}
