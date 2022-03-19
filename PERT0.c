#include <windows.h>
#include <Stdio.h>
#include <locale.h>
#include "petest.h"
#include "opf.h"
#include "dos_header.h"
#include "coff.h"
#include "optional.h"

char inputf(char *fp)
{
    setlocale(LC_ALL, "Portuguese");
    textcolor(3);
    printf("                        Digite o nome do arquivo com a extensão .exe: ");
    fgets(fp,33,stdin);
    printf("\n");
	
    int count = 0;
    for(count;fp[count];count++)
    {
        if(fp[count] =='\n')
            fp[count]=0;
    }
    fflush(stdin);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    while(1){
	    textcolor(2);
	    printf("\t\t\t**************************************************************\n");
	    printf("\t\t\t************************* PERT0 2.0 **************************\n");
	    printf("\t\t\t********** Portable Executable Read - by: Teuzero ************\n");
	    printf("\t\t\t**************************************************************\n\n");
	    printf("****************************************************************************************************************\n");
	    char fp[33];

	    inputf(fp);

	    if(!opf(fp)){
		main();
	    }

	    petest_init(fp);
	    dos_header(fp);
	    coff(fp);
	    optional(fp);
	    
	    textcolor(2);
	    printf("\n****************************************************************************************************************\n");
	    textcolor(7);
	    getchar();
	    system("cls");
	    fflush(stdin);
    }
}
