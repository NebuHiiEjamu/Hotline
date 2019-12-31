project(HotlineServer)

find_package(fmt REQUIRED)
find_package(SQLite::SQLite3 REQUIRED)

add_subdirectory("src")
add_subdirectory("src/common/src")
add_subdirectory("src/user")
