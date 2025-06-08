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
            cout << "없는 책입니다." << endl;
        }
        else if (stock[title] == 0)
        {
            cout << "재고가 없습니다." << endl;
        }
        else
        {
            stock[title]--;
            cout << title << "을 대여했습니다." << endl;
        }
    }

    void returnBook(const string& title) {
        if (stock.count(title) == 0)
        {
            cout << "없는 책입니다." << endl;
        }
        else if(stock[title] == 3)
        {
            cout << "반납할 책이 없습니다." << endl;
        }
        else
        {
            stock[title]++;
            cout << title << "을 반납했습니다." << endl;
        }
    }

    void displayStock() {
        for (const auto& s : stock)
        {
            cout << "- " << s.first << ": " << s.second << "권" << endl;
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
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    
    void searchByTitle(string title) {
        Book* book = findBookByTitle(title);
        char input;

        if (!book)
        {
            cout << "해당 책이 없습니다." << endl;
            return;
        }
        cout << "- " << book->title << " by " << book->author << "을 대여하시겠습니까? (y/n)" << endl;
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
            cout << "해당 책이 없습니다." << endl;
        }
        else
        {
            for (auto* book : books)
            {
                cout << "- " << book->title << " by " << book->author << endl;
            }
            cout << "대여는 제목으로 검색해주세요" << endl;
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
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 제목으로 책 찾기/대여" << endl;
        cout << "4. 작가로 책 찾기" << endl;
        cout << "5. 책 반납하기" << endl;
        cout << "6. 재고 현황 출력" << endl;
        cout << "7. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            string title;
            cout << "검색할 책 제목: ";
            getline(cin, title);
            manager.searchByTitle(title);
        }
        else if (choice == 4) {
            string author;
            cout << "검색할 저자 이름: ";
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (choice == 5) {
            string title;
            cout << "반납할 책 제목: ";
            getline(cin, title);
            manager.returnBook(title);
        }
        else if (choice == 6) {
            manager.displayStock();
        }
        else if (choice == 7) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}
