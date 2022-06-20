#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
#include "Utils.h"

namespace sdds 
{
   class Status 
   {
      char* m_description{};
      int m_statusCode = 0;
   public:
      // Rule of Three
      Status(const char* description = nullptr);
      Status(const Status& copyFrom);
      ~Status();
      Status& operator=(const char* description);
      Status& operator=(int code);
      operator int() const;
      operator const char* () const;
      operator bool() const;
      Status& clear();
   };
   std::ostream& operator<<(std::ostream& ostr, const Status& sts);
}
#endif