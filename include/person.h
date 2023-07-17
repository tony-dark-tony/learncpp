#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person{
    public:
        string name;
        int rollnumber;
        int qouta = 0;
        Person(string name, int rollnumber){
            this->name = name;
            this->rollnumber = rollnumber;
        }
        bool setQouta(int index = 1){
            if (this->qouta < 5 && this->qouta >= 0){
                this->qouta+=index;
                return true;
            }else{
                return false;
            }
        }
};
#endif