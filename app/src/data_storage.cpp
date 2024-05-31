#include "data_storage.h"

void MockDatabase::runDB(){
    string dbDirectory = "../database/financeManager.db";
    sqlite3* db;
    this->createDB(dbDirectory);
    this->createTablesDB(dbDirectory);
}

int MockDatabase::createDB(string dbDirectory){
    sqlite3* db;
    int exit = 0;
    exit = sqlite3_open(dbDirectory.c_str(), &db);
    if(exit != SQLITE_OK){
       cout << sqlite3_errmsg(db);
    }
    sqlite3_close(db);
    return 0;
}

int MockDatabase::createTablesDB(string dbDirectory){
    sqlite3* db;
    string createQueries[3] = {
    "PRAGMA foreign_keys = 1",
    "CREATE TABLE IF NOT EXISTS User (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, login CHAR(50) NOT NULL, password CHAR NOT NULL);",
    "CREATE TABLE IF NOT EXISTS UserTransaction (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, value DECIMAL(10, 2) NOT NULL, income_flag BIT NOT NULL, date DATE NOT NULL, FOREIGN KEY(`user_id`) REFERENCES User(`id`) ON DELETE CASCADE);"
    };

    try{
        int exit = 0;
        exit = sqlite3_open(dbDirectory.c_str(), &db);

        char* msgError;
        for (int i = 0; i < 3; i++)
        {
            exit = sqlite3_exec(db, createQueries[i].c_str(), NULL, 0, &msgError);

            if(exit != SQLITE_OK){
                cerr << "Failed to create table" << endl;
                cout << sqlite3_errmsg(db);
                sqlite3_free(msgError);
            }
        }
        sqlite3_close(db);

    }catch(const exception & err){
        cerr << err.what();
    }
    return 0;
}

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
