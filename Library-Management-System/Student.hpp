#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    double balance;
    vector<int> issuedBooks;

public:
    Student(int roll, string n, double b);
    void display() const;
    int getRollNumber() const;
    double getBalance() const;
    void addBalance(double amount);
    void deductBalance(double amount);
    void addIssuedBook(int isbn);
    void removeIssuedBook(int isbn);
};

#endif
