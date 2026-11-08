#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    int pages;
    int id;
    bool borrowed;

    void display() const {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPages: " << pages
             << "\nStatus: " << (borrowed ? "Borrowed" : "Available")
             << "\n";
    }
};

bool loadBooks(vector<Book>& books) {
    ifstream file("bookData.txt");
    if (!file) {
        cout << "Error: Cannot open bookData.txt\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream row(line);
        Book book;
        string pagesText, idText, status;

        if (!getline(row, book.title, ',') ||
            !getline(row, book.author, ',') ||
            !getline(row, pagesText, ',') ||
            !getline(row, idText, ',') ||
            !getline(row, status)) {
            cout << "Error: Invalid book record found.\n";
            return false;
        }

        try {
            size_t p1, p2;
            book.pages = stoi(pagesText, &p1);
            book.id = stoi(idText, &p2);

            if (p1 != pagesText.size() ||
                p2 != idText.size() ||
                book.pages <= 0) {
                return false;
            }
        } catch (...) {
            cout << "Error: Invalid number in book data.\n";
            return false;
        }

        if (!status.empty() && status.back() == '\r')
            status.pop_back();

        if (status != "true" && status != "false") {
            cout << "Error: Invalid borrowing status.\n";
            return false;
        }

        book.borrowed = (status == "true");
        books.push_back(book);
    }

    return true;
}

bool saveBooks(const vector<Book>& books) {
    ofstream file("bookData.txt");
    if (!file) {
        cout << "Error: Could not save book data.\n";
        return false;
    }

    for (const Book& book : books) {
        file << book.title << ","
             << book.author << ","
             << book.pages << ","
             << book.id << ","
             << (book.borrowed ? "true" : "false") << "\n";
    }

    file.close();
    return file.good();
}

Book* findBook(vector<Book>& books, int id) {
    for (Book& book : books) {
        if (book.id == id) return &book;
    }
    return nullptr;
}

int askNumber(const string& message) {
    string input;
    cout << message;
    getline(cin, input);

    try {
        size_t used;
        int number = stoi(input, &used);
        if (used == input.size()) return number;
    } catch (...) {}

    return -1;
}
void showAll(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    for (const Book& book : books)
        book.display();
}
void manageLoan(vector<Book>& books, bool borrow) {
    int id = askNumber("Enter book ID: ");
    Book* book = findBook(books, id);

    if (!book) {
        cout << "Book not found.\n";
        return;
    }

    book->display();

    if (borrow && book->borrowed) {
        cout << "This book is already borrowed.\n";
        return;
    }

    if (!borrow && !book->borrowed) {
        cout << "This book has not been borrowed.\n";
        return;
    }

    bool oldStatus = book->borrowed;
    book->borrowed = borrow;

    if (saveBooks(books)) {
        cout << (borrow ? "Book borrowed successfully.\n"
                        : "Book returned successfully.\n");
    } else {
        book->borrowed = oldStatus;
        cout << "The change could not be saved.\n";
    }
}
int main() {
    vector<Book> books;

    if (!loadBooks(books))
        return 1;

    cout << "WELCOME TO MIHAELA'S BOOK MANAGER\n";

    while (true) {
        cout << "\n===== BOOK MANAGER =====\n"
             << "1. Display all books\n"
             << "2. Search for a book\n"
             << "3. Borrow a book\n"
             << "4. Return a book\n"
             << "5. Exit\n";

        int choice = askNumber("Choose an option: ");

        if (choice == 1) {
            showAll(books);
        } else if (choice == 2) {
            int id = askNumber("Enter book ID: ");
            Book* book = findBook(books, id);

            if (book)
                book->display();
            else
                cout << "Book not found.\n";
        } else if (choice == 3) {
            manageLoan(books, true);
        } else if (choice == 4) {
            manageLoan(books, false);
        } else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}