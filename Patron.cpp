/******************************************************************************
**Autor: Niza Volair
**Date: 03-11-15
**Description: This is the implimentation for the Patron class
******************************************************************************/
#include "Patron.hpp"
#include "Book.hpp"

#include <iostream>
#include <string>
#include <vector>

Patron::Patron()
{  fineAmount = 0.00;
   setIdNum("");
   setName("");
   checkedOutBooks.reserve(100);
}
Patron::Patron(std::string idnumber, std::string pName)
{  fineAmount = 0.00;
   setIdNum(idnumber);
   setName(pName);  
   checkedOutBooks.reserve(100);
}
void Patron::setIdNum(std::string idnumber)
{  idNum = idnumber;
}
std::string Patron::getIdNum()
{  return idNum;
}
void Patron::setName(std::string pName)
{  name = pName;
}
std::string Patron::getName()
{  return name;   
}
double Patron::getFineAmount()
{  return fineAmount;
}
/******************************************************************************
**Descriptions: shows the currently checked out Books
**Parameters: no parameters
******************************************************************************/
std::vector<Book*> Patron::getCheckedOutBooks()
{  return checkedOutBooks;
}
/******************************************************************************
**Descriptions: adds the specific Book to checkedOutBooks
**Parameters: takes a book object as a parameter
******************************************************************************/
void Patron::addBook(Book* b)
{  checkedOutBooks.push_back(b);  
}
/******************************************************************************
**Descriptions: removes the specific Book from checkedOutBooks
**Parameters: takes a book object as a parameter
******************************************************************************/
void Patron::removeBook(Book* b)
{  for(int i = 0; i < checkedOutBooks.size() ; i++)
   { if(checkedOutBooks[i]  == b)
     {  checkedOutBooks.erase(checkedOutBooks.begin() + i);
        std::cout << " has been removed from checked out book list.\n";
        i = checkedOutBooks.size();
     }
   }
}
/******************************************************************************
**Descriptions: increases and decreases the find amount
**Parameters: takes a double amount as a parameter
******************************************************************************/
void Patron::amendFine(double amount)
{  fineAmount += amount;
}

