#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/video.h"
#include "../include/kernel.h"

#define STD_OUT 1
#define STD_IN 0



DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

long int ticks=0;
char* video = (char *)0xb8000;

void int_08(int hs, int min, int seg) {

    
    
    
		char strHs[2];
		char strMin[2]; 
		char strSeg[2];
		char * strTemp = "80";

		itoa(hs,strHs);
		itoa(min,strMin);
		itoa(seg,strSeg);
    		
    		
    		
		printSystemInfo(video,strHs,strMin,strSeg,"80");
		
    
   
   
   

}


void itoa (int number, char *buffer)
{
   char *p = buffer;
   char *p1, *p2;
   unsigned long ud = number;
   int divisor = 10;

   
   /* Divide ud ( parte del número, ejemplo: 123 -> ud = 3 / ud = 2 / ud = 1) */
   do
     {
       int remainder = ud % divisor;
		
       *p++ = remainder + '0';
     }
   while (ud /= divisor);

   /* Termina el buffer */
   *p = 0;

   /* Da vuelta el buffer, porque los va guardando al revés */
   p1 = buffer;
   p2 = p - 1;
   while (p1 < p2)
     {
       char tmp = *p1;
       *p1 = *p2;
       *p2 = tmp;
       p1++;
       p2--;
     }
     
 }
 



size_t __write(int fd, const void* buffer, size_t count) {

	if(fd == STD_OUT){
        videoPrint(video,buffer, count);
	}

	return (fd == STD_OUT);//no se si esta bien asi
}

size_t __read(int fd, void * buffer, size_t count) {
    if(fd == STD_IN){
        *(char*)buffer = pullBuffer();
    }

    return *(size_t*)buffer;
}

/**********************************************
kmain()
Punto de entrada de cóo C.
*************************************************/

kmain()
{

        int i,num;

/* Borra la pantalla. */

	k_clear_screen(video);


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x09], 0x08, (dword)&_keyboardHandler, ACS_INT, 0);

/* Carga de IDTR    */

	idtr.base = 0;
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;

	_lidt (&idtr);

	_Cli();


        _mascaraPIC1(0xFC); //Permito interrupciones de Teclado y TimerTick
        _mascaraPIC2(0xFF);

	_Sti();

	
		


        while(1)
        {
        
        		
        
        }

}

