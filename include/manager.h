#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <book.h>
#include <person.h>
#include <memory>
#include <chrono>
#include <functional>
#include <algorithm>
using namespace std;
class Logger{
    public:
        Book* book;
        Person* person;
        chrono::time_point<std::chrono::system_clock> date;
        Logger(Book* book, Person* person){
            this->book = book;
            this->person = person;
            this->date = chrono::system_clock::now();
        }
};

class History{
    private:
        static History* historyPtr;
        History(){};
        static mutex mLocker;
    public:
        static History* getInstance(){
            mLocker.lock();
            if (nullptr == historyPtr){
                historyPtr = new History();
            }
            mLocker.unlock();
            return historyPtr;
        };
        vector<Logger*> history;
        Logger* logTracing(string title){
            for (int i = this->history.size()-1; i >= 0; i--)
            {   
                if(this->history[i]->book->getTitle() == title){
                    return this->history[i];
                }
            }
            return nullptr;
        }
        void Borrow(Book* book, Person* person){
            book->borrow(person);
            Logger* log = new Logger(book, person);
            this->history.push_back(log);
            person->setQouta(1);
        }
        void Return(string title){
            Logger* log = this->logTracing(title);
            log->book->returned();
            log->person->setQouta(-1);
        }
        void showBorrowed(Person* p){
            int bullet = 1;
            for (int i = 0; i < this->history.size(); ++i){
                if(this->history[i]->book->getBorrower() == p){
                    cout << bullet << ". " << this->history[i]->book->getTitle() << endl;
                    ++bullet;
                }
            }
        }
};

class BookInfo{
    protected:
        BookInfo(Library* library){
            this->lib= library;
        };
    public:
        Library* lib;
        void showBorrowed(){
            int bullet = 1;
            for (int i = 0; i < this->lib->books.size(); ++i){
                if (this->lib->books[i]->status() == true){
                    cout << bullet << ". " << this->lib->books[i]->getTitle() << endl;
                    ++bullet;
                }  
            } 
        };
        void showAvailable(){
            int bullet = 1;
            for (int i = 0; i < this->lib->books.size(); ++i){
                if (this->lib->books[i]->status() == false){
                    cout << bullet << ". " << this->lib->books[i]->getTitle() << endl;
                    ++bullet;
                }
            }
        };
};

class BookSorter{
    protected:
        BookSorter(Library* lib){
                this->lib = lib;
            }
    public:
        Library* lib;
        static bool byDate(const Book* a, const Book* b){
            return a->getReleaseDate() < b->getReleaseDate();
        }
        static bool byAuthor(const Book* a, const Book* b){
            return a->getAuthor() < b->getAuthor();
        }
        static bool byTitle(const Book* a, const Book* b){
            return a->getTitle() < b->getTitle();
        }
        void sortByDate(){
            sort(this->lib->books.begin(), this->lib->books.end(), byDate);
        }
        void sortByAuthor(){
            sort(this->lib->books.begin(), this->lib->books.end(), byAuthor);
        }
        void sortByTitle(){
            sort(this->lib->books.begin(), this->lib->books.end(), byTitle);
        }
};

class BookFinder{
    protected:
        BookFinder(Library* library){
            this->lib = library;
        }
    public:
        Library* lib;
        Book* findByTitle(string title){
            for(int i = 0; i < this->lib->books.size(); ++i){
                if (this->lib->books[i]->getTitle() == title){
                    return this->lib->books[i];
                }
            }
            return NULL;
        };
        vector<Book*> findByAuthor(string author){
            vector<Book*> results;
            for(int i = 0; i < this->lib->books.size(); ++i){
                if (this->lib->books[i]->getAuthor() == author){
                    results.push_back(this->lib->books[i]);
                }
            }
            return results;
        };
};

class BookManager: public BookFinder, public BookSorter, public BookInfo{
    private:
        static BookManager* managerPtr;
        BookManager(Library* lib): BookFinder(lib), BookSorter(lib), BookInfo(lib){};
        static mutex mLocker;
    public:
        static BookManager* getInstance(Library* lib){
            mLocker.lock();
            if (nullptr == managerPtr){
                managerPtr = new BookManager(lib);
            }
            mLocker.unlock();
            return managerPtr;
        }
};

BookManager* BookManager::managerPtr = nullptr;
mutex BookManager::mLocker;

History* History::historyPtr = nullptr;
mutex History::mLocker;

#endif