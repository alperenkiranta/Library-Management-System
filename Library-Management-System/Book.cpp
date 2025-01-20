#include "Book.hpp"
#include <iostream>

Book::Book(string t, string a, int i, BookCategory c)
    : title(t), author(a), isbn(i), available(true),
    category(c), issuedTo(-1) {}

void Book::display() const {
    cout << "\n----------------------------------------\n";
    cout << "Title: " << title << "\n";
    cout << "Author: " << author << "\n";
    cout << "ISBN: " << isbn << "\n";
    cout << "Category: " << getCategoryString() << "\n";
    cout << "Status: " << (available ? "Available" : "Issued") << "\n";
    if (!available) {
        cout << "Issued to: " << issuedTo << "\n";
        cout << "Issue Date: " << issueDate << "\n";
    }
}

string Book::getCategoryString() const {
    switch (category) {
    case BookCategory::FICTION: return "Fiction";
    case BookCategory::NON_FICTION: return "Non-Fiction";
    case BookCategory::SCIENCE: return "Science";
    case BookCategory::TECHNOLOGY: return "Technology";
    case BookCategory::HISTORY: return "History";
    default: return "Other";
    }
}

bool Book::isAvailable() const { return available; }
int Book::getIsbn() const { return isbn; }
string Book::getTitle() const { return title; }

void Book::setAvailability(bool status) { available = status; }

void Book::setIssueDetails(int studentId, string date) {
    issuedTo = studentId;
    issueDate = date;
    available = false;
}

void Book::clearIssueDetails() {
    issuedTo = -1;
    issueDate = "";
    available = true;
}

Book::~Book() {}

EBook::EBook(string t, string a, int i, BookCategory c, double size, string link)
    : Book(t, a, i, c), fileSize(size), downloadLink(link) {}

void EBook::display() const {
    Book::display();
    cout << "File Size: " << fileSize << " MB\n";
    cout << "Download Link: " << downloadLink << "\n";
}
