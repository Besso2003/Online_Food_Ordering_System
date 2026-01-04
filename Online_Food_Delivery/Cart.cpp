#include "Cart.h"
#include <iostream>

void Cart::addItem(const Item& item, int quantity) {
    int id = item.getId();

    if (items.count(id)) {
        items[id].second += quantity;
    } else {
        items[id] = make_pair(item, quantity);
    }

    cout << "Item added to cart.\n";
}

void Cart::removeItem(int itemId) {
    if (items.erase(itemId)) {
        cout << "Item removed from cart.\n";
    } else {
        cout << "Item not found in cart.\n";
    }
}

double Cart::calculateTotal() const {
    double total = 0;

    for (const auto& entry : items) {
        const Item& item = entry.second.first;
        int quantity = entry.second.second;
        total += item.getPrice() * quantity;
    }

    return total;
}

void Cart::displayCart() const {
    cout << "\n--- CART ITEMS ---\n";

    if (items.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    for (const auto& entry : items) {
        const Item& item = entry.second.first;
        int quantity = entry.second.second;

        cout << "Item: " << item.getName()
             << " | Price: " << item.getPrice()
             << " | Quantity: " << quantity << endl;
    }

    cout << "Total = " << calculateTotal() << endl;
}
