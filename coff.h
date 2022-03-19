/*
    COFF - Common Object File Format
*/


char coff (char *fp)
{  
    
    printf("\n         ***************************************************************************************\n");
    printf("                                        COFF - Common Object File Format");
    printf("\n         ***************************************************************************************\n");
    
    // Abre o arquivo
    FILE *fb = opf(fp);
    printf("         Machine:                       0x%X       \n",inh->FileHeader.Machine);
    printf("         Number of sections:            0x%X       \n",inh->FileHeader.NumberOfSections);
    printf("         Time Date Stamp:               0x%X       \n",inh->FileHeader.TimeDateStamp);
    printf("         Symbol Table offset:           0x%X       \n",inh->FileHeader.PointerToSymbolTable);
    printf("         Number of symbols:             0x%X       \n",inh->FileHeader.NumberOfSymbols);
    printf("         Size of optional header:       0x%X       \n",inh->FileHeader.SizeOfOptionalHeader);
    printf("         Characteristics:               0x%X       \n",inh->FileHeader.Characteristics);
	
    fclose(fb);
    return 0;
}
