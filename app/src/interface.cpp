#include <iostream>
#include <list>
#include <ctime>
#include <stdexcept>
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
void MockInterface::show_error(std::string error_message)
{
    return;
}
CLInterface::CLInterface(){};

time_t getCurrentDate()
{
    return time(nullptr);
}

bool getTransactionType()
{
    int choice;
    std::cout << "Enter transaction type (1- income, 2-expense):" << std::endl;
    std::cin >> choice;
    if (choice != 1 && choice != 2)
    {
        throw std::invalid_argument("Invalid transaction type");
    }
    return (choice == 1);
};

double getTransactionAmount()
{
    double amount;
    std::cout << "Enter the amount: ";
    std::cin >> amount;
    return amount;
};
void clearConsole()
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing the screen and moving cursor to top-left
}
Transaction CLInterface::get_new_transaction()
{
    clearConsole();
    time_t time = getCurrentDate();
    bool type = getTransactionType();
    double value = getTransactionAmount();
    Transaction t = Transaction(value, type, time);
    return t;
};

std::string CLInterface::get_user_name()
{
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;
    return username;
};
std::string CLInterface::get_user_password()
{
    std::string password;
    std::cout << "Enter password: ";
    std::cin >> password;
    return password;
};

void CLInterface::show_transaction(Transaction transaction)
{
    std::cout << transaction;
    return;
}

void CLInterface::show_transactions(std::list<Transaction> transactions)
{
    clearConsole();
    for (const auto &transaction : transactions)
    {
        this->show_transaction(transaction);
    }
    // std::cout << "called show_transactions" << std::endl;
    int a;
    scanf("%d", &a);

    return;
};

UserAction CLInterface::get_user_action()
{
    clearConsole();
    std::string user_choice;
    std::cout << "What do you want do: ";
    std::cout << "A - add transaction, S - show transaction, Q - exit" << std::endl;
    std::cin >> user_choice;

    static std::unordered_map<std::string, UserAction> map = {
        {"A", UserAction::ADD_TRANSACTION},
        {"S", UserAction::SEE_HISTORY},
        {"Q", UserAction::EXIT}};

    auto it = map.find(user_choice);
    if (it != map.end())
    {
        return it->second;
    }
    else
    {
        return UserAction::NOOP;
    }
};

void CLInterface::show_error(std::string error_message)
{
    std::cout << error_message << std::endl;
    int a;
    scanf("%d", &a);
    return;
}
