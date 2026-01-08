#include "manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "delivery_staff.h"
using namespace std;

bool Manager::registerr(const string &email, const string &pass)
{
    ifstream file("manager.txt");
    string line;

    while (getline(file, line))
    {
        string e;
        stringstream ss(line);
        getline(ss, e, ',');
        if (e == email)
        {
            file.close();
            return false;
        }
    }
    file.close();

    ofstream out("manager.txt", ios::app);
    out << email << "," << pass << "\n";
    out.close();

    return true;
}

bool Manager::login(const string &email, const string &pass)
{
    ifstream file("manager.txt");
    string line;

    while (getline(file, line))
    {
        string e, p;
        stringstream ss(line);
        getline(ss, e, ',');
        getline(ss, p, ',');

        if (e == email && p == pass)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool Manager::additem(const Item &t)
{
    ifstream file("item.txt");
    string line;
    bool flag = true;

    while (getline(file, line))
    {
        string temp, name;
        int id;
        stringstream ss(line);
        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, name, ',');

        if (t.get_name() == name)
        {
            flag = false;
            break;
        }
    }
    file.close();

    if (flag)
    {
        ofstream out("item.txt", ios::app);
        out << t.get_id() << ","
            << t.get_name() << ","
            << t.get_price() << ","
            << t.get_quantity() << ","
            << t.get_description() << "\n";
        out.close();
        return true;
    }
    return false;
}

bool Manager::update_item_by_id(const Item &t)
{
    ifstream file("item.txt");
    ofstream temp("temp.txt");
    string line;
    bool updated = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        int id = stoi(idStr);

        if (id == t.get_id())
        {
            temp << t.get_id() << ","
                 << t.get_name() << ","
                 << t.get_price() << ","
                 << t.get_quantity() << ","
                 << t.get_description() << "\n";
            updated = true;
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove("item.txt");
    rename("temp.txt", "item.txt");

    return updated;
}

bool Manager::delete_item(int item_id)
{
    ifstream file("item.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        int id = stoi(idStr);

        if (id == item_id)
        {
            deleted = true;
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove("item.txt");
    rename("temp.txt", "item.txt");

    return deleted;
}

void Manager::view_orders()
{
    ifstream file("order.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, status_int, or_id;
        string items, addr, payment_method;
        int payment_method_int;
        double total_amount;

        getline(ss, temp, '|');
        id = stoi(temp);
        getline(ss, temp, '|');
        or_id = stoi(temp);
        getline(ss, addr, '|');
        getline(ss, items, '|');
        getline(ss, payment_method, '|');
        payment_method_int = stoi(payment_method);
        getline(ss, temp, '|');
        total_amount = stod(temp);
        getline(ss, temp, '|');
        status_int = stoi(temp);

        stringstream items_stream(items);
        string value;

        cout << "Customer ID: " << id << endl;
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
            cout << "( item " << id_str << " with quantity " << qty << " )" << endl;
        }
        cout << endl;

        string payment_method_str = (payment_method_int == 0 ? "cash" : payment_method_int == 1 ? "visa"
                                                                                                : "unknown");
        cout << "Payment Method: " << payment_method_str << endl;

        cout << "total amount : " << total_amount <<endl;

        string status_str;
        switch (status_int)
        {
        case 0:
            status_str = "Pending";
            break;
        case 1:
            status_str = "shipped";
            break;
        case 2:
            status_str = "delivered";
            break;
        default:
            status_str = "unknown";
            break;
        }
        cout << "Status: " << status_str << endl;
        cout << "-----------------------------" << endl;
    }

    file.close();
}

void Manager::assign_order_to_delivery(int order_id, int de_id)
{
    // -------------------- 1. Check if delivery staff exists --------------------
    ifstream dfile("Delivery_staff.txt");
    if (!dfile.is_open()) {
        cout << "Cannot open Delivery_staff.txt\n";
        return;
    }

    bool delivery_exists = false;
    string dline;

    while (getline(dfile, dline))
    {
        stringstream ss(dline);
        string id_str, email, password;
        getline(ss, id_str, ',');
        int id = stoi(id_str);

        if (id == de_id)
        {
            delivery_exists = true;
            break;
        }
    }
    dfile.close();

    if (!delivery_exists)
    {
        cout << "Delivery staff not found\n";
        return;
    }

    // -------------------- 2. Update order with delivery staff --------------------
    ifstream orderFile("order.txt");
    ofstream tempFile("temp.txt");

    if (!orderFile.is_open() || !tempFile.is_open()) {
        cout << "Cannot open order files\n";
        return;
    }

    string line;
    bool order_found = false;

    while (getline(orderFile, line))
    {
        stringstream ss(line);
        string cust_str, or_str, temp_str;
        string addr, items_str;
        int cust_id, or_id, payment, status, delivery_id;
        double total_amount;

        getline(ss, cust_str, '|');
        cust_id = stoi(cust_str);

        getline(ss, or_str, '|');
        or_id = stoi(or_str);

        getline(ss, addr, '|');
        getline(ss, items_str, '|');

        getline(ss, temp_str, '|');
        payment = stoi(temp_str);

        getline(ss, temp_str, '|');
        total_amount = stod(temp_str);

        getline(ss, temp_str, '|');
        status = stoi(temp_str);

        if (getline(ss, temp_str, '|'))
            delivery_id = stoi(temp_str);
        else
            delivery_id = -1;

       if (or_id == order_id)
        {
            order_found = true;
            delivery_id = de_id;
            status = 1;
        }

        tempFile << cust_str << "|"
                 << or_id << "|"
                 << addr << "|"
                 << items_str << "|"
                 << payment << "|"
                 << total_amount << "|"
                 << status << "|"
                 << delivery_id << "\n";
    }

    orderFile.close();
    tempFile.close();

    remove("order.txt");
    rename("temp.txt", "order.txt");

    if (order_found)
        cout << "Order assigned successfully\n";
    else
        cout << "Order not found\n";
}
