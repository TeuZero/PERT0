#include "textcolor.h"

// OPEN FILE
FILE *opf(char *pe)
{   
	setlocale(LC_ALL, "Portuguese");
    textcolor(6);
    FILE *pee = fopen(pe,"r");
    if(!pee)
    {
        textcolor(4);
        printf("\t\t\t\tNão foi possível abrir arquivo.");
        getchar();
        system("cls");
        fflush(stdin);
    }     
}
