#ifndef _HLSERVER_H
#define _HLSERVER_H

#include <bitset>
#include <map>
#include <set>
#include <string_view>

#include "user/forward.hpp"
#include "forward.hpp"
#include "common/src/server.hpp"
#include "common/src/typedefs.hpp"

struct sqlite3;

class HLServer : public Server
{
public:
	static constexpr uint16 version = 197;
	static constexpr uint16 defaultPort = 5500;
	
	static constexpr std::string_view getDefaultDatabase();
	static HLServerRef getInstance();
	static uint32 getRandomSeed();
	//static uint32 kdxDecrypt(uint32, ByteString&);
	static void transform(ByteString&);

	~HLServer();
	bool createSession(uint16, HLConnectionPtr);
	void removeSession(uint16);
	uint16 getNextUserId();
	uint16 getUserCount();
	uint16 getPort() const;
	std::string_view& getDescription() const;
	std::string_view& getName() const;
	std::string_view& getAgreement() const;
	std::string_view& getFlatNews();
	AccountRef getAccount(SessionRef, const std::string_view&, const ByteString&);
	void run(int, char**) override;
private:
	HLServer();
private:
	static std::shared_ptr<HLServer> instance;

	std::string name;
	std::string description;
	std::string agreement;
	std::string flatNews;
	std::map<uint16, SessionPtr> sessionMap;
	std::set<TrackerConnectionPtr> trackerConnections;
	std::map<std::string_view, AccountPtr> accountMap;
	std::set<std::pair<Address, Timestamp>> bans;
	sqlite3 *db;
	std::mutex mutex;
	uint16 port;
	suint16 nextUserId;
	Ciper cipher;
	Compression compression;
};

#endif // _HLSERVER_H
