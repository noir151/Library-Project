#include "Member.h"
#include <iostream>

Member::Member() : id(-1) {}

void Member::addMember() 
{
std::cout << "Enter new member's name: "; 
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Enter new member's address: "; 
        std::getline(std::cin, address);

        std::cout << "Enter new member's email: "; 
        std::getline(std::cin, email);

        id = generateMemberId(); 
}

int Member::generateMemberId() {
static int nextID = 1; // Keeps track of the next available ID for future members
        return nextID++;
}
