#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Status.h"
#include "Utils.h"
#include <ctime>
#include <iostream>
namespace sdds {
   const int maxYearValue = 2030;
   class Date {
      int m_year = 0;
      int m_month = 0;
      int m_day = 0;
      Status State{};
      bool m_formatted = true;
      bool validate();
      int uniqueDateValue();
   public:
      // Rule of three
      Date();
      Date(const Date& copy);
      Date& operator=(const Date& copy);
      Date(int year, int month, int date);
      ~Date();
      bool operator==(Date& equalTo);
      bool operator!=(Date& notEqualTo);
      bool operator<(Date& lessThan);
      bool operator>(Date& greaterThan);
      bool operator<=(Date& lessEqual);
      bool operator>=(Date& greatEqual);
      Status& state();
      Date& formatted(bool value);
      operator bool() const;
      std::ostream& write(std::ostream& ostr, bool value) const;
      std::istream& read(std::istream& istr);
   };
   std::ostream& operator<<(std::ostream& ostr, const Date& dt);
   std::istream& operator>>(std::istream& istr, Date& dt);
}
#endif