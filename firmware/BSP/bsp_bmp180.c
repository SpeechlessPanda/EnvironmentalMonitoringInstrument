/*
 * 立创开发板硬件资料下载：https://www.lckfb.com
 * 技术支持论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 我不赚钱，中国籍工程师为中国技术做贡献
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-02     LCKFB-LP    first version
 */

#include "bsp_bmp180.h"
#include "stdio.h"
#include "math.h"

typedef struct _BMP180_STRUCT{
    short AC1;
    short AC2;
    short AC3;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6;
    short B1;
    short B2;
    short MB;
    short MC;
    short MD;  
}_BMP180_PARAM_;

_BMP180_PARAM_ param={0};

long B5 = 0;



/******************************************************************
 * �� �� �� �ƣ�IIC_Start
 * �� �� ˵ ����IIC��ʼʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Start(void)
{
        SDA_OUT();
        
        SDA(1);
        delay_us(5);
        SCL(1); 
        delay_us(5);
        
        SDA(0);
        delay_us(5);
        SCL(0);
        delay_us(5);
                       
}
/******************************************************************
 * �� �� �� �ƣ�IIC_Stop
 * �� �� ˵ ����IICֹͣ�ź�
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Stop(void)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        
        SCL(1);
        delay_us(5);
        SDA(1);
        delay_us(5);
        
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Send_Ack
 * �� �� ˵ ������������Ӧ����߷�Ӧ���ź�
 * �� �� �� �Σ�0����Ӧ��  1���ͷ�Ӧ��
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Send_Ack(unsigned char ack)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        delay_us(5);
        if(!ack) SDA(0);
        else         SDA(1);
        SCL(1);
        delay_us(5);
        SCL(0);
        SDA(1);
}


/******************************************************************
 * �� �� �� �ƣ�I2C_WaitAck
 * �� �� ˵ �����ȴ��ӻ�Ӧ��
 * �� �� �� �Σ���
 * �� �� �� �أ�0��Ӧ��  1��ʱ��Ӧ��
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
unsigned char I2C_WaitAck(void)
{
        
        char ack = 0;
        unsigned char ack_flag = 10;
        SCL(0);
        SDA(1);
        SDA_IN();
        delay_us(5);
        SCL(1);
    delay_us(5);

        while( (SDA_GET()==1) && ( ack_flag ) )
        {
                        ack_flag--;
                        delay_us(5);
        }
        
        if( ack_flag <= 0 )
        {
                        IIC_Stop();
                        return 1;
        }
        else
        {
                        SCL(0);
                        SDA_OUT();
        }
        return ack;
}

/******************************************************************
 * �� �� �� �ƣ�Send_Byte
 * �� �� ˵ ����д��һ���ֽ�
 * �� �� �� �Σ�datҪд�˵�����
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void Send_Byte(uint8_t dat)
{
        int i = 0;
        SDA_OUT();
        SCL(0);//����ʱ�ӿ�ʼ���ݴ���
        
        for( i = 0; i < 8; i++ )
        {
                SDA( (dat & 0x80) >> 7 );
                delay_us(1);
                SCL(1);
                delay_us(5);
                SCL(0);
                delay_us(5);
                dat<<=1;
        }        
}

/******************************************************************
 * �� �� �� �ƣ�Read_Byte
 * �� �� ˵ ����IIC��ʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ�����������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
unsigned char Read_Byte(void)
{
        unsigned char i,receive=0;
        SDA_IN();//SDA����Ϊ����
        for(i=0;i<8;i++ )
        {
                SCL(0);
                delay_us(5);
                SCL(1);
                delay_us(5);
                receive<<=1;
                if( SDA_GET() )
                {        
                        receive|=1;   
                }
                delay_us(5); 
        }                                         
        SCL(0); 
        return receive;
}


/******************************************************************
 * �� �� �� �ƣ�BMP180_Write_Cmd
 * �� �� ˵ ������BMP180д��һ���ֽ�����
 * �� �� �� �Σ�regaddr�Ĵ�����ַ  cmdд�������
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��regaddr=0xf4, cmd=0X2E
******************************************************************/
void BMP180_Write_Cmd(uint8_t regaddr,uint8_t cmd)
{
        IIC_Start();//��ʼ�ź�
        Send_Byte(0XEE);//������ַ+д
        if( I2C_WaitAck() == 1 ) printf("Write_Cmd NACK -1\r\n");
        
        Send_Byte(regaddr);
        if( I2C_WaitAck() == 1 ) printf("Write_Cmd NACK -2\r\n");
        
        Send_Byte(cmd);
        if( I2C_WaitAck() == 1 ) printf("Write_Cmd NACK -3\r\n");
        
        IIC_Stop();
}

/******************************************************************
 * �� �� �� �ƣ�BMP180_Read16
 * �� �� ˵ ������ȡBMP180����
 * �� �� �� �Σ�regaddr��ȡ�ĵ�ַ len��ȡ�ĳ���
 * �� �� �� �أ���ȡ��������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
//uint16_t BMP180_Read16(uint16_t regaddr,uint8_t len)
//{
//    int timeout = 0;
//    uint16_t dat[3] = {0};
//    int i =0;
//    for( i = 0; i < len; i++ )
//    {
//        IIC_Start();//��ʼ�ź�
//        Send_Byte(0XEE);//������ַ+д
//        if( I2C_WaitAck() == 1 ) printf("Read_Reg NACK -1\r\n");
//        Send_Byte(regaddr+i);
//        if( I2C_WaitAck() == 1 ) printf("Read_Reg NACK -2\r\n");
//        
//        do{
//            timeout++;
//            delay_ms(1);
//            IIC_Start();//��ʼ�ź�
//            Send_Byte(0XEF);//������ַ+��    
//        }while(I2C_WaitAck() == 1 && (timeout < 5) );
//        
//        dat[i] = Read_Byte();
//        IIC_Send_Ack(1);    
//        IIC_Stop();
//        delay_ms(1);
//    }
//    if( len == 2 ) return ( (dat[0]<<8) | dat[1] );
//    if( len == 3 ) return (( (dat[0]<<16) | (dat[1]<<8) | (dat[2]) ) >> 8);
//    return 0;
//}
//�޸ĵ�1������ֵ��Ϊ uint32_t���Ա����� len=3 ʱ����ѹֵ
uint32_t BMP180_Read16(uint16_t regaddr,uint8_t len)
{
    int timeout = 0;
    uint16_t dat[3] = {0};
    int i =0;
    for( i = 0; i < len; i++ )
    {
        IIC_Start();//��ʼ�ź�
        Send_Byte(0XEE);//������ַ+д
        if( I2C_WaitAck() == 1 ) printf("Read_Reg NACK -1\r\n");
        Send_Byte(regaddr+i);
        if( I2C_WaitAck() == 1 ) printf("Read_Reg NACK -2\r\n");
        
        do{
            timeout++;
            delay_ms(1);
            IIC_Start();//��ʼ�ź�
            Send_Byte(0XEF);//������ַ+��   
        }while(I2C_WaitAck() == 1 && (timeout < 5) );
        
        dat[i] = Read_Byte();
        IIC_Send_Ack(1);    
        IIC_Stop();
        delay_ms(1);
    }
    if( len == 2 ) return ( (dat[0]<<8) | dat[1] );
    // �޸ĵ�2������ (uint32_t) ǿת����ֹ����16λʱ�为��
    if( len == 3 ) return (( ((uint32_t)dat[0]<<16) | ((uint32_t)dat[1]<<8) | (dat[2]) ) >> 8);
    return 0;
}


/******************************************************************
 * �� �� �� �ƣ�BMP180_Get_Temperature
 * �� �� ˵ ������ȡ�¶ȵ�λ��
 * �� �� �� �Σ���
 * �� �� �� �أ��¶�
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
//float BMP180_Get_Temperature(void)
//{                       
//        long UT = 0;
//        long X1 = 0, X2 = 0;

//        BMP180_Write_Cmd(0XF4, 0X2E);
//        delay_ms(6);
//        UT = BMP180_Read16(0xf6,2);

//        X1 = ((long)UT - param.AC6) * param.AC5 / 32768.0;
//        X2 = ((long)param.MC * 2048.0) / ( X1 + param.MD );
//        B5 = X1 + X2;
//        return ((B5+8)/16.0)*0.1f;
//}
float BMP180_Get_Temperature(void)
{                       
    long UT = 0;
    long X1 = 0, X2 = 0;

    BMP180_Write_Cmd(0XF4, 0X2E);
    delay_ms(6);
    UT = BMP180_Read16(0xf6,2);

    // �޸ĵ㣺ȥ�� .0 ʹ�ô��������㣬���⸡�������ȽضϺʹ�λ
    X1 = (((long)UT - param.AC6) * param.AC5) / 32768;
    X2 = ((long)param.MC * 2048) / ( X1 + param.MD );
    B5 = X1 + X2;
    
    // B5�������(B5+8)/16 ���� 0.1�� Ϊ��λ���¶�ֵ���ٳ� 0.1f ������������
    return ((B5+8)/16) * 0.1f;
}


/******************************************************************
 * �� �� �� �ƣ�BMP180_Get_Pressure
 * �� �� ˵ ������ȡ��ѹ,��λPa
 * �� �� �� �Σ���
 * �� �� �� �أ���ǰ��ѹ����λPa
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
float BMP180_Get_Pressure(void)
{                       
        long UP = 0;
    uint8_t oss = 0; 
    long X1 = 0, X2 = 0;
    
    BMP180_Get_Temperature();
    
        BMP180_Write_Cmd(0XF4, (0X34+(oss<<6)));
        delay_ms(10);
        UP = BMP180_Read16(0xf6,3);
 

    int32_t B6 = B5 - 4000;
    
    X1 = (B6 * B6 >> 12) * param.B2 >> 11;
    
    X2 = param.AC2 * B6 >> 11;
    
    int32_t X3 = X1 + X2;
    
    int32_t B3 = (((param.AC1 << 2) + X3) + 2) >> 2;

    X1 = param.AC3 * B6 >> 13;
    
    X2 = (B6 * B6 >> 12) * param.B1 >> 16;
    
    X3 = (X1 + X2 + 2) >> 2; 
    
    uint32_t B4 = param.AC4 * (uint32_t)(X3 + 32768) >> 15;

    uint32_t B7 = ((uint32_t)UP - B3) * 50000;
    
    int32_t p;
    if(B7 < 0x80000000)
    {
        p = (B7 << 1) / B4;  
    }
    else
    {
        p = B7/B4 << 1;
    }
    
    X1 = (p >> 8) * (p >> 8);
    
    X1 = (X1 * 3038) >> 16;
    
    X2 = (-7375 * p) >> 16;
    
    p = p + ((X1 + X2 + 3791) >> 4);
     return p;

}

/******************************************************************
 * �� �� �� �ƣ�BMP180_Get_Altitude
 * �� �� ˵ �������㺣�θ߶�
 * �� �� �� �Σ�p=��ǰ��ѹ
 * �� �� �� �أ����θ߶�
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
float BMP180_Get_Altitude(float p)
{  
//#define PRESSURE_OF_SEA        101325.0f // �ο���ƽ��ѹǿ   
    float altitude = 0;
    altitude = 44330*(1 - pow((p)/ 101325.0f, 1.0f / 5.255f));
//    printf("altitude = %.2f\r\n",altitude);
    return altitude;
}


/******************************************************************
 * �� �� �� �ƣ�BMP180_Get_param
 * �� �� ˵ ������ȡ����У׼ֵ
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void BMP180_Get_param(void)
{
    param.AC1 =  BMP180_Read16(0xaa,2);
    param.AC2 =  BMP180_Read16(0xac,2);
    param.AC3 =  BMP180_Read16(0xae,2);
    param.AC4 =  BMP180_Read16(0xb0,2);
    param.AC5 =  BMP180_Read16(0xb2,2);
    param.AC6 =  BMP180_Read16(0xb4,2);
    param.B1  =  BMP180_Read16(0xb6,2);
    param.B2  =  BMP180_Read16(0xb8,2);
    param.MB  =  BMP180_Read16(0xba,2);
    param.MC  =  BMP180_Read16(0xbc,2);
    param.MD  =  BMP180_Read16(0xbe,2);
}

void BMP180_Disable(void)
{
    // ���� SDA ���ţ���DHT11���õ����ţ�
    DL_GPIO_disableOutput(GPIO_PORT, GPIO_SDA_PIN);
    DL_GPIO_initDigitalInput(GPIO_SDA_IOMUX);

    // ���� SCL ����
    DL_GPIO_disableOutput(GPIO_PORT, GPIO_SCL_PIN);
    DL_GPIO_initDigitalInput(GPIO_SCL_PIN);
}
void BMP180_Init(void)
{
    // ֻ����SDA��������������ֻ��SDA_OUT�꣬��SCL_OUT��
    SDA_OUT();
    
    // I2C����Ĭ������
    SDA(1);
    SCL(1);
    
    // �ȴ��������ȶ�
    delay_ms(10);
}
