#include "customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "order.h"
using namespace std;

int Customer::next_id = 1;

Customer::Customer()
{
    id = next_id++;
}
Cart &Customer::get_cart()
{
    return cart;
}

int Customer::get_id() const
{
    return id;
}

void Customer::set_address(const string &addr)
{
    address = addr;
}

string Customer::get_address() const
{
    return address;
}
bool Customer::registerr(const string &email,
                         const string &pass,
                         const string &addr)
{
    ifstream file("customer.txt");
    string line;

    while (getline(file, line))
    {
        string e;
        stringstream ss(line);
        getline(ss, e, ',');
        if (e == email)
        {
            return false;
        }
    }
    set_address(addr);
    ofstream out("customer.txt", ios::app);
    out << email << "," << pass << "," << addr << "\n";
    return true;
}
bool Customer::login(const string &email, const string &pass)
{
    ifstream file("customer.txt");
    string line;

    while (getline(file, line))
    {
        string e, p;
        stringstream ss(line);
        getline(ss, e, ',');
        getline(ss, p, ',');

        if (e == email && p == pass)
            return true;
    }
    return false;
}
void Customer::view_menu()
{
    ifstream file("item.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, price, quantity;
        string name, description;

        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, temp, ',');
        price = stoi(temp);
        getline(ss, temp, ',');
        quantity = stoi(temp);
        getline(ss, description);

        cout << "ID: " << id
             << " Name: " << name
             << " Price: " << price
             << " Quantity: " << quantity
             << " Description: " << description << endl;
    }
    file.close();
}

void Customer::add_item_to_cart(const Item &t, int qty)
{
    cart.add_item(t, qty);
}

bool Customer::update_cart(const Item &t, Cart &c)
{
    auto &items = c.get_items();
    auto it = items.find(t.get_id());
    if (it != items.end())
    {
        it->second.first = t;
        it->second.second = t.get_quantity();
        return true;
    }
    return false;
}

bool Customer::delete_item_from_cart(const Item &t, Cart &c)
{
    auto &items = c.get_items();
    if (items.erase(t.get_id()) > 0)
    {
        return true;
    }
    return false;
}

void Customer::place_order(Cart &c)
{
    if (c.get_items().empty())
    {
        cout << "Cart is empty. Add items first!\n";
        return;
    }
    Order o;
    o.set_items(c.get_items());
    o.set_customer(this);
    o.set_status(order_status::pending);

    double total_amount = 0;

    ifstream itemFileIn("item.txt");
    ofstream tempFile("temp_items.txt");
    string line;

    while (getline(itemFileIn, line))
    {
        stringstream ss(line);
        string id_str, name, price_str, qty_str, desc;

        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, price_str, ',');
        getline(ss, qty_str, ',');
        getline(ss, desc, ',');

        int id = stoi(id_str);
        double price = stod(price_str);
        int quantity = stoi(qty_str);

        auto &order_items = o.get_items();
        if (order_items.find(id) != order_items.end())
        {
            int order_qty = order_items[id].second;

            quantity -= order_qty;
            if (quantity < 0)
                quantity = 0;
            total_amount += order_qty * price;
        }

        tempFile << id << "," << name << "," << price << "," << quantity << "," << desc << "\n";
    }

    itemFileIn.close();
    tempFile.close();

    remove("item.txt");
    rename("temp_items.txt", "item.txt");

    // -------------------- 2. Save order in orders file --------------------
    o.set_total_amount(total_amount);

    ofstream out("order.txt", ios::app);
    out << o.get_customer()->get_id() << "|";
    out << o.get_id() << "|";
    out << this->get_address() << "|";

    for (auto &pair : o.get_items())
    {
        out << pair.second.first.get_id() << ":" << pair.second.second << ",";
    }

    out << "|" << (int)o.get_payment_method();
    out << "|" << o.get_total_amount();
    out << "|" << (int)o.get_status() << "\n";
    out.close();

    c.clear();
}

string Customer::track_order(int order_id)
{
    ifstream file("order.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, or_id;
        string items, addr;
        string payment_method;
        int payment_method_int;
        int status_int;

        getline(ss, temp, '|');
        id = stoi(temp);
        getline(ss, temp, '|');
        or_id = stoi(temp);
        getline(ss, addr, '|');
        getline(ss, items, '|');
        getline(ss, payment_method, '|');
        payment_method_int = stoi(payment_method);
        string totalamount;
        getline(ss, totalamount, '|');
        getline(ss, temp, '|');
        status_int = stoi(temp);

        if (or_id == order_id)
        {
            file.close();
            string status_str;
            switch (status_int)
            {
            case 0:
                status_str = "Pending";
                break;
            case 1:
                status_str = "Shipped";
                break;
            case 2:
                status_str = "Delivered";
                break;
            default:
                status_str = "Unknown";
                break;
            }
            return status_str;
        }
    }

    file.close();
    return "Order not found";
}

void Customer::view_orders_history()
{
    ifstream file("order.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, status_int, payment_method_int, or_id;
        string items, addr;

        getline(ss, temp, '|');
        id = stoi(temp);
        getline(ss, temp, '|');
        or_id = stoi(temp);
        getline(ss, addr, '|');
        getline(ss, items, '|');
        getline(ss, temp, '|');
        payment_method_int = stoi(temp);
        string totalamount;
        getline(ss, totalamount, '|');
        getline(ss, temp, '|');
        status_int = stoi(temp);

        if (id != this->id)
            continue;

        stringstream items_stream(items);
        string value;

        cout << "Order ID: " << or_id << endl;
        cout << "Customer Address: " << addr << endl;

        while (getline(items_stream, value, ','))
        {
            if (value.empty())
                continue;
            stringstream final_values(value);
            string id_str, qty;
            getline(final_values, id_str, ':');
            getline(final_values, qty, ':');
            cout << "(item " << id_str << " with quantity " << qty << ")" << endl;
        }

        string payment_method_str = (payment_method_int == 0 ? "Cash" : payment_method_int == 1 ? "Visa"
                                                                                                : "Unknown");
        cout << "Payment Method: " << payment_method_str << endl;
        cout << "Total amount : " << totalamount << endl;

        string status_str;
        switch (status_int)
        {
        case 0:
            status_str = "Pending";
            break;
        case 1:
            status_str = "Shipped";
            break;
        case 2:
            status_str = "Delivered";
            break;
        default:
            status_str = "Unknown";
            break;
        }
        cout << "Status: " << status_str << endl;
        cout << "-----------------------------" << endl;
    }

    file.close();
}

bool Customer::cancel_order(int order_id)
{
    ifstream file("order.txt");
    ofstream tempFile("temp2.txt");

    if (!file.is_open() || !tempFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    bool deleted = false;
    // First, we store the items of the order being canceled
    std::unordered_map<int, int> canceled_items;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, or_id;
        getline(ss, temp, '|');
        id = stoi(temp);
        getline(ss, temp, '|');
        or_id = stoi(temp);

        if (or_id == order_id)
        {
            deleted = true;
            string addr, items_str;
            getline(ss, addr, '|');
            getline(ss, items_str, '|');

            stringstream item_ss(items_str);
            string item_pair;
            while (getline(item_ss, item_pair, ','))
            {
                if (!item_pair.empty())
                {
                    int colon_pos = item_pair.find(':');
                    int item_id = stoi(item_pair.substr(0, colon_pos));
                    int qty = stoi(item_pair.substr(colon_pos + 1));
                    canceled_items[item_id] = qty;
                }
            }

            continue;
        }
        else
        {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();
    remove("order.txt");
    rename("temp2.txt", "order.txt");
    // -------------------- Re-add quantities to items file --------------------
    if (!canceled_items.empty())
    {
        ifstream itemFileIn("items.txt");
        ofstream tempItemFile("temp_items.txt");

        if (!itemFileIn.is_open() || !tempItemFile.is_open())
        {
            cout << "Error opening items file!" << endl;
            return deleted;
        }

        while (getline(itemFileIn, line))
        {
            stringstream ss(line);
            string id_str, name, price_str, qty_str, desc;

            getline(ss, id_str, '|');
            getline(ss, name, '|');
            getline(ss, price_str, '|');
            getline(ss, qty_str, '|');
            getline(ss, desc, '|');

            int id = stoi(id_str);
            int quantity = stoi(qty_str);

            // If this item was in the canceled order, add back the quantity
            if (canceled_items.find(id) != canceled_items.end())
            {
                quantity += canceled_items[id];
            }

            tempItemFile << id << "|" << name << "|" << price_str << "|" << quantity << "|" << desc << "\n";
        }

        itemFileIn.close();
        tempItemFile.close();

        remove("items.txt");
        rename("temp_items.txt", "items.txt");
    }

    return deleted;
}
