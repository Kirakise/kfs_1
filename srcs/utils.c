#include "../inc/kernel.h"
#include "../inc/keyboard.h"
#include "../inc/utils.h"

void print_next_line()
{
  if (next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

void print_char(char ch)
{
  vga_buffer[vga_index++] = vga_entry(ch, g_fore_color, g_back_color);
}

uint32 strlen(const char *str)
{
  if (!str)
    return 0;
  uint32 len = 0;
  while (str[len])
    len++;
  return len;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if (!num)
    return 1;
  while (num > 0)
  {
    count++;
    num /= 10;
  }
  return count;
}


void itoa(int num, char *number)
{
  int digits = digit_count(num);
  int index = digits - 1;
  char x;
  if (num == 0 && digits == 1) {
    number[0] = '0';
    number[1] = 0;
  } else {
    while (num != 0){
      number[index--] = num%10 + '0';
      num = num / 10;
    }
    number[digits] = 0;
  }
  return;
}

void print_string(char *str)
{
  if (!str)
    return ;
  uint32 index = 0;
  while (str[index])
    print_char(str[index++]);
}

void print_int(int num)
{
  char str_num[digit_count(num) + 1];
  itoa(num, str_num);
  print_string(str_num);
}
