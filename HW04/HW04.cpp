#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BorrowManager {
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(const Book& book, int quantity = 3) {
        stock[book.title] = quantity;
    }

    void borrowBook(const string& title) {
        if (stock.count(title) == 0)
        {
            cout << "���� å�Դϴ�." << endl;
        }
        else if (stock[title] == 0)
        {
            cout << "��� �����ϴ�." << endl;
        }
        else
        {
            stock[title]--;
            cout << title << "�� �뿩�߽��ϴ�." << endl;
        }
    }

    void returnBook(const string& title) {
        if (stock.count(title) == 0)
        {
            cout << "���� å�Դϴ�." << endl;
        }
        else if(stock[title] == 3)
        {
            cout << "�ݳ��� å�� �����ϴ�." << endl;
        }
        else
        {
            stock[title]++;
            cout << title << "�� �ݳ��߽��ϴ�." << endl;
        }
    }

    void displayStock() {
        for (const auto& s : stock)
        {
            cout << "- " << s.first << ": " << s.second << "��" << endl;
        }
    }
};

class BookManager {
private:
    vector<Book> books;
    BorrowManager& borrowManager;

    Book* findBookByTitle(const string& title) {
        for (auto& book : books)
        {
            if (book.title == title)
            {
                return &book;
            }
        }
        return nullptr;
    }

    vector<Book*> findBookByAuthor(const string& author) {
        vector<Book*> result;

        for (auto& book : books)
        {
            if (book.author == author)
            {
                result.push_back(&book);
            }
        }
        return result;
    }

public:
    BookManager(BorrowManager& bm) : borrowManager(bm) {}

    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        borrowManager.initializeStock(books.back());
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    
    void searchByTitle(string title) {
        Book* book = findBookByTitle(title);
        char input;

        if (!book)
        {
            cout << "�ش� å�� �����ϴ�." << endl;
            return;
        }
        cout << "- " << book->title << " by " << book->author << "�� �뿩�Ͻðڽ��ϱ�? (y/n)" << endl;
        cin >> input;
        if (input == 'y')
        {
            borrowManager.borrowBook(title);
        }
    }

    void searchByAuthor(string author) {
        vector<Book*> books = findBookByAuthor(author);

        if (books.empty())
        {
            cout << "�ش� å�� �����ϴ�." << endl;
        }
        else
        {
            for (auto* book : books)
            {
                cout << "- " << book->title << " by " << book->author << endl;
            }
            cout << "�뿩�� �������� �˻����ּ���" << endl;
        }
    }

    void returnBook(const string& title) {
        borrowManager.returnBook(title);
    }

    void displayStock() {
        borrowManager.displayStock();
    }
};

int main() {
    BorrowManager borrowManager;
    BookManager manager(borrowManager);

    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl;
        cout << "2. ��� å ���" << endl;
        cout << "3. �������� å ã��/�뿩" << endl;
        cout << "4. �۰��� å ã��" << endl;
        cout << "5. å �ݳ��ϱ�" << endl;
        cout << "6. ��� ��Ȳ ���" << endl;
        cout << "7. ����" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "å ����: ";
            getline(cin, title);
            cout << "å ����: ";
            getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            string title;
            cout << "�˻��� å ����: ";
            getline(cin, title);
            manager.searchByTitle(title);
        }
        else if (choice == 4) {
            string author;
            cout << "�˻��� ���� �̸�: ";
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (choice == 5) {
            string title;
            cout << "�ݳ��� å ����: ";
            getline(cin, title);
            manager.returnBook(title);
        }
        else if (choice == 6) {
            manager.displayStock();
        }
        else if (choice == 7) {
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0;
}
