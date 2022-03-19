IMAGE_DOS_HEADER* idh;
IMAGE_NT_HEADERS32* inh;
	
petest_init(char* file){
	
	FILE* f = fopen(file, "rb");
    if (!f)
        return 1;

    idh = (IMAGE_DOS_HEADER*)malloc(sizeof(IMAGE_DOS_HEADER));
    if (idh == NULL)
        return 1;

    fread(idh, sizeof(IMAGE_DOS_HEADER), 1, f);
    
    fseek(f,idh->e_lfanew,SEEK_SET);
    inh = (IMAGE_NT_HEADERS32*)malloc(sizeof(IMAGE_NT_HEADERS32));
    if (inh == NULL)
    	return 1;
    
    fread(inh,sizeof(IMAGE_NT_HEADERS32),1,f);
    
	fclose(f);
	return 0;
}

BOOL petest_ispe(void){
	return (idh->e_magic == 0x5a4d);
	return 0;
}
