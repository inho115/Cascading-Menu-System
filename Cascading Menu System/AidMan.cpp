#include "AidMan.h"
using namespace std;
namespace sdds 
{
   unsigned int AidMan::menu() const
   {
      int num = 0;
      cout << "Aid Management System\n";
      cout << "Date: " << Date() << endl;;
      if (m_fileName != nullptr)
      {
         cout << "Data file: " << m_fileName << endl;;
      }
      else
      {
         cout << "Data file: No file\n";
      }
      cout << "---------------------------------\n";
      num = m_mainMenu.run();
      return num;
   }
   void AidMan::dealloc()
   {
      for (int i = 0; i < m_numItem; i++)
      {
         delete m_item[i];
         m_item[i] = nullptr;
      }
      delete[] m_fileName;
      m_fileName = nullptr;
      m_numItem = 0;
   }

   std::ofstream& AidMan::write(std::ofstream& ofstr) const
   {
      int counter = 0;
      char str[18] = "shippingOrder.txt";
      ofstream fout(str);
      fout << "Shipping Order, Date: " << Date() << "\n";
      fout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
      fout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      for (int i = 0; i < m_numItem; i++)
      {
         if (m_item[i]->qtyNeeded() == m_item[i]->qty())
         {
            counter++;
            fout << "   " << counter << " | ";
            m_item[i]->linear(true);
            m_item[i]->display(fout);
            fout << "\n";
         }
      }
      fout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      return ofstr;
   }

   AidMan::AidMan()
   {
      m_fileName = nullptr;
      m_mainMenu = 7;
      m_mainMenu = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n";
   }
   AidMan::~AidMan()
   {
      dealloc();
   }
   void AidMan::run()
   {
      int flag = 0;
      int num = 0;
      int selection = 0;
      int right = 0;
      int left = 0;
      int counter = 0;
      while (flag == 0)
      {
         num = menu();
         if (num != 0 && m_fileName == nullptr)
         {
            num = 7;
         }
         switch (num)
         {
         case 0:
            cout << "Exiting Program!\n";
            save(f);
            flag = 1;
            break;
         case 1:
            cout << "\n****List Items****\n";
            selection = list();
            if (selection > 0)
            {
               cout << "Enter row number to display details or <ENTER> to continue:\n";
               cout << "> ";
               if (cin.peek() != '\n')
               {
                  selection = ut.getint();
                  m_item[selection - 1]->linear(false);
                  m_item[selection - 1]->display(cout);
               }
               cout << endl;
            }
            break;
         case 2:
            cout << "\n****Add Item****\n";
            if (!(m_numItem < sdds_max_num_items))
            {
               cout << "Database full!\n";
            }
            else
            {
               cout << "1- Perishable\n";
               cout << "2- Non-Perishable\n";
               cout << "-----------------\n";
               cout << "0- Exit\n";
               cout << "> ";
               selection = ut.getint(0, 2);
               switch (selection)
               {
               case 1:
                  newItem(1);
                  break;
               case 2:
                  newItem(2);
                  break;
               case 0:
                  cout << "Aborted!\n";
                  break;
               }
            }
            break;
         case 3:
            cout << "\n****Remove Item****\n";
            find(3);
            break;
         case 4:
            cout << "\n****Update Quantity****\n";
            find(4);
            break;
         case 5:
            cout << "\n****Sort****\n";
            iProduct* temp;
            for (int i = 0; i < m_numItem; i++)
            {
               for (int j = i + 1; j < m_numItem; j++)
               {
                  left = m_item[i]->qtyNeeded() - m_item[i]->qty();
                  right = m_item[j]->qtyNeeded() - m_item[j]->qty();
                  if (left < right)
                  {
                     temp = m_item[i];
                     m_item[i] = m_item[j];
                     m_item[j] = temp;
                  }
               }
            }
            cout << "Sort completed!\n\n";
            break;
         case 6:
            cout << "\n****Ship Items****\n";
            write(f);
            for (int i = 0; i < m_numItem; i++)
            {
               if (m_item[i]->qtyNeeded() == m_item[i]->qty())
               {
                  remove(i);
                  counter++;
               }
            }
            cout << "Shipping Order for " << counter << " times saved!\n\n";
            break;
         case 7:
            load(fin);
            cout << m_numItem << " records loaded!\n";
            cout << endl;
            break;
         }
      }
   }
   std::ofstream& AidMan::save(std::ofstream& ofstr) const
   {
      if (m_fileName != nullptr)
      {
         ofstream out(m_fileName);
         for (int i = 0; i < m_numItem; i++)
         {
            m_item[i]->save(out);
         }
      }
      return ofstr;
   }
   std::ifstream& AidMan::load(std::ifstream& ifstr)
   {
      int selection = 0;
      char next{};
      int empty = 0;
      char name[50]{};
      bool flag = true;
      char zero = '0';
      char four = '4';
      char nine = '9';
      dealloc();
      cout << "\n****New/Open Aid Database****\n";
      cout << "Enter file name: ";
      cin.get(name, 50, '\n');
      ut.alocpy(m_fileName, name);
      ifstream fin(m_fileName); // reading
      fin.seekg(0);
      if (fin.fail())           // if reading fails
      {
         cout << "Failed to open " << m_fileName << " for reading!\n";
         cout << "Would you like to create a new data file?\n";
         cout << "1-Yes!\n";
         cout << "0-Exit\n";
         cout << ">";
         selection = ut.getint(0, 1);
         cout << "\n";
         if (selection == 1)
         {
            cout << "***New/Open Aid Database***";
            cout << "Enter file name: ";
            cin.get(name, 50, '\n');
            cin.ignore('\n');
            ut.alocpy(m_fileName, name);
            ofstream file(m_fileName);
         }
      }
      else
      {
         while (flag)
         {
            for (int i = 0; i < sdds_max_num_items; i++)
            {
               if (m_item[i] == nullptr)
               {
                  empty = i;
                  i = sdds_max_num_items;
               }
            }
            next = fin.peek();
            if (!(next > zero && next < nine))
            {
               flag = false;
            }
            else
            {
               if (next < zero || next == '\0')
               {
                  ifstr.setstate(ios::badbit);
               }
               if (next > zero && next < four)
               {
                  m_item[empty] = new Perishable{};
                  m_item[empty]->load(fin);
                  if (m_item[empty]->operator bool())
                  {
                     m_numItem += 1;
                  }
                  else
                  {
                     delete m_item[empty];
                  }
               }
               else if (next >= four && next <= nine)
               {
                  m_item[empty] = new Item{};
                  m_item[empty]->load(fin);
                  if (m_item[empty]->operator bool())
                  {
                     m_numItem += 1;
                  }
                  else
                  {
                     delete m_item[empty];
                  }
               }
            }

         }
      }
      return ifstr;
   }
   int AidMan::list(const char* sub_desc)
   {
      int number = 0;
      cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      if (sub_desc == nullptr)
      {
         for (int i = 0; i < m_numItem; i++)
         {
            cout << "   " << i + 1 << " | ";
            m_item[i]->linear(true);
            m_item[i]->display(cout);
            cout << "\n";
            number++;
         }
      }
      else
      {
         for (int i = 0; i < m_numItem; i++)
         {
            if (m_item[i]->operator==(sub_desc))
            {
               m_item[i]->linear(true);
               m_item[i]->display(cout);
               number++;
            }
         }
      }
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      if (number == 0)
      {
         cout << "The list is empty!\n";
      }
      return number;
   }
   int AidMan::search(int sku) const
   {
      int position = -1;
      for (int i = 0; i < m_numItem; i++)
      {
         if (m_item[i]->operator==(sku))
         {
            position = i;
            i = m_numItem;
         }
      }
      return position;
   }
   void AidMan::remove(int index)
   {
      delete m_item[index];
      for (int i = index; i < m_numItem; i++)
      {
         m_item[i] = m_item[i + 1];
      }
      m_numItem--;
   }
   void AidMan::find(int value)
   {
      int num = 0;
      int number = 0;
      int choice = 0;
      int selection = 0;
      char description[50]{};
      cout << "Item description: ";
      cin.get(description, 50, '\n');
      cin.clear();
      cin.ignore(1000, '\n');
      cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      for (int i = 0; i < m_numItem; i++)
      {
         if (m_item[i]->operator==(description))
         {
            cout << "   " << i + 1 << " | ";
            m_item[i]->linear(true);
            m_item[i]->display(cout);
            cout << "\n";
         }
      }
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
      cout << "Enter SKU: ";
      num = ut.getint(10000, 99999);
      selection = search(num);
      if (selection != -1)
      {
         if (value == 3)
         {
            cout << "Following item will be removed: \n";
            m_item[selection]->linear(false);
            m_item[selection]->display(cout);
            cout << endl;
            cout << "Are you sure?\n";
            cout << "1- Yes!\n";
            cout << "0- Exit\n";
            cout << "> ";
            choice = ut.getint(0, 1);
            if (choice == 1)
            {
               remove(selection);
               cout << "Item removed!\n\n";
            }
            else
            {
               cout << "Aborted!\n\n";
            }
         }
         if (value == 4)
         {
            cout << "1- Add\n";
            cout << "2- Reduce\n";
            cout << "0- Exit\n";
            cout << "> ";
            choice = ut.getint(0, 2);
            if (choice == 1)
            {
               if (m_item[selection]->qty() == m_item[selection]->qtyNeeded())
               {
                  cout << "Quantity Needed already fulfilled!\n\n";
               }
               else
               {
                  cout << "Quantity to add: ";
                  number = ut.getint(1, m_item[selection]->qtyNeeded());
                  m_item[selection]->operator+=(number);
                  cout << number << " items added!\n\n";
               }
            }
            else if (choice == 2)
            {
               if (m_item[selection]->qty() == 0)
               {
                  cout << "Quantity on hand is zero!\n\n";
               }
               else
               {
                  cout << "Quantity to reduce: ";
                  number = ut.getint(1, m_item[selection]->qty());
                  m_item[selection]->operator-=(number);
                  cout << number << " items removed!\n\n";
               }
            }
            else
            {
               cout << "Aborted!\n\n";
            }
         }
      }
      else
      {
         cout << "SKU not found!";
      }
   }
   void AidMan::newItem(int value)
   {
      int num = 0;
      if (value == 1)
      {
         m_item[m_numItem] = new Perishable{};
      }
      if (value == 2)
      {
         m_item[m_numItem] = new Item{};
      }
      num = m_item[m_numItem]->readSku(cin);
      if (search(num) != -1)
      {
         cout << "Sku: " << "num is already in the system, try updating quantity instead.\n";
         delete m_item[m_numItem];
      }
      else
      {
         m_item[m_numItem]->read(cin);
         if (m_item[m_numItem]->operator bool())
         {
            m_numItem++;
         }
         else
         {
            delete m_item[m_numItem];
         }
      }
      cout << endl;
   }
}