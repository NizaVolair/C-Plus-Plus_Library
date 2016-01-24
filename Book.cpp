/******************************************************************************
**Autor: Niza Volair
**Date: 03-11-15
**Description: This is the implimentation for the Book class
******************************************************************************/
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//default constructor
Book::Book()
{  setIdCode("");
   setTitle("");
   setAuthor("");
   setCheckedOutBy(NULL);
   setRequestedBy(NULL);
   setLocation(ON_SHELF);
}
//constructor
Book::Book(string idc, string t, string a)
{  setIdCode(idc);
   setTitle(t);
   setAuthor(a);
   setLocation(ON_SHELF);
}
//set and get methods
void Book::setIdCode(string idc)
{  idCode = idc;
}
string Book::getIdCode()
{  return idCode;
}
void Book::setTitle(string t)
{  title = t;
}
string Book::getTitle()
{  return title;
}
void Book::setAuthor(string a)
{  author = a;
}
string Book::getAuthor()
{  return author;
}
Locale Book::getLocation()
{  return location;
}
void Book::setLocation(Locale lo)
{  location = lo;
}
Patron* Book::getCheckedOutBy()
{  return checkOutBy;
}
void Book::setCheckedOutBy(Patron* p)
{  checkOutBy = p;
}
Patron* Book::getRequestedBy()
{  return requestedBy;
}
void Book::setRequestedBy(Patron* p)
{  requestedBy = p;
}
int Book::getDateCheckedOut()
{  return dateCheckOut;
}
void Book::setDateCheckedOut(int d)
{   dateCheckOut = d;
}

