#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <string>
#include <book.h>
#include <manager.h>
#include <person.h>
using namespace std;

vector<Person*> person;
Library* library;

History* history;
BookManager* manager;
Person* current_user;
string name;

void initialize(vector<Person*>& person, vector<Book*>& books){
        // Initialize
    Person* minh = new Person("Minh", 209);
    Person* linh = new Person("Linh", 402);
    Person* phanh = new Person("Phanh", 409);

    person.push_back(minh);
    person.push_back(linh);
    person.push_back(phanh);

    Book* book1 = new Book("Hello", "Minh", 122);
    books.push_back(book1);
    Book* book2 = new Book("Smile", "Minh", 12);
    books.push_back(book2);
    Book* book3 = new Book("World", "Minh", 543);
    books.push_back(book3);
    Book* book4 = new Book("Sending", "Minh", 998);
    books.push_back(book4);
    cout << "Intialized successfully" << endl;
}

bool user_validation(string name, vector<Person*> person){
    system("clear");
    Person* p;
    for (int i = 0; i < person.size(); ++i) {
        if (person[i]->name == name) {
            cout << "Login successfully" << endl;
            current_user = person[i];
            return true;
        }
    }
    cout << "Your name is not found in database" << endl;
    cout << "Do you want to register?" << endl;
    cout << "1. Yes, I do" << endl;
    cout << "2. No, I do not" << endl;
    cout << "Enter your choice: ";
    int register_c;
    cin >> register_c;
    switch (register_c)
    {
    case 1:
        cout << "Enter your roll number: ";
        int rollnumber;
        cin >> rollnumber;
        p = new Person(name, rollnumber);
        person.push_back(p);
        current_user = p;
        cout << "Register successfully" << endl;
        cout << "Welcome " << name << "!" <<endl;
        system("clear");
        return true;
        break;
    case 2:
        return false;
        break;
    default:
        cout << "Wrong input, please enter your choice again!" << endl;
        break;
    }
    return false;
}

void book_validation(Library* lib){
    string title;
    system("clear");
    cout << "Enter a book name to take action: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);
    for (int i = 0; i < lib->books.size(); ++i){
        if (lib->books[i]->getTitle() == title){
            cout << "Book: " << title << " is found" << endl;
            cout << "Do you want to remove it?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            int rm_c;
            cin >> rm_c;
            switch (rm_c)
            {
            case 1:
                lib->deleteBook(title);
                return;
                break;
            case 2:
                return;
                break;                
            default:
                cout << "Wrong input, please enter your choice again!" << endl;
                break;
            }
        }
    }
    cout << "Please enter more information about the book" << endl;
    cout << "Author: ";
    string author;
    getline(cin, author);
    string publish_year;
    cout << "Publish year: ";
    getline(cin, publish_year);
    Book* b = new Book(title, author, stoi(publish_year));
    lib->books.push_back(b);
    system("clear");
    cout << "The book has been added!" << endl;
    cout << "Current amount of books: " << lib->books.size() << endl;
}

void menu_role(int choice, BookManager* manager, Library* library){   
    string bookname;
    bool breakout = true;
    Book* result;
    vector<Book*> results;
    string author;
    switch (choice)
    {
    case 1:
        /* User privileges */
        cout << "Enter your name to login/register: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        bool exit;
        exit = user_validation(name, person);
        if (exit == false){
            return;
        }else{
            while (breakout){
                cout << "What do you want to do?" << endl;
                cout << "1. Show available book" << endl;
                cout << "2. Borrow a book" << endl;
                cout << "3. Return your borrowed book" << endl;
                cout << "4. Check your status" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                int user_c;
                cin >> user_c;
                string return_book_name;
                switch (user_c)
                {
                case 1:
                    system("clear");
                    cout << "The available books are: " << endl;
                    manager->showAvailable();
                    cout << "*****************************" << endl;
                    break;
                case 2:
                    while(true){
                        system("clear");
                        manager->showAvailable();
                        cout << "Enter the name of the book: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, bookname);
                        result = manager->findByTitle(bookname);
                        if (result != NULL){
                            history->Borrow(result, current_user);
                            cout << "Borrow successfully!" << endl;
                            break;
                        }else{
                            cout << "Book not found, please try again" << endl;
                        }
                    }
                    
                    break;
                case 3:
                    system("clear");
                    cout << "Your borrowed book: " << endl;
                    history->showBorrowed(current_user);
                    cout << "Which book do you want to return: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, return_book_name);
                    history->Return(history->logTracing(return_book_name)->book->getTitle());
                    cout << "Your borrowed book: " << return_book_name << " are returned successfully!" << endl;
                    break;
                case 4:
                    system("clear");
                    cout << "You have borrowed " << current_user->qouta << "/5 book" << endl;
                    break;
                case 5:
                    breakout = false;
                    break;
                default:
                    cout << "Wrong input, please enter your choice again!" << endl; 
                    break;
                }
            }
            break;
        }
    case 2:
        cout << "You have been logged as an administrator" << endl;
        while (breakout){
            cout << "What do you want to do?" << endl;
            cout << "1. Add/remove book" << endl;
            cout << "2. Show book" << endl;
            cout << "3. Find book" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            int admin_c;
            cin >> admin_c;
            switch (admin_c)
            {
            case 1:            
                book_validation(library);
                break;
            case 2:
                system("clear");
                cout << "How do you want the books are listed?" << endl;
                cout << "1. Show all books" << endl;
                cout << "2. Show available books" << endl;
                cout << "3. Sort book by title" << endl;
                cout << "Enter your choice: ";
                int bstat_c;
                cin >> bstat_c;
                switch (bstat_c)
                {
                case 1:
                    system("clear");
                    library->showBook();
                    break;
                case 2:
                    system("clear");
                    manager->showAvailable();
                    break;
                case 3:
                    system("clear");
                    manager->sortByTitle();
                    library->showBook();
                    break;
                default:
                    cout << "Wrong input, please enter your choice again!" << endl; 
                }
                break;
            case 3:
                system("clear");
                cout << "How do you want to find the book: " << endl;
                cout << "1. Find by title" << endl;
                cout << "2. Find by author" << endl;
                cout << "Enter your choice: ";
                int fbook_c;
                cin >> fbook_c;
                switch (fbook_c)
                {
                case 1:
                    cout << "Enter the name of the book: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, bookname);
                    result = manager->findByTitle(bookname);
                    system("clear");
                    cout << "Your book is found: " << endl;
                    cout << result->getTitle() << " by " << result->getAuthor() << " in " << result->getReleaseDate() << endl;
                    break;
                case 2:
                    cout << "Enter the author of the book: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, author);
                    results = manager->findByAuthor(author);
                    system("clear");
                    cout << "Your books are found: " << endl;
                    for (int i = 0; i < results.size(); ++i){
                        cout << i+1 << ". " << results[i]->getTitle() << " by " << results[i]->getAuthor() << " in " << results[i]->getReleaseDate() << endl;
                    }
                    break;
                default:
                    cout << "Wrong input, please enter your choice again!" << endl; 
                }
                break;
            case 4:
                breakout = false;
                break;
            default:
                cout << "Wrong input, please enter your choice again!" << endl; 
            }
        }
        break;
    default:
        break;
    }
}

int main(){
    
    Library* library;
    library = Library::getInstance();
    history = History::getInstance();
    manager = BookManager::getInstance(library);
    initialize(person, library->books);
    int c;
    bool exit_flag = true;
    system("clear");
    while (exit_flag)
    {
        system("clear");
        cout << "==== Welcome to Library Management System ====" << endl;
        cout << "1. Login as user" << endl;
        cout << "2. Login as admin" << endl;
        cout << "3. Exit the system" << endl;
        cout << "Please choose your option: ";
        cin >> c; 
        if (c == 3)
        {
            exit_flag = false;
        }else{
            system("clear");
            menu_role(c, manager, library);
        }
    }
    cout << "Thanks for using Library Management System!" << endl;
}