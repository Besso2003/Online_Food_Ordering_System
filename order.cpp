#include "order.h"
#include "customer.h"

int Order::next_id = 1;

Order::Order() : id(next_id++), status(pending), pm(cash), customer(nullptr) {}

int Order::get_id() const { return id; }
void Order::set_id(int i) { id = i; }

double Order::get_total_amount()const{return total_amount;}
void Order::set_total_amount(double a ){total_amount = a ;}

void Order::set_customer(Customer* c) { customer = c; }
Customer* Order::get_customer() const { return customer; }

void Order::set_items(const std::unordered_map<int, std::pair<Item,int>>& m) { items = m; }
std::unordered_map<int, std::pair<Item,int>> Order::get_items() const { return items; }

void Order::set_status(order_status s) { status = s; }
order_status Order::get_status() const { return status; }

void Order::set_payment_method(payment_method p) { pm = p; }
payment_method Order::get_payment_method() const { return pm; }
