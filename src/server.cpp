#include <boost/endian/conversion.hpp>
#include <sqlite3.h>

#include "server.hpp"
#include "user/hlconnection.hpp"
#include "user/session.hpp"

using boost::endian;

uint32 Server::kdxDecrypt(uint32 key, ByteString &inString)
{
	uint32 *data32 = reinterpret_cast<uint32*>(inString.data());
	uint32 size = inString.size() >> 2;

	for (uint32 i = 0; i < size; i++)
	{
		key = (key << 1) + 0x4878;
		data32[i] ^= endian::big_to_native(key);
	}

	return key;
}

void Server::transform(ByteString &inString)
{
	for (auto &b : inString) b ^= 0xFF;
}

std::shared_ptr<Server> Server::instance = std::make_shared<Server>();

constexpr std::string_view Server::getDefaultDatabase()
{
	return "DROP TABLE IF EXISTS `accounts`;\
		CREATE TABLE `accounts` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`login` VARCHAR(34) NOT NULL,\
			`name` VARCHAR(134) NOT NULL,\
			`password` BLOB,\
			`flags` INTEGER NOT NULL,\
			`flags_ex` INTEGER,\
			`out_bps` INTEGER,\
			`dl` INTEGER,\
			`ul` INTEGER\
		);\
		\
		DROP TABLE IF EXISTS `news_bundles`;\
		CREATE TABLE `news_bundles` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT NOT NULL\
		);\
		\
		DROP TABLE IF EXISTS `news_categories`;\
		CREATE TABLE `news_categories` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT NOT NULL,\
			`bundle` INTEGER,\
			`guid` TEXT NOT NULL,\
			`type` INTEGER NOTR NULL,\
			`add_sn` INTEGER,\
			`delete_sn` INTEGER\
		);\
		DROP TABLE IF EXISTS `news_articles`;\
		CREATE TABLE `news_articles` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`title` TEXT,\
			`poster` TEXT,\
			`date` INTEGER,\
			`flavor` TEXT,\
			`category` INTEGER NOT NULL\
		);\
		\
		DROP TABLE IF EXISTS `trackers`;\
		CREATE TABLE `trackers` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`address` TEXT NOT NULL,\
			`login` TEXT,\
			`password` BLOB\
		);\
		\
		DROP TABLE IF EXISTS `bans`;\
		CREATE TABLE `bans` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`address` TEXT NOT NULL,\
			`expiration` INTEGER\
		);\
		\
		\
		INSERT INTO `accounts` (login, name, password, flags)\
			VALUES ('admin', 'Administrator', x'9E9B929691', 141836996834303),\
				('guest', 'Guest', NULL, 140738026041376);";
}

Server::Server():
	nextUserId(1)
{
}

bool Server::createSession(uint16 id, HLConnectionPtr connection)
{
	LockGuard lock(mutex);
	SessionPtr newSession = std::make_shared<Session>(id, connection);
	connection->setSession(newSession);
	sessionMap[id] = newSession;

	return true;
}

void Server::removeSession(uint16 id)
{
	sessionMap.erase(id);
}

uint16 Server::getNextUserId()
{
	LockGuard lock(mutex);
	return nextUserId++;
}

std::string_view Server::getName() const
{
	return name;
}

std::string_view Server::getAgreement() const
{
	return agreement;
}

std::string_view Server::getDescription() const
{
	return description;
}

uint16 Server::getUserCount()
{
	LockGuard lock(mutex);
	return static_cast<uint16>(sessionMap.size());
}

std::string_view Server::getFlatNews()
{
	LockGuard lock(mutex);
	return flatNews;
}

ServerRef Server::getInstance()
{
	return instance;
}
