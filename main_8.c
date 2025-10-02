#include <iom128v.h>

void delay_m(unsigned int m);

// FND�� ǥ���� ���� ������ (Common Anode Ÿ�� ����)
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
unsigned char number[10] = {0x04, 0x2F, 0x18, 0x09, 0x23, 0x41, 0x40, 0x07, 0x00, 0x01};

int main(void)
{
    char count = 0;
    char is_running = 0; // �ʱ� ���´� '����'

    // --- 1. ��Ʈ �ʱ� ���� ---
    //PORTE = 0x00; // E��Ʈ ���� Ǯ�� ���� ��Ȱ��ȭ

    // Timer/Counter 3 ��� ��Ȱ��ȭ (PE4, PE5�� I/O ��Ʈ�� ���)
    //TCCR3A = 0x00;
    //TCCR3B = 0x00;

    // --- 2. ��Ʈ ���� ���� ---
    DDRE = 0xCF; // PE4(�Է�), PE5(�Է�)�� ���� (0b11001111)
    DDRD = 0xFF; // D��Ʈ ��ü�� ������� ����

    // --- 3. ���� �ݺ� ���� ---
    while(1)
    {
        // '����' ��ư(PE4)�� ���ȴ��� Ȯ��
        if ((PINE & 0x10) == 0x10) // PINE�� 4��° ��Ʈ�� 1�̸�
        {
            is_running = 0; // ī���� ����
        }
        // '����/�簳' ��ư(PE4)�� ���ȴ��� Ȯ��
        else if ((PINE & 0x10) == 0x10) // PINE�� 4��° ��Ʈ�� 1�̸�
        {
            is_running = 1; // ī���� ����/�簳
        }

        // 'is_running' ���°� 1�� ���� ī��Ʈ ���� �� ������ ����
        if (is_running == 1)
        {
            count++;
            if (count == 10)
            {
                count = 0;
            }
            delay_m(500); // �� 0.5�� ������
        }

        // ���� count ���� FND�� �׻� ǥ��
        PORTD = number[count];
    }
    return 0;
}

// ������ �Լ�
void delay_m(unsigned int m)
{
    unsigned int i, j;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < 2100; j++)
        {
            ; // �ƹ� ���۵� ���� ���� (�ð� ���� ����)
        }
    }
}
