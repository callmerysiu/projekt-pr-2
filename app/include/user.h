#pragma once

#include <string>
#include <vector>

class User
{
public:
    int id;
    std::string user_name;

    User(int id, std::string user_name) : id(id), user_name(user_name) {}
};