#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "user.h"
#include "cart.h"
#include "item.h"
class Order;

class Customer : public User {
private:
    Cart cart;
    int id;
    std::string address;
    static int next_id;

public:
    Customer();
    Cart& get_cart();
    int get_id() const;

    void set_address(const std::string& addr);
    std::string get_address() const;

    bool registerr(const std::string& email,
                   const std::string& pass,
                   const std::string& addr);

    bool login(const std::string& email,
               const std::string& pass) override;

    void view_menu();

    void add_item_to_cart(const Item& t, int qty);

    bool update_cart(const Item& t, Cart& c);
    bool delete_item_from_cart(const Item& t, Cart& c);

    void place_order( Cart& c);

    std::string track_order(int order_id);
    void view_orders_history();
    bool cancel_order(int order_id);

};

#endif