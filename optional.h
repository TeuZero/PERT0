/*
    OH - Optional Header
*/

char optional (char *fp)
{  
    
  printf("\n         ***************************************************************************************\n");
	printf("                                        OH - Optional Header or Image Header");
  printf("\n         ***************************************************************************************\n");
    
    // Abre o arquivo
  FILE *fb = opf(fp);
  printf("         Magic number:                  0x%X       \n",inh->OptionalHeader.Magic);
	printf("         Linker major version:          0x%X       \n",inh->OptionalHeader.MajorLinkerVersion);
	printf("         Linker minor version:          0x%X       \n",inh->OptionalHeader.MinorLinkerVersion);
	printf("         Size of .text section:         0x%X       \n",inh->OptionalHeader.SizeOfCode);
	printf("         Size of .data section:         0x%X       \n",inh->OptionalHeader.SizeOfInitializedData);
	printf("         Size of .bss section:          0x%X       \n",inh->OptionalHeader.SizeOfUninitializedData);
	printf("         Entrypoint:                    0x%X       \n",inh->OptionalHeader.AddressOfEntryPoint);
	printf("         ImageBase:                     0x%X       \n",inh->OptionalHeader.ImageBase);
	printf("         Base of code:                  0x%X       \n",inh->OptionalHeader.BaseOfCode);
	printf("         Base of data:                  0x%X       \n",inh->OptionalHeader.BaseOfData);
	printf("         Major version of required OS:  0x%X       \n",inh->OptionalHeader.MajorOperatingSystemVersion);
	printf("         Minor version of required OS:  0x%X       \n",inh->OptionalHeader.MinorOperatingSystemVersion);
	printf("         Major version of image:        0x%X       \n",inh->OptionalHeader.MajorImageVersion);
	printf("         Minor version of image:        0x%X       \n",inh->OptionalHeader.MinorImageVersion);
	printf("         Major version of subsystem:    0x%X       \n",inh->OptionalHeader.MajorSubsystemVersion);
	printf("         Minor version of subsystem:    0x%X       \n",inh->OptionalHeader.MinorSubsystemVersion);
	printf("         Size of image:                 0x%X       \n",inh->OptionalHeader.SizeOfImage);
	printf("         Size of headers:               0x%X       \n",inh->OptionalHeader.SizeOfHeaders);
	printf("         Checksum:                      0x%X       \n",inh->OptionalHeader.CheckSum);
	printf("         Subsystem required:            0x%X       \n",inh->OptionalHeader.Subsystem);
	printf("         DLL characteristics:           0x%X       \n",inh->OptionalHeader.DllCharacteristics);
	printf("         Data directories:              0x%X       \n",inh->OptionalHeader.DataDirectory);
					
	fclose(fb);
  return 0;
}
