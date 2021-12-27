// INCLUDE DO C
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// INCLUDE DO PERT0 1.5
#include "opf.h"
#include "coff.h"
#include "dos_header.h"

// PROTÓTIPOS 
char inputf(char *fp);
char pec(char *fp);

// FUNÇÃO MAIN
int main()
{
    while(1){
    textcolor(2);
    printf("\t\t\t**************************************************************\n");
    printf("\t\t\t************************* PERT0 1.5 **************************\n");
    printf("\t\t\t********** Portable Executable Read - by: Teuzero ************\n");
    printf("\t\t\t**************************************************************\n\n");
    printf("****************************************************************************************************************\n");
    char fp[33];

    inputf(fp);

    if(!opf(fp)){
        main();
    }

    dos_header(fp);
    coff(fp);
    pec(fp);

    textcolor(2);
    printf("\n****************************************************************************************************************\n");
    textcolor(7);
    getchar();
    system("cls");
    fflush(stdin);
    
    }
}

// INPUT FILE
char inputf(char *fp)
{
    textcolor(3);
    printf("                        Digite o nome do arquivo com a extenss%co .exe: ",0xc6);
    fgets(fp,33,stdin);
    printf("\n");

    for(int count = 0;fp[count];count++)
    {
        if(fp[count] =='\n')
            fp[count]=0;
    }
    fflush(stdin);
}


// PEC - Portable Executable Compile
char pec(char *fp)
{   
    textcolor(6);
    // Abre o arquivo
    FILE *fb = opf(fp);
    unsigned char pe[4], pe2[4], pe3[4];
    
    fseek(fb,0x80,SEEK_SET);
    fread(pe,4,1,fb);
    fseek(fb,0xF0,SEEK_SET);
    fread(pe2,4,1,fb);
    fseek(fb,0x100,SEEK_SET);
    fread(pe3,4,1,fb); 
    
    if(pe[0] == 0x50 && pe[1] == 0x45 && pe[2] == 0x00 && pe[3] == 0x00)
    {
        printf("         O ARQUIVO FOI COMPILADO COM:             MINGW        - C/C++ ");
    }else if(pe2[0] == 0x50 && pe2[1] == 0x45 && pe2[2] == 0x00 && pe2[3] == 0x00)
    {
        //printf("         ASSINATURA PE:                             0x%X%X%X%X     - %c%c%c%c\n",pe2[3],pe2[2],pe2[1],pe2[0],pe2[0],pe2[1],pe2[2],pe2[3]);
    }else if(pe3[0] == 0x50 && pe3[1] == 0x45 && pe3[2] == 0x00 && pe3[3] == 0x00){
        printf("         O ARQUIVO FOI COMPILADO COM:             DELPHI       - PASCAL ");
    }

    // Fecha o arquivo
    fclose(fb);
    textcolor(7);
}