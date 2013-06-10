#include "../include/kc.h"
#include "../include/video.h"
#include "../include/stdarg.h"

#define STD_OUT 1
#define STD_IN 0


/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/


void k_clear_screen(char * video)
{
	videoClear(video);
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

void putc(char c){
    __write(STD_OUT, &c, 1);
    return;
}


char getc(){
    char buffer;
    do{
        __read(STD_IN, &buffer ,1);
    }while(buffer == EOF);
}

void printInt(int a) {
    if (a/10 == 0) {
        putc('0' + a);
        return;
    }

    printInt(a/10);
    putc('0' + a%10);
    return;
}

void strcpy(char *s1, char *s2){
    while (*s1++ = *s2++);
}

void printf(char * fmt, ...){

    va_list fp; //apunta a cada arg en orden
    va_start(fp, fmt); //hace que fp apunte al 1er arg
    char *i, *j;

    for(i = fmt ; *i != 0 ; i++){

        if(*i != '%'){
            putc(*i);
        }else{
            switch(*(++i)){

                case 'c': putc(va_arg(fp, int));
                          break;

                case 's': for(j= va_arg(fp, char*) ; *j != 0 ; j++){
                               putc(*j);
                          }
                          break;

                case 'd': printInt(va_arg(fp, int));
                          break;

            }
        }
    }
    va_end(fp); //limpia todo
    return;
}

int scanf(char * fmt,  ...){

	char *i, *j;
	char c;
	int cant,a;

	va_list fp;
	va_start(fp, fmt);

	char * aux;
	for(i = fmt ; *i != 0 ; i++){

		if(*i == '%'){

			switch(*(++i)){

				case 'c': *aux = va_arg(fp, int);
                          *aux = getc();
                          cant++;
                          break;

				case 's':   a = 0;
                            c = getc();
                            //putc(c);
			    aux = va_arg(fp, char*);
                            while(c != '\n'){
                                    aux[a] = c;
                                    putc(aux[a++]);
                                    c = getc();
                            }
                            aux[a] = 0;
                            //aux = va_arg(fp, char*);
                            //strcpy(aux,j);
                            printf("%s\n", aux);
                            cant++;
                            break;

            }
		}
	}

	va_end(fp);
	return cant;
}

int strcmp(char* s1, char* s2){
	int resp;
    int i;

	for(i=0 ; s1[i] || s2[i] ; i++){
		resp = s1[i]-s2[i];
		if(resp != 0){
			return resp;
		}
	}

	return 0;
}
