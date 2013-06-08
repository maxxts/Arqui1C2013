#include "../include/video.h"
#include "../include/kernel.h"
#include "../include/kc.h"

#define MAX_COLS 80
#define MAX_ROWS 25
#define TAB_SIZE 8

int cRow = 1;
int cCol = 0;

int topCol =0;

int vindex = 0;


//char* posVideo = (char *) 0xb8000;

void resetCursor(){
    cRow = 1;
    cCol = 0;
}

void printSystemInfo(char * video, char * hs, char * min, char * seg, char * temp)
{

	//IMPRIMO HORAS
	writeScreen(video, 64+0, 0, hs[0]);
	writeScreen(video, 64+1, 0, hs[1]);
	
	writeScreen(video, 64+2, 0, ':');
	
	//IMPRIMO MINUTOS
	writeScreen(video, 64+3, 0, min[0]);
	writeScreen(video, 64+4, 0, min[1]);
	
	writeScreen(video, 64+5, 0, ':');
	
	//IMPRIMO SEGUNDOS
	writeScreen(video, 64+6, 0, seg[0]);
	writeScreen(video, 64+7, 0, seg[1]);
	
	writeScreen(video, 64+8, 0, ' ');
	
	writeScreen(video, 64+9, 0, 'h');
	writeScreen(video, 64+10, 0, 's');
	
	//IMPRIMO TEMPERATURA
	
	writeScreen(video, 64+11, 0, ' ');
	writeScreen(video, 64+12, 0, temp[0]);
	writeScreen(video, 64+13, 0, temp[1]);
	writeScreen(video, 64+14, 0, ' ');
	writeScreen(video, 64+15, 0, 'C');
	
	
}

void videoClear(char * video){


	int i=0;
	while(i < (MAX_COLS*MAX_ROWS*2)) {

		video[i]=' ';
		i++;
		video[i]=GREEN_TXT;
		i++;
	}

	resetCursor();


}

void writeScreen(char * video, int col, int row, char c)
{
	video[ 2*(col) + 2*(row)*(MAX_COLS) ] = c;
	return;
}

int checkPosition(video)
{
	if(cCol == (MAX_COLS - 1)){
		if(cRow == MAX_ROWS - 1){
				//SCROLL
		} else {
			cRow++;
			cCol = 0;
		}
	}	
}

int videoPrintChar (char* video, char c){
	
	//VALIDO MI POSICION
	
	checkPosition(video);

	writeScreen(video,0,0, (char) cCol);
	
	switch(c){
		//Pregunto por "Enter", "Tab" y "Backspace"
		case '\t':
			tabKey(video);
			return 0;
		case '\b':
			backKey(video);
			return 0;
		case '\n':
			enterKey(video);
			return 0;
		default:
			//video[ 2*(cCol) + 2*(cRow)*(MAX_COLS) ] = c;			
			writeScreen(video, cCol, cRow, c);			
			cCol++;
			return 1;

	}	
	
}

void tabKey(char * video) {
	
	int i;
	for (i=1; i <= TAB_SIZE; i++)
	{
		videoPrintChar(video,' ');
	}
	return;
}

void enterKey(char * video) { 

	if (cRow < MAX_ROWS){
		cRow++;
		cCol=0;
	}else{
		//scroll	
	}
	return;

}

void backKey(char * video) {
	
		
	if (cCol != 0) {
		//No estoy en el principio de la linea
		cCol--;
		writeScreen(video,cCol,cRow,' '); //SOBRESCRIBO EL CARACTER
	}

}									


int videoPrint(char* video,const char* buffer, int count) {

	int index = 0;

	if(buffer == 0) {
		return;
	}

	while(buffer[index] != '\0' && count > 0) {

		videoPrintChar(video, buffer[index]);
		index++;
		count--;
	}

	return;

}



