#include <Funciones.c>

void send_RTC(int8 send);     //funcion para enviar datos al RTC

int8 reciv_RTC(int8 read);     //para leer datos del RTC

void START ();                //para dar los pulsos de START en el RTC

void STOP ();                 //para dar los pulsos de STOP en el RTC

void write_RTC (int8 reg,int8 data); //escribir un dato en el registro especificado

int8 read_RTC(int8 reg);      //leer un dato del registro especificado.    
