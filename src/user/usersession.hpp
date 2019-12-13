#ifndef _USERSESSION_H
#define _USERSESSION_H

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

class UserSession : public std::enable_shared_from_this<UserSession>
{
public:
	static constexpr uint32 trtpVersion = 0x10002;
	
	UserSession(uint16, HLConnectionPtr);
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

#endif // _USERSESSION_H
