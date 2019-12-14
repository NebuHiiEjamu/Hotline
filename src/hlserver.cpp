#include <boost/endian/conversion.hpp>
#include <fmt/core.h>
#include <limits>
#include <random>
#include <sqlite3.h>

#include "hlserver.hpp"
#include "common/src/hive.hpp"
#include "user/hlconnection.hpp"
#include "user/session.hpp"

/*uint32 HLServer::kdxDecrypt(uint32 key, ByteString &inString)
{
	uint32 *data32 = reinterpret_cast<uint32*>(inString.data());
	uint32 size = inString.size() >> 2;

	for (uint32 i = 0; i < size; i++)
	{
		key = (key << 1) + 0x4878;
		data32[i] ^= boost::endian::big_to_native(key);
	}

	return key;
}*/

void HLServer::transform(ByteString &inString)
{
	for (auto &b : inString) b = ~b;
}

std::shared_ptr<HLServer> HLServer::instance = std::make_shared<HLServer>();

constexpr std::string_view HLServer::getDefaultDatabase()
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
			VALUES ('admin', 'Administrator', x'9E9B929691', 18443313597422501888),\
				('guest', 'Guest', NULL, 2337381538192162816);";
}

HLServer::HLServer():
	nextUserId(1)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint32> dist(std::numeric_limits<uint32>::min(),
		std::numeric_limits<uint32>::max()),
	randomSeed = dist(mt);

	logger->debug("Random seed for tracker connections is {}", randomSeed);
}

bool HLServer::createSession(suint16 id, HLConnectionPtr connection)
{
	LockGuard lock(mutex);
	SessionPtr newSession(new UserSession(id, connection));
	
	connection->setSession(newSession);
	sessionMap[id] = newSession;
	logger->info("Incoming connection from {} with session ID {}",
		connection->getAddress().to_string(), id);

	return true;
}

void HLServer::removeSession(uint16 id)
{
	sessionMap.erase(id);
}

uint16 HLServer::getNextUserId()
{
	LockGuard lock(mutex);
	return nextUserId++;
}

uint16 HLServer::getPort() const
{
	return port;
}

uint32 HLServer::getRandomSeed() const
{
	return randomSeed;
}

std::string_view& HLServer::getName() const
{
	return name;
}

std::string_view& HLServer::getAgreement() const
{
	return agreement;
}

std::string_view& HLServer::getDescription() const
{
	return description;
}

uint16 HLServer::getUserCount()
{
	LockGuard lock(mutex);
	return static_cast<uint16>(sessionMap.size());
}

std::string_view& HLServer::getFlatNews()
{
	LockGuard lock(mutex);
	return flatNews;
}

AccountRef HLServer::getAccount(UserSessionRef session, const std::string_view &login,
	const ByteString &password)
{
	auto account = accountMap.find(login);

	if (account != accountMap.end())
	{
		logger->debug("Account found for session ID {}: {}", session->getId(), login);
		return account->second;
	}
	else
	{
		logger->warn("Account not found for session ID {}: {}", session->getId(), login);
		return nullptr;
	}
}

void HLServer::run(int argc, char **argv)
{
}

HLServerRef HLServer::getInstance()
{
	return instance;
}
