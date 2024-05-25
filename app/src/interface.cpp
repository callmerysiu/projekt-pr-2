#include <iostream>
#include <list>
#include <ctime>
#include "interface.h"

MockInterface::MockInterface(){};

Transaction MockInterface::get_new_transaction()
{
    std::time_t time = 0;
    Transaction t = Transaction(1, 1, 0);
    return t;
};

std::string MockInterface::get_user_name()
{
    return "dupa";
};
std::string MockInterface::get_user_password()
{
    return "2137";
};

void MockInterface::show_transactions(std::list<Transaction>)
{
    std::cout << "called show_transactions" << std::endl;
    return;
};

UserAction MockInterface::get_user_action()
{
    return UserAction::EXIT;
};
