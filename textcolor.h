/*
* Text Color
*/
void textcolor(int iColor)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color,iColor);
}
