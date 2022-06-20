#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include <fstream>
#include <string.h>
#include "iProduct.h"
#include "Status.h"
#include "Utils.h"

namespace sdds 
{
   class Item : public iProduct 
   {
      double m_price = 0;
      int m_qty = 0;
      int m_qtyNeeded = 0;
      char* m_description{};
      bool m_linearFlag = 0;
      void dealloc();
   protected:
      Status m_state{};
      int m_sku = 0;
      bool linear() const;
   public:
      //Rule of Three 
      Item();
      Item(const Item& copyFrom);
      Item& operator=(const Item& assignFrom);
      ~Item();
      int qtyNeeded()const;
      int qty()const;
      operator double()const;
      operator bool()const;
      int operator-=(int qty);
      int operator+=(int qty);
      void linear(bool isLinear);
      void clear();
      bool operator==(int sku) const;
      bool operator==(const char* description)const;
      std::ofstream& save(std::ofstream& ofstr) const;
      std::ifstream& load(std::ifstream& ifstr);
      std::ostream& display(std::ostream& ostr) const;
      std::istream& read(std::istream& istr);
      int readSku(std::istream& istr);
   };
}
#endif