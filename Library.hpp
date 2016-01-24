/******************************************************************************
**Author: Niza Volair (code given with assignment)
**Date: 03-11-15
**Description: This is th header file for the library class
******************************************************************************/
#ifndef LIBRARY_HPP
#define LiBRARY_HPP

#include <string>
#include <vector>

class Patron;   //forward declaration
class Book;

class Library
{
private:
   std::vector<Book> holdings;
   std::vector<Patron> members;
   int currentDate;
public:
   Library();
   void addBook();
   void addMember();
   void checkOutBook(std::string patronID, std::string bookID);
   void returnBook(std::string bookID);
   void requestBook(std::string PatronID, std::string bookID);
   void incrementCurrentDate();
   void payFine(std::string patronID, double payment);
   void viewPatronInfo(std::string patronID);
   void viewBookInfo(std::string bookID);
   int validateBook(std::string bookID);
   int validatePatron(std::string patronID);
};
#endif




