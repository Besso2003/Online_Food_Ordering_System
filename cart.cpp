#include "cart.h"


void Cart::add_item(const Item& t, int qty) {
    items[t.get_id()] = {t, qty};
}

std::unordered_map<int, std::pair<Item, int>>& Cart::get_items() {
    return items;
}

void Cart::set_items(const std::unordered_map<int, std::pair<Item, int>>& m) {
    items = m;
}

void Cart::clear() {
    items.clear();
}
