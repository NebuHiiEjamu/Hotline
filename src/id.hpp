#ifndef _ID_H
#define _PACKET_H

#include "../common.hpp"

enum class Magic : uint32
{
	AMAC = 0x414D4143,
	BMP = 0x424D5020,
	DATA = 0x44415441,
	FILP = 0x46494C50,
	GIFf = 0x47494666,
	HOTL = 0x484F544C,
	HTRK = 0x4854524B,
	HTXF = 0x48545846,
	INFO = 0x494E464F,
	JPEG = 0x4A504547,
	MWIN = 0x4D57494E,
	PICT = 0x50494354,
	RFLT = 0x52464C54,
	TRTP = 0x54525450,
	URL = 0x55524C20,
	fldr = 0x666C6472
};

enum class TransId : uint16
{
	error = 100,
	getMsgs,
	newMsg,
	oldPostNews,
	serverMsg,
	chatSend,
	chatMsg,
	login,
	sendInstantMsg,
	showAgreement,
	disconnectUser,
	disconnectMsg,
	inviteNewChat,
	inviteToChat,
	rejectChatInvite,
	joinChat,
	leaveChat,
	notifyChatChangeUser,
	notifyChatDeleteUser,
	notifyChatSubject,
	setChatSubject,
	agreed,
	serverBanner,
	getFileNameList = 200,
	downloadFile = 202,
	uploadFile,
	deleteFile,
	newFolder,
	getFileInfo,
	setFileInfo,
	moveFile,
	makeFileAlias,
	downloadFldr,
	downloadInfo,
	downloadBanner,
	uploadFldr,
	getUserNameList = 300,
	notifyChangeUser,
	notifyDeleteUser,
	getClientInfoText,
	setClientUserInfo,
	newUser = 350,
	deleteUser,
	getUser,
	setUser,
	userAccess,
	userBroadcast,
	getNewsCatNameList = 370,
	getNewsArtNameList,
	delNewsItem = 380,
	newNewsFldr,
	newNewsCat,
	getNewsArtData = 400,
	postNewsArt = 410,
	delNewsArt,
	editNewsArt,
	sendKeepAlive = 500,
	index = 513,
	indexStatus = 801,
	emptyTrash = 803,
	folderAccess,
	setFldrAccessList,
	script
};

enum class Field : uint16
{
	errorText = 100,
	data,
	userName,
	userId,
	userIconId,
	userLogin,
	userPassword,
	refNum,
	transferSize,
	chatOptions,
	userAccess,
	userAlias,
	userFlags,
	options,
	chatId,
	chatSubject,
	waitingCount,
	serverAgreement = 150,
	serverBanner,
	serverBannerType,
	serverBannerUrl,
	noServerAgreement,
	vers = 160,
	communityBannerId,
	serverName,
	fileNameWithInfo = 200,
	fileName,
	filePath,
	fileResumeData,
	fileXferOptions,
	fileTypeString,
	fileCreatorString,
	fileSize,
	fileCreateDate,
	fileModifyDate,
	fileComment,
	fileNewName,
	fileNewPath,
	fileType,
	quotingMsg,
	fldrItemCount = 220,
	userNameWithInfo = 300,
	newsCatGuid = 319,
	newsCatListData,
	newsArtListData,
	newsCatName,
	newsCatListData15,
	newsPath = 325,
	newsArtId,
	newsArtDataFlav,
	newsArtTitle,
	newsArtPoster,
	newsArtDate,
	newsArtPrevArt,
	newsArtNextArt,
	newsArtData,
	newsArtFlags,
	newsArtParentArt,
	newsArt1stChildArt,
	newsArtRecurseDel
};

#endif // _PACKET_H
