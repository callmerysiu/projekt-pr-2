#include "data_storage.h"

Transaction::Transaction(int value, bool income, time_t date) : value(value), income(income), date(date){};

void MockDatabase::runDB()
{
}

int MockDatabase::createDB()
{
    return 0;
}

int MockDatabase::createTablesDB()
{
    return 0;
}

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

SqliteDatabase::SqliteDatabase(string dbDirectory) : dbDirectory(dbDirectory) {}

void SqliteDatabase::runDB()
{
    this->createDB();
    this->createTablesDB();
}

int SqliteDatabase::createDB()
{
    sqlite3 *db;
    int exit = 0;
    exit = sqlite3_open(dbDirectory.c_str(), &db);
    if (exit != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    sqlite3_close(db);
    return 0;
}

int SqliteDatabase::createTablesDB()
{
    sqlite3 *db;
    string createQueries[3] = {
        "PRAGMA foreign_keys = 1",
        "CREATE TABLE IF NOT EXISTS User (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, login CHAR(50) NOT NULL, password CHAR NOT NULL);",
        "CREATE TABLE IF NOT EXISTS UserTransaction (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, value DECIMAL(10, 2) NOT NULL, income_flag BIT NOT NULL, date DATE NOT NULL, FOREIGN KEY(`user_id`) REFERENCES User(`id`) ON DELETE CASCADE);"};

    try
    {
        int exit = 0;
        exit = sqlite3_open(dbDirectory.c_str(), &db);

        char *msgError;
        for (int i = 0; i < 3; i++)
        {
            exit = sqlite3_exec(db, createQueries[i].c_str(), NULL, 0, &msgError);

            if (exit != SQLITE_OK)
            {
                cerr << "Failed to create table" << endl;
                cout << sqlite3_errmsg(db);
                sqlite3_free(msgError);
            }
        }
        sqlite3_close(db);
    }
    catch (const exception &err)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return 0;
}

list<Transaction> SqliteDatabase::get_user_transactions(int user_id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    string sql = "SELECT value, income_flag, date FROM UserTransaction WHERE user_id = ?;";
    
    sqlite3_open(dbDirectory.c_str(), &db);
    
    std::list<Transaction> transactions;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double value = sqlite3_column_double(stmt, 0);
        bool income = sqlite3_column_int(stmt, 1);
        time_t date = static_cast<time_t>(sqlite3_column_int64(stmt, 2));

        transactions.emplace_back(value, income, date);
    }

    if (sqlite3_errcode(db) != SQLITE_DONE && sqlite3_errcode(db) != SQLITE_ROW)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return transactions;
}

void SqliteDatabase::store_user_transaction(int user_id, Transaction thing_to_store)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    string sql = "INSERT INTO UserTransaction (user_id, value, income_flag, date) VALUES (?, ?, ?, ?);";

    sqlite3_open(dbDirectory.c_str(), &db);

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_double(stmt, 2, thing_to_store.value);
    sqlite3_bind_int(stmt, 3, thing_to_store.income);
    sqlite3_bind_int64(stmt, 4, static_cast<sqlite3_int64>(thing_to_store.date));

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

list<Transaction> SqliteDatabase::get_user_transactions_filterd(int user_id, time_t start_date, time_t end_date)
// TODO implement this XD
{
    time_t time = 0;
    Transaction t = Transaction(1, 1, 0);
    list<Transaction> transaction_list = {t};
    return transaction_list;
}

User *SqliteDatabase::get_user(string user_name, string input_password)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    string sql = "SELECT id, login, password FROM User WHERE login = ?;";

    sqlite3_open(dbDirectory.c_str(), &db);

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::invalid_argument("No user found with the given username.");
    }

    int id = sqlite3_column_int(stmt, 0);
    string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

    // Add password encryption
    if (password != input_password)
    {
        sqlite3_finalize(stmt);
        throw std::invalid_argument("No user found with the given username.");
    }

    sqlite3_finalize(stmt);

    User *user = new User(id, user_name);
    return user;
}

bool SqliteDatabase::add_user(string user_name, string password)
// Add password encryption
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    string sql = "INSERT INTO User (login, password) VALUES (?, ?);";

    sqlite3_open(dbDirectory.c_str(), &db);

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return true;
}