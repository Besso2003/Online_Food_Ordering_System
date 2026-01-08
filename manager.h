#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "user.h"
#include "item.h"
#include "order.h"

class Manager : public User {
public:
    bool registerr(const std::string& email, const std::string& pass);
    bool login(const std::string& email, const std::string& pass) override;

    bool additem(const Item& t);
    bool update_item_by_id(const Item& t);
    bool delete_item(int item_id);

    void view_orders();
    void assign_order_to_delivery(int order_id, int de_id );
};

#endif