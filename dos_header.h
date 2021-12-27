#include <stdio.h>
/*
    Cabeçalho Do DOS
*/

// DOS_HEADER
struct DosHeader{
    // MZ
    unsigned char mz[2];

    // TDUP - Tamanho da última página
    unsigned char tdup[2];

    // TDP - Total de Páginas
    unsigned char tdp[2];

    // IDT - Itens de relocação
    unsigned char idt[2];

    // TDCD - Tamanho do Cabeçalho DOS
    unsigned char tdcd[2];

    // TMDM - Tamanho Mínimo da Memória
    unsigned char tmdm[2];

    // TMDM2 -  Tamanho Mínimo de Memória
    unsigned char tmdm2[2];

    // VIDRSS - Valor Inicial do Registrador SS (Stack Segment)
    unsigned char vidrss[2];

    // VIDRSP - Valor Inicial do Registrador SP (Stack Pointer)
    unsigned char vidrsp[2];

    // CDCD - Checksum do Cabçalho DOS
    unsigned char cdcd[2];

    // VIDRIP - Valor Inicial do Registrador IP (Intruction Pointer)
    unsigned char vidrip[2];

    // VIDRCS - Valor Inicial do Registrador CS (Code Segment)
    unsigned char vidrcs[2];

    // ODFSD - Offset do Fragmento (Stub) DOS  
    unsigned char odfsd[2];

    // ODCDAP - Offset do Cabeçalho do Arquivo PE
    unsigned char odcdap[4];

    // OVN- Overlay number 
    unsigned char ovn[2];

    //OEMID - Identificador OEM
    unsigned char oemid[2];

    //OEMIF - Informações OEM
    unsigned char oemif[2];

    // BR - Bytes Reservados
    unsigned char br[4];

    // Betov's CheckSum
    unsigned char bc[4];
};

char dos_header(char *fp)
{   
    DosHeader DosHeader;
    printf("\n         ***************************************************************************************\n");
    printf("                                                MZ_DOS_HEADER");
    printf("\n         ***************************************************************************************\n");
    
    FILE *fb = opf(fp);

    fread(DosHeader.mz,2,1,fb);
    
    // BUSCA PELA ASSINATURA MZ
    if(DosHeader.mz[0] == 0x4D && DosHeader.mz[1] == 0x5A)
    {
        printf("         Magic number:                            0x%x%x       - %c%c\n",DosHeader.mz[1],DosHeader.mz[0],DosHeader.mz[0],DosHeader.mz[1]);
    }else{
        printf("                            O ARQUIVO %c .COM OU %c DESCONHE%CIDO. \n                            N%cO ME INTERESSA ARQUIVO QUE N%cO COME%cA COM MZ.", 0x90,0x90,0x80,0xC7,0xC7,0x80);
        getchar();
        system("cls");
        fflush(stdin);
    }

    // TAMANHO DA ÚLTIMA PÁGINA
    fseek(fb,0x02,SEEK_SET);
    fread(DosHeader.tdup,2,1,fb);
    printf("         Bytes in last page:                      0x%2.2X%2.2X       - %d \n",DosHeader.tdup[1],DosHeader.tdup[0],DosHeader.tdup[0]);

    // TOTAL DE PÁGINAS
    fseek(fb,0x04,SEEK_SET);
    fread(DosHeader.tdp,2,1,fb);
    printf("         Pages in file:                           0x%2.2X%2.2X       - %d \n",DosHeader.tdp[1],DosHeader.tdp[0],DosHeader.tdp[0]);

    // ITENS DE RELOCAÇÃO
    fseek(fb,0x06,SEEK_SET);
    fread(DosHeader.idt,2,1,fb);
    printf("         Relocations:                             0x%X%X         - %d \n", DosHeader.idt[1],DosHeader.idt[0],DosHeader.idt[0]);

    // TAMANHO DO CABEÇALHO DOS
    fseek(fb,0x08,SEEK_SET);
    fread(DosHeader.tdcd,2,1,fb);
    int tdcdInt = DosHeader.tdcd[0];
    tdcdInt += DosHeader.tdcd[1];
    printf("         Size of header in paragraphs:            0x%x%x         - %d \n",DosHeader.tdcd[1],DosHeader.tdcd[0],tdcdInt*16);   
    
    // TAMANHO MÍNIMO DA MEMÓRIA
    fseek(fb,0x0A,SEEK_SET);
    fread(DosHeader.tmdm,2,1,fb);
    printf("         Minimum extra paragraphs:                0x%X%X         - %d%d \n",DosHeader.tmdm[1],DosHeader.tmdm[0],DosHeader.tmdm[0],DosHeader.tmdm[1]);
    
    // TAMANHO MÁXIMO DE MAMÓRIA
    fseek(fb,0x0C,SEEK_SET);
    fread(DosHeader.tmdm2,2,1,fb);
    int tmdmInt = DosHeader.tmdm2[0]+1;
    tmdmInt *= DosHeader.tmdm2[1]+1;
    printf("         Maximum extra paragraphs:                0x%X%X       - %d \n",DosHeader.tmdm2[0],DosHeader.tmdm2[1],tmdmInt-1);
    
    // VALOR INICIAL DO REGISTRADOR SS
    fseek(fb,0x0e,SEEK_SET);
    fread(DosHeader.vidrss,2,1,fb);
    printf("         Initial (relative) SS value:             0x%X%X         - %d%d\n", DosHeader.vidrss[1],DosHeader.vidrss[0],DosHeader.vidrss[0],DosHeader.vidrss[1]);
    
    // VALOR INICIAL DO REGISTRADOR SP
    fseek(fb,0x10,SEEK_SET);
    fread(DosHeader.vidrsp,2,1,fb);
    printf("         Initial SP value:                        0x%2.2X%2.2X       - %d\n",DosHeader.vidrsp[1],DosHeader.vidrsp[0],DosHeader.vidrsp[0]);

    // CHECKSUM DO CABEÇALHO DOS
    fseek(fb,0x12,SEEK_SET);
    fread(DosHeader.cdcd,2,1,fb);
    printf("         O Checksum do cabecalho DOS:             0x%X%X         - %d%d\n",DosHeader.cdcd[1],DosHeader.cdcd[0],DosHeader.cdcd[0],DosHeader.cdcd[1]);

    // VALOR INICIAL DO REGISTRADOR IP (Intruction Pointer)
    fseek(fb,0x14,SEEK_SET);
    fread(DosHeader.vidrip,2,1,fb);
    printf("         Initial IP value:                        0x%X%X         - %d%d\n",DosHeader.vidrip[1],DosHeader.vidrip[0],DosHeader.vidrip[0],DosHeader.vidrip[1])  ; 
    
    // VALOR INICIAL DO REGISTRADOR CS (Code Segment)
    fseek(fb,0x16,SEEK_SET);
    fread(DosHeader.vidrcs,2,1,fb);
    printf("         Initial (relative) CS value:             0x%X%X         - %d%d\n",DosHeader.vidrcs[1],DosHeader.vidrcs[0],DosHeader.vidrcs[0],DosHeader.vidrcs[1]);


    // OFFSET DO FRAMENTO (Stub) DOS
    fseek(fb,0x18,SEEK_SET);
    fread(DosHeader.odfsd,2,1,fb);
    printf("         Address of relocation table:             0x%X         \n",DosHeader.odfsd[0]);

    
    // Overlay number
    fseek(fb,0x1A,SEEK_SET);
    fread(DosHeader.ovn,2,1,fb);
    printf("         Overlay number:                          0x%X%X         - %d%d\n",DosHeader.ovn[1],DosHeader.ovn[0],DosHeader.ovn[0],DosHeader.ovn[1]);

    // OEM Identifier
    fseek(fb,0x1C,SEEK_SET);
    fread(DosHeader.oemid,2,1,fb);
    printf("         OEM identifier:                          0x%X%X         - %d%d\n",DosHeader.oemid[1],DosHeader.oemid[0],DosHeader.oemid[0],DosHeader.oemid[1]);
    
    // OEM Informaton
    fseek(fb,0x1E,SEEK_SET);
    fread(DosHeader.oemif,2,1,fb);
    printf("         OEM information:                         0x%X%X         - %d%d\n",DosHeader.oemif[1],DosHeader.oemif[0],DosHeader.oemif[0],DosHeader.oemif[1]);
    
    // Bytes Reservados
    fseek(fb,0x20,SEEK_SET);
    fread(DosHeader.br,4,1,fb);
    printf("         The first reserved bytes are:            0x%X%X%X%X       - %d%d%d%d\n",DosHeader.br[3],DosHeader.br[2],DosHeader.br[1],DosHeader.br[0],DosHeader.br[0],DosHeader.br[2],DosHeader.br[2],DosHeader.br[2]);
    

    //Betov's CheckSum
    fseek(fb,0x38,SEEK_SET);
    fread(DosHeader.bc,4,1,fb);
    printf("         Betov's CheckSum:                        0x%X%X%X%X       - %d%d%d%d\n",DosHeader.bc[3],DosHeader.bc[2],DosHeader.bc[1],DosHeader.bc[0],DosHeader.bc[0],DosHeader.bc[1],DosHeader.bc[2],DosHeader.bc[3]);
    

    // Offset do Cabeçalho do Arquivo PE
    fseek(fb,0x3C,SEEK_SET);
    fread(DosHeader.odcdap,4,1,fb);
    printf("         PE header offset:                        0x%2.2X%2.2X%2.2X%2.2X        \n",DosHeader.odcdap[3],DosHeader.odcdap[2],DosHeader.odcdap[1],DosHeader.odcdap[0]);
    
    
    fclose(fb);  
    return 0; 
}

