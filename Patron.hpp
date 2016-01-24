/******************************************************************************
**Author: Niza Volair (code given with assignment)
**Date: 03-11-15
**Description: This is th header file for the patron class
******************************************************************************/
#ifndef PATRON_HPP
#define PATRON_HPP

#include <iostream>
#include <string>
#include <vector>

class Book;   //forward declaration

class Patron
{
private:
   std::string idNum;
   std::string name;
   std::vector<Book*> checkedOutBooks;
   double fineAmount;
public:
   Patron();
   Patron(std::string idn, std::string n);
   void setIdNum(std::string idn);
   void setName(std::string n);
   std::string getIdNum();
   std::string getName();
   std::vector<Book*> getCheckedOutBooks();
   void addBook(Book* b);
   void removeBook(Book* b);
   double getFineAmount();
   void amendFine(double amount);
};

#endif
