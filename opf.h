#include <stdio.h>
#include "textcolor.h"

// OPEN FILE
FILE *opf(char *pe)
{   
    textcolor(6);
    FILE *pee = fopen(pe,"r");
    if(!pee)
    {
        textcolor(4);
        printf("\t\t\t\tN%co foi poss%cvel abrir arquivo.",0xc6,0x8d);
        getchar();
        system("cls");
        fflush(stdin);
    }     
}