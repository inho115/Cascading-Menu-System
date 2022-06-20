#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <iostream>
#include "iProduct.h"
#include "Item.h"
#include "Date.h"
#include "Utils.h"

namespace sdds 
{
   class Perishable : public Item 
   {
      Date m_expiryDate{};
      char* m_instruction{};
      void dealloc();
   public:
      Perishable();
      Perishable(const Perishable& copy);
      Perishable& operator=(const Perishable& copy);
      ~Perishable();
      const Date& expiry() const;
      int readSku(std::istream& istr);
      std::ofstream& save(std::ofstream& ofstr) const;
      std::ifstream& load(std::ifstream& ifstr);
      std::ostream& display(std::ostream& ostr) const;
      std::istream& read(std::istream& istr);
   };
}
#endif