#pragma once

#include <string>
#include <vector>

class User
{
public:
    User() = default;

    User(const std::string& username, const std::string& password)
    : username(username), password(password){}

    bool authenticate(const std::string& input_password) const {
        return password == input_password;
    }

    void addTransaction(const Transaction& transaction){
        transactions.push_back(transaction);
    }
    void listTransitions() const {
        for(const auto& transaction: transactions){
            transaction.print();
        }
    }

private:
    std::string username;
    std::string password;
    std::vector<Transaction> transactions;
};