#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <bitset>
#include <boost/predef.h>

#include "../common.hpp"
#include "session.h"

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
		editArticles,
		moveNewsBundles,
		moveCategories,
		spam,
		emptyTrash,
		viewHiddenUsers,
		editFolderAccess,
		assignFolderAccess
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
		assignFolderAccess,
		editFolderAccess,
		viewHiddenUsers,
		emptyTrash,
		spam,
		moveCategories,
		moveNewsBundles,
		editArticles,
		sendMessages,
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

namespace FolderAccess
{
	enum
	{
		see = 0,
		create,
		uploadFiles,
		uploadFolders,
		moveInItems,
		aliasInItems,
		copyInItems,
		deleteFiles = 9,
		deleteFolders,
		moveOutItems,
		seeContent = 19,
		downloadFiles,
		downloadFolders,
		aliasOutItems,
		copyOutItems,
		renameItems = 29,
		setItemAttributes,
		editFileContents,
		all
	};
};

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
	std::bitset<FolderAccess::all> folderAccess;
	uint32 downloads;
	uint32 uploads;
	uint32 outBps;
	uint16 icon;
	uint16 color;
};

#endif // _ACCOUNT_H
