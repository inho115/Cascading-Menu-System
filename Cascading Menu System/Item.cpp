#define _CRT_SECURE_NO_WARNINGS
#include "Item.h"

using namespace std;
namespace sdds 
{
   void Item::dealloc()
   {
      delete[] m_description;
      m_description = nullptr;
   }
   bool Item::linear() const
   {
      return m_linearFlag;
   }
   Item::Item()
   {
      m_price = 0;
      m_qty = 0;
      m_qtyNeeded = 0;
      m_description = nullptr;
      m_linearFlag = false;
      m_sku = 0;
   }
   Item::Item(const Item& copyFrom)
   {
      operator=(copyFrom);
   }
   Item& Item::operator=(const Item& assignFrom)
   {
      if (this != &assignFrom)
      {
         m_price = assignFrom.m_price;
         m_qty = assignFrom.m_qty;
         m_qtyNeeded = assignFrom.m_qtyNeeded;
         m_linearFlag = assignFrom.m_linearFlag;
         m_state = assignFrom.m_state.operator int();
         m_state = assignFrom.m_state.operator const char* ();
         m_sku = assignFrom.m_sku;
         ut.alocpy(m_description, assignFrom.m_description);
      }
      return *this;
   }
   Item::~Item()
   {
      dealloc();
      m_state.clear();
   }
   int Item::qtyNeeded() const
   {
      return m_qtyNeeded;
   }
   int Item::qty() const
   {
      return m_qty;
   }
   Item::operator double() const
   {
      return m_price;
   }
   Item::operator bool() const
   {
      return m_state;
   }
   int Item::operator-=(int qty)
   {
      m_qty -= qty;
      return m_qty;
   }
   int Item::operator+=(int qty)
   {
      m_qty += qty;
      return m_qty;
   }
   void Item::linear(bool isLinear)
   {
      m_linearFlag = isLinear;
   }
   void Item::clear()
   {
      m_state = nullptr;
      m_state = 0;
   }
   bool Item::operator==(int sku) const
   {
      bool result = false;
      if (m_sku == sku)
      {
         result = true;
      }
      return result;
   }
   bool Item::operator==(const char* description) const
   {
      bool result = false;
      if (strstr(m_description, description) != nullptr)
      {
         result = true;
      }
      return result;
   }
   std::ofstream& Item::save(std::ofstream& ofstr) const
   {
      ofstr.setf(ios::fixed);
      ofstr.precision(2);
      if (m_state.operator bool())
      {
         ofstr << m_sku << "\t" << m_description << "\t" << m_qty << "\t" << m_qtyNeeded << "\t";
         ofstr << m_price;
         if (m_sku >= 40000)
         {
            ofstr << "\n";
         }
      }
      return ofstr;
   }
   std::ifstream& Item::load(std::ifstream& ifstr)
   {
      char description[1000];
      ifstr >> m_sku;
      ifstr.clear();
      ifstr.ignore();
      ifstr.get(description, 1000, '\t');
      ifstr.clear();
      ifstr.ignore(1000, '\t');
      ut.alocpy(m_description, description);
      ifstr >> m_qty;
      ifstr.clear();
      ifstr.ignore(1000, '\t');
      ifstr >> m_qtyNeeded;
      ifstr.clear();
      ifstr.ignore(1000, '\t');
      ifstr >> m_price;
      if (m_sku >= 40000)
      {
         ifstr.clear();
         ifstr.ignore(1000, '\n');
      }
      if (!ifstr)
      {
         m_state = "Input file stream read failed!";
      }
      return ifstr;
   }
   std::ostream& Item::display(std::ostream& ostr) const
   {
      string str = m_description;
      string limited = str.substr(0, 35);
      ostr.setf(ios::fixed);
      ostr.precision(2);
      if (m_state.operator bool())
      {
         if (m_linearFlag)
         {
            ostr << m_sku << " | ";
            ostr.width(35);
            ostr.fill(' ');
            ostr.setf(ios::left);
            if (strlen(m_description) > 35)
            {
               ostr << limited << " | ";
            }
            else
            {
               ostr << m_description << " | ";
            }
            ostr.width(4);
            ostr.fill(' ');
            ostr.setf(ios::right);
            ostr << m_qty << " | ";
            ostr.width(4);
            ostr.fill(' ');
            ostr << m_qtyNeeded << " | ";
            ostr.width(7);
            ostr << m_price << " |";
            ostr.unsetf(ios::right);
         }
         else
         {
            ostr << "AMA Item:\n";
            ostr << m_sku << ": " << m_description << "\n";
            ostr << "Quantity Needed: " << m_qtyNeeded << "\n";
            ostr << "Quantity Available: " << m_qty << "\n";
            ostr << "Unit Price: $";
            ostr << m_price << "\n";
            ostr << "Needed Purchase Fund: $";
            ostr << double((m_qtyNeeded - m_qty) * m_price) << "\n";
         }
      }
      else
      {
         m_state.operator const char* ();
      }
      return ostr;
   }
   std::istream& Item::read(std::istream& istr)
   {
      cout.setf(ios::fixed);
      cout.precision(2);
      clear();
      char description[1000] = {};
      cout << "AMA Item:\n";
      cout << "SKU: " << m_sku << "\n";
      cout << "Description: ";
      istr.get(description, 1000, '\n');
      istr.ignore(1000, '\n');
      ut.alocpy(m_description, description);
      cout << "Quantity Needed: ";
      m_qtyNeeded = ut.getint(1, 9999);
      cout << "Quantity On Hand: ";
      m_qty = ut.getint(0, m_qtyNeeded);
      cout << "Unit Price: $";
      m_price = ut.getdouble(0.0, 9999.00);
      if (!istr)
      {
         m_state = "Console entry failed";
      }
      return istr;
   }
   int Item::readSku(std::istream& istr)
   {
      cout << "SKU: ";
      m_sku = ut.getint(40000, 99999);
      return m_sku;
   }
}