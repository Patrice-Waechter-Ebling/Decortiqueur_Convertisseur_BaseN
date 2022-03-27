// DecortiqueurBinaire.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:4244)

int tableBin[17] = { 0 };
int tableBinN[17] = { 0 };
int LectureBin[17] = { 0 };
char binaire[17] = { 0 };
HANDLE console;

void OverrideParamConsole() //compatible 32 et 64bits
{
    char fill = (char)0x00;
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}
//2bits
void CreerTableDe2()
{
    for (int a = 0; a <= 16; a++)
    {
        binaire[a] = (char)0x1E;
        tableBin[a] = pow(2, a);
    }
}
void AfficheTableDe2()
{
    for (int a = 0; a <= 16; a++)
    {
        printf("\n2^%2d = %5d", a, tableBin[a]);
    }
}

//8 bits
int toBase_8(int number) 
{
    int base(8);
    double resTemp = (double)number / base;
    int entier1 = (int)resTemp;
    double decimal = resTemp - entier1;
    double entier2 = decimal * (double)base;
    int res = ((entier1 * 10) + (int)entier2);
    return res;
}
int toBase_2_8bits(float number) {
    if (number > 0 && number <= 255) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void AfficherTable8bits()
{
    for (int a = 7; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, tableBin[a], LectureBin[a]);
    }
}
void AfficherBinaire8b()
{
    for (int a = 7; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}

//16bits
int toBase_2_16bits(float number) {
    if (number > 0 && number <= 0xFFFF) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void AfficherTable16bits()
{
    for (int a = 16; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, tableBin[a], LectureBin[a]);
    }
}
void AfficherBinaire16b()
{
    for (int a = 16; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}

void CreerTableDeBaseDesiree(int BaseN)
{
    for (int a = 0; a <= 16; a++)
    {
        binaire[a] = (char)0x1E;
        tableBinN[a] = pow(BaseN, a);
    }
}
int RechercherLaPlusHautePuissance(int valeur)
{
    int reste;
    if (valeur < 2) return 1;
    int a = 0;
    for (a = 16; a >= 0; a--) {
        if (a == 16)
        {
            reste = valeur;
        }
        if (tableBin[a] > reste)
        {
            LectureBin[a] = 0;
        }
        else
        {
            LectureBin[a] = 1;
            return a + 1;
        }

    }
}
int ExtractPuissanceLog2(int Valeur)
{
    return  abs(log2(Valeur));
}
int main()
{
    int A,B;
    CreerTableDe2();
    OverrideParamConsole();
    SetConsoleTitleA("Decortiqueur et convertisseur de base a detection 8/16bits");
    printf("Convertisseur decimal a baseN\t%cPatrice Waechter-Ebling\tv:1.00\nLimite maximale fixee a 16bits soit 65534\n\n", 0xA9);
    printf("Entrez le nombre a convertir\t");
    scanf("%d", &A);
    printf("Entrez le base desiree\t");
    scanf("%d", &B);
    A = fabs(A); //protection anti chiffre negatif
    int bits = RechercherLaPlusHautePuissance(A);
    printf("\n%d donne en Hexa: %X en ASCII: %c en octal: %o  Persistance:%d ValeurPersistant:%d reste:%d\n", A, A, A, A, ExtractPuissanceLog2(A), tableBin[ExtractPuissanceLog2(A)], (A - tableBin[ExtractPuissanceLog2(A)]));
    if (ExtractPuissanceLog2(A) > 16 || A > 65535) {
        SetConsoleTextAttribute(console, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("2^%d requiere l'algorhitme 32bits qui n'est pas inclu dans le mode demo \nContactez l'auteur (Patrice Waechter-Ebling) pour vous procurer la version complete\n", ExtractPuissanceLog2(A) + 1);
        SetConsoleTextAttribute(console, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        return -32;
    }
    if (ExtractPuissanceLog2(A) > 7)
    {
        printf("Commutation 16bits requise: requiere %dbits minimal\n", bits);
        toBase_2_16bits(A);
        AfficherBinaire16b();
        AfficherTable16bits();
    }
    else {
        toBase_2_8bits(A);
        printf("\nnombre de bits requis %d en Binaire Theorique: ", bits);
        AfficherBinaire8b();
        AfficherTable8bits();
    }
}

