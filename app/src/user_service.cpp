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
        {
            try
            {
                Transaction new_transaction = this->interface->get_new_transaction();
                this->storage->store_user_transaction(this->user->id, new_transaction);
            }
            catch (const exception &err)
            {
                this->interface->show_error(err.what());
            }
            break;
        }
        case SEE_HISTORY:
        {
            this->interface->show_transactions(this->storage->get_user_transactions(this->user->id));
            break;
        }
        case L_NOOP:
        {
            break;
        }
        case L_EXIT:
        {
            exit(0);
            break;
        }
        }
    }
};
