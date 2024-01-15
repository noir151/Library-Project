#include "LibrarianFunctions.h"
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<Member> members;
std::vector<Book> books;

void readCsv(const std::string& filename) 
{
std::ifstream file(filename); 

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;  
        return;
    }

    books.clear();

    std::string line;
    while (std::getline(file, line))
    {
        Book book;
        char comma;

        file >> book.id >> comma;
        std::getline(file, book.name, ',');
        std::getline(file, book.authorFirstName, ',');
        std::getline(file, book.authorLastName, ',');
        std::getline(file, book.type, ',');
        file >> book.pageCount >> comma;
        file >> std::boolalpha >> book.borrowed >> comma;
        file >> book.memberId >> comma;
        file >> book.dueDate;

        books.push_back(book);
    }

    file.close();
}

void addMember() 
{
    Member newMember;
    newMember.addMember();
    members.push_back(newMember);

    std::cout << "New member added:\n";
    std::cout << "ID: " << newMember.id << ", Name: " << newMember.name << ", Address: " << newMember.address << ", Email: " << newMember.email << std::endl;
}

void issueBook() 
{
int memberId, bookId; // Declares variables to store member and book IDs
    std::cout << "Enter member ID: "; // Member has to input their member ID 
    std::cin >> memberId;
    // Search's for the member's ID in the vector of members
    auto memberIt = find_if(members.begin(), members.end(), [memberId](const Member &m){ return m.id == memberId; });
    if (memberIt == members.end()) // Conditional set if the member was not found
    {
        std::cout << "Member with ID " << memberId << " not found.\n";
        return;
    }

    std::cout << "Enter book ID: "; // Member has to enter a book ID
    std::cin >> bookId;
    // Search's for the book's ID in the vector of books
    auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book &b){ return b.id == bookId && !b.borrowed; });
    if (bookIt == books.end()) // Conditional set if the book was not found
    {
        std::cout << "Book with ID " << bookId << " is already borrowed or not found.\n";
        return;
    }

    bookIt->borrowed = true; // Marks the book as borrowed
    bookIt->memberId = memberId; // Assign's the member's ID
    time_t now = time(0); // Sets the due date
    bookIt->dueDate = now + 3 * 24 * 60 * 60; // Sets the due date to 3 days from the current time

    std::cout << "Book issued successfully to member ID " << memberId << std::endl; // Prints a success message indicating that the book has been issued to the member

    // Displays the issued book details
    std::cout << "Issued Book Details:\n";
    std::cout << "------------------------------------\n";
    std::cout << "Book ID: " << bookIt->id << std::endl;
    std::cout << "Book Name: " << bookIt->name << std::endl;
    std::cout << "Author First Name: " << bookIt->authorFirstName << std::endl;
    std::cout << "Author Last Name: " << bookIt->authorLastName << std::endl;
    std::cout << "Book Type: " << bookIt->type << std::endl;
    std::cout << "Page Count: " << bookIt->pageCount << std::endl;
    std::cout << "Member ID: " << bookIt->memberId << std::endl;
    std::cout << "Due Date: " << ctime(&bookIt->dueDate);
    std::cout << "------------------------------------\n";
}

void returnBooks() 
{
int bookId;
    std::cout << "Enter book ID to return: "; // Member has to enter book ID for return
    std::cin >> bookId;
    // Search's for the borrowed book by its ID
    auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book &b)
                          { return b.id == bookId && b.borrowed; });
    if (bookIt == books.end()) // Conditional set if the book was not borrowed
    {
        std::cout << "Book with ID " << bookId << " is not currently borrowed or not found.\n";
        return;
    }

    bookIt->borrowed = false; // Marks the book as not borrowed
    bookIt->memberId = -1; // Resets the member ID to indicate that the book is not borrowed

    time_t currentDate = time(0); // Gets the current date and time

    if (bookIt->dueDate < currentDate) // Checks if the due date of the returned book is overdue
    {
        // Book is overdue, calculate and display fine
        std::cout << "Book is overdue. "; // Message to inform member that the book is overdue 
        double fineRatePerDay = 1.0; // Fine rate of £1 per day                       
        double daysOverdue = difftime(currentDate, bookIt->dueDate) / (24 * 60 * 60); // Calculates days overdue
        double fineAmount = fineRatePerDay * daysOverdue; // Calculates the total fine based on the fine rate and days overdue

        std::cout << "Fine Amount: $" << fineAmount << std::endl; // Displays the fine amount
    }

    std::cout << "Book with ID " << bookId << " returned successfully.\n"; // Message that book has been successfully returned  

    // Displays returned book details
    std::cout << "Returned Book Details:\n";
    std::cout << "------------------------------------\n";
    std::cout << "Book ID: " << bookIt->id << std::endl;
    std::cout << "Book Name: " << bookIt->name << std::endl;
    std::cout << "Author First Name: " << bookIt->authorFirstName << std::endl;
    std::cout << "Author Last Name: " << bookIt->authorLastName << std::endl;
    std::cout << "Book Type: " << bookIt->type << std::endl;
    std::cout << "Page Count: " << bookIt->pageCount << std::endl;
    std::cout << "------------------------------------\n";
}

void displayBorrowedBooks() 
{
std::cout << "Borrowed Books:\n";

    for (const auto &book : books) // Will only show borrowed books
    {
        if (book.borrowed)
        {
            // Displays book details
            std::cout << "------------------------------------\n";
            std::cout << "Book ID: " << book.id << std::endl;
            std::cout << "Book Name: " << book.name << std::endl;
            std::cout << "Author First Name: " << book.authorFirstName << std::endl;
            std::cout << "Author Last Name: " << book.authorLastName << std::endl;
            std::cout << "Book Type: " << book.type << std::endl;
            std::cout << "Page Count: " << book.pageCount << std::endl;
            std::cout << "Member ID: " << book.memberId << std::endl;
            std::cout << "Due Date: " << ctime(&book.dueDate);
            std::cout << "------------------------------------\n";
        }
    }
}
