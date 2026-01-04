#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item
{
private:
    int id;
    string name;
    double price;
    int quantity;
    string description_item;

public:
    Item();
    Item(int id, string name, double price, int quantity, string description);

    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void displayDetails() const;
};

#endif
