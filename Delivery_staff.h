#ifndef DELIVERY_STAFF_H
#define DELIVERY_STAFF_H
#include "user.h"
#include <string>
class Delivery_staff : public User
{
private:
    int id;
    static int next_id;

public:
    Delivery_staff();

    int get_id() const;
    bool registerr(const std::string& email, const std::string& pass);
    bool login(const std::string& email, const std::string& pass) override;
    void view_assigned_orders();
};

#endif
