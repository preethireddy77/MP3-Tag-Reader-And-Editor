#ifndef FILES_H
#define FILES_H
#include "types.h"

typedef struct
{
    FILE *fptr;
    char *filename;
}ViewInfo;

Status view_mp3(ViewInfo *viewInfo);

#endif