

/** INCLUDES **/


#include "../include/kernel.h"
#include "../include/kc.h"
#include "../include/shell.h"




/** Variables del Shell **/


/* Arreglo que contiene los caracteres que se ingresaron en el shell.
 * Esto permite que despues se pueda leer el texto ingresado y evita que el usuario borre caracteres que imprimio el sistema.
 */
char shellInput[MAX_INPUT + 1]; //Ultimo espacio reservado para cerrar la cadena en caso de llegar al tope.
//Direccion actual del arreglo.
char inputPos = 0;



void initializeShell() {


		/** BIENVENIDA **/

		printShell();

		while(1)
		{

			char inChar;

			inChar = getc();
			if (inChar == '\t'){

				//Inhibo el TAB en la linea de comandos


			}else if (inChar == '\b'){

				//Verifico la posicion. Si es 0 => No permito que borre.
				if (inputPos > 0)
				{
					putc(inChar);
					inputPos--;
				}


			}else if (inChar == '\n'){

				//Imprimo el ENTER
				putc(inChar);
				//ANALIZO COMANDOS
				addToInput('\0'); //Cierro la cadena
				checkInput();
				//Vacio el buffer
				inputPos = 0;
				//Muestro el Shell
				printShell();

			}else {

				//Agrego caracter al input
				if (!MaxReached())
				{
					addToInput(inChar);
					putc(inChar);
				}else{

					//Alcanzo el final de la linea

				}


			}







		}
}

void addToInput( char c ){

	shellInput[inputPos] = c;
	inputPos++;

}

void checkInput(){

	//Leo el INPUT y comparo con los comandos
	char c = shellInput[inputPos-1];
	strcpy(shellInput,c);

	char first=shellInput[0];
	switch(first){

                case 'l':   if(strcmp("lspci",shellInput) == 0){
                                //printPCI();
                            }else{
                                printf("Comando invalido\n");
                            }
                            break;

                case 'b':   if(strcmp("burnProc", shellInput) == 0){
                                //burnProc();
                            }else{
                                printf("Comando Invalido\n");
                            }
                            break;
	}

}


void printShell(){

	printf("user@OurOS:~$ ");
}

int MaxReached() {

	return inputPos == MAX_INPUT - 1;

}
