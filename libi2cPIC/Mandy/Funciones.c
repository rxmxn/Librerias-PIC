//----------send_RTC-----------------------
void send_RTC(int8 send)
{
   set_tris_a(0b00000011);                //poner el pin de SDA como salida
   PIN_LOW (SCL);
  
   for (int i = 0; i <8; i++)
   {
    set_tris_a(0b00000011);                  //poner el pin de SDA como salida
    output_bit(SDA,shift_left(&send, 1,0));  //enviando los 8 bits del dato
    PIN_HIGH (SCL);
    delay_ms(1);
    PIN_LOW (SCL);
    set_tris_a(0b00000111);               // poniendo el pin de SDA como entrada para que no haga colicion con el ACK  
    delay_ms(1);
   }
   
  PIN_HIGH(SCL);                          //pulso del reloj para el ACK
  delay_ms(1);
  PIN_LOW(SCL);
   
}

//--------------recive_RTC-----------------
//lo mismo de send pero para recivir los datos del RTC
int8 reciv_RTC(int8 read)    //read es el registro que se desea leer.
{
   //send_RTC(read);
   read = 0;
   set_tris_a(0b00000111);
   
    for (int i = 0; i <8; i++)
   {
    shift_left(&read,1,input_state(SDA));
    PIN_HIGH (SCL);
    delay_ms(1);
    PIN_LOW (SCL);
    delay_ms(1);
    
   }
  PIN_HIGH(SCL);
  delay_ms(1);
  PIN_LOW(SCL);
  
  return read;
   
}

//---------START---------------------
void START ()           
{
   set_tris_a(0b00000011);
   PIN_HIGH (SDA);
   delay_ms(1);
   PIN_HIGH (SCL);   //un pulso de 
   delay_ms(1);     //SDA con SCL
   PIN_LOW (SDA);    //en '1' es el START
   
}


//------------STOP--------
void STOP ()
{
   set_tris_a(0b00000011);
   PIN_LOW (SDA);
   delay_ms(1);
   PIN_HIGH(SCL);    //parada
   delay_ms(1);     //poiendo a '1' SDA   
   PIN_HIGH(SDA);    //con SCL en '0'
}

//--------write_RTC----------------

//para escribir un dato en el RTC en el reg especificado
void write_RTC (int8 reg,int8 data)
{
   //disable_interrupts(GLOBAL);
   START();
   send_RTC(0b11010000);
   send_RTC(reg);
   send_RTC(data);
   STOP();
   //enable_interrupts(GLOBAL);
}

//-------read_RTC-----------------
//para leer un dato del reg especificado en el RTC
int8 read_RTC(int8 reg)
{
   //disable_interrupts(GLOBAL);
   START();
   send_RTC(0b11010000);
   send_RTC(reg);
   STOP();
   
   /*enable_interrupts(GLOBAL);
   delay_ms(1);
   disable_interrupts(GLOBAL);*/
   
   START();
   send_RTC(0b11010001);
   reg = reciv_RTC(reg);
   STOP();
   //enable_interrupts(GLOBAL);
   return reg;
}



