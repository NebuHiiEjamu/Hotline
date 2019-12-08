#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <bitset>
#include <boost/predef.h>

#include "../common/src/typedefs.hpp"
#include "session.h"

namespace Access
{
	enum
	{
#if BOOST_ENDIAN_BIG_BYTE
		deleteFile = 0,
		uploadFile,
		downloadFile,
		renameFile,
		moveFile,
		createFolder,
		deleteFolder,
		renameFolder,
		moveFolder,
		readChat,
		sendChat,
		createChat,
		closeChat,
		showInList,
		createUser,
		deleteUser,
		openUser,
		modifyUser,
		changeOwnPass,
		sendPrivMsg,
		newsReadArt,
		newsPostArt,
		disconUser,
		cannotBeDiscon,
		getClientInfo,
		uploadAnywhere,
		anyName,
		noAgreement,
		setFileComment,
		setFolderComment,
		viewDropBoxes,
		makeAlias,
		broadcast,
		newsDeleteArt,
		newsCreateCat,
		newsDeleteCat,
		newsCreateFldr,
		newsDeleteFldr,
		uploadFolder,
		downloadFolder,
		sendMessage,
		fakeRed,
		away,
		changeNick,
		changeIcon,
		speakBefore,
		refuseChat,
		blockDownload,
		visible,
		canViewInvisible,
		canFlood,
		viewOwnDropBox,
		dontQueue,
		adminSpector,
		postBefore,
#else
		renameFolder = 0,
		deleteFolder,
		createFolder,
		moveFile,
		renameFile,
		downloadFile,
		uploadFile,
		deleteFile,
		deleteUser,
		createUser,
		showInList,
		closeChat,
		createChat,
		sendChat,
		readChat,
		moveFolder,
		cannotBeDiscon,
		disconUser,
		newsPostArt,
		newsReadArt,
		sendPrivMsg,
		changeOwnPass,
		modifyUser,
		openUser,
		makeAlias,
		viewDropBoxes,
		setFolderComment,
		setFileComment,
		noAgreement,
		anyName,
		uploadAnywhere,
		getClientInfo,
		downloadFolder,
		uploadFolder,
		newsDeleteFldr,
		newsCreateFldr,
		newsDeleteCat,
		newsCreateCat,
		newsDeleteArt,
		broadcast,
		blockDownload,
		refuseChat,
		speakBefore,
		changeIcon,
		changeNick,
		away,
		fakeRed,
		sendMessage,
		postBefore,
		adminSpector,
		dontQueue,
		viewOwnDropBox,
		canFlood,
		canViewInvisible,
		visible,
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

class Account : public std::enable_shared_from_this<Account>
{
public:
	static constexpr uint32 legacyUserDataMagic = 0x10000;
	static constexpr uint32 legacyUserDataSize = 734;

	Account(std::string_view, std::string_view, ByteString);
	uint64 getAccess();
	uint32 getAccessEx();
	std::string_view getLogin();
	void setAccess(uint64);
	void setAccessEx(uint32);
	void exportLegacyUserData(const FilePath&) const;
	void exportHxdAccess(const FilePath&) const;
	void exportHxdConf(const FilePath&) const;
private:
	std::string login;
	std::string name;
	ByteString password;
	std::mutex mutex;
	std::bitset<Access::all> access;
	std::bitset<AccessEx::all> accessEx;
	std::bitset<UserStatusEx::all> statusEx;
	uint32 downloads;
	uint32 uploads;
	uint32 outBps;
	uint16 icon;
	uint16 color;
};

#endif // _ACCOUNT_H
