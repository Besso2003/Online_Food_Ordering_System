#include <iostream>
#include <fstream>
#include <map>
#include <utility>

#include "Item.h"
#include "Cart.h"

using namespace std;

int main()
{
    map<int, Item> menu;

    menu[1] = Item(1, "Burger", 50, 100, "Beef burger");
    menu[2] = Item(2, "Pizza", 80, 50, "Cheese pizza");

    Cart cart;
    cart.addItem(1, 2);
    cart.addItem(2, 1);

    cart.displayCart(menu);

    return 0;
}

