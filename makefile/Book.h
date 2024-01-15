#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>

class Book {
public:
    int id;
    std::string name;
    std::string authorFirstName;
    std::string authorLastName;
    std::string type;
    int pageCount;
    bool borrowed;
    int memberId;
    time_t dueDate;

    Book();
};

#endif // BOOK_H
