#ifndef CART_H
#define CART_H

#include <map>
#include "Item.h"

using namespace std;

class Cart {
private:
    // itemID -> quantity
    map<int, int> items;

public:
    void addItem(int itemID, int quantity);
    void removeItem(int itemID);

    double calculateTotal(const map<int, Item>& menu) const;
    void displayCart(const map<int, Item>& menu) const;

    const map<int, int>& getItems() const;
};

#endif
