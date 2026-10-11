#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"

Status view_mp3(ViewInfo *viewInfo)
{
    FILE *fptr;
    char header[10];
    char tag[5];
    unsigned char size_bytes[4];
    unsigned int size;
    char *data;
    int i;
    char *tags[]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    char *tag_full_form[]={"Title","Artist","Album","Year","Genre","Comment"};
    fptr = fopen(viewInfo->filename,"rb");
    if (fptr == NULL)
    {
        printf("ERROR: Unable to open file\n");
        return e_failure;
    }
    fread(header,1,10,fptr);
    for(i=0;i<6;i++)
    {
        fread(tag,1,4,fptr);
        tag[4]='\0';
        fread(size_bytes,1,4,fptr);
        size = ((unsigned int)size_bytes[0]<<24)|((unsigned int)size_bytes[1]<<16)|((unsigned int)size_bytes[2]<<8)|((unsigned int)size_bytes[3]);
        fseek(fptr,2,SEEK_CUR);
        if (strcmp(tag,tags[i])==0)
        {
            data=malloc(size);
            if (data==NULL)
            {
                fclose(fptr);
                return e_failure;
            }
            fseek(fptr,1,SEEK_CUR);
            fread(data,1,size-1,fptr);
            data[size-1]='\0';
            printf("%-10s : %s\n",tag_full_form[i],data);
            free(data);
        }
        else
        {
            fseek(fptr,size,SEEK_CUR);
        }
    }
    fclose(fptr);
    return e_success;
}