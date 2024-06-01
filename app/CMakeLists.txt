file(GLOB SOURCES "src/*.cpp")
add_executable(PBapp main.cpp ${SOURCES})
target_include_directories(PBapp PUBLIC "${PROJECT_SOURCE_DIR}/app/include")
find_package(SQLite3)

include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (PBapp ${SQLITE3_LIBRARIES})

include_directories("${PROJECT_SOURCE_DIR}/sqlite")
target_link_libraries (PBapp sqlite3)