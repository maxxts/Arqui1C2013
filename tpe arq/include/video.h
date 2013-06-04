/*********************************************
video.h

************************************************/

#include "../include/kernel.h"
#ifndef _video_
#define _video_

int videoPrintChar(char* video, char c);

int videoPrint(char* video, const char* buffer, int count);

void videoClear(char * video);


#endif
