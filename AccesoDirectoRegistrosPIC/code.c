#byte TRISC = 0x0F94	//direccion del registro TRISC
#define pinOUTPUT(pin) (TRISC &= ~(1<<pin))
#define pinINPUT(pin) (TRISC |= 1<<pin)

#byte PORTC = 0x0F82	//direccion del registro PORTC
#define pinHIGH(pin) (PORTC |= 1<<pin)
#define pinLOW(pin) (PORTC &= ~(1<<pin))

#bit RC3 = 0x0F82.3
#define RC3HIGH RC3=1
#define RC3LOW RC3=0