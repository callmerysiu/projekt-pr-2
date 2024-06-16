#pragma once

#include <ctime>
#include <iostream>
#include <list>

#include "transaction.h"
#include "user.h"

using namespace std;

class IDataStorage
{
public:
    virtual void runDB() = 0;
    virtual int createDB() = 0;
    virtual int createTablesDB() = 0;
    virtual list<Transaction> get_user_transactions(int user_id) = 0;                 // wszystkie jednego
    virtual void store_user_transaction(int user_id, Transaction thing_to_store) = 0; // zapisz JEDNA transakcje

    virtual list<Transaction> get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date) = 0; // wyciagnij transakcje od daty do daty
    virtual User *get_user(string user_name, string password) = 0;                                                // osobna tabela w bazie, user i password, jak jest nie teges rzuca errorem
    virtual bool add_user(string user_name, string password) = 0;                                                 // osobna tabela w bazie, user i password, jak jest nie teges rzuca errorem
    virtual ~IDataStorage() {}
};

class MockDatabase : public IDataStorage
{
public:
    void runDB();
    int createDB();
    int createTablesDB();
    list<Transaction> get_user_transactions(int user_id);
    void store_user_transaction(int user_id, Transaction thing_to_store);
    list<Transaction> get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date);
    User *get_user(string user_name, string password);
    bool add_user(string user_name, string password); // osobna tabela w bazie, user i password, jak jest nie teges rzuca errorem
};
