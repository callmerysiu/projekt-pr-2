#include "login.h"

// User::User(int id, string user_name): id(id), user_name(user_name) {}

LoginService::LoginService(IDataStorage *database, IUserInterface *interface)
{
    this->database = database;
    this->interface = interface;
}

User *LoginService::login()
{
    string user_name = this->interface->get_user_name();
    string password = this->interface->get_user_password();
    User *user = this->database->get_user(user_name, password); // TODO add try catch for a situation when user does not exists
    return user;
};

void LoginService::add_user()
{
    string user_name = this->interface->get_user_name();
    string password = this->interface->get_user_password();
    this->database->add_user(user_name, password); // TODO add try catch for when the user is not added
    return;
};