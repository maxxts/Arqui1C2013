#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/video.h"
#include "../include/kernel.h"

DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

int tickpos=0;
char* video = (char *)0xb8000;

void int_08() {

    //char *video = (char *) 0xb8000;
    //video[tickpos+=2]='';

}

void int_09() {

    //char *video = (char *) 0xb8000;
    //video[tickpos+=2]='!';

}
/*

	fila
	columna

	pos = (fila*COLUMNA_SIZE + columna)*2 

*/


size_t __write(int fd, const void* buffer, size_t count) {
	
	//Validar FD	
	videoPrint(video,buffer, count);
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
/* Habilito interrupcion de timer tick*/

        _mascaraPIC1(0xFE);
        _mascaraPIC2(0xFF);
        
	_Sti();

	
	
	__write(1,"Hola",4);
	
	
        while(1)
        {
        }
	
}

