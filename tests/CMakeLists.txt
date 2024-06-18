include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories("${PROJECT_SOURCE_DIR}/app/include")
include_directories("${PROJECT_SOURCE_DIR}/app/src")

find_package(SQLite3)
include_directories("${PROJECT_SOURCE_DIR}/sqlite")

include(GoogleTest)
 
file(GLOB TESTS "test_*.cpp")

add_executable(
  Tests
  ${TESTS}
)
 
target_link_libraries(
  Tests
  SrcCode
  GTest::gtest_main
  GTest::gmock_main
)
  
gtest_discover_tests(Tests)

  