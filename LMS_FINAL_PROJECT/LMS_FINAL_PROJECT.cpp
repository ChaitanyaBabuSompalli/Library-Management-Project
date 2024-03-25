#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

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

    // Function to format book information for saving to file
    string formatForFile() const {
        stringstream ss;
        ss << title << "," << author << "," << id << "\n";
        return ss.str();
    }
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
    string booksFile = "books.txt"; // File to store books

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

    void displayBooks() const;
    void saveBooksToFile() const;
};

void Library::displayBooks() const {
    ifstream file(booksFile);
    if (file.is_open()) {
        string line;
        cout << "Books in the library:" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author;
            int id;
            getline(ss, title, ',');
            getline(ss, author, ',');
            ss >> id;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "ID: " << id << endl;
            cout << endl;
        }
        file.close();
    }
    else {
        cout << "Error opening file for reading." << endl;
    }
}

void Library::saveBooksToFile() const {
    ofstream file(booksFile, ios::out | ios::app); // Open file for appending
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.formatForFile();
        }
        file.close(); // Close the file
        cout << "Books saved to file successfully!" << endl;
    }
    else {
        cout << "Error opening file for writing." << endl;
    }
}



int main() {
    Library library;

    cout << "Welcome to the Library Management System!" << endl;
    cout << "Available commands:" << endl;
    cout << "- AddBook [title] [author] [id]" << endl;
    cout << "- AddUser [name] [id]" << endl;
    cout << "- SearchBook [title]" << endl;
    cout << "- BorrowBook [title] [user_id] [date]" << endl;
    cout << "- DisplayBooks" << endl;
    cout << "- ReturnBook [title]" << endl;
    cout << "- SaveBooks" << endl;
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
            string name, idStr;
            if (ss >> name >> idStr) {
                // Remove square brackets from idStr
                idStr = idStr.substr(1, idStr.size() - 2);
                int id = stoi(idStr);
                library.addUser(User(name, id));
                cout << "User added successfully!" << endl;
            }
            else {
                cout << "Invalid command format! Usage: AddUser [name] [id]" << endl;
            }
        }
        else if (action == "SearchBook") {
            string title;
            if (ss >> title) {
                Book* foundBook = library.searchBook(title);
                if (foundBook != nullptr) {
                    cout << "Book found:" << endl;
                    cout << "Title: " << foundBook->getTitle() << endl;
                    cout << "Author: " << foundBook->getAuthor() << endl;
                    cout << "ID: " << foundBook->getId() << endl;
                }
                else {
                    cout << "Book not found!" << endl;
                }
            }
            else {
                cout << "Invalid command format! Usage: SearchBook [title]" << endl;
            }
        }
        else if (action == "BorrowBook") {
            // Your code for borrowing book...
            string title, userIdStr, date;
            if (ss >> title >> userIdStr >> date) {
                // Remove square brackets from userIdStr
                userIdStr = userIdStr.substr(1, userIdStr.size() - 2);
                int userId = stoi(userIdStr);

                Book* bookToBorrow = library.searchBook(title);
                if (bookToBorrow != nullptr) {
                    User borrower("", userId); // Create a temporary user object with only ID
                    library.borrowBook(*bookToBorrow, borrower, date);
                    cout << "Book borrowed successfully!" << endl;
                }
                else {
                    cout << "Book not found!" << endl;
                }
            }
            else {
                cout << "Invalid command format! Usage: BorrowBook [title] [user_id] [date]" << endl;
            }
        }
        else if (action == "ReturnBook") {
            // Your code for returning book...
            string title;
            if (ss >> title) {
                Book* bookToReturn = library.searchBook(title);
                if (bookToReturn != nullptr) {
                    library.returnBook(*bookToReturn);
                    cout << "Book returned successfully!" << endl;
                }
                else {
                    cout << "Book not found!" << endl;
                }
            }
            else {
                cout << "Invalid command format! Usage: ReturnBook [title]" << endl;
            }
        }
        else if (action == "DisplayBooks") {
            library.displayBooks();
        }
        else if (action == "SaveBooks") {
            library.saveBooksToFile();
        }
        else {
            cout << "Invalid command! Please try again." << endl;
        }
    }

    return 0;
}