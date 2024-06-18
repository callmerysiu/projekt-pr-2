file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")
add_executable(FMapp main.cpp )

include_directories("${PROJECT_SOURCE_DIR}/app/include")
target_include_directories(FMapp PUBLIC "${PROJECT_SOURCE_DIR}/app/include")

add_library(SrcCode STATIC ${SOURCES} ${INCLUDES})

find_package(SQLite3)

include_directories("${PROJECT_SOURCE_DIR}/sqlite")
target_link_libraries(
  FMapp
  SrcCode
  sqlite3
)


