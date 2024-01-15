#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <iostream>
#include <string>

class Librarian {
public:
    int id;
    std::string name;
    std::string address;
    std::string email;

    Librarian();

    void getLibrarianDetails();

    void displayWelcomeMessage();
};

#endif // LIBRARIAN_H