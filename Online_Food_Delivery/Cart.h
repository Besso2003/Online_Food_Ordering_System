#ifndef CART_H
#define CART_H

#include <map>
#include "Item.h"

using namespace std;

class Cart {
private:
    // itemID -> (Item, quantity)
    map<int, pair<Item, int>> items;

public:
    void addItem(const Item& item, int quantity);
    void removeItem(int itemId);
    double calculateTotal() const;
    void displayCart() const;
};

#endif
