#include "drivers/register/stc8g.h"
#include "drivers/uart/uart.h"
#include <utils/delay/soft_delay.h>
volatile uint8_t key_pressed = 0;
    
static void ports_init(void)
{
    P3M0 = 0x00;
    P3M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;

    // 设置P3.2 为 INA226的Alert 输入
    P3M0 |= 0x04;
    P3M0 |= 0x04;
}

static void interrupts_init(void)
{
    EA = 1;
}

static void key_init(void)
{
    EX1 = 1;
    IT1 = 1;
}

void key_interrupt(void) __interrupt(2)
{
    Delay10ms();
    key_pressed=1;
}

void main(void)
{
    ports_init();      // 端口配置
    interrupts_init(); // 中断开启
    uart_init();       // 初始化串口

    key_init();
    uart_send_string("hello world\n");

    while (1) 
    {
        if (key_pressed) {
            key_pressed = 0;
            uart_send_string("Button pressed\n");
        }
    }
}
