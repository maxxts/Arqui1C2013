#include "../include/video.h"
#include "../include/kernel.h"
#include "../include/kc.h"

#define MAX_COLS 80
#define MAX_ROWS 25

int cRow = 0; 
int cCol = 0;

int vindex = 0;


char* posVideo = (char *) 0xb8000;

void videoClear(char * video){

	
	int i=0;
	while(i < (MAX_COLS*MAX_ROWS*2)) {

		video[i]=' ';
		i++;
		video[i]=GREEN_TXT;
		i++;
	}

	cRow = 0;
	cCol = 0;


}


int videoPrintChar (char* video, char c)
{
	//Cambio pagina y eso
	video[ 2*(cCol) + 2*(cRow)*(MAX_COLS) ] = c;
	cCol++;

	return 1; 
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



