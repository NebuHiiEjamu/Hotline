project(HotlineServer)

find_package(fmt)
find_package(SQLite::SQLite3)

add_subdirectory("src")
add_subdirectory("src/common/src")
add_subdirectory("src/user")
