#include "data_storage.h"

// Transaction::Transaction()
list<Transaction> MockDatabase::get_user_transactions(int id)
{
    time_t time = 0;
    Transaction t = Transaction(1, 1, time);
    list<Transaction> transaction_list = {t};
    return transaction_list;
}