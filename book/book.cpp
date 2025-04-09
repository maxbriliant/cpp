#include <string>
#include "book.h"
#include <iostream>

using namespace std;


Book::Book(string initTitle, string initAuthor, int initPages, double initPrice)
    : title(initTitle),
      author(initAuthor),
      pages(initPages),
      price(initPrice) {}


bool Book::isAffordable(double initBudget) const{
    return initBudget >= price;
}

void Book::printDetails(){
    cout << title << " von ";
    cout << author << endl;
    cout << pages << " Seiten" << endl;
    cout << price << "€" << endl;
}

void Book::setPrice(double newPrice){
    price = newPrice;
}
