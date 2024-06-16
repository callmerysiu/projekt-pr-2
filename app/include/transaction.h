#pragma once
#include <ctime>
#include <../sqlite/sqlite3.h>

class Transaction
{
public:
    double value;
    bool income; // jezli true to znaczy ze to przychod jest // TODO add enum for transaction type
    time_t date;

    Transaction(int value, bool income, time_t date);
    friend std::ostream &operator<<(std::ostream &os, const Transaction &obj)
    {
        os << "Amount: " << obj.value << " Income: " << obj.income << " Date: " << ctime(&obj.date) << "";
        return os;
    };
};