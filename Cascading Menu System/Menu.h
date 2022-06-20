#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
#include "Utils.h"

namespace sdds 
{
   const int maxOption = 15;
   class Menu 
   {
      char* m_option{};
      unsigned int m_numOption = 0;
      void dealloc();
   public:
      // Rule of Three
      Menu(unsigned int number = 0, const char* text = nullptr);
      ~Menu();
      Menu& operator=(const char* menuContent);
      Menu& operator=(unsigned int num);
      unsigned int run() const;
   };
}
#endif