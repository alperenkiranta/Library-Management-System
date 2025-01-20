#include "LibrarySystem.hpp"
#include "Book.hpp"
#include "Student.hpp"
#include <ctime>
#include <algorithm>
#include <iomanip>

// Get current date as a string
std::string LibrarySystem::getCurrentDate() const {
    time_t now = time(nullptr);
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &now);
    std::string date(timeStr);
    return date.substr(0, date.length() - 1); // Remove newline
}

// Main function to run the library system
void LibrarySystem::run() {
    while (true) {
        std::cout << "\n=== Library Management System ===\n"
                  << "1. Admin Login\n"
                  << "2. Student Login\n"
                  << "0. Exit\n"
                  << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: adminMenu(); break;
        case 2: studentMenu(); break;
        default: std::cout << "Invalid choice!\n"; break;
        }
    }
}

// Admin menu logic
void LibrarySystem::adminMenu() {
    std::string password;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    if (!validateAdminPassword(password)) {
        std::cout << "Invalid password!\n";
        return;
    }

    while (true) {
        std::cout << "\n=== Admin Menu ===\n"
                  << "1. Add Book\n"
                  << "2. View All Books\n"
                  << "3. View All Students\n"
                  << "4. Create Student Account\n"
                  << "0. Back\n"
                  << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayAllBooks(); break;
        case 3: displayAllStudents(); break;
        case 4: createStudentAccount(); break;
        default: std::cout << "Invalid choice!\n"; break;
        }
    }
}

// Student menu logic
void LibrarySystem::studentMenu() {
    int roll;
    std::cout << "Enter roll number: ";
    std::cin >> roll;

    Student* student = nullptr;
    for (auto& s : students) {
        if (s->getRollNumber() == roll) {
            student = s.get();
            break;
        }
    }

    if (!student) {
        std::cout << "Student not found!\n";
        return;
    }

    while (true) {
        std::cout << "\n=== Student Menu ===\n"
                  << "1. View Profile\n"
                  << "2. Issue Book\n"
                  << "3. View Available Books\n"
                  << "0. Back\n"
                  << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: student->display(); break;
        case 2: issueBook(); break;
        case 3: displayAllBooks(); break;
        default: std::cout << "Invalid choice!\n"; break;
        }
    }
}

// Admin password validation
bool LibrarySystem::validateAdminPassword(const std::string& password) {
    return password == ADMIN_PASSWORD;
}

// Add a new book to the library
void LibrarySystem::addBook() {
    if (books.size() >= 1000) {
        std::cout << "Maximum book limit reached!\n";
        return;
    }

    std::string title, author;
    int isbn;
    int category;
    std::cout << "Enter book title: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::cout << "Enter author name: ";
    std::getline(std::cin, author);

    std::cout << "Enter ISBN: ";
    std::cin >> isbn;

    // Add logic to check if book exists by ISBN, if needed

    std::cout << "Select category (1: Fiction, 2: Non-Fiction, 3: Science, 4: Technology, 5: History, 6: Other): ";
    std::cin >> category;

    BookCategory bookCategory = static_cast<BookCategory>(category - 1);

    books.push_back(std::make_unique<Book>(title, author, isbn, bookCategory));

    std::cout << "Book added successfully!\n";
}

// Create a new student account
void LibrarySystem::createStudentAccount() {
    if (students.size() >= 100) {
        std::cout << "Maximum student limit reached!\n";
        return;
    }

    int roll;
    std::string name;
    double initialDeposit;
    std::cout << "Enter roll number: ";
    std::cin >> roll;

    // Add logic to check if student exists by roll number, if needed

    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter initial deposit: ";
    std::cin >> initialDeposit;

    students.push_back(std::make_unique<Student>(roll, name, initialDeposit));

    std::cout << "Student account created successfully!\n";
}

// Issue a book to a student
void LibrarySystem::issueBook() {
    int roll, isbn;
    std::cout << "Enter student roll number: ";
    std::cin >> roll;

    Student* student = nullptr;
    for (auto& s : students) {
        if (s->getRollNumber() == roll) {
            student = s.get();
            break;
        }
    }

    if (!student) {
        std::cout << "Student not found!\n";
        return;
    }

    std::cout << "Enter book ISBN: ";
    std::cin >> isbn;

    Book* book = nullptr;
    for (auto& b : books) {
        if (b->getIsbn() == isbn) {
            book = b.get();
            break;
        }
    }

    if (!book) {
        std::cout << "Book not found!\n";
        return;
    }

    if (!book->isAvailable()) {
        std::cout << "Book is already issued!\n";
        return;
    }

    book->setIssueDetails(roll, getCurrentDate());
    student->addIssuedBook(isbn);

    std::cout << "Book issued successfully!\n";
}

// Display all books in the library
void LibrarySystem::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "No books in library!\n";
        return;
    }
    for (const auto& book : books) {
        book->display();
    }
}

// Display all students in the system
void LibrarySystem::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "No students registered!\n";
        return;
    }
    for (const auto& student : students) {
        student->display();
    }
}
