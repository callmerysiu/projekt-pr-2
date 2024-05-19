#include "data_storage.h"
#include "interface.h"
class User
{
};

class ILogin
{
public:
    virtual User get_user();
};

class LoginService : public ILogin
{
public:
    LoginService(IDataStorage *, IUserInterface *);
    User get_user();
};

