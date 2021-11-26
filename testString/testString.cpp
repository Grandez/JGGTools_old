// testString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Resumiendo, si se crea con new hay que destruir
// Si se alloca tambien
// Si no, lo hace solo
#include <iostream>
#include "mstring.hpp"
#include "StackWalker.h"

void string1() {
mString str;
mString *sz = new mString();
cout << "debe ser UNO: " << str.str1 << endl;
cout << "debe ser DOS: " << str.str2 << endl;
string& aux1 = str.str1;
cout << "Con referencia puede camaniar: ";
aux1 = " cambiado";
cout << str.str1 << endl;
cout << "Con copia se crea otro. cambio o OTRO: " ;
string aux2 = str.str2;
aux2 = "OTRO";
cout << str.str2 << endl;
mString str4(str);
cout << "Con constructor de copia no se cambia: ";
str4.str1 = "NUEVO";
cout << "En str: " << str.str1 << " en la copia " << str4.str1 << endl;
}
int main()
{
    std::cout << "Hello World!\n";
    string1();
std::cout << "fin\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
