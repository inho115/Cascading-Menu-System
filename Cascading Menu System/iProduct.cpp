#include "iProduct.h"

using namespace std;
namespace sdds 
{
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