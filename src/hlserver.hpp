#ifndef _HLSERVER_H
#define _HLSERVER_H

#include <bitset>
#include <map>
#include <random>
#include <set>
#include <string_view>

#include "user/forward.hpp"
#include "forward.hpp"
#include "common/src/server.hpp"
#include "common/src/typedefs.hpp"

struct sqlite3;
using SeedDistribution = std::uniform_int_distribution<uint32>;

class HLServer : public Server
{
public:
	static constexpr uint16 version = 197;
	
	static constexpr std::string_view getDefaultDatabase();
	static HLServerRef getInstance();
	//static uint32 kdxDecrypt(uint32, ByteString&);
	static void transform(ByteString&);

	~HLServer();
	bool createSession(suint16, HLConnectionPtr);
	void removeSession(uint16);
	uint16 getNextUserId();
	uint16 getUserCount();
	std::string_view& getDescription() const;
	std::string_view& getName() const;
	std::string_view& getAgreement() const;
	std::string_view& getFlatNews();
	AccountRef getAccount(UserSessionRef, const std::string_view&, const ByteString&);
	void run(int, char**) override;
private:
	HLServer();
private:
	static std::shared_ptr<HLServer> instance;

	std::string name;
	std::string description;
	std::string agreement;
	std::string flatNews;
	std::map<suint16, UserSessionPtr> sessionMap;
	std::set<TrackerSessionPtr> trackerSessions;
	std::map<std::string_view, AccountPtr> accountMap;
	std::set<std::pair<Address, Timestamp>> bans;
	std::random_device seedDevice;
	std::mt19937 seedEngine;
	SeedDistribution seedGenerator;
	sqlite3 *db;
	std::mutex mutex;
	suint16 nextUserId;
};

#endif // _SERVER_H
