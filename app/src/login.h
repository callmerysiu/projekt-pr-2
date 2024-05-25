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
    virtual User *get_user() = 0;
    virtual ~ILogin() {}
};

class MockLoginService : public ILogin
{
public:
    MockLoginService(IDataStorage *, IUserInterface *);
    User *get_user();
};
