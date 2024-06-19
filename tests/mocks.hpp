#pragma once
#include <gmock/gmock.h>

class MockTestDataStorage : public IDataStorage
{
public:
    MOCK_METHOD(void, runDB, (), (override));
    MOCK_METHOD(int, createDB, (), (override));
    MOCK_METHOD(int, createTablesDB, (), (override));
    MOCK_METHOD(list<Transaction>, get_user_transactions, (int user_id), (override));
    MOCK_METHOD(void, store_user_transaction, (int user_id, Transaction thing_to_store), (override));
    MOCK_METHOD(list<Transaction>, get_user_transactions_filtered, (int user_id, time_t start_date, time_t end_date), (override));
    MOCK_METHOD(User *, get_user, (string user_name, string password), (override));
    MOCK_METHOD(bool, add_user, (string user_name, string password), (override));
};
class MockTestInterface : public IUserInterface
{
public:
    MOCK_METHOD(Transaction, get_new_transaction, (), (override));
    MOCK_METHOD(void, show_transactions, (std::list<Transaction>), (override));
    MOCK_METHOD(std::string, get_user_name, (), (override));
    MOCK_METHOD(std::string, get_user_password, (), (override));
    MOCK_METHOD(UserAction, get_user_action, (), (override));
    MOCK_METHOD(void, show_error, (const std::string), (override));
};
