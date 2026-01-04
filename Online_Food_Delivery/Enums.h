#ifndef ENUMS_H
#define ENUMS_H

enum class OrderStatus {
    Pending,
    InProgress,
    Delivered,
    Failed
};

enum class PaymentMethod {
    Cash,
    Visa
};

#endif
