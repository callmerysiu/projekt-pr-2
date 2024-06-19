#include "login.h"

// User::User(int id, string user_name): id(id), user_name(user_name) {}

LoginService::LoginService(IDataStorage *database, IUserInterface *interface)
{
    this->database = database;
    this->interface = interface;
}

User *LoginService::login()
{
    bool logged_in = false;
    int attempt = 0;
    while (attempt < 3)
    {
        string user_name = this->interface->get_user_name();
        string password = this->interface->get_user_password();
        try
        {
            User *user = this->database->get_user(user_name, password); // TODO add try catch for a situation when user does not exists
            return user;
        }
        catch (const std::invalid_argument& e)
        {
            attempt += 1;
        }
    };
        throw(std::runtime_error("Failed to logg in"));
};

void LoginService::add_user()
{
    string user_name = this->interface->get_user_name();
    string password = this->interface->get_user_password();
    this->database->add_user(user_name, password);
};