#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <array>
#include <bitset>
#include <boost/predef.h>

#include "../common/src/typedefs.hpp"
#include "session.hpp"

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
		// -- GLoarb ---
		createChat,
		closeChat,
		// ---
		showInList,
		createUser,
		deleteUser,
		
		openUser,
		modifyUser,
		// --- GLoarb ---
		changeOwnPass,
		sendPrivMsg,
		// ---
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
		// --- GLoarb ---
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
		// --- GLoarb ---
		closeChat,
		createChat,
		// ---
		sendChat,
		readChat,
		moveFolder,
		
		cannotBeDiscon,
		disconUser,
		newsPostArt,
		newsReadArt,
		// --- GLoarb ---
		sendPrivMsg,
		changeOwnPass,
		// ---
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
		
		// --- GLoarb ---
		blockDownload,
		refuseChat,
		speakBefore,
		changeIcon,
		changeNick,
		away,
		fakeRed,
		// ---
		sendMessage,
		
		// --- GLoarb ---
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
		chatPrivate = 0,
		msg,
		userGetList,
		fileList,
		fileGetInfo,
		fileHash,
		canLogin,
		userVisibility,
		userColor,
		canSpam,
		setSubject,
		debug,
		userAccess,
		accessVolatile,
		user0wn,
		is0wn3d,
		manageUsers,
		infoGetAddress,
		infoGetLogin,
		nameLock,
		canAgree,
		canPing,
		bannerGet [[deprecated("Insecure and annoying")]],
		ignoreQueue,
		all
	};
}

class Account : public std::enable_shared_from_this<Account>
{
public:
	static constexpr uint32 legacyUserDataMagic = 0x10000;
	static constexpr Size legacyUserDataSize = 734;
	static constexpr Size maxLoginSize = 34;
	static constexpr Size maxNameSize = 32;
	static constexpr Size maxPasswordSize = 32;

	Account(const std::string_view&, const std::string_view&, ByteString);
	uint64 getAccess();
	uint32 getAccessEx();
	uint16 getColor();
	std::string_view& getLogin();
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
