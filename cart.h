#ifndef CART_H
#define CART_H

#include <unordered_map>
#include "item.h"

class Cart
{
private:
    std::unordered_map<int, std::pair<Item, int>> items;

public:
    void set_items(const std::unordered_map<int, std::pair<Item, int>> &m);
    std::unordered_map<int, std::pair<Item, int>> &Cart::get_items();

    void add_item(const Item &t, int qty);
    void Cart::clear();
};

#endif
