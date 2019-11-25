#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <bitset>
#include <boost/predef.h>

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

class Account : public std::enable_shared_from_this<Account>
{
public:
	Account(std::string_view, std::string_view, ByteString);
	uint64 getAccess();
	uint32 getAccessEx();
	void setAccess(uint64);
	void setAccessEx(uint32);
private:
	std::string login;
	std::string name;
	ByteString password;
	std::mutex mutex;
	std::bitset<Access::all> access;
	std::bitset<AccessEx::all> accessEx;
	uint32 downloads;
	uint32 uploads;
	uint32 outBps;
};

#endif // _ACCOUNT_H
