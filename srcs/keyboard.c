#include "../inc/kernel.h"
#include "../inc/keyboard.h"

uint8 inb(uint16 port)
{ 
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode(void)
{
  char ch = 0;
  while ((ch = inb(KEYBOARD_PORT)) != 0){
    if (ch > 0)
      return ch;
  }
  return ch;
}

void wait_for_io(uint32 timer)
{
  while(1) {
    asm volatile("nop");
    timer--;
    if (timer <= 0)
      break;
  }
}

void sleep(uint32 timer)
{
  wait_for_io(timer);
}
