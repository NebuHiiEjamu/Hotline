#ifndef _SESSION_H
#define _SESSION_H

#include <bitset>

#include "forward.hpp"
#include "../common/src/forward.hpp"
#include "../common/src/typedefs.hpp"
#include "../stream.hpp"

namespace UserStatus
{
	enum
	{
		away = 0,
		admin,
		refusesPrivateMessages,
		refusesChatInvites,
		all
	};
}

namespace UserStatusEx
{
	enum
	{
		visible = 0,
		away,
		isHL = 3,
		isTide [[deprecated("Discontinued")]],
		isAniClient [[deprecated("Discontinued")]],
		isHeidrun [[deprecated("Discontinued")]],
		isFrogblast [[deprecated("Discontinued")]],
		isIRC,
		isKDX,
		inPing,
		inLogin,
		sockUnix,
		all
	};
}

class Session : public std::enable_shared_from_this<Session>
{
public:
	static constexpr uint32 trtpVersion = 0x10002;
	static constexpr Size chatPrefixSize = 17;
	static constexpr Size maxChatSize = 4096;
	static constexpr Size maxGifIconSize = 32768;
	static constexpr Size maxMessageSize = 2048;
	
	Session(uint16, HLConnectionPtr);
	uint16 getId() const;
	uint16 getIcon();
	uint16 getStatus();
	uint32 getStatusEx();
	std::string&& getClientInfoText();
	std::string&& getVersionString() const;
	//std::string_view&& getClient() const;
	void setStatus(uint16);
	void setStatusEx(uint32);
	void setIcon(uint16);
	void sendDisconnect();
	void handleLogin(HLInStream&, const Transaction&);
private:
	AccountRef account;
	HLConnectionPtr connection;
	std::string nickname;
	std::string autoReply;
	ByteString key;
	ByteString gifIcon;
	Timestamp uptime;
	std::mutex mutex;
	std::bitset<UserStatus::all> status;
	std::bitset<UserStatusEx::all> statusEx; // separate from account
	suint32 lastTransactionId;
	suint32 replies;
	uint16 id;
	[[deprecated("Superseded by custom icons")]] uint16 icon; // separate from account
	uint16 color; // separate from account
	uint16 version;
	Cipher cipher;
	Compression compression;
};

#endif // _SESSION_H
