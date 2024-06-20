#include <iostream>
#include <ctime>
#include "user_service.h"
#include "interface.h"

using namespace std;

// TODO add some seeded database

int main()
{
    string dbDirectory = "../database/financeManager.db";

    IDataStorage *database = new SqliteDatabase(dbDirectory);
    database->runDB();
    IUserInterface *interface = new CLInterface();

    ILogin *login = new LoginService(database, interface);
    User *user = login->login();
    UserService *service = new UserService(user, database, interface);
    service->run();
}