#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/video.h"
#include "../include/kernel.h"

#define STD_OUT 1
#define STD_IN 0



DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

int tickpos=0;
char* video = (char *)0xb8000;

void int_08(int hs, int min, int seg) {

    char * strHs = "";
    char * strMin = ""; 
    char * strSeg = "";
    char * strTemp = "80";
   
   itoa(hs,strHs);
   itoa(min,strMin);
   itoa(seg,strSeg);
    
    
    
    printSystemInfo(video,hs,min,seg,"80");

}

void intToString(int a, char * str) {
    if (a/10 == 0) {
        str = str + ('0' + a);
        return;
    }
    
    intToString(a/10,str);
    str = str + ('0' + a%10);
    return;
    
}

 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     //reverse(s);
 }
 
  void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
 
int strlen(char* str)
{
    int i;
    while (str[i] != '\0')
        ++i;
    return i;
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

	/*char * c = "Hola!";
	scanf("%s", c);
	printf("%s",c);
	*/
	//printf("Hola: %s","Maxi");
	





        while(1)
        {
        }

}

