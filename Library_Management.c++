#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Book {
  string title;
  string author;
  string ISBN;
  bool isAvailable;
};

struct Transaction {
  string bookISBN;
  string borrowerName;
  time_t checkoutDate;
  time_t dueDate;
};

class Library {
private:
  vector<Book> books;
  vector<Transaction> transactions;

public:
  void addBook(const string &title, const string &author, const string &ISBN) {
    books.push_back({title, author, ISBN, true});
    cout << "Book added: " << title << " by " << author << " (ISBN: " << ISBN
         << ")" << endl;
  }

  void searchBook(const string &searchTerm) {
    cout << "Search Results for: " << searchTerm << endl;
    bool found = false;
    for (const auto &book : books) {
      if (book.title.find(searchTerm) != string::npos ||
          book.author.find(searchTerm) != string::npos ||
          book.ISBN == searchTerm) {
        cout << "Found Book: " << book.title << " by " << book.author
             << " (ISBN: " << book.ISBN << ")" << endl;
        found = true;
      }
    }
    if (!found) {
      cout << "No books found." << endl;
    }
  }

  void checkoutBook(const string &ISBN, const string &borrowerName) {
    for (auto &book : books) {
      if (book.ISBN == ISBN && book.isAvailable) {
        book.isAvailable = false;
        time_t now = time(0);
        time_t dueDate = now + (10 * 24 * 60 * 60);
        transactions.push_back({ISBN, borrowerName, now, dueDate});
        cout << "Book checked out to " << borrowerName
             << ". Due date: " << ctime(&dueDate);
        return;
      }
    }
    cout << "Book not available for checkout." << endl;
  }

  void returnBook(const string &ISBN) {
    for (auto &book : books) {
      if (book.ISBN == ISBN) {
        book.isAvailable = true;
        cout << "Book returned: " << book.title << endl;
        calculateFine(ISBN);
        return;
      }
    }
    cout << "This book was not checked out." << endl;
  }

  void calculateFine(const string &ISBN) {
    for (const auto &transaction : transactions) {
      if (transaction.bookISBN == ISBN) {
        time_t now = time(0);
        double seconds = difftime(now, transaction.dueDate);
        if (seconds > 0) {
          int daysOverdue = seconds / (60 * 60 * 24);
          double fine = daysOverdue * 0.50;
          cout << "Fine for overdue book: $" << fine << " for " << daysOverdue
               << " days." << endl;
        } else {
          cout << "No fine for this transaction." << endl;
        }
        return;
      }
    }
  }
};

int main() {
  Library library;
  int choice;
  string title, author, ISBN, borrowerName;

  do {
    cout << "\nLibrary Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
      cout << "Enter Book Title: ";
      getline(cin, title);
      cout << "Enter Author Name: ";
      getline(cin, author);
      cout << "Enter ISBN: ";
      getline(cin, ISBN);
      library.addBook(title, author, ISBN);
      break;
    case 2:
      cout << "Enter search term (title/author/ISBN): ";
      getline(cin, title);
      library.searchBook(title);
      break;
    case 3:
      cout << "Enter ISBN to checkout: ";
      getline(cin, ISBN);
      cout << "Enter Borrower's Name: ";
      getline(cin, borrowerName);
      library.checkoutBook(ISBN, borrowerName);
      break;
    case 4:
      cout << "Enter ISBN to return: ";
      getline(cin, ISBN);
      library.returnBook(ISBN);
      break;
    case 5:
      cout << "Exiting the program." << endl;
      break;
    default:
      cout << "Invalid choice, try again." << endl;
      break;
    }
  } while (choice != 5);

  return 0;
}

// output
/*

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 1
Enter Book Title:  c programming
Enter Author Name: balgu
Enter ISBN: 12Ib     2345
Book added:  c programming by balgu (ISBN: 12345)

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: python      1
Enter Book Title: Python program
Enter Author Name: henry
Enter ISBN: 45627
Book added: Python program by henry (ISBN: 45627)

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 2
Enter search term (title/author/ISBN): 12345
Search Results for: 12345
Found Book:  c programming by balgu (ISBN: 12345)

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 3
Enter ISBN to checkout: 12345
Enter Borrower's Name: monika
Book checked out to monika. Due date: Sun Aug 18 10:18:51 2024

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 4
Enter ISBN to return: 12345
Book returned:  c programming
No fine for this transaction.

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 2
Enter search term (title/author/ISBN): 12345
Search Results for: 12345
Found Book:  c programming by balgu (ISBN: 12345)

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Choose an option: 5
Exiting the program.

*/
