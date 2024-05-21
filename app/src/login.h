// #include <string> 
#include "data_storage.h"
#include "interface.h"
class User
{
    public:
        int id;
        string userName;
        User(int id, string userName);
};

class ILogin
{
public:
    virtual User get_user()= 0;
    virtual ~ILogin(){ }

};

class MockLoginService : public ILogin
{
public:
    MockLoginService(IDataStorage *, IUserInterface *);
    User get_user();
};

