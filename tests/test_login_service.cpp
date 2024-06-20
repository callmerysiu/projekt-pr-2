#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "user_service.h"
#include "interface.h"
#include "mocks.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

TEST(LoginServiceTest, add_user_AddsUser)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillOnce(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillOnce(Return("2137"));
    EXPECT_CALL((*mockStorage), add_user("Ada", "2137"))
        .WillOnce(Return(true));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    login->add_user();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, add_user_PassDBErrors)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillOnce(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillOnce(Return("2137"));
    EXPECT_CALL((*mockStorage), add_user("Ada", "2137"))
        .WillOnce(Return(true));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    login->add_user();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_existing_PassDBErrors)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillOnce(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillOnce(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Throw(std::runtime_error("Failed to logg in")));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    EXPECT_ANY_THROW(login->login_existing());

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_existing_AllowsFor3Attempts)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Throw(std::invalid_argument("No user found with the given username.")))
        .WillOnce(Throw(std::invalid_argument("No user found with the given username.")))
        .WillOnce(Return(validUser));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    login->login_existing();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_existing_LogsUserIn)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Return(validUser));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    login->login_existing();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_existing_ThrowsErrorAfter3Attempts)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .Times(3)
        .WillRepeatedly(Throw(std::invalid_argument("No user found with the given username.")));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    EXPECT_THROW(login->login_existing(), std::runtime_error);

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_Starts)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    EXPECT_CALL((*mockInterface), get_login_action())
        .WillOnce(Return(LoginAction::L_EXIT));

    LoginService *login = new LoginService(mockStorage, mockInterface);

    EXPECT_EXIT(login->login(), testing::ExitedWithCode(0), "");
}

TEST(LoginServiceTest, login_AllowsForLogIn)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_login_action())
        .WillOnce(Return(LoginAction::LOGIN));
    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Return(validUser));

    LoginService *login = new LoginService(mockStorage, mockInterface);

    EXPECT_EQ(login->login(), validUser);

    delete mockStorage;
    delete mockInterface;
}

TEST(LoginServiceTest, login_AllowsForNOOP)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_login_action())
        .WillOnce(Return(LoginAction::L_NOOP))
        .WillOnce(Return(LoginAction::LOGIN));
    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Return(validUser));

    LoginService *login = new LoginService(mockStorage, mockInterface);

    EXPECT_EQ(login->login(), validUser);

    delete mockStorage;
    delete mockInterface;
}

TEST(LoginServiceTest, login_AllowsForSignIn)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    EXPECT_CALL((*mockInterface), get_login_action())
        .WillOnce(Return(LoginAction::SIGNUP))
        .WillOnce(Return(LoginAction::LOGIN));
    EXPECT_CALL((*mockInterface), get_user_name())
        .WillRepeatedly(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillRepeatedly(Return("2137"));
    EXPECT_CALL((*mockStorage), add_user("Ada", "2137"))
        .WillOnce(Return(true));
    EXPECT_CALL((*mockStorage), get_user("Ada", "2137"))
        .WillOnce(Return(validUser));

    LoginService *login = new LoginService(mockStorage, mockInterface);

    EXPECT_EQ(login->login(), validUser);

    delete mockStorage;
    delete mockInterface;
}

TEST(LoginServiceTest, login_ThrowsWhenLoginAlreadyExists)
{
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();


    EXPECT_CALL((*mockInterface), get_login_action())
        .WillOnce(Return(LoginAction::SIGNUP));
    EXPECT_CALL((*mockInterface), get_user_name())
        .WillOnce(Return("Ada"));
    EXPECT_CALL((*mockInterface), get_user_password())
        .WillOnce(Return("2137"));
    EXPECT_CALL((*mockStorage), add_user("Ada", "2137"))
        .WillOnce(Throw(std::invalid_argument("User with such name already exists.")));

    LoginService *login = new LoginService(mockStorage, mockInterface);
    EXPECT_THROW(login->login(), std::invalid_argument);

    delete mockInterface;
    delete mockStorage;
}