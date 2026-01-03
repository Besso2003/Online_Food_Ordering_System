# Online Food Ordering System

## Overview
The **Online Food Ordering System** is a simple yet efficient application that allows customers to browse a menu, place orders, and manage their purchases. The system also includes functionalities for managers to manage menu items and for delivery staff to track orders. All data is stored in local files, making it lightweight and easy to use.

---

## Features

### Customer Features
- **Register & Login:** Customers can create accounts and log in securely.
- **View Menu:** Browse available food items with prices.
- **Add/Remove Items to Cart:** Customers can select items to add to or remove from their cart.
- **Place Order:** Confirm and submit orders.
- **Cancel Order (Optional):** Cancel orders before they are processed.
- **Track Status (Optional):** Track order status using order ID and details (Delivered / Not yet).
- **Payment Integration:** Supports cash or visa payments.
- **Order History:** View past orders.

### Manager Features
- **Register & Login:** Secure manager access.
- **Add Product:** Add new menu items.
- **Delete Product:** Remove items from the menu.
- **Update Product:** Modify details of existing menu items.

### Delivery Staff Features
- **Register & Login:** Access the system for delivery operations.
- **Track Orders:** View and manage assigned delivery orders.

---

## Non-Functional Requirements

| Requirement | Description |
|------------|-------------|
| **Availability** | The system should be accessible whenever needed. |
| **Scalability** | Able to handle a growing number of users or orders. |
| **Low Response Time** | Fast performance with minimal delays. |
| **Security** | Protect user data and prevent unauthorized access. |
| **Friendly User Interface** | Easy and intuitive for all users. |
| **Maintainability** | Easy to update code and add new features. |
| **Reliability** | Stable system with minimal downtime and errors. |

---

## Class Diagram

The system's classes and their relationships are represented in the diagram below:

![Class Diagram](diagrams/Class Diagram.png)
