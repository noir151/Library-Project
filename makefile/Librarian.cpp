#include "Librarian.h"

Librarian::Librarian() : id(-1) {}

void Librarian::getLibrarianDetails() 
{
    std::cout << "Enter Librarian's Name: ";
        std::cin >> std::ws; // 
        std::getline(std::cin, name);

        std::cout << "Enter Librarian's Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter Librarian's email: ";
        std::getline(std::cin, email);


        std::cout << "Enter Librarian's ID: "; 
        std::cin >> id;

        std::cin.ignore(); 
}

void Librarian::displayWelcomeMessage() 
{
        std::cout << "Welcome, " << name << "!" << std::endl; 
}

