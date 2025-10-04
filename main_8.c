#include <iom128v.h>

void delay_m(unsigned int m);

// FND에 표시할 0~9 숫자 데이터 (커먼 애노드 방식 기준)
unsigned char number[10] = {0x04, 0x2F, 0x18, 0x09, 0x23, 0x41, 0x40, 0x07, 0x00, 0x01};

int main(void)
{
    char count = 0;
    // [수정된 부분] 초기 상태를 '실행'으로 변경
    char is_running = 1; // 0: 정지, 1: 실행

    // --- 1. 포트 방향 설정 ---
    DDRE = 0xCF; // PE4(입력)으로 설정 (0b11001111)
    DDRD = 0xFF; // D포트 전체를 출력으로 설정

    // --- 2. 무한 반복 실행 ---
    while(1)
    {
        // --- 3. 버튼 입력 처리 (토글 기능) ---
        // '정지/재개' 버튼(PE4)이 눌렸는지 확인 (풀다운 회로이므로 눌렀을 때 HIGH)
        if ((PINE & 0x10) == 0x10)
        {
            // 채터링 방지를 위한 짧은 딜레이 (Debouncing)
            delay_m(50);

            // is_running 상태를 반전시킴 (0 -> 1, 1 -> 0)
            is_running = !is_running;

            // 버튼에서 손을 뗄 때까지 대기 (중복 입력 방지)
            while ((PINE & 0x10) == 0x10);
        }

        // --- 4. 카운팅 및 FND 출력 ---
        if (is_running == 1) // is_running 상태가 1일 때만 카운트 증가
        {
            // FND에 숫자를 먼저 표시
            PORTD = number[count];
            delay_m(500); // 0.5초 대기

            count++;
            if (count == 10)
            {
                count = 0;
            }
        }
        else // 정지 상태일 때는 현재 숫자를 계속 표시
        {
            PORTD = number[count];
        }
    }
    return 0;
}

// 딜레이 함수
void delay_m(unsigned int m)
{
    unsigned int i, j;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < 2100; j++);
    }
}
