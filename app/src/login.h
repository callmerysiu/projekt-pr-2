#pragma once

#include <string> 
#include "user.h"
#include "data_storage.h"
#include "interface.h"

class ILogin
{
public:
    virtual User get_user(string user_name, string password)= 0;
    virtual ~ILogin(){ }

};

class MockLoginService : public ILogin
{
public:
    MockLoginService(IDataStorage *, IUserInterface *);
    User get_user(string user_name, string password);
};

