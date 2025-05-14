#include <drivers/register/stc8g.h>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

static void ports_init(void)
{
    P3M0 = 0x00;
    P3M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;

    //����P3.2 Ϊ INA226��Alert ����
    P3M0 |= 0x04;
    P3M0 |= 0x04;
}

static void interrupts_init(void)
{
    EA=1;
}

//115200bps @24.000MHz
void uart_init(void)
{

}

void main()
{
    ports_init();   //�˿�����
    interrupts_init();  //�жϿ���


    while (1)
    {
        
    }
    
}


