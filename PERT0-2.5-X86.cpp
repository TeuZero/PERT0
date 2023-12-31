#include <windows.h>
#include <iostream>
#include <locale.h>
#include "textcolor.h"

int main(int argc, char* argv[]) {
    
	char *fileName = new char;
	
	memcpy(fileName,argv[1], 33);
	HANDLE file = 0;
	DWORD fileSize = 0;
	DWORD bytesRead = 0;
	LPVOID fileData = 0;
	PIMAGE_DOS_HEADER dosHeader = {0};
	PIMAGE_NT_HEADERS imageNTHeaders = {0};
	PIMAGE_SECTION_HEADER sectionHeader = {0};
	PIMAGE_SECTION_HEADER importSection = {0};
	IMAGE_IMPORT_DESCRIPTOR* importDescriptor = {0};
	PIMAGE_THUNK_DATA thunkData = {0};
	DWORD thunk = 0;
	DWORD rawOffset = 0;
	
	// open file
	file = CreateFileA(fileName, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE){
	
	std::cout << "Could not read file";
	}else{
		
		// allocate heap
		fileSize = GetFileSize(file, NULL);
		fileData = HeapAlloc(GetProcessHeap(), 0, fileSize);
		
		// read file bytes to memory
		ReadFile(file, fileData, fileSize, &bytesRead, NULL);
		
		textcolor(2);
		std::cout << "\t\t\t**************************************************************\n";
		std::cout << "\t\t\t************************* PERT0 2.5 **************************\n";
		std::cout << "\t\t\t********** Portable Executable Read - by: Teuzero ************\n";
		std::cout << "\t\t\t**************************************************************\n\n";
		std::cout << "****************************************************************************************************************\n";
	    textcolor(6);
	    
	    // IMAGE_DOS_HEADER
		dosHeader = (PIMAGE_DOS_HEADER)fileData;
		std::cout << "******* DOS HEADER *******" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_magic  << "\t\tMagic number"<< std::endl;
		std::cout << "\t0x" << std::hex  << dosHeader->e_cblp << "\t\tBytes on last page of file" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_cp << "\t\tPages in file" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_crlc << "\t\tRelocations" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_cparhdr << "\t\tSize of header in paragraphs" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_minalloc << "\t\tMinimum extra paragraphs needed" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_maxalloc << "\t\tMaximum extra paragraphs needed" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_ss << "\t\tInitial (relative) SS value" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_sp << "\t\tInitial SP value " << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_csum << "\t\tChecksum" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_ip << "\t\tInitial IP value" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_cs << "\t\tInitial (relative) CS value" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_lfarlc << "\t\tFile address of relocation table" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_ovno << "\t\tOverlay number" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_oemid << "\t\tOEM identifier (for e_oeminfo)" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_oeminfo << "\t\tOEM information; e_oemid specific" << std::endl;
		std::cout << "\t0x" << std::hex << dosHeader->e_lfanew << "\t\tFile address of new exe header" << std::endl;
	
		// IMAGE_NT_HEADERS
		imageNTHeaders = (PIMAGE_NT_HEADERS)((DWORD)fileData + dosHeader->e_lfanew);
		std::cout << "\n******* NT HEADERS *******" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->Signature << "\t\tSignature "<< std::endl;
		
		// FILE_HEADER
		std::cout << "\n******* FILE HEADER *******" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.Machine << "\t\tMachine" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.NumberOfSections << "\t\tNumber of Sections" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.TimeDateStamp << "\t\tTime Stamp" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.PointerToSymbolTable << "\t\tPointer to Symbol Table" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.NumberOfSymbols << "\t\tNumber of Symbols" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.SizeOfOptionalHeader << "\t\tSize of Optional Header" << std::endl;
		std::cout << "\t0x" << imageNTHeaders->FileHeader.Characteristics << "\t\tCharacteristics" << std::endl;
	
		// OPTIONAL_HEADER
		std::cout << "\n******* OPTIONAL HEADER *******" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.Magic << "\t\tMagic" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MajorLinkerVersion << "\t\tMajor Linker Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MinorLinkerVersion << "\t\tMinor Linker Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfCode << "\t\tSize Of Code" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfInitializedData << "\t\tSize Of Initialized Data" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfUninitializedData << "\t\tSize Of UnInitialized Data" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.AddressOfEntryPoint << "\t\tAddress Of Entry Point (.text)" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.BaseOfCode << "\t\tBase Of Code" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.BaseOfData << "\t\tBase Of Data" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.ImageBase << "\t\tImage Base" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SectionAlignment << "\t\tSection Alignment" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.FileAlignment << "\t\tFile Alignment" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MajorOperatingSystemVersion << "\t\tMajor Operating System Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MinorOperatingSystemVersion << "\t\tMinor Operating System Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MajorImageVersion << "\t\tMajor Image Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MinorImageVersion << "\t\tMinor Image Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MajorSubsystemVersion << "\t\tMajor Subsystem Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.MinorSubsystemVersion << "\t\tMinor Subsystem Version" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.Win32VersionValue << "\t\tWin32 Version Value" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfImage << "\t\tSize Of Image" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfHeaders << "\t\tSize Of Headers" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.CheckSum << "\t\tCheckSum" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.Subsystem << "\t\tSubsystem" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.DllCharacteristics << "\t\tDllCharacteristics" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfStackReserve << "\t\tSize Of Stack Reserve" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfStackCommit << "\t\tSize Of Stack Commit" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfHeapReserve << "\t\tSize Of Heap Reserve" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.SizeOfHeapCommit << "\t\tSize Of Heap Commit" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.LoaderFlags << "\t\tLoader Flags" << std::endl;
		std::cout << "\t0x" << std::hex << imageNTHeaders->OptionalHeader.NumberOfRvaAndSizes << "\t\tNumber Of Rva And Sizes" << std::endl;
	
		// DATA_DIRECTORIES
		std::cout << "\n******* DATA DIRECTORIES *******" << std::endl;
		std::cout << "\tExport Directory Address: 0x; " << imageNTHeaders->OptionalHeader.DataDirectory[0].VirtualAddress << "Size: 0x" << imageNTHeaders->OptionalHeader.DataDirectory[0].Size << std::endl;
		std::cout << "\tImport Directory Address: 0x; " << imageNTHeaders->OptionalHeader.DataDirectory[1].VirtualAddress << "Size: 0x" << imageNTHeaders->OptionalHeader.DataDirectory[1].Size << std::endl;
	
		// SECTION_HEADERS
		std::cout << "\n******* SECTION HEADERS *******" << std::endl;
		// get offset to first section headeer
		DWORD sectionLocation = (DWORD)imageNTHeaders + sizeof(DWORD) + (DWORD)(sizeof(IMAGE_FILE_HEADER)) + (DWORD)imageNTHeaders->FileHeader.SizeOfOptionalHeader;
		DWORD sectionSize = (DWORD)sizeof(IMAGE_SECTION_HEADER);
		
		// get offset to the import directory RVA
		DWORD importDirectoryRVA = imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	
		// print section data
		for (int i = 0; i < imageNTHeaders->FileHeader.NumberOfSections; i++) {
			sectionHeader = (PIMAGE_SECTION_HEADER)sectionLocation;
			std::cout << "\t" << (char*)sectionHeader->Name << std::endl;
			std::cout << "\t\t0x" << sectionHeader->Misc.VirtualSize << "\t\tVirtual Size" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->VirtualAddress << "\t\tVirtual Address" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->SizeOfRawData << "\t\tSize Of Raw Data" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->PointerToRawData << "\t\tPointer To Raw Data" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->PointerToRelocations << "\t\tPointer To Relocations" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->PointerToLinenumbers << "\t\tPointer To Line Numbers" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->NumberOfRelocations << "\t\tNumber Of Relocations" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->NumberOfLinenumbers << "\t\tNumber Of Line Numbers" << std::endl;
			std::cout << "\t\t0x" << sectionHeader->Characteristics << "\tCharacteristics" << std::endl;
	
			// save section that contains import directory table
			if (importDirectoryRVA >= sectionHeader->VirtualAddress && importDirectoryRVA < sectionHeader->VirtualAddress + sectionHeader->Misc.VirtualSize) {
				importSection = sectionHeader;
			}
			sectionLocation += sectionSize;
		}
	
		// get file offset to import table
		rawOffset = (DWORD)fileData + importSection->PointerToRawData;
		
		// get pointer to import descriptor's file offset. Note that the formula for calculating file offset is: imageBaseAddress + pointerToRawDataOfTheSectionContainingRVAofInterest + (RVAofInterest - SectionContainingRVAofInterest.VirtualAddress)
		importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(rawOffset + (imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));
		
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
		}
	    
	    
		textcolor(2);
		std::cout << "\n****************************************************************************************************************\n";
		textcolor(7);
	}
	return 0;
}

	

