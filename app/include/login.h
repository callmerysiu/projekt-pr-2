#pragma once

#include <string>
#include "user.h"
#include "data_storage.h"
#include "interface.h"

class ILogin
{
protected:
    IUserInterface *interface;
    IDataStorage *database;

public:
    virtual User *login() = 0;
    virtual void add_user() = 0;
    virtual ~ILogin() {}
};

class LoginService : public ILogin
{
public:
    LoginService(IDataStorage *, IUserInterface *);
    User *login();
    User *login_existing();
    void add_user();
};
