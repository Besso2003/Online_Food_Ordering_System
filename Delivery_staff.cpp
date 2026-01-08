#include "delivery_staff.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int Delivery_staff::next_id = 1;

Delivery_staff::Delivery_staff()
{
    id = next_id++;
}

int Delivery_staff::get_id() const
{
    return id;
}

bool Delivery_staff::registerr(const string &email, const string &pass)
{
    ifstream file("Delivery_staff.txt");
    bool flag = false;
    string line;

    while (getline(file, line))
    {
        string e, p, i;
        stringstream ss(line);
        getline(ss, i, ',');
        getline(ss, e, ',');
        getline(ss, p, ',');

        if (email == e)
        {
            flag = true;
            break;
        }
    }
    file.close();

    if (!flag)
    {
        ofstream out("Delivery_staff.txt", ios::app);
        out << this->id << "," << email << "," << pass << "\n";
        out.close();
        return true;
    }

    return false;
}

bool Delivery_staff::login(const string &email, const string &pass)
{
    ifstream file("Delivery_staff.txt");
    string line;

    while (getline(file, line))
    {

        string e, p, i;
        stringstream ss(line);
        getline(ss, i, ',');
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

void Delivery_staff::view_assigned_orders()
{
    ifstream file("order.txt");
    if (!file.is_open())
    {
        cout << "Unable to open order file.\n";
        return;
    }

    string line;
    bool found_any = false;

    cout << "===== Orders assigned to Delivery Staff ID: " << id << " =====\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp_str, addr, items_str;
        int cust_id, or_id, payment, status, delivery_id;
        string total_amount;
        // Parse order line
        getline(ss, temp_str, '|');
        cust_id = stoi(temp_str);

        getline(ss, temp_str, '|');
        or_id = stoi(temp_str);

        getline(ss, addr, '|');
        getline(ss, items_str, '|');

        getline(ss, temp_str, '|');
        payment = stoi(temp_str);
        getline(ss, total_amount, '|');

        getline(ss, temp_str, '|');
        status = stoi(temp_str);

        if (getline(ss, temp_str, '|'))
            delivery_id = stoi(temp_str);
        else
            delivery_id = -1;

        if (delivery_id == id)
        {
            found_any = true;

            string status_text;
            switch (status)
            {
            case 0:
                status_text = "Pending";
                break;
            case 1:
                status_text = "Assigned";
                break;
            case 2:
                status_text = "Delivered";
                break;
            default:
                status_text = "Unknown";
                break;
            }

            string payment_text = (payment == 0) ? "Cash" : "Visa";

            stringstream item_ss(items_str);
            string item_pair;
            string readable_items;
            while (getline(item_ss, item_pair, ','))
            {
                if (!item_pair.empty())
                {
                    int colon_pos = item_pair.find(':');
                    string item_id_str = item_pair.substr(0, colon_pos);
                    string qty_str = item_pair.substr(colon_pos + 1);
                    readable_items += "Item ID " + item_id_str + " x" + qty_str + "; ";
                }
            }

            cout << "Order ID: " << or_id
                 << " | Customer ID: " << cust_id
                 << " | Address: " << addr
                 << " | Items: " << readable_items
                 << " | Payment: " << payment_text
                 << " | Total Amount " << total_amount
                 << " | Status: " << status_text << "\n";
        }
    }

    if (!found_any)
        cout << "No orders assigned.\n";

    file.close();
}
