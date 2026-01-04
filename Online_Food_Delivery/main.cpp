#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Item.h"
#include "Cart.h"

using namespace std;

int main() {
    map<int, Item> menu;

    ifstream file("items.txt");
    if (!file) {
        cout << "Failed to open items.txt\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        Item item(line);
        menu[item.getId()] = item;
    }
    file.close();

    cout << "--- MENU ---\n";
    for (auto& pair : menu) {
        pair.second.displayDetails();
        cout << endl;
    }

    Cart cart;
    cart.addItem(1, 2);
    cart.displayCart(menu);

    cart.removeItem(1);
    cart.displayCart(menu);

    return 0;
}
