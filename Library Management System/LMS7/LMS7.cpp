#include <iostream>
#include <cstring>
#include <vector>
#include <string> // getline fonksiyonu için

using namespace std;

// Global constants
const int MAX_STUDENTS = 20;
const int MAX_BOOKS = 15;
const int MAX_NAME_LENGTH = 50;

// Global variables
int student_count = 0;
int book_count = 0;

// Base class: Book
class Book {
public:
    string title;
    string author;
    int isbn;
    bool available;

    // Constructor
    Book(string t, string a, int i) : title(t), author(a), isbn(i), available(true) {}

    // Getter functions
    virtual void display() const {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "Available: " << (available ? "Yes" : "No") << "\n\n";
    }

    // Virtual Destructor (for polymorphism)
    virtual ~Book() {}
};

// Derived class: EBook
class EBook : public Book {
public:
    double size;  // Size in MB

    // Constructor for EBook
    EBook(string t, string a, int i, double s) : Book(t, a, i), size(s) {}

    // Override the display method to include file size
    void display() const override {
        Book::display();
        cout << "File Size: " << size << "MB" << endl;
    }
};

// Class for Students
class Student {
public:
    int roll;
    char name[MAX_NAME_LENGTH];
    double balance;

    // Constructor
    Student(int r, const char* n, double b) : roll(r), balance(b) {
        strcpy_s(name, n);
    }

    void display() const {
        cout << "Roll No: " << roll << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Global vectors to store students and books
vector<Student> students;
vector<Book*> books;  // Pointers to Book objects

// Function prototypes
void create_account();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void display_sorted();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();

int main() {
    // Initialization for students and books
    while (true) {
        cout << "Login as:\n1. Admin\n2. Student\n0. Exit\n";
        int option;
        cin >> option;

        if (option == 0) {
            break;
        }

        if (option == 1) { // Admin login
            string password;
            cout << "Enter password: ";
            cin >> password;

            if (password == "password") {  // Use a simple password for demonstration purposes.
                cout << "Admin options:\n1. Add book\n2. Edit book\n3. View book status\n4. View enrolled students\n5. View student balance\n";
                cin >> option;

                switch (option) {
                case 1:
                    add_book();
                    break;
                case 2:
                    edit_book();
                    break;
                case 3:
                    view_books();
                    break;
                case 4:
                    display_sorted();
                    break;
                case 5: {
                    int roll;
                    cout << "Enter student roll number: ";
                    cin >> roll;
                    display(roll);
                    break;
                }
                }
            }
        }
        else { // Student login
            int roll;
            cout << "Enter your roll number: ";
            cin >> roll;

            int index = find_student(roll);
            if (index == -1) {
                cout << "Student not found. Create an account? (1. Yes / 2. No): ";
                cin >> option;
                if (option == 1) {
                    create_account();
                }
            }
            else {
                cout << "Student options:\n1. View balance\n2. Deposit amount\n3. Issue item\n";
                cin >> option;

                switch (option) {
                case 1:
                    display(roll);
                    break;
                case 2: {
                    double amount;
                    cout << "Enter the amount to deposit: ";
                    cin >> amount;
                    deposit_amount(roll, amount);
                    break;
                }
                case 3:
                    issue_item(roll);
                    break;
                }
            }
        }
    }
    // Cleanup: Delete dynamically allocated books
    for (Book* book : books) {
        delete book;
    }

    return 0;
}

void create_account() {
    if (student_count >= MAX_STUDENTS) {
        cout << "Student limit reached. Cannot create more accounts.\n";
        return;
    }

    int roll;
    cout << "Enter roll number (BBRRRR format): ";
    cin >> roll;

    if (find_student(roll) != -1) {
        cout << "Account already exists for this roll number.\n";
        return;
    }

    char name[MAX_NAME_LENGTH];
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(name, MAX_NAME_LENGTH);

    double initial_deposit;
    cout << "Enter initial deposit amount ($50 minimum): ";
    cin >> initial_deposit;

    if (initial_deposit < 50) {
        cout << "Initial deposit must be at least $50.\n";
        return;
    }

    double final_balance = initial_deposit - 20 - 30; // Account opening and security deposit
    students.push_back(Student(roll, name, final_balance));
    student_count++;
}

void display(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students[index].display();
}

void deposit_amount(int roll, double amount) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students[index].balance += amount;
    cout << "New balance: $" << students[index].balance << endl;
}

void issue_item(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Available books:\n";
    for (int i = 0; i < book_count; i++) {
        if (books[i]->available) {
            books[i]->display();
        }
    }

    int choice;
    cout << "Enter the number of the book you want to issue (0 to cancel): ";
    cin >> choice;

    // Ensure choice is within valid range
    if (choice < 1 || choice > book_count) {
        cout << "Invalid choice, please select a valid book number.\n";
        return;
    }

    // Check if the selected book is available
    if (books[choice - 1]->available && students[index].balance >= 2) {
        books[choice - 1]->available = false;
        students[index].balance -= 2;
        cout << "Book issued successfully. New balance: $" << students[index].balance << endl;
    }
    else {
        cout << "Cannot issue the book. Insufficient balance or book is unavailable.\n";
    }
}

void display_sorted() {
    for (int i = 0; i < student_count; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].roll > students[j].roll) {
                swap(students[i], students[j]);
            }
        }
    }

    for (int i = 0; i < student_count; i++) {
        students[i].display();
    }
}

int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll) {
            return i;
        }
    }
    return -1;
}

int find_book(int isbn) {
    for (int i = 0; i < book_count; i++) {
        if (books[i]->isbn == isbn) {
            return i;
        }
    }
    return -1;
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        cout << "Book limit reached. Cannot add more books.\n";
        return;
    }

    string title, author;
    int isbn;

    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter book author: ";
    getline(cin, author);

    cout << "Enter ISBN: ";
    cin >> isbn;

    Book* newBook = new Book(title, author, isbn);
    books.push_back(newBook);
    book_count++;
    cout << "Book added successfully.\n";
}

void edit_book() {
    int isbn;
    cout << "Enter ISBN of the book to edit: ";
    cin >> isbn;

    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    string title, author;
    cout << "Enter new title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter new author: ";
    getline(cin, author);

    books[index]->title = title;
    books[index]->author = author;
    cout << "Book information updated.\n";
}

void view_books() {
    for (int i = 0; i < book_count; i++) {
        books[i]->display();
    }
}


