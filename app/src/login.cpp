#include "login.h"

User::User(int id, string user_name): id(id), user_name(user_name){}

MockLoginService::MockLoginService(IDataStorage *database, IUserInterface *interface) {}

User MockLoginService::get_user(string user_name, string password) {
    return User(1, user_name);
};

