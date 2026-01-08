#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    int id;
    static int next_id;
    std::string name;
    int price;
    int quantity;
    std::string description;

public:
    Item();
    Item(const std::string& n, int p, int q, const std::string& desc);

    void set_id(int e);
    void set_name(const std::string& n);
    void set_price(int e);
    void set_quantity(int e);
    void set_description(const std::string& n);

    int get_price() const;
    int get_quantity() const;
    std::string get_name() const;
    std::string get_description() const;
    int get_id() const;

    bool operator<(const Item& other) const;

    void display_items() const;
};

#endif