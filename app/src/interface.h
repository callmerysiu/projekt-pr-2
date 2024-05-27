#pragma once

#include <string>
#include <list>
#include <unordered_map>

#include "transaction.h"
#include "user.h"

enum UserAction
{
    ADD_TRANSACTION,
    SEE_HISTORY,
    EXIT
};

class IUserInterface
{
public:
    virtual Transaction get_new_transaction() = 0;
    virtual void show_transactions(std::list<Transaction>) = 0;
    virtual std::string get_user_name() = 0;
    virtual std::string get_user_password() = 0;
    virtual UserAction get_user_action() = 0;

    virtual ~IUserInterface(){};
};

class MockInterface : public IUserInterface
{
public:
    Transaction get_new_transaction();
    void show_transactions(std::list<Transaction>);
    std::string get_user_name();
    std::string get_user_password();
    UserAction get_user_action();

    MockInterface();
};

class BudgetManager {
public:
    void addUser(const std::string& username, const std::string& password){
        users.emplace(username, User(username, password));
    }
    User* login(const std::string& username, const std::string& password){
        auto it = users.find(username);
        if(it != users.end() && it->second.authenticate(password)){
            return &it->second;
        }
        return nullptr;
    }
private:
    std::unordered_map<std::string, User> users;
}