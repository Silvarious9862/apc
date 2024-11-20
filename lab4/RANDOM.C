#include <stdio.h>
#include <conio.h>
#include <dos.h>

void clearscreen();
void rnd_set(int bound);
int rnd_get(void);

int main(void)
{
	int bound = 0, number = 0;
	clearscreen();

	printf("\nRNG."
		   "\nPut any number,"
		   "\nTo end, put 0"
		   "\n");

	while (1)
	{
		scanf("%d", &bound);
		if(bound > 255 || bound < 1) break;
		rnd_set(bound);

		printf("Number from 0 to %d. Press any key. ", bound);
		fflush(stdin);
		getch();

		number = rnd_get();

		printf("Number = %d\n", number);
		fflush(stdin);
	}
	return 0;
}

void clearscreen()
{
	__asm push ax
	__asm mov ah, 0
	__asm mov al, 3
	__asm int 10h
	__asm pop ax
}

void rnd_set(int bound)
{
	// Устанавливаем режим 3 для второго канала таймера
	outp(0x43, 0xb6);

	// Загружаем регистр счетчика таймера - сначала
	// младший, затем старший байты
	outp(0x42, (bound & 0x00ff));
	outp(0x42, (bound & 0xff00) >> 8);

	// Разрешаем работу канала
	outp(0x61, inp(0x61) | 1);
}

int rnd_get(void)
{
	int i = 0;

	// Выдаем команду CLC для фиксирования
	// текущего значения регистра канала 2 таймера
	outp(0x43, 0x86);

	// Вводим младший и старший байты счетчика
	i = inp(0x42);
	i = (inp(0x42) << 8) + i;

	return i;
}