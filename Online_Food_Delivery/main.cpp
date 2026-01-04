#include <iostream>
#include "Item.h"
#include "Cart.h"

using namespace std;

int main() {

    cout << "=== Testing Cart Class ===\n\n";

    Item burger(1, "Burger", 50.0, 100, "Beef burger");
    Item pizza(2, "Pizza", 80.0, 50, "Cheese pizza");

    Cart cart;

    cart.addItem(burger, 2);
    cart.addItem(pizza, 1);
    cart.addItem(burger, 1);

    cart.displayCart();

    cart.removeItem(2);

    cart.displayCart();

    return 0;
}
