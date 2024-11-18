#pragma once

#include<iostream>
#include<cstring>
using namespace std;

class LoanBookData
{
private:
    string name; // Name of the book
    int code;    // Code or identifier of the book
    string author; // Author of the book
    int year;    // Publication year of the book
    int loan_count;  // Number of times the book has been loaned

public:
    LoanBookData() { this->loan_count = 0; } // Default constructor, initializes loan count to 0
    ~LoanBookData() {};   // Destructor
    // Setters for individual attributes
    void setBookData(string name, int code, string author, int year) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
    }

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    // Increment the loan count when the book is loaned
    void updateCount() { this->loan_count += 1; }
    // Set the loan count to a specific value
    void setloancount(int count) { this->loan_count = count; }
    // Getters for individual attributes
    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }

    // Get the current loan count
    int getLoanCount() { return loan_count; }
};