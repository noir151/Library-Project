#include <iostream> // Provides functionality for reading from and writing to console
#include <fstream> // Provides functionality for reading from and writing to files
#include <ctime> //  Provides functionality for working with time and date
#include <vector> // Provides the implementation of dynamic arrays
#include <algorithm> // Contains a various functions for performing different operations on sequences

using namespace std;

class Librarian // Class for Librarian
{
public:
    int id; // Variable to store the ID of the Librarian
    std::string name; // Variable to store the name of the Librarian
    std::string address; // Variable to store the address of the Librarian
    std::string email; // Variable to store the email of the Librarian

    Librarian() : id(-1) {} // Constructor sets id to -1 to provide default values

    void getLibrarianDetails() // Function to get Librarian details 

    {
        std::cout << "Enter Librarian's Name: "; // Input for the Librarian's name
        std::cin >> ws; // 
        std::getline(cin, name);

        std::cout << "Enter Librarian's Address: "; // Input for the Librarian's address
        std::getline(cin, address);

        std::cout << "Enter Librarian's email: "; // Input for the Librarian's address
        std::getline(cin, email);


        std::cout << "Enter Librarian's ID: "; // Input for the Librarian's ID
        std::cin >> id;

        std::cin.ignore(); 
    }

    
    void displayWelcomeMessage() // Function to display a welcome message for the Librarian
    {
        std::cout << "Welcome, " << name << "!" << std::endl; // Welcome message to Librarian
    }
};

class Book // Class for Book
{
public:
    int id; // Variable to store the ID of the Book
    std::string name; // Variable to store the name of the Book
    std::string authorFirstName; // Variable to store the Author's first name of the Book
    std::string authorLastName; // Variable to store the Author's last name of the Book
    std::string type; // Variable to store the type of the Book
    int pageCount; // Variable to store the page count of the Book
    bool borrowed; // Variable to store the borrowed books 
    int memberId; // Variable to store the ID of the Book
    time_t dueDate; // Variable to store the ID of the Book

    Book() : borrowed(false), memberId(-1) {} // Constructor sets borrowed to false and memberId to -1
};

class Member // Class for Member
{
public:
    int id; // Variable to store the ID of the Member
    std::string name; // Variable to store the name of the Member
    std::string email; // Variable to store the email of the Member
    std::string address; // Variable to store the address of the Member

    Member() : id(-1) {} // Constructor sets id to -1 to provide default values

    void addMember() // Function to add a new member 
    {
        std::cout << "Enter new member's name: "; // Input for the new Member's name
        std::cin.ignore();
        std::getline(cin, name);

        std::cout << "Enter new member's address: "; // Input for the new Member's address
        std::getline(cin, address);

        std::cout << "Enter new member's email: "; // Input for the new Member's email
        std::getline(cin, email);

        id = generateMemberId(); // Generates a member ID
    }

 int generateMemberId() // Function to generate a unique member ID
    {
        static int nextID = 1; // Keeps track of the next available ID for future members
        return nextID++;
    }
};

// Vectors to store members and books
vector<Member> members;
vector<Book> books;

void readCsv(const std::string &filename) // Function to read book data from a CSV file
{
    ifstream file(filename); // Opens an input file using it's specified filename

    if (!file.is_open()) // Checks if the file is successfully opened
    {
        std::cerr << "Error opening file: " << filename << std::endl;  
        return;
    }

    books.clear(); // Clears existing books vector

    std::string line;
    while (std::getline(file, line))
    {
        Book book;
        char comma; // To handle the commas in the CSV file

        // Reads each field directly from the line
        file >> book.id >> comma;
        std::getline(file, book.name, ',');
        std::getline(file, book.authorFirstName, ',');
        std::getline(file, book.authorLastName, ',');
        std::getline(file, book.type, ',');
        file >> book.pageCount >> comma;
        file >> boolalpha >> book.borrowed >> comma;
        file >> book.memberId >> comma;
        file >> book.dueDate;

        books.push_back(book);
    }

    file.close();
}

void addMember() // Function to add a new member
{
    // Invokes the function to input details for the new member and adds them to the vector of members
    Member newMember;
    newMember.addMember();
    members.push_back(newMember);
    // Prints a message indicating that a new member has been added, along with their details
    std::cout << "New member added:\n";
    std::cout << "ID: " << newMember.id << ", Name: " << newMember.name << ", Address: " << newMember.address << ", Email: " << newMember.email << std::endl;
}

void issueBook() // Function to issue a book to a member
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
    std::cout << "Book ID: " << bookIt->id << endl;
    std::cout << "Book Name: " << bookIt->name << endl;
    std::cout << "Author First Name: " << bookIt->authorFirstName << endl;
    std::cout << "Author Last Name: " << bookIt->authorLastName << endl;
    std::cout << "Book Type: " << bookIt->type << endl;
    std::cout << "Page Count: " << bookIt->pageCount << endl;
    std::cout << "Member ID: " << bookIt->memberId << endl;
    std::cout << "Due Date: " << ctime(&bookIt->dueDate);
    std::cout << "------------------------------------\n";
}

void returnBooks() // Function to return a borrowed book
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

        std::cout << "Fine Amount: $" << fineAmount << endl; // Displays the fine amount
    }

    std::cout << "Book with ID " << bookId << " returned successfully.\n"; // Message that book has been successfully returned  

    // Displays returned book details
    std::cout << "Returned Book Details:\n";
    std::cout << "------------------------------------\n";
    std::cout << "Book ID: " << bookIt->id << endl;
    std::cout << "Book Name: " << bookIt->name << endl;
    std::cout << "Author First Name: " << bookIt->authorFirstName << endl;
    std::cout << "Author Last Name: " << bookIt->authorLastName << endl;
    std::cout << "Book Type: " << bookIt->type << endl;
    std::cout << "Page Count: " << bookIt->pageCount << endl;
    std::cout << "------------------------------------\n";
}

void displayBorrowedBooks() // Function to display details of borrowed books
{
    std::cout << "Borrowed Books:\n";

    for (const auto &book : books) // Will only show borrowed books
    {
        if (book.borrowed)
        {
            // Displays book details
            std::cout << "------------------------------------\n";
            std::cout << "Book ID: " << book.id << endl;
            std::cout << "Book Name: " << book.name << endl;
            std::cout << "Author First Name: " << book.authorFirstName << endl;
            std::cout << "Author Last Name: " << book.authorLastName << endl;
            std::cout << "Book Type: " << book.type << endl;
            std::cout << "Page Count: " << book.pageCount << endl;
            std::cout << "Member ID: " << book.memberId << endl;
            std::cout << "Due Date: " << ctime(&book.dueDate);
            std::cout << "------------------------------------\n";
        }
    }
}

// Main function
int main()
{
    readCsv("filename.csv"); // This is where the csv file will be implemented into the code so it can read

    Librarian librarian; // Gets the details of the Librarian
    librarian.getLibrarianDetails(); 

    std::cout << "LionX Library" << endl; // Library name header
    int option;

    librarian.displayWelcomeMessage(); // Welcome message shown to Librarian

    // Main menu loop
    do
    {
        // Main menu interface for user selection
        std::cout << "===============================================" << endl;
        std::cout << "Press 1 to add a member\n";
        std::cout << "Press 2 to issue a book\n";
        std::cout << "Press 3 to return a book\n";
        std::cout << "Press 4 to display borrowed books\n";
        std::cout << "Press 5 to exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        // These switch cases are to handle user input
        switch (option)
        {
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
            cout << "Invalid Entry." << endl;
        }
    } while (option != 5); // Exits loop when user chooses option 5

    return 0;
}
