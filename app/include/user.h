#pragma once

#include <string>
#include <vector>
// transaction.print(); // TODO implement this shit

class User
{
public:
    User(int id, std::string user_name) : id(id), user_name(user_name) {}

    int id;
    std::string user_name;
};