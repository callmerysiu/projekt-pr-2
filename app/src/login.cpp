#include "login.h"

User::User(int id, string userName): id(id), userName(userName){}


MockLoginService::MockLoginService(IDataStorage *database, IUserInterface *interface) {}

User MockLoginService::get_user() {
    return User(1,"dupa");
};