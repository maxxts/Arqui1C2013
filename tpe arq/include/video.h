/*********************************************
video.h

************************************************/

#include "../include/kernel.h"
#ifndef _video_
#define _video_


int videoPrintChar(char* video, char c);

int videoPrint(char* video, const char* buffer, int count);

void videoClear(char * video);
void writeScreen(char * video, int col, int row, char c);
char readScreen(char * video, int col, int row);

void tabKey(char * video);

void enterKey(char * video); 


void backKey(char * video);

void pageDown(char * video);

#endif
