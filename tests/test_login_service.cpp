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

TEST(LoginServiceTest, login_PassDBErrors)
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
    EXPECT_ANY_THROW(login->login());

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_AllowsFor3Attempts)
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
    login->login();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_LoggsInUser)
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
    login->login();

    delete mockInterface;
    delete mockStorage;
}

TEST(LoginServiceTest, login_ThrowsErrorAfter3Attempts)
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
    EXPECT_THROW(login->login(), std::runtime_error);

    delete mockInterface;
    delete mockStorage;
}
