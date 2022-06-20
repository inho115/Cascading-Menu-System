#include "Date.h"
using namespace std;
namespace sdds {
   bool Date::validate()
   {
      bool result = true;
      if (m_year < 2022 || m_year > maxYearValue)
      {
         State = "Invalid year in date";
         State = 1;
         result = false;
      }
      if (result != false && (m_month < 1 || m_month > 12))
      {
         State = "Invalid month in date";
         State = 2;
         result = false;
      }
      if (result != false && (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year))) {
         State = "Invalid day in date";
         State = 3;
         result = false;
      }
      if (m_day == 0 && m_month == 0 && m_year == 0)
      {
         State = "Invalid date value";
         State = 0;
         result = false;
      }
      if (result == true)
      {
         State.clear();
      }
      return result;
   }
   int Date::uniqueDateValue()
   {
      return m_year * 372 + m_month * 31 + m_day;
   }
   Date::Date()
   {
      ut.testMode(false);
      ut.getSystemDate(&m_year, &m_month, &m_day);
      m_month = 3;
      m_day = 31;
   }
   Date::Date(const Date& copy)
   {
      operator=(copy);
   }
   Date& Date::operator=(const Date& copy)
   {
      if (this != &copy)
      {
         m_day = copy.m_day;
         m_month = copy.m_month;
         m_year = copy.m_year;
      }
      return *this;
   }
   Date::Date(int year, int month, int date)
   {
      m_year = year;
      m_month = month;
      m_day = date;
   }
   Date::~Date()
   {
      State.clear();
   }
   bool Date::operator==(Date& equalTo)
   {
      bool result = false;
      if (uniqueDateValue() == equalTo.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   bool Date::operator!=(Date& notEqualTo)
   {
      bool result = false;
      if (uniqueDateValue() != notEqualTo.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   bool Date::operator<(Date& lessThan)
   {
      bool result = false;
      if (uniqueDateValue() < lessThan.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   bool Date::operator>(Date& greaterThan)
   {
      bool result = false;
      if (uniqueDateValue() > greaterThan.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   bool Date::operator<=(Date& lessEqual)
   {
      bool result = false;
      if (uniqueDateValue() <= lessEqual.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   bool Date::operator>=(Date& greatEqual)
   {
      bool result = false;
      if (uniqueDateValue() >= greatEqual.uniqueDateValue())
      {
         result = true;
      }
      return result;
   }
   Status& Date::state()
   {
      return State;
   }
   Date& Date::formatted(bool value)
   {
      m_formatted = value;
      return *this;
   }
   Date::operator bool() const
   {
      return this->State;
   }
   std::ostream& Date::write(std::ostream& ostr, bool value = true) const
   {
      if (m_formatted == true && value == true)
      {
         ostr << m_year << "/";
         ostr.setf(ios::right);
         ostr.fill('0');
         ostr.width(2);
         ostr << m_month;
         ostr << "/";
         ostr.fill('0');
         ostr.width(2);
         ostr << m_day;
         ostr.unsetf(ios::right);
      }
      else
      {
         ostr << m_year - 2000;
         ostr.width(2);
         ostr.fill('0');
         ostr << m_month << m_day;
      }
      return ostr;
   }
   std::istream& Date::read(std::istream& istr)
   {
      int date;
      istr >> date;
      if (date > 0 && date > 999 && date < 9999)
      {
         ut.getSystemDate(&m_year);
         m_month = date / 100;
         m_day = date % 100;
      }
      if (date > 0 && date > 100000 && date < 999999)
      {
         m_year = (date / 10000) + 2000;
         date %= 10000;
         m_month = date / 100;
         m_day = date % 100;
      }
      if (date == 0)
      {
         m_year = 0;
         m_month = 0;
         m_day = 0;
      }
      if (date > 0 && date < 99)
      {
         ut.getSystemDate(&m_year);
         m_month = 13;
         m_day = 1;
      }
      if (validate() == false)
      {
         istr.setstate(ios::badbit);
      }
      return istr;
   }
   std::ostream& operator<<(std::ostream& ostr, const Date& dt)
   {
      dt.write(ostr);
      return ostr;
   }
   std::istream& operator>>(std::istream& istr, Date& dt)
   {
      dt.read(istr);
      return istr;
   }
}