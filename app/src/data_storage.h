#include <ctime>
#include <iostream>

using namespace std;

class Transaction
{
private:
    int value;
    bool income; // jezli true to znaczy ze to przychod jest
    time_t date;
public:
    Transaction(int value, bool income, time_t date);
    ~Transaction();
};


class IDataStorage{
    public:
        virtual Transaction* get_user_transactions(int user_id);
        virtual void store_user_transaction(int user_id, Transaction thing_to_store);

        virtual Transaction* get_user_transactions_from(int user_id);
};

class MockDatabase : public IDataStorage{};