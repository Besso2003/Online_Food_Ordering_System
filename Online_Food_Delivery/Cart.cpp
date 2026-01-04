#include "Cart.h"
#include <iostream>

using namespace std;

void Cart::addItem(int itemID, int quantity)
{
    items[itemID] += quantity;
    cout << "Item added to cart.\n";
}

void Cart::removeItem(int itemID)
{
    if (items.erase(itemID))
        cout << "Item removed from cart.\n";
    else
        cout << "Item not found in cart.\n";
}

double Cart::calculateTotal(const map<int, Item>& menu) const
{
    double total = 0;

    for (const auto& entry : items)
    {
        int itemID = entry.first;
        int quantity = entry.second;

        if (menu.count(itemID))
            total += menu.at(itemID).getPrice() * quantity;
    }

    return total;
}

void Cart::displayCart(const map<int, Item>& menu) const
{
    cout << "\n--- CART ITEMS ---\n";

    if (items.empty())
    {
        cout << "Cart is empty.\n";
        return;
    }

    for (const auto& entry : items)
    {
        int itemID = entry.first;
        int quantity = entry.second;

        if (menu.count(itemID))
        {
            const Item& item = menu.at(itemID);
            cout << item.getName()
                 << " | Price: " << item.getPrice()
                 << " | Quantity: " << quantity << endl;
        }
    }

    cout << "Total = " << calculateTotal(menu) << endl;
}

const map<int, int>& Cart::getItems() const
{
    return items;
}
