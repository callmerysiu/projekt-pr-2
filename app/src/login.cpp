#include "login.h"

User::User(int id, string user_name) : id(id), user_name(user_name) {}

MockLoginService::MockLoginService(IDataStorage *database, IUserInterface *interface)
{
    this->database = database;
    this->interface = interface;
}

User *MockLoginService::get_user()
{
    string user_name = this->interface->get_user_name();
    string password = this->interface->get_user_password();
    User *user = this->database->get_user(user_name, password);
    return user;
};
