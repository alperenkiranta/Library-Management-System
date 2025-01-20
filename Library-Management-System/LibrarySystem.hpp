#ifndef LIBRARYSYSTEM_HPP
#define LIBRARYSYSTEM_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "Book.hpp"
#include "Student.hpp"

class LibrarySystem {
public:
    void run(); // Main loop to run the library system
    void adminMenu(); // Admin menu logic
    void studentMenu(); // Student menu logic
    void addBook(); // Add a book
    void createStudentAccount(); // Create student account
    void issueBook(); // Issue book to student
    void displayAllBooks() const; // Display all books
    void displayAllStudents() const; // Display all students

private:
    bool validateAdminPassword(const std::string& password); // Validate admin password
    std::string getCurrentDate() const; // Get the current date

    std::vector<std::unique_ptr<Book>> books; // Vector to store books
    std::vector<std::unique_ptr<Student>> students; // Vector to store students
    const std::string ADMIN_PASSWORD = "admin123"; // Admin password
};

#endif // LIBRARYSYSTEM_HPP
