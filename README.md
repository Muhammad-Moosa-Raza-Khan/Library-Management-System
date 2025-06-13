# Library Management System 

## Overview  
This project implements a complete **Library Management System** using C++ and object-oriented programming. It allows librarians to manage books, members, borrowing/returning processes, and calculate fines for overdue books. The system uses efficient data structures (`unordered_map`, `list`) for fast lookups and maintains borrowing history.  

## Key Features  
- **Book Management**: Add books with titles, authors, ISBNs, categories, and locations.  
- **Member Management**: Register members with unique IDs and contact details.  
- **Search Functionality**: Find books by title, author, ISBN, or category.  
- **Borrow/Return System**: Track book availability and handle reservations.  
- **Fine Calculation**: Automatic fine computation for overdue books ($0.5/day after 14 days).  
- **Menu-Driven Interface**: Easy-to-use console interface for all operations.  

## Data Structures Used  
- `unordered_map`: For O(1) access to books (by ISBN) and members (by ID).  
- `list`: To maintain borrowing history and reservation queues.  
- `time_t`: For tracking borrowing dates and calculating fines.  

## How to Compile & Run  
1. **Compile**:  
   ```bash
   g++ DAA_Final_Project.cpp -o library_system
   ```
2. **Execute**:  
   ```bash
   ./library_system
   ```

## Sample Workflow  
1. Add books/members via the menu.  
2. Search for books using keywords.  
3. Borrow books (automatically handles reservations if unavailable).  
4. Return books (triggers reservations for next member if any).  
5. Calculate fines for overdue books.  

## Example Output  
```plaintext
Menu:
1. Add Book
2. Add Member
3. Search Book
4. Borrow Book
5. Return Book
6. Calculate Fine
7. Exit
Enter your choice: 3
Enter title, author, ISBN, or category to search: Gatsby
Title: The Great Gatsby
Author: F. Scott Fitzgerald
ISBN: 1234567890
Category: Fiction
Location: Shelf A1
Availability: Available
```

## Future Enhancements  
- **File Persistence**: Save/load data to/from files.  
- **GUI**: Implement using Qt or SFML.  
- **Admin/Member Roles**: Separate interfaces for librarians and members.  

Developed as a final project for Design Analysis & Algorithms (DAA) course.
