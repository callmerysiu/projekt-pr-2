#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "user_service.h"
#include "interface.h"
#include "mocks.hpp"

using ::testing::Return;
using ::testing::_;

TEST(UserServiceTest, Starts) {
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    EXPECT_CALL((*mockInterface), get_user_action())
        .WillOnce(Return(UserAction::U_EXIT));

    UserService *userService= new UserService(validUser, mockStorage, mockInterface);

    EXPECT_EXIT(userService->run(), testing::ExitedWithCode(0),"");
}

TEST(UserServiceTest, AllowsForNOOP) {
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    EXPECT_CALL((*mockInterface), get_user_action())
        .WillOnce(Return(UserAction::U_NOOP))
        .WillOnce(Return(UserAction::U_EXIT));

    UserService *userService= new UserService(validUser, mockStorage, mockInterface);

    EXPECT_EXIT(userService->run(), testing::ExitedWithCode(0),"");
}

TEST(UserServiceTest, ShowsHistory) {
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    EXPECT_CALL((*mockInterface), get_user_action())
        .WillOnce(Return(UserAction::SEE_HISTORY))
        .WillOnce(Return(UserAction::U_EXIT));
    EXPECT_CALL((*mockInterface), show_transactions(_))
        .WillOnce(Return());

    UserService *userService= new UserService(validUser, mockStorage, mockInterface);

    EXPECT_EXIT(userService->run(), testing::ExitedWithCode(0),"");
}

TEST(UserServiceTest, DoesNothing) {
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    EXPECT_CALL((*mockInterface), get_user_action())
        .WillOnce(Return(UserAction::U_NOOP))
        .WillOnce(Return(UserAction::U_EXIT));

    UserService *userService= new UserService(validUser, mockStorage, mockInterface);

    EXPECT_EXIT(userService->run(), testing::ExitedWithCode(0),"");
}

TEST(UserServiceTest, GoesToAddTransaction) {
    User *validUser = new User(25, "Alice");
    MockTestDataStorage *mockStorage = new MockTestDataStorage();
    MockTestInterface *mockInterface = new MockTestInterface();

    testing::Mock::AllowLeak(mockInterface);
    testing::Mock::AllowLeak(mockStorage);
    EXPECT_CALL((*mockInterface), get_user_action())
        .WillOnce(Return(UserAction::ADD_TRANSACTION))
        .WillOnce(Return(UserAction::U_EXIT));
    EXPECT_CALL((*mockStorage), store_user_transaction(25,_))
        .WillOnce(Return());

    UserService *userService= new UserService(validUser, mockStorage, mockInterface);

    EXPECT_EXIT(userService->run(), testing::ExitedWithCode(0),"");
}