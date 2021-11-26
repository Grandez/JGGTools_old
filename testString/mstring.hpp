#pragma once
#include <string>

/*****************************************************************//**
 * \file   msring.hpp
 * \brief  Modo de gestion de cadenas
 *  
 * \author Javier
 * \date   November 2021
 *********************************************************************/
using namespace std;

class mString {
    public:
       string str1 = "UNO";
       string str2 = string("DOS");
        ~mString() {
          cout << "entra en destroy\n";
        }
        mString() {
          str1 = "TRES";
          str2 = "CUATRO";
        }
};
