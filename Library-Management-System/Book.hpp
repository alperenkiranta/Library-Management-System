#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
using namespace std;

enum class BookCategory {
    FICTION,
    NON_FICTION,
    SCIENCE,
    TECHNOLOGY,
    HISTORY,
    OTHER
};

class Book {
protected:
    string title;
    string author;
    int isbn;
    bool available;
    BookCategory category;
    string issueDate;
    int issuedTo;

public:
    Book(string t, string a, int i, BookCategory c);
    virtual void display() const;
    string getCategoryString() const;
    bool isAvailable() const;
    int getIsbn() const;
    string getTitle() const;
    void setAvailability(bool status);
    void setIssueDetails(int studentId, string date);
    void clearIssueDetails();
    virtual ~Book();
};

class EBook : public Book {
private:
    double fileSize;
    string downloadLink;

public:
    EBook(string t, string a, int i, BookCategory c, double size, string link);
    void display() const override;
};

#endif
