#include <iostream>
#include "user_service.h" // TODO guard aginst circural imports

using namespace std;

int main(){
    IDataStorage *database = new MockDatabase();
    IUserInterface *interface = new MockInterface();

    ILogin *login = new MockLoginService(database, interface);
    User user = login->get_user();
    UserService(user, database, interface);
}