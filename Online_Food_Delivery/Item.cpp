#include "Item.h"
#include <iostream>

Item::Item()
{
    id = 0;
    price = 0;
    quantity = 0;
}

Item::Item(int id, string name, double price, int quantity, string description)
{
    this->id = id;
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->description_item = description;
}

int Item::getId() const
{
    return id;
}

string Item::getName() const
{
    return name;
}

double Item::getPrice() const
{
    return price;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::displayDetails() const
{
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Price: " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Description: " << description_item << endl;
}
