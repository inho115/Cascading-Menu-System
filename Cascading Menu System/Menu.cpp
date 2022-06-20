#include "Menu.h"

using namespace std;
namespace sdds 
{
   void Menu::dealloc()
   {
      delete[] m_option;
      m_option = nullptr;
   }
   Menu::Menu(unsigned int number, const char* text)
   {
      if (number > maxOption || text == nullptr)
      {
         m_numOption = 0;
         dealloc();
      }
      else
      {
         m_numOption = number;
         ut.alocpy(m_option, text);
      }
   }
   Menu::~Menu()
   {
      dealloc();
   }
   Menu& Menu::operator=(const char* menuContent)
   {
      ut.alocpy(m_option, menuContent);
      return *this;
   }
   Menu& Menu::operator=(unsigned int num)
   {
      m_numOption = num;
      return *this;
   }
   unsigned int Menu::run() const
   {
      unsigned int number = 0;
      cout << m_option << "0- Exit\n";
      cout << "> ";
      number = ut.getint(0, m_numOption);
      return number;
   }
}