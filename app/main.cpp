#include <iostream>
#include <ctime>
#include "user_service.h" // TODO guard aginst circural imports

using namespace std;

time_t getCurrentDate(){
    return time(nullptr);
}

bool getTransactionType(){
    int choice;
    std::cout << "Enter transation type (1- income, 2-expense): ";
    std::cin >> choice;
    return(choice==1);
}

double getTransactionAmount(){
    double amount;
    std::cout<<"Enter the amount: ";
    std::cin>>amount;
    return amount;
}

int main(){
    IDataStorage *database = new MockDatabase();
    IUserInterface *interface = new MockInterface();

    ILogin *login = new MockLoginService(database, interface);
    User *user = login->get_user();
    UserService *service = new UserService(user, database, interface);
    service->run();

    BudgetManager manager;
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* loggedInUser = manager.login(username, password);
    if(loggedInUser){
        cout << "Login successful!\n ";

        bool isIncome = getTransactionType();
        double amount = getTransactionAmount();
        time_t date = getCurrentDate();

        loggedInUser->addTransaction(Transaction(isIncome,amount, date));
        cout << "Transation added successfully!";

        cout << "Listing all transactions: \n";
        loggedInUser->listTransitions();

    }
    else {
        cout << "Login failed! \n";
    }
}