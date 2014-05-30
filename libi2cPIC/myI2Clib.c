#define SIO_CLOCK_DELAY 100

#bit TRISC3 = 0x0F94.3
#define SIO_C_OUTPUT TRISC3=0
#define SIO_C_INPUT TRISC3=1

#bit TRISC4 = 0x0F94.4
#define SIO_D_OUTPUT TRISC4=0
#define SIO_D_INPUT TRISC4=1

#bit PORTC3 = 0x0F82.3
#define SIO_C_HIGH PORTC3=1
#define SIO_C_LOW PORTC3=0

#bit PORTC4 = 0x0F82.4
#define SIO_D_HIGH PORTC4=1
#define SIO_D_LOW PORTC4=0

void Init_i2c(void)
{
  SIO_C_OUTPUT;
  SIO_D_OUTPUT;
  SIO_C_HIGH;
  SIO_D_HIGH;
  //Serial.println("Init_i2c - PortDirectionSet & Set High OK");
}

void Start_i2c(void)
{
//  Serial.println("Start_i2c");

  SIO_D_HIGH;
  delay_us(SIO_CLOCK_DELAY);
  SIO_C_HIGH;
  delay_us(SIO_CLOCK_DELAY);
  SIO_D_LOW;
  delay_us(SIO_CLOCK_DELAY);
  SIO_C_LOW;
  delay_us(SIO_CLOCK_DELAY);
}

void Stop_i2c(void)
{
  //  Serial.println("Stop_i2c");

  SIO_D_LOW;
  delay_us(SIO_CLOCK_DELAY);
  SIO_C_HIGH;
  delay_us(SIO_CLOCK_DELAY);
  SIO_D_HIGH;
  delay_us(SIO_CLOCK_DELAY);
}

char _i2cWrite(byte m_data)
{
  unsigned char j, tem;

  for (j = 0; j < 8; j++)
  {
    if ((m_data << j) & 0x80)
    {
      SIO_D_HIGH;
    }
    else
    {
      SIO_D_LOW;
    }
    delay_us(SIO_CLOCK_DELAY);
    SIO_C_HIGH;
    delay_us(SIO_CLOCK_DELAY);
    SIO_C_LOW;
    delay_us(SIO_CLOCK_DELAY);
  }

  SIO_D_INPUT;
  
  delay_us(SIO_CLOCK_DELAY);

  SIO_C_HIGH;
  delay_us(SIO_CLOCK_DELAY);

  if (PORTC4 == HIGH)
  {
    tem = 0;
    Serial.println("_i2cWrite NG");
  }
  else
  {
    tem = 1;
  }
  SIO_C_LOW;
  delay_us(SIO_CLOCK_DELAY);
  SIO_D_OUTPUT;

  return tem;
}

char _i2cRead(void)
{
  unsigned char _read, j;
  _read = 0x00;

  SIO_D_INPUT;
  
  delay_us(SIO_CLOCK_DELAY);

  for (j = 8; j > 0; j--)
  {
    delay_us(SIO_CLOCK_DELAY);
    SIO_C_HIGH;
    delay_us(SIO_CLOCK_DELAY);
    
    _read = _read << 1;
    if (PORTC4 == HIGH)
    {
      _read = _read + 1;
    }
    
    SIO_C_LOW;
    delay_us(SIO_CLOCK_DELAY);
  }

  SIO_D_OUTPUT;
  
  return (_read);
}

int InitDEVICE(void)
{
  byte x=1;
  
  Init_i2c();   
  
 // x&=WriteDEVICE(0x11, 0x27);  

  return x;
}

int WriteDEVICE(char regID, char regDat)
{
  Start_i2c();
  if (_i2cWrite(0x3C) == 0)  //direccion para WRITE
  {
//    Serial.println(" Write Error 0x42");
    Stop_i2c();
    return (0);
  }
  delay_us(SIO_CLOCK_DELAY);
  if (_i2cWrite(regID) == 0)
  {
 //   Serial.println(" Write Error regID");
    Stop_i2c();
    return (0);
  }
  delay_us(SIO_CLOCK_DELAY);
  if (_i2cWrite(regDat) == 0)
  {
//    Serial.println(" Write Error regDat");
    Stop_i2c();
    return (0);
  }
  Stop_i2c();

  return (1);
}

unsigned char ReadDEVICE(unsigned char regID, unsigned char *regDat)
{
  Start_i2c();

  if (0 == _i2cWrite(0x3C))	//direccion para WRITE
  {
 //   Serial.println(" Write Error 0x42");
    Stop_i2c();
    return (0);
  }
  delay_us(SIO_CLOCK_DELAY);
  if (0 == _i2cWrite(regID))
  {
 //   Serial.println(" Error in regID");
    Stop_i2c();
    return (0);
  }
  Stop_i2c();

  delay_us(SIO_CLOCK_DELAY);

  Start_i2c();
  if (0 == _i2cWrite(0x3D))  //direccion para READ
  {
//    Serial.println(" Read Error 0x43");
    Stop_i2c();
    return (0);
  }
  delay_us(SIO_CLOCK_DELAY);
  *regDat = _i2cRead();
  noAck();
  Stop_i2c();

  return (1);
}

void noAck(void)
{
  SIO_D_HIGH;
  delay_us(SIO_CLOCK_DELAY);

  SIO_C_HIGH;
  delay_us(SIO_CLOCK_DELAY);

  SIO_C_LOW;
  delay_us(SIO_CLOCK_DELAY);

  SIO_D_LOW;
  delay_us(SIO_CLOCK_DELAY);
}