#include "Librarian.h"
#include "LibrarianFunctions.h"

int main() {
    readCsv("filename.csv");

    Librarian librarian;
    librarian.getLibrarianDetails();

    std::cout << "LionX Library" << std::endl;
    int option;

    librarian.displayWelcomeMessage();

    do {
        std::cout << "===============================================" << std::endl;
        std::cout << "Press 1 to add a member" << std::endl;
        std::cout << "Press 2 to issue a book" << std::endl;
        std::cout << "Press 3 to return a book" << std::endl;
        std::cout << "Press 4 to display borrowed books" << std::endl;
        std::cout << "Press 5 to exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option) {
        case 1:
            addMember();
            break;
        case 2:
            issueBook();
            break;
        case 3:
            returnBooks();
            break;
        case 4:
            displayBorrowedBooks();
            break;
        case 5:
            break;
        default:
            std::cout << "Invalid Entry." << std::endl;
        }
    } while (option != 5);

    return 0;
}
