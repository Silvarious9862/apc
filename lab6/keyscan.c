#include <stdio.h>
#include <dos.h>

int main(void)
{
    union REGS rg;

    printf("KBDSCAN, (c) A. Frolov, 1997\n"
           "Press <ESC> to exit\n");

    for (;;)
    {
        // Вызываем прерывание INT 16h
        rg.h.ah = 0;
        int86(0x16, &rg, &rg);

        // Выводим на экран содержимое регистров AH и AL,
        // содержащих, соответственно, скан-код и код ASCII
        // нажатой клавиши
        printf("\nScan = %02.2X Ascii = %02.2X",
               rg.h.ah, rg.h.al);

        // Если была нажата клавиша ESC, завершаем работу
        // программы
        if (rg.h.ah == 1)
            break;
    }
    return 0;
}