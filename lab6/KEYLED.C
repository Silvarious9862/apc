#include <stdio.h>
#include <conio.h>

int main(void)
{
    int i;

    printf("KBDLED, (c) A. Frolov, 1997\n");

    printf("0. %d\n", inp(0x60));
    // Посылаем процессору клавиатуры
    // команду управления светодиодами
    outp(0x60, 0xed);
    printf("1. %d\n", inp(0x60));
    // Перед посылкой второго байта команды
    // выполняем небольшую задержку
    for (i = 0; i < 4000; i++)
        ;

    // Выводим второй байт команды, младшие три бита
    // которого определяют состояние светодиодов
    // на лицевой панели клавиатуры
    outp(0x60, 7);
    printf("2. %d\n", inp(0x60));
    delay(1000);

    //outp(0x60, 0xed);
    printf("1. %d\n", inp(0x60));
    for (i = 0; i < 4000; i++)
        ;
    outp(0x60, 3);
    printf("2. %d\n", inp(0x60));
    delay(1000);
    
    outp(0x60, 1);
    delay(1000);
    outp(0x60, 1);
    delay(10000);
    outp(0x60, 2);
    delay(1000);
    outp(0x60, 4);
    delay(1000);
    outp(0x60, 7);
    delay(1000);
    outp(0x60, 0);
    delay(1000);
    outp(0x60, 7);
    delay(1000);
    outp(0x60, 0);
    delay(1000);
    outp(0x60, 7);
    

    printf("Press any key to disable LEDs...\n");

    // Задерживаем выполнение программы, пока
    // пользователь не нажмет на любую клавишу
    getch();

    // Выключаем все светодиоды
    outp(0x60, 0xed);
    for (i = 0; i < 4000; i++)
        ;
    outp(0x60, 0);

    return 0;
}