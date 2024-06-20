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
    virtual list<Transaction> get_user_transactions(int user_id) = 0;
    virtual void store_user_transaction(int user_id, Transaction thing_to_store) = 0;
    virtual list<Transaction> get_user_transactions_filtered(int user_id, time_t start_date, time_t end_date) = 0;

    virtual User *get_user(string user_name, string password) = 0;
    virtual bool add_user(string user_name, string password) = 0;
    virtual bool check_if_user_exists(string user_name) = 0;
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
    list<Transaction> get_user_transactions_filtered(int user_id, time_t start_date, time_t end_date);

    User *get_user(string user_name, string password);
    bool add_user(string user_name, string password); // osobna tabela w bazie, user i password, jak jest nie teges rzuca errorem
    bool check_if_user_exists(string user_name);
};

class SqliteDatabase : public IDataStorage
{
private:
    string dbDirectory;

public:
    void runDB();
    int createDB();
    int createTablesDB();
    list<Transaction> get_user_transactions(int user_id);
    void store_user_transaction(int user_id, Transaction thing_to_store);
    list<Transaction> get_user_transactions_filtered(int user_id, time_t start_date, time_t end_date);

    User *get_user(string user_name, string password);
    bool add_user(string user_name, string password); // osobna tabela w bazie, user i password, jak jest nie teges rzuca errorem
    bool check_if_user_exists(string user_name);

    SqliteDatabase(string dbDirectory);
};