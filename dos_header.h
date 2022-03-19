/*
    Cabeçalho Do DOS
*/

// DOS_HEADER

char dos_header(char *fp)
{   
    printf("\n         ***************************************************************************************\n");
    printf("                                                MZ_DOS_HEADER");
    printf("\n         ***************************************************************************************\n");
    
    FILE *fb = opf(fp);
	
	if(petest_ispe)
			printf("         [+] O Arquivo é um PE\n\n");
		else
			printf("         [-] Arquivo não é um PE\n\n");
	
    	printf("         Magic number:                  0x%X       \n",idh->e_magic);
	printf("         Bytes in last page:            0x%X       \n",idh->e_cblp);
	printf("     	 Pages in file:                 0x%X       \n",idh->e_cp);	
	printf("     	 Relocations:                   0x%X       \n",idh->e_crlc);	
	printf("     	 Size of header in paragraphs:  0x%X       \n",idh->e_cparhdr);	
	printf("     	 Minimum extra paragraphs:      0x%X       \n",idh->e_minalloc);		
	printf("     	 Maximum extra paragraphs:      0x%X       \n",idh->e_maxalloc);	
	printf("     	 Initial (relative) SS value:   0x%X       \n",idh->e_ss);	
	printf("     	 Initial SP value:              0x%X       \n",idh->e_sp);	
	printf("     	 O Checksum do cabecalho DOS:   0x%X       \n",idh->e_csum);	
	printf("     	 Initial IP value:              0x%X       \n",idh->e_ip);	
	printf("     	 Initial (relative) CS value:   0x%X       \n",idh->e_cs);	
	printf("     	 Address of relocation table:   0x%X       \n",idh->e_lfarlc);	
	printf("     	 Overlay number:                0x%X       \n",idh->e_ovno);	
	printf("     	 PE header offset:              0x%X       \n",idh->e_lfanew);	
	
	fclose(fb);  	
	return 0; 
}
