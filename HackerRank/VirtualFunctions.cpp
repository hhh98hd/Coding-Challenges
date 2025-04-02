// https://www.hackerrank.com/challenges/virtual-functions/problem?isFullScreen=true

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Person {
    public:
        virtual void getdata() {};
        virtual void putdata() {};
    
    protected:
        int id;
        int age;
        string name;
    };
    
class Professor : public Person {
private:
    int publications;

protected:
    static int cur_id;

public:
    Professor() {
        cur_id += 1;
        this->id = cur_id;
    }

    void getdata() override {
        cin >> this->name >> this->age >> this->publications;
    }

    void putdata() override {
        cout << this->name << " " << this->age << " " << this->publications << " " << this->id << endl;
    }
};
    
class Student : public Person {
private:
    int marks[6];

    int totalMark () {
        int total = 0;

        for(int i = 0; i < 6; i++)
            total += this->marks[i];

        return total;
    }

protected:
    static int cur_id;

public:
    Student() {
        cur_id += 1;
        this->id = cur_id;
    }

    void getdata() override {
        cin >> this->name >> this->age;
        for(int i = 0; i < 6; i++)
            cin >> this->marks[i];
    }

    void putdata() override {
        cout << this->name << " " << this->age << " " << this->totalMark() << " " << this->id << endl;
    }
};
    
int Professor::cur_id = 0;
int Student::cur_id = 0;

int main() {
    return 0;
}