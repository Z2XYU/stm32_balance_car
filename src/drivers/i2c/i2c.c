#include <drivers/i2c/i2c.h>
#include <drivers/register/stc8g.h>
#include <drivers/i2c/i2c_config.h>

/*
* ��ʼ��i2c 
* ���ö�Ӧ������
*/
void i2c_init(void)
{
    P_SW2 = 0x80;
#if I2C_CHANNEL == 2
    //�ر�P_SW2�еĵ���λ���򿪵���λ ��ʵ��I2C ������ӳ��
    P_SW2 &= ~(1<<5);
    P_SW2 |=  (1<<4);
#endif

    I2CCFG = 0xe0;
    I2CMSST = 0x00;
}

/*
 * �ȴ� I2C �������
 * ��� I2CMSST �Ĵ����� 0x40 λ�Ƿ���λ��
 * ��λ��ʾ��ǰ������ɣ��������ñ�־λ��
 */
void i2c_wait(void)
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

/*
 * ���� I2C ��ʼ�ź�
 * �� I2CMSCR ��Ϊ 0x01 ��ʾ�����ź�
 */
void i2c_start(void)
{
    I2CMSCR=0x01;   //��ʼ����
    i2c_wait();
}


/*
 * ����һ���ֽ�����
 * ����:
 *   data -- Ҫ���͵������ֽ�
 */
void i2c_send_data(uint8_t data)
{
    I2CTXD=data;
    I2CMSCR=0x02;
    i2c_wait();
}

/*
 * ��ȡ���ͺ�� ACK
 * ͨ���������� 0x03 ���� ACK ��ȡ��Ȼ��ȴ����
 */
void i2c_recv_ack(void)
{
    I2CMSCR = 0x03;
    i2c_wait();
}

/*
 * ����һ���ֽ�����
 * ͨ���������� 0x04 �������ݽ��գ��ȴ���ɺ󷵻ؽ��յ�������
 */
uint8_t i2c_recv_data(void)
{
    I2CMSCR = 0x04;
    i2c_wait();
    return I2CRXD;
}

/*
 * ���� ACK��ȷ���źţ�
 * �� I2CMSST �Ĵ����� 0x00��Ȼ���������� 0x05 ���� ACK�����ȴ����
 */
 void i2c_send_ack(void)
 {
    I2CMSST=0x00;
    I2CMSCR = 0x05;
    i2c_wait();
 }

 /*
 * ���� NAK����ȷ���źţ�
 * �� I2CMSST �Ĵ����� 0x01��Ȼ���������� 0x05 ���� NAK�����ȴ����
 */
void i2c_send_nak(void) 
{
    I2CMSST = 0x01;  // ����ĳλ�Ա�ʾ NAK������ο��ֲᣩ
    I2CMSCR = 0x05;  // ͬ��ʹ������ 0x05����״̬��ͬ����ʾ���� NAK
    i2c_wait();
}

/*
 * ���� I2C ֹͣ�ź�
 * �������� 0x06 ����ֹͣ�źţ�Ȼ��ȴ����
 */
void i2c_stop(void)
{
    I2CMSCR=0x06;
    i2c_wait();
}








