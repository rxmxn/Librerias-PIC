//incluyes la biblioteca
#include "serialLib.c"

void TxUsb()
{
	//...
}

void analizar_Rx(char Rx)
{   
  signed long int linumber=0;
  linumber = getNumber();
  
  switch(Rx)
  {  
      case 'W': 
        //... 	   	
        break;
        
      case 'R': 
        //... 	   	
        break;
  }
}

void setup()
{
	//...
	//Llamar a la funcion para activar usb por cdc
}

//El main() quedaria:
void main()
{
	//...
	while(1)
	{
		if (usb_cdc_kbhit()) 
			serial_port();
		
		if(buffer_complete())
		{    
			restart_buffer();
			guardar_bufferRx();
			analizar_Rx(getOption());    
			
			//aqui es donde el micro le escribe a la PC
			TxUsb();
		}
	}
}