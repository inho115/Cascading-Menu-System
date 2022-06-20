#define _CRT_SECURE_NO_WARNINGS
#include "Perishable.h"

using namespace std;
namespace sdds 
{
   void Perishable::dealloc()
   {
      delete[] m_instruction;
      m_instruction = nullptr;
   }
   Perishable::Perishable()
   {
      dealloc();
   }
   Perishable::Perishable(const Perishable& copy)
   {
      if (copy.m_instruction != nullptr && copy.m_instruction[0] != '\0')
      {
         operator=(copy);
      }
   }
   Perishable& Perishable::operator=(const Perishable& copy)
   {
      if (this != &copy)
      {
         m_expiryDate = copy.m_expiryDate;
         (Item&)*this = copy;
         ut.alocpy(m_instruction, copy.m_instruction);
      }
      return *this;
   }
   Perishable::~Perishable()
   {
      dealloc();
   }
   const Date& Perishable::expiry() const
   {
      return m_expiryDate;
   }
   int Perishable::readSku(std::istream& istr)
   {
      cout << "SKU: ";
      m_sku = ut.getint(10000, 39999);
      return m_sku;
   }
   std::ofstream& Perishable::save(std::ofstream& ofstr) const
   {
      if (m_state.operator bool())
      {
         Item::save(ofstr);
         ofstr << "\t";
         if (m_instruction != nullptr)
         {
            ofstr << m_instruction;
         }
         ofstr << "\t";
         m_expiryDate.write(ofstr, false);
         ofstr << "\n";
      }
      return ofstr;
   }
   std::ifstream& Perishable::load(std::ifstream& ifstr)
   {
      char instruction[100]{};
      Item::load(ifstr);
      ifstr.clear();
      ifstr.ignore(1000, '\t');
      char next = ifstr.peek();
      if (next == '\t')
      {
         dealloc();
         ifstr.clear();
         ifstr.ignore(1000, '\t');
      }
      else
      {
         ifstr.get(instruction, 100, '\t');
         ifstr.clear();
         ifstr.ignore(1000, '\t');
         ut.alocpy(m_instruction, instruction);
      }
      m_expiryDate.read(ifstr);
      ifstr.clear();
      ifstr.ignore(1000, '\n');
      if (!ifstr)
      {
         m_state = "Input file stream read (perishable) failed!";
      }
      return ifstr;
   }
   std::ostream& Perishable::display(std::ostream& ostr) const
   {
      if (m_state.operator bool() == false)
      {
         ostr << m_state.operator const char* ();
      }
      else
      {
         if (linear())
         {
            Item::display(ostr);
            if (m_instruction != nullptr && m_instruction[0] != '\0')
            {
               ostr << "*";
            }
            else
            {
               ostr << " ";
            }
            m_expiryDate.write(ostr, true);
         }
         else
         {
            ostr << "Perishable ";
            Item::display(ostr);
            ostr << "Expiry date: ";
            m_expiryDate.write(ostr, true);
            if (m_instruction != nullptr && m_instruction[0] != '\0')
            {
               ostr << "\nHandling Instructions: " << m_instruction;
            }
            cout << endl;
         }
      }
      return ostr;
   }
   std::istream& Perishable::read(std::istream& istr)
   {
      char instruction[100]{};
      Item::read(istr);
      dealloc();
      cout << "Expiry date (YYMMDD): ";
      m_expiryDate.read(istr);
      istr.clear();
      istr.ignore(1000, '\n');
      cout << "Handling Instructions, ENTER to skip: ";
      char next = istr.peek();
      if (next != '\n')
      {
         istr.get(instruction, 100, '\n');
         istr.clear();
         istr.ignore(1000, '\n');
         ut.alocpy(m_instruction, instruction);
      }
      if (!istr)
      {
         m_state = "Perishable console date entry failed!";
      }
      return istr;
   }
}