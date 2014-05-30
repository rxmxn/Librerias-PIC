/*
	autor: Ramon Carrasco Duboue
*/

#define buffer_size 10

//Variables para el puerto serie
char *buffer;
char bufferRx[buffer_size+1]={0,0,0,0,0,0,0,0,0,0}; //utilizada en la Rx
//Utilizada en el analisis de la trama Rx
//Cuando se adquiere una trama completa (almacenada en bufferRx),
//se guarda en bRx, para posteriormente analizarla
char bRx[buffer_size+1]={0,0,0,0,0,0,0,0,0,0};   
bool fRx=false;
char bRxSelect,bufferRxSelect;

void serial_port()
{     
    static bool fRxFirst=false;
    static int posicion=0;
    char Rx;
    int i;
    static bool flag=false;

    Rx=cdc_getc();

    if(Rx=='<')        
    {
        posicion=0;
        fRxFirst=true;
        flag=false;
    }    
    else
    {
        if(Rx==13)//ENTER (fin de trama)
        {
            fRx=true;
            if((posicion < buffer_size) && !flag)
                for(i=posicion;i<buffer_size;i++)  
                    bufferRx[i]='\0';
        }    
        else
        {
            if(fRxFirst) {bufferRxSelect=Rx; fRxFirst=false;}
            else 
            {
                bufferRx[posicion++]=Rx;
                
                if(posicion==buffer_size)
                {
                    posicion=0;
                    flag=true;
                }    
            }
        }    
    }
}

void guardar_bufferRx()
{
    int i;
    
    bRxSelect=bufferRxSelect;
    
    for(i=0;i<buffer_size;i++)
        bRx[i]=bufferRx[i];
}

char getOption()
{
  return bRxSelect;
}

signed long int getNumber()
{   
  return strtol(bRx,&buffer,10);  //10 es la base  
}

bool buffer_complete()
{
  return fRx;
}

void restart_buffer()
{
  fRx=false;
}
