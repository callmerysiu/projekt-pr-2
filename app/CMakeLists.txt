add_executable(PBapp main.cpp)
target_include_directories(PBapp PUBLIC "${PROJECT_SOURCE_DIR}/app/include")
file(GLOB SOURCES "src/*.cpp")
add_executable(MyProject ${SOURCES})
