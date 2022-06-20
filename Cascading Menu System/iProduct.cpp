/* Citation and Sources...
Final Project Milestone 5
Filename: iProduct.cpp
Version 1.0
Author: IN HO HAN
Student ID: 106053218
Revision History
-----------------------------------------------------------
Date
2022/4/08
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#include "iProduct.h"
using namespace std;
namespace sdds {
   iProduct::~iProduct()
   {
   }
   std::ostream& operator<<(std::ostream& ostr, const iProduct& RO)
   {
      RO.display(ostr);
      return ostr;
   }
   std::istream& operator>>(std::istream& istr, iProduct& RO)
   {
      RO.read(istr);
      return istr;
   }
}