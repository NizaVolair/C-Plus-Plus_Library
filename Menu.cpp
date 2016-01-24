/******************************************************************************
**Author: Niza Volair
**Date: 03-15-2015
**Description: This is the menu of the library system 
******************************************************************************/
#include "Patron.hpp"
#include "Book.hpp"
#include "Library.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{  //declare user variables
   std::string userIdCode, userTitle, userAuthor, userIdNum, userName;
   double userFineAmt = 0;
   Library library;
   int choice = 0;

   do
   {  //display library menu
      std::cout << "~~~~~~~Library Menu~~~~~~~\n\n";
      std::cout << "1) Add Book\n";
      std::cout << "2) Add Member\n";
      std::cout << "3) Check Out Book\n";
      std::cout << "4) Return Book\n";
      std::cout << "5) Request Book\n";
      std::cout << "6) Increment Current Date\n";
      std::cout << "7) Pay Fine\n";
      std::cout << "8) View Patron Information\n";
      std::cout << "9) View Book Information\n";
      std::cout << "10) Exit Menu\n" << std::endl;
 
      //get choice from user
      std::cout << "Enter choice: ";
      std::cin >> choice;      
      std::cout << std::endl;

      if(choice != 10)
      {  switch(choice)
         {  case 1: //add book to holdings
                    library.addBook();
                    std::cout << std::endl;
                    break;
            case 2: //add patron to members
                    library.addMember();
                    std::cout << std::endl;
                    break;
            case 3: //check out book to a specific patron
                    std::cout << "Enter Patron ID: ";
                    std::cin >> userIdNum;
                    std::cout << "Enter Book ID: ";
                    std::cin >> userIdCode;
                    library.checkOutBook(userIdNum, userIdCode);
                    std::cout << std::endl;
                    break;
            case 4: //return a book from being checked out
                    std::cout << "Enter Book ID: ";
                    std::cin >> userIdCode;
                    library.returnBook(userIdCode);
                    std::cout << std::endl;
                    break;
            case 5: //request a book for a specific member
                    std::cout << "Enter Patron ID: ";
                    std::cin >> userIdNum;
                    std::cout << "Enter Book ID: ";
                    std::cin >> userIdCode;
                    library.requestBook(userIdNum, userIdCode);
                    std::cout << std::endl;
                    break;
            case 6: //increment current date
                    library.incrementCurrentDate();
                    std::cout << std::endl;
                    break;
            case 7: //pay fine for specific member
                    std::cout << "Enter Patron ID: ";
                    std::cin >> userIdNum;
                    std::cout << "Enter Payment Amount: ";
                    std::cin >> userFineAmt;
                    library.payFine(userIdNum, ( - userFineAmt)); 
                    std::cout << std::endl;
                    break;
            case 8: //view patron info
                    std::cout << "Enter Patron ID: ";
                    std::cin >> userIdNum;
                    library.viewPatronInfo(userIdNum);
                    std::cout << std::endl;
                    break;
            case 9: //view book info
                    std::cout << "Enter Book ID: ";
                    std::cin >> userIdCode;
                    library.viewBookInfo(userIdCode);
                    std::cout << std::endl;
                    break;
        }
      } 
   } while(choice != 10);

   return 0;
}
