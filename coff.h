#include <stdio.h>

/*
    COFF - Common Object File Format
*/

struct GetData{
    // Variáveis para armazenar dados da data de criação
    char bin0[27], bin1[27], bin2[27], bin3[27];
    unsigned char ivTimeData[4];

    // Variáveis para amazenar dados do ano
    char binCat[109];
    unsigned long dec;
    unsigned char timeDt[4];

     // Faz os calculos para saber em que ano foi criado o executável
    int dia;
    int result;
    int anosAtras;
};

// OBTÉM DATA DE CRIAÇÃO - EM FASE DE TESTE
int getData(unsigned char timeData[4])
{
    GetData GetData;

    GetData.timeDt[0] = timeData[0];
    GetData.timeDt[1] = timeData[1];
    GetData.timeDt[2] = timeData[2];
    GetData.timeDt[3] = timeData[3];

    // Iverte o hexa da data de criação
    int j = 0;
    int s = 0;
    int a = 0;
    int i = 0;

    for(int i = strlen((char*)timeData)-1; i>=0;i--)
    {    
        GetData.ivTimeData[j] = timeData[i];
        j += 1;
    }

    // Converte hexa da data de criação em binario
    itoa(GetData.ivTimeData[0],GetData.bin0,2);
    itoa(GetData.ivTimeData[1],GetData.bin1,2);
    itoa(GetData.ivTimeData[2],GetData.bin2,2);
    itoa(GetData.ivTimeData[3],GetData.bin3,2);

    // Concatena numero binário da data de criação em uma array
    a = (sprintf(GetData.binCat, "%08.8s",GetData.bin0));
    a += (sprintf(GetData.binCat+a, "%08.8s",GetData.bin1));
    a += (sprintf(GetData.binCat+a, "%08.8s",GetData.bin2));
    a += (sprintf(GetData.binCat+a, "%08.8s",GetData.bin3));

    // Converte número binário da data de criação em decimal
    s = strlen(GetData.binCat);

    while(s--){
        if(GetData.binCat[s] == '0' || GetData.binCat[s] == '1'){
            GetData.dec = GetData.dec + pow(2,i++) * (GetData.binCat[s] - '0');
        }
    
    }
    
    SYSTEMTIME st;
    GetLocalTime(&st);

    float seg = 86400;
    float ano = 365;
   
    GetData.dia = GetData.dec/seg;
    GetData.anosAtras = GetData.dia/ano;
    GetData.result = -(GetData.anosAtras - st.wYear);
    
    return printf("         Date/time stamp:                         0x%X%X%X%X   - %d\n",GetData.timeDt[3],GetData.timeDt[2],GetData.timeDt[1],GetData.timeDt[0], GetData.result);
}

// COMPARA MAQUINA
char getMachine(unsigned char machine[2])
{
    switch(machine[0],machine[1])
    {
        case (unsigned char)0x4c01:
        case (unsigned char)0x6486:
        case (unsigned char)0xbc0e:
        case (unsigned char)0x6602:
            if(machine[0] == 0x4c && machine[1] == 0x01)
            {
                printf("         Machine:                                 0x%X%X        - Intel 386 ou processador posterior e compat%cvel  \n",machine[1],machine[0],0x8d);
                break;
            }else if(machine[0] == 0x64 && machine[1] == 0x86)
            {
                printf("         Machine:                                 0x%X%X       - AMD X64 \n",machine[1],machine[0]);
                break;
            }else if(machine[0] == 0xbc && machine[1] == 0x0e)
            {
                printf("         Machine:                                 0x%X%X        - EFI byte code \n",machine[1],machine[0]);
                break;
            }else if(machine[0] == 0x66 && machine[1] == 0x02)
            {
                printf("         Machine:                                 0x%X%X        - MIPS16 \n",machine[1],machine[0]);
                break;
            }
            default:
                printf("         Esse tipo de arquivo não me interessa.\n");
    }
}

// COFF
struct Coff{
    
    // Variável para armazenar em que tipo de maquina roda
    unsigned char machine[2];
    
    // Variável para armazenar seções
    unsigned char secion[2];

    // Variáveis para armazenar o PE
    unsigned char pe[4], pe2[4], pe3[4];

    // Variáveis para armazenar Ponteiro para simbolo de tabela
    unsigned char pointerToSymbolTable[4];

    // Variável para armazenar data de criação
    unsigned char timeData[4];

    // Variável para armazenar número de Símbolo
    unsigned char numSm[4];

    // Variável para armazenar tamanho do cabeçalho opcional
    unsigned char tdco[2];

    // Variável para armazenar as características do arquivo (Definidas por bit flags)
    unsigned char cdq[2];

};

char coff (char *fp)
{  
    Coff Coff;
    printf("\n\n         ***************************************************************************************\n");
    printf("                                        COFF - Common Object File Format");
    printf("\n         ***************************************************************************************\n");
    
    // Abre o arquivo
    FILE *fb = opf(fp);

    // BUSCA PELA ASSINATURA PE
    fseek(fb,0x80,SEEK_SET);
    fread(Coff.pe,4,1,fb);
    fseek(fb,0xF0,SEEK_SET);
    fread(Coff.pe2,4,1,fb);
    fseek(fb,0x100,SEEK_SET);
    fread(Coff.pe3,4,1,fb);
 
    // COMPARA PE, SEÇÕES E PONTEIRO DA DATA
    if(Coff.pe[0] == 0x50 && Coff.pe[1] == 0x45 && Coff.pe[2] == 0x00 && Coff.pe[3] == 0x00)
    {
        // BUSCA POR MAQUINA QUE É EXECUTADA
        fseek(fb,0x84,SEEK_SET);
        fread(Coff.machine,2,1,fb);
        getMachine(Coff.machine);

        // BUSCA PELA QUANTIDADE DE SEÇÕES NO COFF
        fseek(fb,0x86,SEEK_SET);
        fread(Coff.secion,2,1,fb);

        // BUSCA PELA DATA DE CRIAÇÃO
        fseek(fb,0x88,SEEK_SET);
        fread(Coff.timeData,4,1,fb);

        // BUSCA POR PONTEIRO PARA TABELA DE SÍMBOLO
        fseek(fb,0x8C,SEEK_SET);
        fread(Coff.pointerToSymbolTable,4,1,fb);

        // NÚMERO DE SÍMBOLOS
        fseek(fb,0x90,SEEK_SET);
        fread(Coff.numSm,4,1,fb);

        // TAMANHO DO CABEÇALHO OPCIONAL
        fseek(fb,0x94,SEEK_SET);
        fread(Coff.tdco,2,1,fb);

        // CARACTERÍSTICAS DO ARQUIVO (Definidas por bit flags)
        fseek(fb,0x96,SEEK_SET);
        fread(Coff.cdq,2,1,fb);

        printf("         Number of sections:                      0x%X%X         - %d \n",Coff.secion[1],Coff.secion[0],Coff.secion[0]);     
        getData(Coff.timeData);
        printf("         Symbol Table offset:                     0x%2.2X%2.2X%2.2X%2.2X       \n",Coff.pointerToSymbolTable[3],Coff.pointerToSymbolTable[2],Coff.pointerToSymbolTable[1],Coff.pointerToSymbolTable[0]);
        printf("         Number of symbols:                       0x%2.2X%2.2X%2.2X%2.2X   - %d \n",Coff.numSm[3],Coff.numSm[2],Coff.numSm[1],Coff.numSm[0],Coff.numSm[0]);
        printf("         Size of optional header:                 0x%2.2X%2.2X       - %d \n",Coff.tdco[1],Coff.tdco[0],Coff.tdco[0]);   
        printf("         Characteristics:                         0x%2.2X%2.2X       - %d \n",Coff.cdq[1],Coff.cdq[0],Coff.cdq[0]);    
        }else if(Coff.pe2[0] == 0x50 && Coff.pe2[1] == 0x45 && Coff.pe2[2] == 0x00 && Coff.pe2[3] == 0x00)
    {    
        // BUSCA POR MAQUINA QUE É EXECUTADA
        fseek(fb,0xF4,SEEK_SET);
        fread(Coff.machine,2,1,fb);
        getMachine(Coff.machine);

        // BUSCA PELA QUANTIDADE DE SEÇÕES NO COFF
        fseek(fb,0xF6,SEEK_SET);
        fread(Coff.secion,2,1,fb);

        // BUSCA PELA DATA DE CRIAÇÃO
        fseek(fb,0xF8,SEEK_SET);
        fread(Coff.timeData,4,1,fb);

        // BUSCA POR PONTEIRO PARA TABELA DE SÍMBOLO
        fseek(fb,0xFC,SEEK_SET);
        fread(Coff.pointerToSymbolTable,4,1,fb);

        // NÚMERO DE SÍMBOLOS
        fseek(fb,0x100,SEEK_SET);
        fread(Coff.numSm,4,1,fb);

        // TAMANHO DO CABEÇALHO OPCIONAL
        fseek(fb,0x104,SEEK_SET);
        fread(Coff.tdco,2,1,fb);

        // CARACTERÍSTICAS DO ARQUIVO (Definidas por bit flags)
        fseek(fb,0x106,SEEK_SET);
        fread(Coff.cdq,2,1,fb);

        printf("         Number of sections:                      0x%X%X         - %d \n",Coff.secion[1],Coff.secion[0],Coff.secion[0]);
        getData(Coff.timeData);
        printf("         Symbol Table offset:                     0x%2.2X%2.2X%2.2X         \n", Coff.pointerToSymbolTable[3],Coff.pointerToSymbolTable[2],Coff.pointerToSymbolTable[1],Coff.pointerToSymbolTable[0]);
        printf("         Number of symbols:                       0x%2.2X%2.2X%2.2X%2.2X   - %d \n",Coff.numSm[3],Coff.numSm[2],Coff.numSm[1],Coff.numSm[0],Coff.numSm[0]);
        printf("         Size of optional header:                 0x%2.2X%2.2X       - %d \n",Coff.tdco[1],Coff.tdco[0],Coff.tdco[0]);
        printf("         Characteristics:                         0x%2.2X%2.2X       - %d \n",Coff.cdq[1],Coff.cdq[0],Coff.cdq[0]);   
        }else if(Coff.pe3[0] == 0x50 && Coff.pe3[1] == 0x45 && Coff.pe3[2] == 0x00 && Coff.pe3[3] == 0x00)
    {
        // BUSCA POR MAQUINA QUE É EXECUTADA
        fseek(fb,0x104,SEEK_SET);
        fread(Coff.machine,2,1,fb);
        getMachine(Coff.machine);

        // BUSCA PELA QUANTIDADE DE SEÇÕES NO COFF
        fseek(fb,0x106,SEEK_SET);
        fread(Coff.secion,2,1,fb);

        // BUSCA PELA DATA DE CRIAÇÃO
        fseek(fb,0x108,SEEK_SET);
        fread(Coff.timeData,4,1,fb);

        // BUSCA POR PONTEIRO PARA TABELA DE SÍMBOLO
        fseek(fb,0x10C,SEEK_SET);
        fread(Coff.pointerToSymbolTable,4,1,fb);

        // NÚMERO DE SÍMBOLOS
        fseek(fb,0x110,SEEK_SET);
        fread(Coff.numSm,4,1,fb);

        // TAMANHO DO CABEÇALHO OPCIONAL
        fseek(fb,0x114,SEEK_SET);
        fread(Coff.tdco,2,1,fb);

        // CARACTERÍSTICAS DO ARQUIVO (Definidas por bit flags)
        fseek(fb,0x116,SEEK_SET);
        fread(Coff.cdq,2,1,fb);

        printf("         Number of sections:                      0x%X%X         - %d \n",Coff.secion[1],Coff.secion[0],Coff.secion[0]);
        getData(Coff.timeData);
        printf("         Symbol Table offset:                     0x%2.2X%2.2X%2.2X         \n", Coff.pointerToSymbolTable[3],Coff.pointerToSymbolTable[2],Coff.pointerToSymbolTable[1],Coff.pointerToSymbolTable[0]);
        printf("         Number of symbols:                       0x%2.2X%2.2X%2.2X%2.2X   - %d \n",Coff.numSm[3],Coff.numSm[2],Coff.numSm[1],Coff.numSm[0],Coff.numSm[0]);
        printf("         Size of optional header:                 0x%2.2X%2.2X       - %d \n",Coff.tdco[1],Coff.tdco[0],Coff.tdco[0]);
        printf("         Characteristics:                         0x%2.2X%2.2X       - %d \n",Coff.cdq[1],Coff.cdq[0],Coff.cdq[0]);   
       
        // TESTE
        /*for(int countt = 1970-1; countt < st.wYear-1; 4+countt++){
            int resultt;
            resultt = countt%4;
            if(resultt == 0)
            {
                    printf("\nachou\n");
            }
        }*/       
    }

    // Fecha o arquivo
    fclose(fb);
    return 0;    
}
