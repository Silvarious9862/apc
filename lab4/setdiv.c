#include <stdio.h>
#include <conio.h>

void setDivider(int divider, int CWR, int channel);
void resetDivider(int CWR, int channel);
void checkCE(unsigned channel, unsigned CWR);

int main()
{
    int channel;
    int newdiv;
    //do {
        printf("\nChoose channel: ");
        scanf("%d", channel);
        fflush(stdin);
    //} while (channel != 0 && channel != 1 && channel != 2);
    printf("\nSet new divider: ");
    scanf("%d", newdiv);
    switch (channel)
    {
    case 0:
        setDivider(newdiv, 0x36, 0x40);
        checkCE(0x40, 0x00);
        resetDivider(0x36, 0x40);
        break;
    case 1:
        setDivider(newdiv, 0x76, 0x41);
        checkCE(0x41, 0x40);
        resetDivider(0x76, 0x41);
        break;
    case 2:
        setDivider(newdiv, 0xB6, 0x42);
        checkCE(0x42, 0x80);
        resetDivider(0xB6, 0x42);
        break;
    default:
        break;
    }

    return 0;
}

void setDivider(int divider, int CWR, int channel)
{
    outp(0x43, CWR);
    outp(channel, (divider & 0x00ff));
    outp(channel, (divider & 0xff00) >> 8);
}

void resetDivider(int CWR, int channel)
{
    outp(0x43, CWR);
    outp(channel, (0xFFFF & 0x00ff));
    outp(channel, (0xFFFF & 0xff00) >> 8);
}

void convertToBinary(unsigned a)
{
    /* step 1 */
    if (a > 1)
        convertToBinary(a / 2);

    /* step 2 */
    printf("%d", a % 2);
}

void checkCE(unsigned channel, unsigned CWR)
{
    unsigned ce;
    outp(0x43, CWR);
    ce = (inp(channel));
    ce = (inp(channel) << 8) + ce;
    printf("\nCount register (CE): %04.4X = %u = ", ce, ce);
    convertToBinary(ce);
}