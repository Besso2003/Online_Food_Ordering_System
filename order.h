#ifndef ORDER_H
#define ORDER_H

#include <unordered_map>
#include "item.h"
#include "customer.h"

enum order_status { pending, shipped, delivered };
enum payment_method { cash, visa };

class Order {
private:
    int id;
    static int next_id;
    Customer* customer;
    std::unordered_map<int, std::pair<Item,int>> items; 
    order_status status;
    payment_method pm;
    double total_amount;

public:
    Order();

    int get_id() const;
    void set_id(int i);
    
    double get_total_amount()const;
    void set_total_amount(double a);

    void set_customer(Customer* c);
    Customer* get_customer() const;

    void set_items(const std::unordered_map<int, std::pair<Item,int>>& m);
    std::unordered_map<int, std::pair<Item,int>> get_items() const;

    void set_status(order_status s);
    order_status get_status() const;

    void set_payment_method(payment_method p);
    payment_method get_payment_method() const;
};

#endif
