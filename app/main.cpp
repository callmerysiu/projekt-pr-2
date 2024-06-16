#include <iostream>
#include <ctime>
#include "user_service.h" // TODO guard aginst circural imports
#include "interface.h"

using namespace std;

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