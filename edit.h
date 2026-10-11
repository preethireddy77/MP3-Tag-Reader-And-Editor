#ifndef EDIT_H
#define EDIT_H

#include<stdio.h>
#include "types.h"

typedef struct
{
     FILE *fptr;
     char  *new_data;
     char *filename;
     char *tag;
     char *option;
}EditInfo;
Status edit_mp3(EditInfo *editInfo);

#endif