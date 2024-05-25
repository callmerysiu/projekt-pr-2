#pragma once

#include <ctime>

class Transaction
{
private:
    double value;
    bool income; // jezli true to znaczy ze to przychod jest
    time_t date;

public:
    Transaction(int value, bool income, time_t date);
    //     ~Transaction();
};
