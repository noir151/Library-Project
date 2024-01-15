#ifndef LIBRARIANFUNCTIONS_H
#define LIBRARIANFUNCTIONS_H

#include <string>
#include <vector>

#include "Librarian.h"
#include "Book.h"
#include "Member.h"

void readCsv(const std::string& filename);

void addMember();

void issueBook();

void returnBooks();

void displayBorrowedBooks();

#endif // LIBRARIANFUNCTIONS_H