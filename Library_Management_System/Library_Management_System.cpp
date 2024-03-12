#include <iostream>
#include <vector>
#include <string>

using namespace std;
//changes
// Define Book class
class Book {
    string title;
    string author;
    int id;
public:
    // Constructor
    Book(string t, string a, int i) : title(t), author(a), id(i) {}

    // Getters
    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getId() { return id; }
};

// Define Library class to manage books
class Library {
    vector<Book> books;
public:
    // Add book to library
    void addBook(Book b) {
        books.push_back(b);
    }

    // Search book by title
    Book* searchBook(string title) {
        for (int i = 0; i < books.size(); ++i) {
            if (books[i].getTitle() == title) {
                return &books[i];
            }
        }
        return nullptr; // Book not found
    }

    // Other functionalities can be added similarly
};

int main() {
    // Test your code here
    Library library;
    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", 1));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", 2));
    // Add more books...

    // Search for a book
    Book* book = library.searchBook("To Kill a Mockingbird");
    if (book != nullptr) {
        cout << "Book found: " << book->getTitle() << " by " << book->getAuthor() << endl;
    }
    else {
        cout << "Book not found!" << endl;
    }

    return 0;
}
