#include "data_storage.h"

Transaction::Transaction(int value, bool income, time_t date) : value(value), income(income), date(date){};
list<Transaction> MockDatabase::get_user_transactions(int id)
{
    time_t time = 0;
    Transaction t = Transaction(1, 1, 0);
    list<Transaction> transaction_list = {t};
    return transaction_list;
}

void MockDatabase::store_user_transaction(int user_id, Transaction thing_to_store) {}
list<Transaction> MockDatabase::get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date)
{
    time_t time = 0;
    Transaction t = Transaction(1, 1, 0);
    list<Transaction> transaction_list = {t};
    return transaction_list;
}

User *MockDatabase::get_user(string user_name, string password)
{
    return new User(12, "heheszki");
};

bool MockDatabase::add_user(string user_name, string password)
{
    return true;
};
