#include <stdio.h>
#include <conio.h>

void convertToBinary(unsigned a);
void clearscreen();

int main()
{
  unsigned ce;
  int status;

  clearscreen();

  printf("\n\nChannel 0\n-------");

  // Читаем слово состояния канала,
  // команда 0xe2 = 11100010B
  outp(0x43, 0xe2);
  // printf("\nStatus word: %02.2X", inp(0x40));
  status = inp(0x40);
  printf("\nStatus word: %02.2X = ", status);
  convertToBinary(status);
  // Читаем текущее состояние регистра счетчика
  // канала. Для этого вначале выдаем команду CLC
  // для канала 0. Код этой команды - 0x00
  outp(0x43, 0x00);

  // Выводим младший и старший байты счетчика
  // и отображаем его.
  ce = (inp(0x40));
  ce = (inp(0x40) << 8) + ce;
  printf("\nCount register (CE): %04.4X = %u = ", ce, ce);
  convertToBinary(ce);



  // Повторяем те же действия для 1 и 2 каналов.
  printf("\n\nChannel 1\n-------");
  outp(0x43, 0xe4);
  status = inp(0x41);
  printf("\nStatus word: %02.2X = ", status);
  convertToBinary(status);

  outp(0x43, 0x40);
  ce = inp(0x41);
  ce = (inp(0x41) << 8) + ce;
  printf("\nCount register (CE): %04.4X = %u = ", ce, ce);
  convertToBinary(ce);



  printf("\n\nChannel 2\n-------");
  outp(0x43, 0xe8);
  status = inp(0x42);
  printf("\nStatus word: %02.2X = ", status);
  convertToBinary(status);

  outp(0x43, 0x80);
  ce = inp(0x42);
  ce = (inp(0x42) << 8) + ce;
  printf("\nCount register (CE): %04.4X = %u = ", ce, ce);
  convertToBinary(ce);

  return 0;

}

void convertToBinary(unsigned a)
{
  /* step 1 */
  if (a > 1)
    convertToBinary(a / 2);

  /* step 2 */
  printf("%d", a % 2);
}

void clearscreen()
{
	__asm push ax
	__asm mov ah, 0
	__asm mov al, 3
	__asm int 10h
	__asm pop ax
}