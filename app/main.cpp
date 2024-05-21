#include <iostream>
#include "user_service.h" // TODO guard aginst circural imports

using namespace std;

int main(){

    IDataStorage *database = new MockDatabase();
    IUserInterface *interface = new CLI();

    ILogin *login = new LoginService(database, interface);
    User user = login->get_user();
    UserService(user, database, interface);
}