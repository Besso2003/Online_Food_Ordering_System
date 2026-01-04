#include "Item.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>


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

Item::Item(string line)
{
    size_t pos;

    pos = line.find(",");
    id = atoi(line.substr(0, pos).c_str());
    line.erase(0, pos + 1);

    pos = line.find(",");
    name = line.substr(0, pos);
    line.erase(0, pos + 1);

    pos = line.find(",");
    price = atof(line.substr(0, pos).c_str());
    line.erase(0, pos + 1);

    pos = line.find(",");
    quantity = atoi(line.substr(0, pos).c_str());
    line.erase(0, pos + 1);

    description_item = line;
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

string Item::toFileString() const
{
    stringstream ss;
    ss << id << ","
       << name << ","
       << price << ","
       << quantity << ","
       << description_item;

    return ss.str();
}


void Item::displayDetails() const
{
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Price: " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Description: " << description_item << endl;
}
