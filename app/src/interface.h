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
    EXIT,
    NOOP
};

class IUserInterface
{
public:
    virtual Transaction get_new_transaction() = 0;
    virtual void show_transactions(std::list<Transaction>) = 0;
    virtual std::string get_user_name() = 0;
    virtual std::string get_user_password() = 0;
    virtual UserAction get_user_action() = 0;
    virtual void show_error(const std::string) = 0;

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
    void show_error(const std::string);

    MockInterface();
};

class CLInterface : public IUserInterface
{
private:
    void show_transaction(Transaction);

public:
    Transaction get_new_transaction();
    void show_transactions(std::list<Transaction>);
    std::string get_user_name();
    std::string get_user_password();
    UserAction get_user_action();
    void show_error(const std::string);

    CLInterface();
};
