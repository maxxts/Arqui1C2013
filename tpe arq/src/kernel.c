#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/video.h"
#include "../include/kernel.h"
#include "../include/shell.h"

#define STD_OUT 1
#define STD_IN 0

extern int _readPci(int pos);





DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

long int ticks=0;
char* video = (char *)0xb8000;

void int_08(int temp, int hs, int min, int seg) {

		int hs1,hs2,min1,min2,seg1,seg2;

		char strHs1[2];
		char strMin1[2];
		char strSeg1[2];

		char strHs2[2];
		char strMin2[2];
		char strSeg2[2];

		char strHs[2];
		char strMin[2];
		char strSeg[2];
		char strTemp[3];

		temp = temp & 0x007F0000;
		temp = temp >> 16;
		//printf("Temp: %d\n",temp);

		hs1 = hs >> 4; // OBTENGO PRIMER DIGITO
		hs2 = hs & 0x000F; //OBTENGO SEGUNDO DIGITO

		min1 = min >> 4;
		min2 = min & 0x000F;

		seg1 = seg >> 4;
		seg2 = seg & 0x000F;



		itoa(hs1,strHs1); itoa(hs2,strHs2);
		itoa(min1,strMin1); itoa(min2,strMin2);
		itoa(seg1,strSeg1); itoa(seg2,strSeg2);

		itoa(temp,strTemp);

		strHs[0] = strHs1[0]; strHs[1] = strHs2[0];
		strMin[0] = strMin1[0]; strMin[1] = strMin2[0];
		strSeg[0] = strSeg1[0]; strSeg[1] = strSeg2[0];



		printSystemInfo(video,strHs,strMin,strSeg,strTemp);






}

//http://faculty.qu.edu.qa/rriley/cmpt507/minix/lspci_8c-source.html
/*
int getPciList(){
         struct pciinfo_entry *entry;
         struct pciinfo pciinfo;

       // obtain a list of PCI devices from PM
        if (getsysinfo())
        {
                printf("getsysinfo failed");
                return -1;
        }

        // print the list of devices
         entry = pciinfo.pi_entries;
         while (pciinfo.pi_count-- > 0)
        {
             printf("%.4X:%.4X %s\n", entry->pie_vid, entry->pie_did, entry->pie_name);
               entry++;
         }

      return 0;
}
*/




void clearVideoScreen(){

 	videoClear(video);
}


void listPci(){
	
	

	int pciInfo, i=0;
	int vendorId,deviceId;
	do{
		
		pciInfo = _readPci(i++);
		
		//OBTENGO VENDORID Y DEVICEID
		vendorId = pciInfo & 0x0000FFFF;
		deviceId = pciInfo & 0xFFFF0000;
		deviceId = deviceId >> 16;

		printPci(vendorId,deviceId);

	}while(vendorId != 0);

}


void printPci(int vendor, int device){

	printf("Vendor > %d | Device > %d \n",vendor,device);

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

    return *(size_t*)buffer; //tendria q devolver el tamaño del buffer en realidad pero no esta guardado el keyboard eso
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

	initializeShell();



}

