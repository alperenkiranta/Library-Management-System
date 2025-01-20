#include "Student.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

Student::Student(int roll, string n, double b)
    : rollNumber(roll), name(n), balance(b) {}

void Student::display() const {
    cout << "\n----------------------------------------\n";
    cout << "Roll Number: " << rollNumber << "\n";
    cout << "Name: " << name << "\n";
    cout << "Balance: $" << fixed << setprecision(2) << balance << "\n";
    cout << "Books Issued: " << issuedBooks.size() << "\n";
}

int Student::getRollNumber() const { return rollNumber; }
double Student::getBalance() const { return balance; }
void Student::addBalance(double amount) { balance += amount; }
void Student::deductBalance(double amount) { balance -= amount; }
void Student::addIssuedBook(int isbn) { issuedBooks.push_back(isbn); }

void Student::removeIssuedBook(int isbn) {
    issuedBooks.erase(
        remove(issuedBooks.begin(), issuedBooks.end(), isbn),
        issuedBooks.end()
    );
}
