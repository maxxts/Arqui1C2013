

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


		showSplashScreen();

		printShell();

		while(1)
		{

			char inChar;
			inChar = getc();

			//Verifico haber recibido un caracter
			if (inChar!=EOF)
			{



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
}


void showSplashScreen(){

printf("	  ___  ____  ____     ___  ____  ____   __  ____  __  _  _  ____  \n");
printf("	 / __)(  __)(_  _)   / __)(  _ \\(  __) / _\\(_  _)(  )/ )( \\(  __) \n");
printf("	( (_ \\ ) _)   )(    ( (__  )   / ) _) /    \\ )(   )( \\ \\/ / ) _)  \n");
printf("	 \\___/(____) (__)    \\___)(__\\_)(____)\\_/\\_/(__) (__) \\__/ (____) \n\n");

printf("Bienvenido a GetCreativeOS! \nPara ver la lista de comandos ingrese \"help\".\n\n");
printf("************************************************************************\n");

}

void addToInput( char c ){

	shellInput[inputPos] = c;
	inputPos++;

}

void checkInput(){

	//Leo el INPUT y comparo con los comandos

	char first=shellInput[0];
	switch(first){

                case 'l':   if(strcmp("lspci",shellInput) == 0){
                                char * c;
                                scanf("%s", c);
                                printf("Puse: %s\n",c);
                                printf("Puse: %s\n",c);
                                printf("Puse: %s\n",c);
                                printf("Ejecutando \"lspci\"...\n");
                            }else{
                                printf("Comando Invalido. Pruebe \"lspci\" o consulte \"help\".\n");
                            }
                            break;

                case 'b':   if(strcmp("burnproc", shellInput) == 0){
                                 printf("Ejecutando \"burnproc\"...\n");
                            }else{
                                printf("Comando Invalido. Pruebe \"burnproc\" o consulte \"help\".\n");
                            }
                            break;

                case 'c':   if(strcmp("clear", shellInput) == 0){
                                 clearScreen();
                            }else{
                                printf("Comando Invalido. Pruebe \"clear\" o consulte \"help\".\n");
                            }
                            break;

                case 'h':   if(strcmp("help", shellInput) == 0){
                                 showHelp();
                            }else{
                                printf("Comando Invalido. Pruebe \"help\".\n");
                            }
                            break;
                default:
                		printf("Comando Invalido. Consulte \"help\" para ver todos los comandos.\n");
                		break;
	}

}

void showHelp(){
	printf("LISTA DE COMANDOS\n");
	printf("************************************************************************\n");

	printf("\"burnproc\" >> Levanta la temperatura del procesador.\n");

	printf("\"clear\" >> Limpia la pantalla.\n");

	printf("\"help\" >> Muestra la lista de comandos.\n");

	printf("\"lspci\" >> Muestra la lista de los dispositivos PCI.\n");

	printf("************************************************************************\n");


}

void clearScreen(){


	clearVideoScreen();

}


void printShell(){

	printf("user@GetCreative:~$ ");
}

int MaxReached() {

	return inputPos == MAX_INPUT - 1;

}
