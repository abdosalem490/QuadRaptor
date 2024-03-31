#include "debug.h"
#include "mpu6050.h"
#include "math.h"

int atan_test(void)
{
    float ans;
    char buffer[10];
    USART_Printf_Init(57600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();

    ans = atan(0);
    gcvt(ans, 10, buffer);

    while(1)
    {
        printf("%s\r\n", buffer);
        Delay_Ms(1000);
    }
}


int sqrt_test(void)
{
    float ans;
    char buffer[10];
    USART_Printf_Init(57600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();

    ans = sqrt(2500);
    gcvt(ans, 10, buffer);

    while(1)
    {
        printf("%s\r\n", buffer);
        Delay_Ms(1000);
    }
}