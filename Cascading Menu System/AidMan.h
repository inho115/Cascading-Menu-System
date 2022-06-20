#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
#include "Utils.h"
#include "Date.h"
#include "Menu.h"
#include "Perishable.h"
#include <fstream>
#include <iostream>
namespace sdds 
{
   const int sdds_max_num_items = 100;
   class AidMan
   {
      char* m_fileName{};
      Menu m_mainMenu{};
      unsigned int menu() const;
      iProduct* m_item[sdds_max_num_items]{};
      int m_numItem = 0;
      void dealloc();
      std::ofstream& write(std::ofstream& ofstr) const;
      std::ofstream& save(std::ofstream& ofstr) const;
      std::ifstream& load(std::ifstream& ifstr);
   public:
      std::ofstream f;
      std::ifstream fin;
      AidMan();
      ~AidMan();
      void run();
      int list(const char* sub_desc = nullptr);
      int search(int sku) const;
      void remove(int index);
      void find(int value);
      void newItem(int value);
   };
}
#endif