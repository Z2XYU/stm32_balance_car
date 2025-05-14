#include <drivers/i2c/i2c.h>
#include <drivers/register/stc8g.h>
#include <drivers/i2c/i2c_config.h>

/*
* 初始化i2c 
* 配置对应的引脚
*/
void i2c_init(void)
{
    P_SW2 = 0x80;
#if I2C_CHANNEL == 2
    //关闭P_SW2中的第五位，打开第四位 ，实现I2C 引脚重映射
    P_SW2 &= ~(1<<5);
    P_SW2 |=  (1<<4);
#endif

    I2CCFG = 0xe0;
    I2CMSST = 0x00;
}

/*
 * 等待 I2C 操作完成
 * 检查 I2CMSST 寄存器的 0x40 位是否置位，
 * 置位表示当前操作完成，随后清除该标志位。
 */
void i2c_wait(void)
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

/*
 * 发送 I2C 起始信号
 * 将 I2CMSCR 置为 0x01 表示启动信号
 */
void i2c_start(void)
{
    I2CMSCR=0x01;   //起始命令
    i2c_wait();
}


/*
 * 发送一个字节数据
 * 参数:
 *   data -- 要发送的数据字节
 */
void i2c_send_data(uint8_t data)
{
    I2CTXD=data;
    I2CMSCR=0x02;
    i2c_wait();
}

/*
 * 读取发送后的 ACK
 * 通过设置命令 0x03 发起 ACK 读取，然后等待完成
 */
void i2c_recv_ack(void)
{
    I2CMSCR = 0x03;
    i2c_wait();
}

/*
 * 接收一个字节数据
 * 通过设置命令 0x04 发起数据接收，等待完成后返回接收到的数据
 */
uint8_t i2c_recv_data(void)
{
    I2CMSCR = 0x04;
    i2c_wait();
    return I2CRXD;
}

/*
 * 发送 ACK（确认信号）
 * 将 I2CMSST 寄存器置 0x00，然后设置命令 0x05 发送 ACK，并等待完成
 */
 void i2c_send_ack(void)
 {
    I2CMSST=0x00;
    I2CMSCR = 0x05;
    i2c_wait();
 }

 /*
 * 发送 NAK（非确认信号）
 * 将 I2CMSST 寄存器置 0x01，然后设置命令 0x05 发送 NAK，并等待完成
 */
void i2c_send_nak(void) 
{
    I2CMSST = 0x01;  // 设置某位以表示 NAK（具体参考手册）
    I2CMSCR = 0x05;  // 同样使用命令 0x05，但状态不同，表示发送 NAK
    i2c_wait();
}

/*
 * 发送 I2C 停止信号
 * 设置命令 0x06 发起停止信号，然后等待完成
 */
void i2c_stop(void)
{
    I2CMSCR=0x06;
    i2c_wait();
}








