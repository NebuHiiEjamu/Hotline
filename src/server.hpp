#ifndef _SERVER_H
#define _SERVER_H

#include <bitset>
#include <map>
#include <set>

#include "net/forward.hpp"
#include "user/forward.hpp"
#include "forward.hpp"
#include "common.hpp"

using boost::asio;

struct TrackerInfo : std::enable_shared_from_this<TrackerInfo>
{
	asio::ip::address address;
	std::string login;
	ByteString password;
};

using TrackerInfoPtr = std::shared_ptr<TrackerInfo>;
using TrackerInfoRef = std::weak_ptr<TrackerInfo>;

struct sqlite3;

class Server final : public std::enable_shared_from_this<Server>
{
public:
	static constexpr uint16 version = 192;
	
	static constexpr std::string_view getDefaultDatabase();
	static ServerRef getInstance();
	static uint32 kdxDecrypt(uint32, ByteString&);
	static void transform(ByteString&);

	~Server();
	bool createSession(suint16, HLConnectionPtr);
	void removeSession(suint16);
	suint16 getNextUserId();
	uint16 getUserCount();
	std::string_view getDescription() const;
	std::string_view getName() const;
	std::string_view getAgreement() const;
	std::string_view getFlatNews();
private:
	Server();
private:
	static std::shared_ptr<Server> instance;

	std::string name;
	std::string description;
	std::string agreement;
	std::string flatNews;
	std::map<suint16, SessionPtr> sessionMap;
	std::set<SessionPtr> trackerSessions;
	std::set<AccountPtr> accounts;
	std::set<TrackerInfoPtr> trackers;
	std::set<std::pair<asio::ip::address, Timestamp>> bans;
	sqlite3 *db;
	std::mutex mutex;
	suint16 nextUserId;
};

#endif // _SERVER_H
