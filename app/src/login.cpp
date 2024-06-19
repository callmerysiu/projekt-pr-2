#include "login.h"

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
            User *user = this->database->get_user(user_name, password);
            return user;
        }
        catch (const std::invalid_argument &e)
        {
            this->interface->show_error("Invalid password");
            attempt += 1;
        }
    };
    throw(std::runtime_error("Failed to log in"));
};

void LoginService::add_user()
{
    string user_name = this->interface->get_user_name();
    string password = this->interface->get_user_password();
    this->database->add_user(user_name, password);
};