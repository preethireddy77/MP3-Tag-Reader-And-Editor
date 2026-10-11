#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "edit.h"

Status edit_mp3(EditInfo *editInfo)
{
    FILE *src,*temp;
    char header[10];
    char tag[5];
    unsigned char size_bytes[4];
    unsigned int size,new_size;
    char *data;
    int i,j;
    char *option[]={"-t","-a","-A","-y","-g","-c"};
    char *tag_name[]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    for(i=0;i<6;i++){
        if(strcmp(editInfo->option,option[i])==0)
        {
            editInfo->tag=tag_name[i];
            break;
        }
    }
    src=fopen(editInfo->filename,"rb");
    temp=fopen("temp.mp3","wb");
    if(src==NULL||temp==NULL)
    {
        return e_failure;
    }
    fread(header,1,10,src);
    fwrite(header,1,10,temp);
    for(i=0;i<6;i++){
        fread(tag,1,4,src);
        tag[4]='\0';
        fread(size_bytes,1,4,src);
        size=((unsigned int)size_bytes[0]<<24)|((unsigned int)size_bytes[1]<<16)|((unsigned int)size_bytes[2]<<8)|((unsigned int)size_bytes[3]);
        unsigned char flags[2];
        fread(flags,1,2,src);
        if(strcmp(tag,editInfo->tag)==0){
           new_size=strlen(editInfo->new_data)+1;
            fwrite(tag,1,4,temp);
            fwrite(size_bytes,1,4,temp);
            fwrite(flags,1,2,temp);
            fputc(0,temp);
            fwrite(editInfo->new_data,1,strlen(editInfo->new_data),temp);
            for(j=new_size;j<size;j++)
            fputc(0,temp);
            fseek(src,size,SEEK_CUR);
        }
        else{
            fwrite(tag,1,4,temp);
            fwrite(size_bytes,1,4,temp);
            fwrite(flags,1,2,temp);
            data=malloc(size);
            fread(data,1,size,src);
            fwrite(data,1,size,temp);
            free(data);
        }
    }
    while((i=fgetc(src))!=EOF)
    fputc(i,temp);
    fclose(temp);
    remove(editInfo->filename);
    rename("temp.mp3",editInfo->filename);
    return e_success;
}