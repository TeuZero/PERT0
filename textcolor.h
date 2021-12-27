/*
* Text Color
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void textcolor(int iColor)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color,iColor);
}