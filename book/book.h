#ifndef BOOK_H // Include guard: Prevents multiple inclusions
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int pages;
    double price;

public:
    Book(std::string initTitle, std::string initAuthor, int initPages, double initPrice);

    void printDetails();
    void setPrice(double newPrice);
    bool isAffordable(double budget) const;

};

#endif