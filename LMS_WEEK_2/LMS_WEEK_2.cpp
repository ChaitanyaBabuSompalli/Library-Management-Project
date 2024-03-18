#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Book {
    string title;
    string author;
    int id;
public:
    Book(string t, string a, int i) : title(t), author(a), id(i) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getId() const { return id; }
};

class User {
    string name;
    int id;
public:
    User(string n, int i) : name(n), id(i) {}

    string getName() const { return name; }
    int getId() const { return id; }
};

class Transaction {
    Book book;
    User user;
    string date;
    bool returned;
public:
    Transaction(Book b, User u, string d) : book(b), user(u), date(d), returned(false) {}

    void markReturned() {
        returned = true;
    }

    Book getBook() const { return book; }
    User getUser() const { return user; }
    string getDate() const { return date; }
    bool isReturned() const { return returned; }
};

class Library {
    vector<Book> books;
    vector<User> users;
    vector<Transaction> transactions;
public:
    void addBook(const Book& b) {
        books.push_back(b);
    }

    void addUser(const User& u) {
        users.push_back(u);
    }

    Book* searchBook(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    void borrowBook(const Book& b, const User& u, const string& date) {
        transactions.push_back(Transaction(b, u, date));
    }

    void returnBook(const Book& b) {
        for (auto& transaction : transactions) {
            if (transaction.getBook().getId() == b.getId()) {
                transaction.markReturned();
                break;
            }
        }
    }
};

int main() {
    Library library;

    cout << "Welcome to the Library Management System!" << endl;
    cout << "Available commands:" << endl;
    cout << "- AddBook [title] [author] [id]" << endl;
    cout << "- AddUser [name] [id]" << endl;
    cout << "- SearchBook [title]" << endl;
    cout << "- BorrowBook [title] [user_id] [date]" << endl;
    cout << "- ReturnBook [title]" << endl;
    cout << "- Exit" << endl;

    string command;
    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "Exit") {
            cout << "Exiting program..." << endl;
            break;
        }
        else if (action == "AddBook") {
            string title, author, idStr;
            if (ss >> title >> author >> idStr) {
                // Remove square brackets from idStr
                idStr = idStr.substr(1, idStr.size() - 2);
                int id = stoi(idStr);
                library.addBook(Book(title, author, id));
                cout << "Book added successfully!" << endl;
            }
            else {
                cout << "Invalid command format! Usage: AddBook [title] [author] [id]" << endl;
            }
        }
        else if (action == "AddUser") {
            // Your code for adding user...
        }
        else if (action == "SearchBook") {
            // Your code for searching book...
        }
        else if (action == "BorrowBook") {
            // Your code for borrowing book...
        }
        else if (action == "ReturnBook") {
            // Your code for returning book...
        }
        else {
            cout << "Invalid command! Please try again." << endl;
        }
    }

    return 0;
}