#ifndef _SESSION_H
#define _SESSION_H

#include <bitset>

#include "forward.hpp"
#include "../common/src/forward.hpp"
#include "../common/src/typedefs.hpp"

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
		hotline = 3,
		tide,
		aniclient,
		heidrun,
		frogblast,
		irc,
		kdx,
		inPing,
		inLogin,
		unixSock,
		all
	};
}

class Session : public std::enable_shared_from_this<Session>
{
public:
	static constexpr uint32 trtpVersion = 0x10002;
	
	Session(uint16, HLConnectionPtr);
	uint16 getId() const;
	uint16 getIcon();
	uint16 getStatus();
	uint32 getStatusEx();
	std::string&& getClientInfoText();
	std::string&& getVersionString() const;
	//std::string_view getClient() const;
	void setStatus(uint16);
	void setStatusEx(uint32);
	void setIcon(uint16);
private:
	AccountRef account;
	HLConnectionPtr connection;
	std::string nickname;
	std::string autoReply;
	std::mutex mutex;
	std::bitset<UserStatus::all> status;
	std::bitset<UserStatusEx::all> statusEx; // separate from account
	suint32 lastTransactionId;
	suint32 replies;
	uint16 id;
	uint16 icon; // separate from account
	uint16 color; // separate from account
	uint16 version;
};

#endif // _SESSION_H
