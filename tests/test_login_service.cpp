#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "user_service.h"
#include "interface.h"
#include "mocks.hpp"

using ::testing::Return;
using ::testing::_;

TEST(LoginServiceTest, AddsUser) {
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