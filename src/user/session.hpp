#ifndef _SESSION_H
#define _SESSION_H

#include <array>
#include <bitset>
#include <boost/predef.h>

#include "forward.hpp"
#include "../forward.hpp"
#include "../net/forward.hpp"
#include "../common.hpp"

namespace Access
{
	enum
	{
#if BOOST_ENDIAN_BIG_BYTE
		deleteFiles = 0,
		uploadFiles,
		downloadFiles,
		renameFiles,
		moveFiles,
		createFolders,
		deleteFolders,
		renameFolders,
		moveFolders,
		readChat,
		sendChat,
		createChats,
		deleteChats,
		showInList,
		createAccounts,
		deleteAccounts,
		readAccounts,
		editAccounts,
		changeOwnPassword,
		sendPrivateMessage,
		readNews,
		postNews,
		kickUsers,
		cantBeKicked,
		getUserInfo,
		uploadAnywhere,
		anyName,
		dontShowAgreement,
		commentFiles,
		commentFolders,
		viewDropBoxes,
		makeAliases,
		broadcast,
		deleteArticles,
		createCategories,
		deleteCategories,
		createNewsBundles,
		deleteNewsBundles,
		uploadFolders,
		downloadFolders,
		sendMessages,
#else
		renameFolders = 0,
		deleteFolders,
		createFolders,
		moveFiles,
		renameFiles,
		downloadFiles,
		uploadFiles,
		deleteFiles,
		deleteAccounts,
		createAccounts,
		showInList,
		deleteChats,
		createChats,
		sendChat,
		readChat,
		moveFolders,
		cantBeKicked,
		kickUsers,
		postNews,
		readNews,
		sendPrivateMessage,
		changeOwnPassword,
		editUsers,
		readAccounts,
		makeAliases,
		viewDropBoxes,
		commentFolders,
		commentFiles,
		dontShowAgreement,
		anyName,
		uploadAnywhere,
		getUserInfo,
		downloadFolders,
		uploadFolders,
		deleteNewsBundles,
		createNewsBundles,
		deleteCategories,
		createCategories,
		deleteArticles,
		broadcast,
		sendMessages = 47,
#endif
		all
	};
}

namespace AccessEx
{
	enum
	{
		privateChat = 0,
		message,
		getUserList,
		getFileList,
		getFileInfo,
		getFileHash,
		login,
		visibility,
		color,
		spam,
		setTopic,
		debug,
		access,
		accessVolatile,
		own,
		owned,
		editAccount,
		getAddressInfo,
		getLoginInfo,
		lockName,
		agree,
		ping,
		getBanner,
		ignoreQueue,
		all
	};
}

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
	Session(uint16, HLConnectionPtr);
	uint64 getAccess();
	uint32 getAccessEx();
	uint16 getId() const;
	uint16 getIcon();
	uint16 getStatus();
	uint32 getStatusEx();
	uint16 getVersion() const;
	void setAccess(uint64);
	void setAccessEx(uint32);
	void setStatus(uint16);
	void setStatusEx(uint32);
	void setIcon(uint16);
private:
	HLConnectionPtr connection;
	std::string login;
	std::string name;
	ByteString password;
	std::mutex mutex;
	std::bitset<Access::all> access;
	std::bitset<AccessEx::all> accessEx;
	std::bitset<UserStatus::all> status;
	std::bitset<UserStatusEx::all> statusEx;
	uint16 id;
	uint16 icon;
	uint16 version;
};

#endif // _SESSION_H
