#include <iostream>
#include <string>
#include "customer.h"
#include "manager.h"
#include "item.h"
#include "cart.h"
#include "order.h"
#include "delivery_staff.h"

using namespace std;

void manager_menu(Manager &manager);
void customer_menu(Customer &customer);
void delivery_menu(Delivery_staff &deli);

int main()
{
    Manager manager;
    Customer currentCustomer;
    Delivery_staff currentDeli;

    while (true)
    {
        cout << "\n===== ONLINE FOOD ORDERING SYSTEM =====\n";
        cout << "1. Manager Login/Register\n";
        cout << "2. Customer Login/Register\n";
        cout << "3. Delivery Staff Login/Register\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
        {
            int m_choice;
            cout << "1. Login\n2. Register\nEnter choice: ";
            cin >> m_choice;
            string email, pass;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> pass;

            if (m_choice == 1)
            {
                if (!manager.login(email, pass))
                    cout << "Manager not found or wrong password!\n";
                else
                {
                    cout << "Manager logged in successfully!\n";
                    manager_menu(manager);
                }
            }
            else if (m_choice == 2)
            {
                manager.registerr(email, pass);
                cout << "Manager registered successfully!\n";
                manager_menu(manager);
            }
            else
            {
                cout << "Invalid choice!\n";
            }
            break;
        }

        case 2:
        {
            int c_choice;
            cout << "1. Login\n2. Register\nEnter choice: ";
            cin >> c_choice;
            string email, pass, address;

            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> pass;

            if (c_choice == 1)
            {
                if (!currentCustomer.login(email, pass))
                    cout << "Customer not found or wrong password!\n";
                else
                {
                    cout << "Customer logged in successfully!\n";
                    customer_menu(currentCustomer);
                }
            }
            else if (c_choice == 2)
            {
                if (!currentCustomer.registerr(email, pass, ""))
                {
                    cout << "Customer already exists. Logging in...\n";
                    currentCustomer.login(email, pass);
                }
                else
                {
                    cout << "Enter address: ";
                    cin.ignore();
                    getline(cin, address);
                    currentCustomer.set_address(address);
                    cout << "Customer registered successfully!\n";
                }
                customer_menu(currentCustomer);
            }
            else
            {
                cout << "Invalid choice!\n";
            }
            break;
        }

        case 3:
        {
            int d_choice;
            cout << "1. Login\n2. Register\nEnter choice: ";
            cin >> d_choice;
            string email, pass;

            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> pass;

            if (d_choice == 1)
            {
                if (!currentDeli.login(email, pass))
                    cout << "Delivery Staff not found or wrong password!\n";
                else
                {
                    cout << "Delivery Staff logged in successfully!\n";
                    delivery_menu(currentDeli);
                }
            }
            else if (d_choice == 2)
            {
                if (!currentDeli.registerr(email, pass))
                {
                    cout << "Delivery Staff already exists. Logging in...\n";
                    currentDeli.login(email, pass);
                }
                else
                {
                    cout << "Delivery Staff registered successfully!\n";
                }
                delivery_menu(currentDeli);
            }
            else
            {
                cout << "Invalid choice!\n";
            }
            break;
        }

        default:
            cout << "Invalid choice!\n";
        }
    }

    cout << "Exiting system. Goodbye!\n";
    return 0;
}

void manager_menu(Manager &manager)
{
    while (true)
    {
        cout << "\n--- MANAGER MENU ---\n";
        cout << "1. Add Menu Item\n";
        cout << "2. View Orders\n";
        cout << "3. Assign Order to Delivery Staff\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
        {
            string name, desc;
            double price;
            int qty;
            cout << "Item name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Item price: ";
            cin >> price;
            cout << "Item quantity: ";
            cin >> qty;
            cout << "Item description: ";
            cin >> ws;
            getline(cin, desc);
            Item item(name, price, qty, desc);
            manager.additem(item);
            cout << "Item added!\n";
            break;
        }
        case 2:
            manager.view_orders();
            break;
        case 3:
        {
            int order_id, deli_id;
            cout << "Enter Order ID to assign: ";
            cin >> order_id;
            cout << "Enter Delivery Staff ID: ";
            cin >> deli_id;
            manager.assign_order_to_delivery(order_id, deli_id);
            break;
        }
        default:
            cout << "Invalid choice!\n";
        }
    }
}

void customer_menu(Customer &customer)
{
    Cart &cart = customer.get_cart(); 
    while (true)
    {
        cout << "\n--- CUSTOMER MENU ---\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item to Cart\n";
        cout << "3. Update Item in Cart\n";
        cout << "4. Delete Item from Cart\n";
        cout << "5. Place Order\n";
        cout << "6. View Order History\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            customer.view_menu();
            break;
        case 2:
        {
            int item_id, qty;
            cout << "Enter Item ID: ";
            cin >> item_id;
            cout << "Enter quantity: ";
            cin >> qty;

            Item item;
            item.set_id(item_id);
            item.set_quantity(qty);
            customer.add_item_to_cart(item, qty);
            cout << "Added to cart!\n";
            break;
        }
        case 3:
        {
            int item_id, qty;
            cout << "Enter Item ID to update: ";
            cin >> item_id;
            cout << "Enter new quantity: ";
            cin >> qty;

            Item item;
            item.set_id(item_id);
            item.set_quantity(qty);
            if (customer.update_cart(item, cart))
                cout << "Cart updated!\n";
            else
                cout << "Item not found in cart!\n";
            break;
        }
        case 4:
        {
            int item_id;
            cout << "Enter Item ID to remove: ";
            cin >> item_id;
            Item item;
            item.set_id(item_id);
            if (customer.delete_item_from_cart(item, cart))
                cout << "Item removed from cart!\n";
            else
                cout << "Item not found!\n";
            break;
        }
        case 5:
            if (!cart.get_items().empty())
            {
                customer.place_order(cart);
                cout << "Order placed successfully!\n";
                cart.clear(); 
            }
            else
            {
                cout << "Cart is empty. Add items first!\n";
            }
            break;
        case 6:
            customer.view_orders_history();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

void delivery_menu(Delivery_staff &deli)
{
    while (true)
    {
        cout << "\n--- DELIVERY STAFF MENU ---\n";
        cout << "1. View Assigned Orders\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            deli.view_assigned_orders();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }
}
