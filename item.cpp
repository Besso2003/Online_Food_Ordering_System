#include "item.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int Item::next_id = 1;

Item::Item() : id(next_id++), price(0), quantity(0) {}

Item::Item(const string& n, int p, int q, const string& desc)
    : id(next_id++), name(n), price(p), quantity(q), description(desc) {}


void Item::set_id(int e) {
    id = e;
}

void Item::set_name(const string& n) {
    name = n;
}

void Item::set_price(int e) {
    price = e;
}

void Item::set_quantity(int e) {
    quantity = e;
}

void Item::set_description(const string& n) {
    description = n;
}

int Item::get_price() const {
    return price;
}

int Item::get_quantity() const {
    return quantity;
}

string Item::get_name() const {
    return name;
}

string Item::get_description() const {
    return description;
}

int Item::get_id() const {
    return id;
}

bool Item::operator<(const Item& other) const {
    return id < other.id;
}

void Item::display_items() const {
    ifstream file("item.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int id, price, quantity;
        string name, description;

        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, temp, ','); price = stoi(temp);
        getline(ss, temp, ','); quantity = stoi(temp);
        getline(ss, description, ',');

        cout << "ID: " << id
             << " Name: " << name
             << " Price: " << price
             << " Quantity: " << quantity
             << " Description: " << description << endl;
    }
}