#pragma once

#include <string>
#include <list>

#include "transaction.h"

class IUserInterface
{
    public:
        virtual Transaction get_new_transaction() = 0;
        virtual void show_transactions(std::list<Transaction>) = 0;
        virtual std::string get_user_name() = 0;
        virtual std::string get_user_password() = 0;
        virtual ~IUserInterface(){};
};

class MockInterface : public IUserInterface
{
    public:
        Transaction get_new_transaction();
        void show_transactions(std::list<Transaction>);
        std::string get_user_name();
        std::string get_user_password();

        MockInterface();
};
