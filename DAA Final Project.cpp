#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <ctime>
using namespace std;

// Book class representing a book in the library
class Book {
public:
    string title;    // Title of the book
    string author;    // Author of the book
    string ISBN;    // ISBN of the book
    string category;    // Category of the book
    bool isAvailable;    // Availability status of the book
    string location;    // Location of the book in the library

    // Constructor to initialize a book object
    Book(string t, string a, string i, string c, string l)
        : title(t), author(a), ISBN(i), category(c), location(l), isAvailable(true) {}
};

// Member class representing a library member
class Member {
public:
    string name;    // Name of the member
    string contact;    // Contact information of the member
    int memberID;    // Unique ID of the member
    list<string> borrowingHistory;    // List of borrowed books' ISBNs
    unordered_map<string, time_t> borrowedBooks;    // Currently borrowed books with borrow time

    // Constructor to initialize a member object
    Member(string n, string c, int id)
        : name(n), contact(c), memberID(id) {}
};

// Library class representing the library system
class Library {
private:
    unordered_map<string, Book*> booksByISBN;  // Map of books by their ISBN
    unordered_map<int, Member*> membersByID;  // Map of members by their ID
    unordered_map<string, list<int>> reservations; // Map of reservations for each book by ISBN

    // Display information of a book
    void displayBookInfo(Book* book) {
        cout << "Title: " << book->title << "\nAuthor: " << book->author
             << "\nISBN: " << book->ISBN << "\nCategory: " << book->category
             << "\nLocation: " << book->location << "\nAvailability: "
             << (book->isAvailable ? "Available" : "Checked Out") << "\n";
    }

public:
    // Add a new book to the library
    void addBook(Book* book) {
        booksByISBN[book->ISBN] = book;
    }

    // Add a new member to the library
    void addMember(Member* member) {
        membersByID[member->memberID] = member;
    }

    // Search for books in the library by a query
    void searchBook(string query) {
        bool found = false;
        for (auto& pair : booksByISBN) {
            Book* book = pair.second;
            if (book->title.find(query) != string::npos || 
                book->author.find(query) != string::npos ||
                book->ISBN == query || 
                book->category.find(query) != string::npos) {
                displayBookInfo(book);
                found = true;
            }
        }
        if (!found) {
            cout << "No books found matching the query: " << query << "\n";
        }
    }

    // Borrow a book from the library
    void borrowBook(int memberID, string ISBN) {
        if (booksByISBN.find(ISBN) == booksByISBN.end()) {
            cout << "Book not found.\n";
            return;
        }
        if (membersByID.find(memberID) == membersByID.end()) {
            cout << "Member not found.\n";
            return;
        }

        Book* book = booksByISBN[ISBN];
        Member* member = membersByID[memberID];

        if (book->isAvailable) {
            book->isAvailable = false;
            time_t now = time(0);
            member->borrowedBooks[ISBN] = now;
            member->borrowingHistory.push_back(ISBN);
            cout << "Book borrowed successfully.\n";
        } else {
            reservations[ISBN].push_back(memberID);
            cout << "Book is currently checked out. You have been added to the reservation list.\n";
        }
    }

    // Return a borrowed book to the library
    void returnBook(int memberID, string ISBN) {
        if (booksByISBN.find(ISBN) == booksByISBN.end()) {
            cout << "Book not found.\n";
            return;
        }
        if (membersByID.find(memberID) == membersByID.end()) {
            cout << "Member not found.\n";
            return;
        }

        Book* book = booksByISBN[ISBN];
        Member* member = membersByID[memberID];

        if (member->borrowedBooks.find(ISBN) != member->borrowedBooks.end()) {
            book->isAvailable = true;
            member->borrowedBooks.erase(ISBN);
            cout << "Book returned successfully.\n";

            if (!reservations[ISBN].empty()) {
                int nextMemberID = reservations[ISBN].front();
                reservations[ISBN].pop_front();
                borrowBook(nextMemberID, ISBN);
                cout << "Book reserved for next member in queue.\n";
            }
        } else {
            cout << "This book was not borrowed by this member.\n";
        }
    }

    // Calculate fine for a member
    void calculateFine(int memberID) {
        if (membersByID.find(memberID) == membersByID.end()) {
            cout << "Member not found.\n";
            return;
        }

        Member* member = membersByID[memberID];
        time_t now = time(0);
        double totalFine = 0.0;
        
        for (auto& pair : member->borrowedBooks) {
            double days = difftime(now, pair.second) / (60 * 60 * 24);
            if (days > 14) { // Assuming 14 days borrowing period
                totalFine += (days - 14) * 0.5; // Assuming $0.5 fine per day
            }
        }

        cout << "Total fine for member " << memberID << ": $" << totalFine << "\n";
    }
};

int main() {
    Library lib;
    // Adding sample books and members
    lib.addBook(new Book("The Great Gatsby", "F. Scott Fitzgerald", "1234567890", "Fiction", "Shelf A1"));
    lib.addBook(new Book("To Kill a Mockingbird", "Harper Lee", "0987654321", "Fiction", "Shelf B2"));
    lib.addMember(new Member("John Doe", "555-1234", 1));
    lib.addMember(new Member("Jane Smith", "555-5678", 2));

    int choice;
    do {
        cout << "\nMenu:\n1. Add Book\n2. Add Member\n3. Search Book\n4. Borrow Book\n5. "
             << "Return Book\n6. Calculate Fine\n7. Exit\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Adding a new book
                string title, author, ISBN, category, location;
                cout << "Enter title: "; cin.ignore(); getline(cin, title);
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter ISBN: "; getline(cin, ISBN);
                cout << "Enter category: "; getline(cin, category);
                cout << "Enter location: "; getline(cin, location);
                lib.addBook(new Book(title, author, ISBN, category, location));
                break;
            }
            case 2: {
                // Adding a new member
                string name, contact;
                int memberID;
                cout << "Enter name: "; cin.ignore(); getline(cin, name);
                cout << "Enter contact: "; getline(cin, contact);
                cout << "Enter member ID: "; cin >> memberID;
                lib.addMember(new Member(name, contact, memberID));
                break;
            }
            case 3: {
                // Searching for a book
                string query;
                cout << "Enter title, author, ISBN, or category to search: "; 
                cin.ignore(); getline(cin, query);
                lib.searchBook(query);
                break;
            }
            case 4: {
                // Borrowing a book
                int memberID;
                string ISBN;
                cout << "Enter member ID: "; cin >> memberID;
                cout << "Enter ISBN of the book to borrow: "; cin.ignore(); getline(cin, ISBN);
                lib.borrowBook(memberID, ISBN);
                break;
            }
            case 5: {
                // Returning a borrowed book
                int memberID;
                string ISBN;
                cout << "Enter member ID: "; cin >> memberID;
                cout << "Enter ISBN of the book to return: "; cin.ignore(); getline(cin, ISBN);
                lib.returnBook(memberID, ISBN);
                break;
            }
            case 6: {
                // Calculating fine for a member
                int memberID;
                cout << "Enter member ID to calculate fine: "; cin >> memberID;
                lib.calculateFine(memberID);
                break;
            }
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}