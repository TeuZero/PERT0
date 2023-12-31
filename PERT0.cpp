#include <windows.h>
#include <locale.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "textcolor.h"

typedef unsigned __int64 QWORD, *PQWORD;

void logo(LPVOID p);

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Portuguese");
    
	logo(NULL);
	
	PIMAGE_THUNK_DATA thunkData = {0};
	DWORD thunk = 0;
	DWORD rawOffset = 0;
	
    //IMAGE DO ARQUIVO
    //================================================================================          
    IMAGE_DOS_HEADER* mz;
    mz = (IMAGE_DOS_HEADER*)malloc(sizeof(IMAGE_DOS_HEADER));
    IMAGE_NT_HEADERS* inh;
    inh = ( IMAGE_NT_HEADERS*)malloc(sizeof(IMAGE_NT_HEADERS));
    IMAGE_SECTION_HEADER* ids;
    ids = (IMAGE_SECTION_HEADER*)malloc(sizeof(IMAGE_SECTION_HEADER));
    
    IMAGE_SECTION_HEADER *sectionHeader;
	IMAGE_SECTION_HEADER *importSection;
	sectionHeader = (IMAGE_SECTION_HEADER*)malloc(sizeof(IMAGE_SECTION_HEADER));
	importSection = (IMAGE_SECTION_HEADER*)malloc(sizeof(IMAGE_SECTION_HEADER));
	
	IMAGE_IMPORT_DESCRIPTOR* importDescriptor;
	importDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)malloc(sizeof(IMAGE_IMPORT_DESCRIPTOR));
    //================================================================================
    
	
	/*
    *
    *   Abri o arquivo, le todos os bytes dele e grava na variavel buffer.
    *   
    */
    
    std::fstream is (argv[1], std::ios::binary | std::ios::out | std::ios::in); // abrir o arquivo modo leitura e escrita em binary
    if(!is) // se nao conseguir abrir retorna 1
        return 1;
    is.seekp(0,is.end); // seta para o final do arquivo
    int length = is.tellp(); // diz quandos bytes tem ate onde ele ta? 
    is.seekp(0, is.beg); // devolve para o inicio
    char *buffer = new char[length]; // alocar espaco na variavel do tamanho do arquivo

    std::cout << "\n Reading: " << length << " bytes...\n\n";
    is.read(buffer,length); // le o tamanho length no arquivo e armazena no buffer
    is.close(); // fecha arquivo 

    
	/*
    *
    *   Copia bytes de IMAGE no arquivo para as estruturas IMAGE.
    *   
    */
    
    memcpy(mz,buffer,sizeof(IMAGE_DOS_HEADER));
    memcpy(inh,buffer+mz->e_lfanew,sizeof(IMAGE_NT_HEADERS32)); 
    printf("\n================== File data header information  ==================\n\n");            
    
    // IMAGE_DOS_HEADER
	
	std::cout << "******* DOS HEADER *******" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_magic  << "\t\tMagic number"<< std::endl;
	std::cout << "\t0x" << std::hex << mz->e_cblp << "\t\tBytes on last page of file" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_cp << "\t\tPages in file" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_crlc << "\t\tRelocations" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_cparhdr << "\t\tSize of header in paragraphs" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_minalloc << "\t\tMinimum extra paragraphs needed" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_maxalloc << "\t\tMaximum extra paragraphs needed" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_ss << "\t\tInitial (relative) SS value" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_sp << "\t\tInitial SP value " << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_csum << "\t\tChecksum" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_ip << "\t\tInitial IP value" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_cs << "\t\tInitial (relative) CS value" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_lfarlc << "\t\tFile address of relocation table" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_ovno << "\t\tOverlay number" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_oemid << "\t\tOEM identifier (for e_oeminfo)" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_oeminfo << "\t\tOEM information; e_oemid specific" << std::endl;
	std::cout << "\t0x" << std::hex << mz->e_lfanew << "\t\tFile address of new exe header" << std::endl;

	// IMAGE_NT_HEADERS
	std::cout << "\n******* NT HEADERS *******" << std::endl;
	std::cout << "\t0x" << inh->Signature << "\t\tSignature "<< std::endl;
	
	// FILE_HEADER
	std::cout << "\n******* FILE HEADER *******" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.Machine << "\t\tMachine" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.NumberOfSections << "\t\tNumber of Sections" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.TimeDateStamp << "\t\tTime Stamp" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.PointerToSymbolTable << "\t\tPointer to Symbol Table" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.NumberOfSymbols << "\t\tNumber of Symbols" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.SizeOfOptionalHeader << "\t\tSize of Optional Header" << std::endl;
	std::cout << "\t0x" << inh->FileHeader.Characteristics << "\t\tCharacteristics" << std::endl;

	// OPTIONAL_HEADER
	std::cout << "\n******* OPTIONAL HEADER *******" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.Magic << "\t\tMagic" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MajorLinkerVersion << "\t\tMajor Linker Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MinorLinkerVersion << "\t\tMinor Linker Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfCode << "\t\tSize Of Code" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfInitializedData << "\t\tSize Of Initialized Data" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfUninitializedData << "\t\tSize Of UnInitialized Data" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.AddressOfEntryPoint << "\t\tAddress Of Entry Point (.text)" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.BaseOfCode << "\t\tBase Of Code" << std::endl;
	//std::cout << "\t0x" << std::hex << inh->OptionalHeader.BaseOfData << "\t\tBase Of Data" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.ImageBase << "\t\tImage Base" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SectionAlignment << "\t\tSection Alignment" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.FileAlignment << "\t\tFile Alignment" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MajorOperatingSystemVersion << "\t\tMajor Operating System Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MinorOperatingSystemVersion << "\t\tMinor Operating System Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MajorImageVersion << "\t\tMajor Image Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MinorImageVersion << "\t\tMinor Image Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MajorSubsystemVersion << "\t\tMajor Subsystem Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.MinorSubsystemVersion << "\t\tMinor Subsystem Version" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.Win32VersionValue << "\t\tWin32 Version Value" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfImage << "\t\tSize Of Image" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfHeaders << "\t\tSize Of Headers" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.CheckSum << "\t\tCheckSum" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.Subsystem << "\t\tSubsystem" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.DllCharacteristics << "\t\tDllCharacteristics" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfStackReserve << "\t\tSize Of Stack Reserve" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfStackCommit << "\t\tSize Of Stack Commit" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfHeapReserve << "\t\tSize Of Heap Reserve" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.SizeOfHeapCommit << "\t\tSize Of Heap Commit" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.LoaderFlags << "\t\tLoader Flags" << std::endl;
	std::cout << "\t0x" << std::hex << inh->OptionalHeader.NumberOfRvaAndSizes << "\t\tNumber Of Rva And Sizes" << std::endl;

	// DATA_DIRECTORIES
	std::cout << "\n******* DATA DIRECTORIES *******" << std::endl;
	std::cout << "\tExport Directory Address: 0x; " << inh->OptionalHeader.DataDirectory[0].VirtualAddress << "Size: 0x" << inh->OptionalHeader.DataDirectory[0].Size << std::endl;
	std::cout << "\tImport Directory Address: 0x; " << inh->OptionalHeader.DataDirectory[1].VirtualAddress << "Size: 0x" << inh->OptionalHeader.DataDirectory[1].Size << std::endl;
	
	
	// SECTION_HEADERS
	std::cout << "\n******* SECTION HEADERS *******" << std::endl;
	
	// get offset to the import directory RVA
	DWORD importDirectoryRVA = inh->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

	// print section data
	int j = 0x28;
	for (int i= 0; i < inh->FileHeader.NumberOfSections;i++) {
		
		memcpy(ids,buffer+mz->e_lfanew+248+j*i,sizeof(IMAGE_SECTION_HEADER));
		std::cout << "\t" << (char*)ids->Name << std::endl;
		std::cout << "\t\t0x" << ids->Misc.VirtualSize << "\t\tVirtual Size" << std::endl;
		std::cout << "\t\t0x" << ids->VirtualAddress << "\t\tVirtual Address" << std::endl;
		std::cout << "\t\t0x" << ids->SizeOfRawData << "\t\tSize Of Raw Data" << std::endl;
		std::cout << "\t\t0x" << ids->PointerToRawData << "\t\tPointer To Raw Data" << std::endl;
		std::cout << "\t\t0x" << ids->PointerToRelocations << "\t\tPointer To Relocations" << std::endl;
		std::cout << "\t\t0x" << ids->PointerToLinenumbers << "\t\tPointer To Line Numbers" << std::endl;
		std::cout << "\t\t0x" << ids->NumberOfRelocations << "\t\tNumber Of Relocations" << std::endl;
		std::cout << "\t\t0x" << ids->NumberOfLinenumbers << "\t\tNumber Of Line Numbers" << std::endl;
		std::cout << "\t\t0x" << ids->Characteristics << "\tCharacteristics" << std::endl;
		
		DWORD terminateS = ids->PointerToRawData + ids->SizeOfRawData;
    	DWORD bytesLivre = ids->SizeOfRawData - ids->Misc.VirtualSize;
    	std::cout  << "\t\tEssa secao termina em "<< "\t\t0x" << terminateS << std::endl;
    	std::cout  << "\t\tEssa tem  "<< std::dec << bytesLivre << "\t\tBytes livre no seu final"<< std::endl;
    	

		// save section that contains import directory table
		if (importDirectoryRVA >= sectionHeader->VirtualAddress && importDirectoryRVA < sectionHeader->VirtualAddress + sectionHeader->Misc.VirtualSize) {
			importSection = sectionHeader;
		}
		
	}
	

	

	
	/* TEST
	
	// get file offset to import table
	rawOffset = (DWORD)fileData + importSection->PointerToRawData;

	// get pointer to import descriptor's file offset. Note that the formula for calculating file offset is: imageBaseAddress + pointerToRawDataOfTheSectionContainingRVAofInterest + (RVAofInterest - SectionContainingRVAofInterest.VirtualAddress)
	importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(rawOffset + (inh->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));
	
	std::cout << "\n******* DLL IMPORTS *******" << std::endl;	
	for (; importDescriptor->Name != 0; importDescriptor++)	{
		// imported dll modules
		std::cout << "\t" << (char*)(rawOffset + (importDescriptor->Name - importSection->VirtualAddress)) << std::endl;
		thunk = importDescriptor->OriginalFirstThunk == 0 ? importDescriptor->FirstThunk : importDescriptor->OriginalFirstThunk;
		thunkData = (PIMAGE_THUNK_DATA)(rawOffset + (thunk - importSection->VirtualAddress));
		
		// dll exported functions
		for (; thunkData->u1.AddressOfData != 0; thunkData++) {
			//a cheap and probably non-reliable way of checking if the function is imported via its ordinal number ¯\_(?)_/¯
			if (thunkData->u1.AddressOfData > 0x80000000) {
				//show lower bits of the value to get the ordinal ¯\_(?)_/¯
				std::cout << "\t\tOrdinal: " << std::hex << (WORD)thunkData->u1.AddressOfData << std::endl;
			} else {
				std::cout << "\t\t " << (char*)(rawOffset + (thunkData->u1.AddressOfData - importSection->VirtualAddress + 2)) << std::endl;
			}
		}
	} */
    
 
    textcolor(2);
	std::cout << "\n****************************************************************************************************************\n";
	textcolor(7);
    
    free(mz);
    free(inh);
    free(ids);
    return 0;
}



void logo(LPVOID p){
	textcolor(2);
	std::cout << "\t\t\t**************************************************************\n";
	std::cout << "\t\t\t************************* PERT0 3.0 **************************\n";
	std::cout << "\t\t\t********** Portable Executable Read - by: Teuzero ************\n";
	std::cout << "\t\t\t**************************************************************\n\n";
	std::cout << "****************************************************************************************************************\n";
    textcolor(6);
}
