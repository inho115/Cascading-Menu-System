#include "Status.h"
using namespace std;
namespace sdds {
   Status::Status(const char* description)
   {
      ut.alocpy(m_description, description);
      m_statusCode = 0;
   }
   Status::Status(const Status& copyFrom)
   {
      if (copyFrom.operator bool() == false) {
         operator=(copyFrom.m_description);
         operator=(copyFrom.m_statusCode);
      }
   }
   Status::~Status()
   {
      clear();
   }

   Status& Status::operator=(const char* description)
   {
      ut.alocpy(m_description, description);
      return *this;
   }

   Status& Status::operator=(int code)
   {
      m_statusCode = code;
      return *this;
   }

   Status::operator int() const
   {
      return m_statusCode;
   }
   Status::operator const char* () const
   {
      return m_description;
   }
   Status::operator bool() const
   {
      bool result = false;
      if (m_description == nullptr)
      {
         result = true;
      }
      return result;
   }
   Status& Status::clear()
   {
      delete[] m_description;
      m_description = nullptr;
      m_statusCode = 0;
      return *this;
   }
   ostream& operator<<(ostream& ostr, const Status& sts)
   {
      if (sts.operator bool() == false)
      {
         if (sts.operator int() != 0)
         {
            ostr << "ERR#" << sts.operator int() << ": ";
         }
         ostr << sts.operator const char* ();
      }
      return ostr;
   }
}