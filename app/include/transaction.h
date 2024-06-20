#pragma once
#include <ctime>
#include <../sqlite/sqlite3.h>

class Transaction
{
public:
    double value;
    bool income; // jesli true to znaczy ze to przychod jest // TODO add enum for transaction type
    time_t date;

    Transaction(int value, bool income, time_t date);
    friend std::ostream &operator<<(std::ostream &os, const Transaction &obj)
    {
        std::string transaction_type_descriptor = "";
        if (obj.income)
        {
            transaction_type_descriptor = "Credit";
        }
        else
        {
            transaction_type_descriptor = "Debt  ";
        }
        os << "Amount: " << obj.value << "$ Type: " << transaction_type_descriptor << " Date: " << ctime(&obj.date) << "";
        return os;
    };
};