#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
using namespace std;
namespace sdds {
   // The ut object of type Utils that is accessible to any file including "Utils.h" to call the Utils
   // methods
   Utils ut;

   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::alocpy(char*& destination, const char* source)
   {
      delete[] destination;
      destination = nullptr;
      if (source != nullptr)
      {
         destination = new char[strlen(source) + 1];
         strcpy(destination, source);
      }
   }
   int Utils::getint(const char* prompt) /////////////////
   {
      int integer = 0;
      int flag = 0;
      if (prompt != nullptr)
      {
         cout << prompt << endl;
      }
      while (flag == 0)
      {
         cin >> integer;
         if (!cin)
         {
            cout << "Invalid Integer, retry: ";
            cin.setstate(ios::badbit);
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else
         {
            flag = 1;
         }
      }
      return integer;
   }
   int Utils::getint(int min, int max, const char* prompt, const char* errMes) ////////
   {
      int integer = 0;
      int flag = 0;
      while (flag == 0)
      {
         integer = getint();
         if (!(integer >= min && integer <= max))
         {
            if (errMes != nullptr)
            {
               cout << errMes << ", retry: ";
               cin.setstate(ios::badbit);
            }
            else
            {
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               cin.setstate(ios::badbit);
            }
            if (!cin)
            {
               cin.clear();
               cin.ignore(1000, '\n');
            }
         }
         else
         {
            flag = 1;
            cin.ignore(1000, '\n');
         }
      }
      return integer;
   }
   double Utils::getdouble(const char* prompt)
   {
      double integer = 0;
      int flag = 0;
      if (prompt != nullptr)
      {
         cout << prompt << endl;
      }
      while (flag == 0)
      {
         cin >> integer;
         if (!cin)
         {
            cout << "Invalid number, retry: ";
            cin.setstate(ios::badbit);
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else
         {
            flag = 1;
         }
      }
      return integer;
   }
   double Utils::getdouble(double min, double max, const char* prompt, const char* errMes)
   {
      double integer = 0;
      int flag = 0;
      while (flag == 0)
      {
         integer = getdouble();
         if (!(integer >= min && integer <= max))
         {
            if (errMes != nullptr)
            {
               cout << errMes << ", retry: ";
               cin.setstate(ios::badbit);
            }
            else
            {
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               cin.setstate(ios::badbit);
            }
            if (!cin)
            {
               cin.clear();
               cin.ignore(1000, '\n');
            }
         }
         else
         {
            flag = 1;
            cin.ignore(1000, '\n');
         }
      }
      return integer;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if (day) *day = sdds_testDay;
         if (mon) *mon = sdds_testMon;
         if (year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
}