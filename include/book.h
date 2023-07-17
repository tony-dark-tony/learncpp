#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <person.h>
#include <mutex>

using namespace std;
class Book{
    protected:
        string title;
        string author;
        int releaseDate;
        bool isBorrowed;
        Person* person;
    public:
        Book(string title, string author, int releaseDate){
            this->title = title;
            this->author = author;
            this->releaseDate = releaseDate;
            this->isBorrowed = false;
        };
        string getTitle() const{
            return this->title;
        }
        string getAuthor() const{
            return this->author;
        }
        int getReleaseDate() const{
            return this->releaseDate;
        }
        bool status() const{
            return this->isBorrowed;
        }
        Person* getBorrower() const{
            return this->person;
        }
        void borrow(Person* p){
            this->isBorrowed = true;
            this->person = p;
        }
        void returned(){
            this->isBorrowed = false;
            this->person = NULL;
        }
};

class Library{
    private:
        Library(){};
        static Library* ptrLibrary;
        static mutex mLocker;
    public:
        vector<Book*> books;
        void addBook(Book* book){
            this->books.push_back(book);
        };
        void deleteBook(string title){
            for(int i = 0; i < this->books.size(); ++i){
                if (this->books[i]->getTitle() == title){
                    cout << this->books[i]->getTitle();
                    this->books.erase(this->books.begin() + i);
                }
            }
        };
        void showBook(){
            for (int i = 0; i < this->books.size(); ++i){
                cout << i+1 << ". " << this->books[i]->getTitle() << " - Author: " << this->books[i]->getAuthor() << " - Publish year: " << this->books[i]->getReleaseDate() << endl;
            }
        }
        static Library* getInstance(){
            mLocker.lock();
            if (nullptr == ptrLibrary){
                ptrLibrary = new Library();
            }
            mLocker.unlock();
            return ptrLibrary;
        }
};

Library* Library::ptrLibrary = nullptr;
mutex Library::mLocker;
#endif