#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "view.h"
#include "edit.h"
int main(int argc,char *argv[])
{
    ViewInfo viewInfo;
    if(strcmp(argv[1],"-v")==0)
    {
       viewInfo.filename=argv[2];
       view_mp3(&viewInfo);
    }
    else if(strcmp(argv[1],"-e")==0)
    {
        EditInfo editInfo;
        editInfo.option = argv[2];
        editInfo.new_data = argv[3];
        editInfo.filename=argv[4];
        edit_mp3(&editInfo);
    }
    else{
        printf("Invalid option\n");
    }
    return 0;
}