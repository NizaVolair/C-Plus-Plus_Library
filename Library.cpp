/******************************************************************************
**Autor: Niza Volair
**Date: 03-11-15
**Description: This is the implimentation for the Library class
******************************************************************************/
#include "Library.hpp"
#include "Book.hpp"
#include "Patron.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

Library::Library()
{  currentDate = 0;
   holdings.reserve(100);
   members.reserve(100);
}
/******************************************************************************
**Descriptions: adds the specific Book to holdings
**Parameters: no parameters, prompts for all info
******************************************************************************/
void Library::addBook()
{  //define and get user variables
   Book book;
   string title;
   string author;
   string idcode;
   cout << "Enter the title: ";
   cin.get();
   getline(cin, title);
   cout << "Enter the author: ";
   getline(cin, author);
   cout << "Enter the ID code: ";
   cin >> idcode;
   //validate book
   int bIndex = (validateBook(idcode));
   if(bIndex != -1)
   {  cout << "Invalid Book ID\n";
   }
   else
   {  //add book to holdings
      book.setIdCode(idcode);
      book.setTitle(title);
      book.setAuthor(author);
      book.setLocation(ON_SHELF);
      holdings.push_back(book);
      cout << title << " has been added to the library holdings.\n";
   }
}
/******************************************************************************
**Descriptions: adds the specific Patron to members
**Parameters: no parameters, prompts for all info
******************************************************************************/
void Library::addMember()
{  //define and get user variables
   Patron patron;
   string pName;
   string pIdNum;
   cout << "Enter the name: ";
   cin.get();
   getline(cin, pName);
   cout << "Enter the ID number: ";
   cin >> pIdNum;   
   //validate patron
   int pIndex = (validatePatron(pIdNum));
   if(pIndex != -1)
   {  cout << "Invalid Patron ID\n";
   }
   else
   {  //add patron to members
      patron.setName(pName);
      patron.setIdNum(pIdNum);
      members.push_back(patron);
      cout << pName << " has been added to the library members.\n";
   }
}
/******************************************************************************
**Descriptions: checks out Books to patrons
**Parameters: patron id string, book id string
******************************************************************************/
void Library::checkOutBook(string pID, string bID)
{  //validate book and patron
   int pIndex = (validatePatron(pID));
   int bIndex = (validateBook(bID));
   if(pIndex == -1)
   {  cout << "Invalid Patron\n";
   }
   if(bIndex == -1)
   {  cout << "Invalid Book\n";
   }
   if(pIndex != -1 && bIndex != -1)
   {  //check is book is in library 
      if(holdings[bIndex].getLocation() == CHECKED_OUT)
      {  cout << "This book is already checked out.\n";
      }
      else
      {  //ensure book is not on request by another patron
         if(holdings[bIndex].getRequestedBy() == NULL || 
         holdings[bIndex].getRequestedBy() == &members[pIndex])
         {  //set checked out by to NULL in case it's on request by this patron
            holdings[bIndex].setCheckedOutBy(NULL);
            //check out book to patron
            members[pIndex].addBook(&holdings[bIndex]);
            holdings[bIndex].setLocation(CHECKED_OUT);
            holdings[bIndex].setDateCheckedOut(currentDate);
            cout << holdings[bIndex].getTitle() << " has been checked out to "
                 << members[pIndex].getName() << ".\n";
         }
         else
         {  //book is on request by another patron
            cout << "Book is requested by another patron.\n";  
         }
      } 
   }
}
/******************************************************************************
**Descriptions: returns a specific Book to holdings
**Parameters: book id string
******************************************************************************/
void Library::returnBook(string bID)
{  //validate book
   int bIndex = (validateBook(bID));
   if(bIndex == -1)
   {  cout << "Invalid Book\n";
   }
   //ensure book has been checked out
   else if(holdings[bIndex].getLocation() == ON_SHELF || 
      holdings[bIndex].getLocation() == ON_HOLD_SHELF)
   {  cout << "Book has not been checked out\n";
   }
   else  
   {  //return book to library
      cout << holdings[bIndex].getTitle() << " has been returned.\n";
      //delete book from member book pointer vector with for loop to find
      //member and patron remove book function
      cout << holdings[bIndex].getTitle();
      for(int i = 0; i < members.size(); i++)
      {  vector<Book*> bookVec= members[i].getCheckedOutBooks();
         for(int j = 0; j < bookVec.size(); j++)
         {  if((holdings[bIndex].getTitle()) == (bookVec[j]->getTitle()))
            {   members[i].removeBook(&holdings[bIndex]);
            }
         }
      }
      holdings[bIndex].setCheckedOutBy(NULL); 
      //put book on shelf if not requested
      if(holdings[bIndex].getRequestedBy() == NULL)
      {  holdings[bIndex].setLocation(ON_SHELF);
         cout << holdings[bIndex].getTitle() << " is now on the shelf.\n"; 
      }
      else
      {  //put on hold shelf if requested
         holdings[bIndex].setLocation(ON_HOLD_SHELF);
         cout << holdings[bIndex].getTitle() << " is now on the hold shelf.\n";
      } 
   } 

}
/******************************************************************************
**Descriptions: requests a Books for Patrons
**Parameters: no parameters, prompts for all info
******************************************************************************/
void Library::requestBook(string pID, string bID)
{  //validate patron and book
   int bIndex = (validateBook(bID));
   int pIndex = (validatePatron(pID));
   if(bIndex == -1)
   {  cout << "Invalid Book\n";
   }
   if(pIndex == -1)
   {  cout << "Invalid Patron\n";
   }
   if(pIndex != -1 && bIndex != -1)
   {  //ensure book is not already on request
      if(holdings[bIndex].getRequestedBy() == NULL)
      {  holdings[bIndex].setRequestedBy(&members[pIndex]);
         cout << holdings[bIndex].getTitle() << " is now on request for ";
         cout << members[pIndex].getName() << ".\n";                
         //if book is in library put on hold shelf
         if(holdings[bIndex].getLocation() == ON_SHELF)
         {  holdings[bIndex].setLocation(ON_HOLD_SHELF);
            cout << holdings[bIndex].getTitle();
            cout << "'s location is now on the hold shelf.\n";
         }
         else
         {  //book is checked out place on hold shelf when returned
            cout << holdings[bIndex].getTitle();
            cout << "'s location is currently checked out.\n";
            cout << "It will be placed on the hold shelf when returned\n";
         }
      }
      else 
      {  //book is already requested
         cout << "Book already requested by another patron\n";
      }
   } 
}
/******************************************************************************
**Descriptions: increases Patron's fine by 10 cents for any overdue Book 
**Parameters: no parameters
******************************************************************************/
void Library::incrementCurrentDate()
{ //add 1 to date
  currentDate++; 
  cout << "Current date is: " << currentDate << endl;
  //create local book pointer vector and book and fine amount
  vector<Book*> bookVec;
  Book book;
  double fine = 0.10;
  //create for loop to increment fine amounts for all checked out books
  for( int i = 0; i < members.size(); i++)
  {  bookVec = members[i].getCheckedOutBooks();
     for(int j = 0; j < bookVec.size(); j++)
     {  if((currentDate - (bookVec[j]-> getDateCheckedOut())) >
           book.CHECK_OUT_LENGTH)
        {  members[i].amendFine(fine);
        }
     }
  }
}
/******************************************************************************
**Description: updates fines and prints message telling the current fine amount
**Parameters: string for patron id and double for the fine amount
******************************************************************************/
void Library::payFine(string pID, double fineAmt)
{ //validate patron
  int pIndex = validatePatron(pID);
  if(pIndex == -1)
  {  cout << "Invalid Patron\n";
  }
  else
  {  //show current fine amount if greater than 0
     members[pIndex].amendFine(fineAmt);
     cout << "The current fine amount is: $";
     if(members[pIndex].getFineAmount() >= 0.00)
     {  cout << fixed << setprecision(2) 
             << members[pIndex].getFineAmount() << endl;
     }
     else
     {  //if result is negative display 0
        cout << "$0.00" << endl;
     }      
  }
}
/******************************************************************************
**Descriptions: prints Patrons id, books checked out, and current fines
**Parameters: string for patron id
******************************************************************************/
void Library::viewPatronInfo(string pID)
{ //validate patron
  int pIndex = validatePatron(pID);
  if(pIndex == -1)
  {  cout << "Invalid Patron\n";
  }
  else
  {  //display patron info
     cout << "ID Number: " << members[pIndex].getIdNum() << endl;
     cout << "Name: " << members[pIndex].getName() << endl;
     vector<Book*> bookVec= members[pIndex].getCheckedOutBooks();
     //create a for loop for all books
     for( int i = 0; i < bookVec.size(); i++)
     {  cout << "Book Title: ";
        cout << bookVec.at(i)->getTitle() << endl;
     }
     cout << "Fine Amount: $";
     //display fine amount greater then or equal to 0
     if(members[pIndex].getFineAmount() >= 0.00)
     {  cout << fixed << setprecision(2)
             << members[pIndex].getFineAmount() << endl;
     }
     else
     {  //don't display negative fine amounts
        cout << "$0.00" << endl;
     }
  }
}
/******************************************************************************
**Descriptions: prints Book id, title, author, location, name of requesting
**Patron, name of checked out Patron, number of days left until it's due
**Parameters: string for book id
******************************************************************************/
void Library::viewBookInfo(string bID)
{ //validate book 
  int bIndex = validateBook(bID);
  if(bIndex == -1)
  {  cout << "Invalid Book\n";
  }
  //display book info
  else
  {  cout << "ID Code: " << holdings[bIndex].getIdCode() << endl;
     cout << "Title: " << holdings[bIndex].getTitle() << endl;
     cout << "Author: " << holdings[bIndex].getAuthor() << endl;
     cout << "Location: ";
     if(holdings[bIndex].getLocation() == ON_SHELF)
     {  cout << "on shelf\n";
     }
     else if(holdings[bIndex].getLocation() == ON_HOLD_SHELF)
     {  cout << "on hold shelf\n";
     } 
     else if(holdings[bIndex].getLocation() == CHECKED_OUT)
     {  cout << "checked out by ";
        for(int i = 0; i < members.size(); i++)
        {  vector<Book*> bookVec= members[i].getCheckedOutBooks();
           for(int j = 0; j < bookVec.size(); j++)
           {  if((holdings[bIndex].getTitle()) == (bookVec[j]->getTitle()))
              {  cout << members[i].getName() << endl;
              }
           }
        }
        //if book is not overdue display days until due which is current date
        // minus check out date subtracted from the check out length
        cout<< "Number of days until due date: ";      
        Book book;
        if(currentDate - holdings[bIndex].getDateCheckedOut() < 
           book.CHECK_OUT_LENGTH)
        {  cout << (book.CHECK_OUT_LENGTH - (currentDate -
                    holdings[bIndex].getDateCheckedOut())) << endl;
        }   
        else 
        {  //book is overdue if number is greater than check out length
           cout << "Overdue\n" << endl;
        } 
     }
  }
}
/******************************************************************************
**Descriptions: validates the existance of a Book
**Parameters: string for the book id
******************************************************************************/
int Library::validateBook(string bID)
{  //initialize result to -1
   int result = -1;
   //if book is in holdings return it's index
   for(int i = 0; i < holdings.size(); i++)
   {  if(holdings[i].getIdCode() == bID)
      { result = i;
      }
   }
   return result;
}
/******************************************************************************
**Descriptions: validates the existance of a Patron
**Parameters: string for the patron id
******************************************************************************/
int Library::validatePatron(string pID)
{  //intialize result to -1
   int result = -1;
   //if patron is in members return it's index
   for(int i = 0; i < members.size(); i++)
   {  if(members[i].getIdNum() == pID)
      { result = i;
      }
   }
   return result;
}
