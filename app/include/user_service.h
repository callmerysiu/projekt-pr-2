#pragma once
#include <login.h>

class UserService
{
private:
    User *user;
    IDataStorage *storage;
    IUserInterface *interface;

public:
    UserService(User *, IDataStorage *, IUserInterface *);
    void run();
};