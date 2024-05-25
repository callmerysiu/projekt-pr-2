#include "user_service.h"

UserService::UserService(User *user, IDataStorage *storage, IUserInterface *interface)
{
    this->user = user;
    this->storage = storage;
    this->interface = interface;
};

void UserService::run()
{
    while (1)
    {
        UserAction action = this->interface->get_user_action();
        switch (action)
        {
        case ADD_TRANSACTION:
            break;
        case SEE_HISTORY:
            break;
        case EXIT:
            exit(0);
        }
    }
};
