#include <ctime>
#include <iostream>
#include <list>

using namespace std;

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


class IDataStorage{
    public:
        virtual list<Transaction> get_user_transactions(int user_id)= 0; // wszystkie jednego
        virtual void store_user_transaction(int user_id, Transaction thing_to_store)= 0; // zapisz JEDNA transakcje

        virtual list<Transaction> get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date)= 0; // wyciagnij transakcje od daty do daty
        virtual ~IDataStorage(){ }
};

class MockDatabase : public IDataStorage{
    public:
        virtual list<Transaction> get_user_transactions(int user_id);
        virtual void store_user_transaction(int user_id, Transaction thing_to_store);
        virtual list<Transaction> get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date);
};