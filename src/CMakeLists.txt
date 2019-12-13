project(hlserver)

set(SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	common/src/connection.cpp
	common/src/hive.cpp
	common/src/listener.cpp
	common/src/logger.cpp
	common/src/server.cpp
	common/src/stream.cpp
	user/account.cpp
	user/hlconnection.cpp
	user/usersession.cpp
	hlserver.cpp
	main.cpp
	stream.cpp
)

add_executable(hlserver ${SOURCE_FILES})
target_link_libraries(hlserver fmt::fmt SQLite3_LIBRARIES)
