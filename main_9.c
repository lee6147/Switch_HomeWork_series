#include <iom128v.h>

void delay_m(unsigned int m);

unsigned char number[10] = {0x04, 0x2F, 0x18, 0x09, 0x23, 0x41, 0x40, 0x07, 0x00, 0x01};

int main(void)
{
    char count = 0;
    char mode = 0;

    PORTE = 0x00;

    DDRE = 0xCF;
    DDRD = 0xFF;

    while(1)
    {
        if ((PINE & 0x10) == 0x10)
        {
            mode = 1;
        }
        else if ((PINE & 0x20) == 0x20)
        {
            mode = 2;
        }

        if (mode == 1)
        {
            count++;
            if (count > 9)
            {
                count = 0;
            }
        }

        else if (mode == 2)
        {
            // ���ڸ� ���̱� ���� ���� 0���� Ȯ���մϴ�.
            if (count == 0)
            {
                count = 9; // 0�̾��ٸ� 9�� ����
            }
            else
            {
                count--; // 0�� �ƴϾ��ٸ� 1 ����
            }
        }

        PORTD = number[count];

        if (mode != 0)
        {
            delay_m(500);
        }
    }
    return 0;
}

void delay_m(unsigned int m)
{
    unsigned int i, j;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < 2100; j++)
        {
            ;
        }
    }
}
