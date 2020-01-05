#ifndef _ID_H
#define _ID_H

#include <utility>

#include "common/src/typedefs.hpp"

static const char *lpszNone = "NONE";

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
	MACR [[deprecated("Discontinued")]] = 0x4D414352,
	MWIN = 0x4D57494E,
	PICT [[deprecated("Discontinued and unused")]] = 0x50494354,
	RFLT = 0x52464C54,
	TRTP = 0x54525450,
	URL = 0x55524C20,
	fldr = 0x666C6472,
	harc = 0x68617263
};

enum class TransId : uint16
{
	reply = 0,
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
	serverBanner [[deprecated("Insecure and annoying")]],
	// --- GLoarb ---
	gloarbIconChange [[deprecated("Superseded by custom icons")]],
	nickChange,
	fakeRed,
	away,
	crazyServer,
	blockDownload,
	visible,
	adminSpector,
	standardMessage,
	// ---
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
	downloadBanner [[deprecated("Insecure and annoying")]],
	uploadFldr,
	killDownload,
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
	keepConnectionAlive = 500,
	// --- Avaraline ---
	iconList = 1861,
	iconSet,
	iconGet,
	avaraIconChange,
	linkLogin = 2048,
	linkJoin,
	linkLeave,
	linkPacket,
	newsGetUnformatted = 2149,
	userInfoUnformatted = 2160,
	accountSelfModify = 2304,
	permissionList,
	// --- HOPE ---
	fileHash = 3808,
	// --- Catkiller phxd ---
	task = 65535
};

enum class Field : uint16
{
	errorText = 100,
	data,
	userName,
	userId,
	userIconId [[deprecated("Superseded by custom icons")]],
	userLogin,
	userPassword,
	transferId,
	transferSize,
	chatOptions,
	userAccess,
	userAlias,
	userFlags,
	options,
	chatId,
	chatSubject,
	waitingCount,
	// --- GLoarb ---
	iconId [[deprecated("Superseded by custom icons")]],
	nickName,
	fakeRed,
	away,
	blockDownload,
	visible,
	adminSpector,
	standardMessage,
	// ---
	serverAgreement = 150,
	serverBanner [[deprecated("Insecure and annoying")]],
	serverBannerType [[deprecated("Insecure and annoying")]],
	serverBannerUrl [[deprecated("Insecure and annoying")]],
	noServerAgreement,
	vers = 160,
	communityBannerId [[deprecated("Insecure and annoying")]],
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
	automaticResponse,
	fldrItemCount = 220,
	userNameWithInfo = 300,
	newsCatGuid = 319,
	newsCatListData [[deprecated("Hotline 1.5 beta only")]],
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
	newsArtRecurseDel,
	// --- Avaraline ---
	gifIcon = 768,
	gifList,
	offset = 793,
	limit,
	count,
	newsLimit = 800,
	// --- Catkiller phxd ---
	ircOldNick = 1024,
	// --- Avaraline ---
	search = 1024,
	color = 1280,
	packet = 1536,
	post = 2048,
	postId,
	permGroup = 2128,
	perm,
	ip = 2304,
	// --- HOPE ---
	sessionKey = 3587,
	macAlg,
	sid [[deprecated("Unused")]] = 3687,
	hashMd5 = 3712,
	hashHaval,
	hashSha1,
	iconCicn [[deprecated("Unused")]] = 3728,
	chatAway = 3745,
	sCipherAlg = 3777,
	cCipherAlg,
	sCipherMode,
	cCipherMode,
	sCipherIVec,
	cCipherIVec,
	sChecksumAlg,
	cChecksumAlg,
	sCompressAlg,
	cCompressAlg
};

enum class FileAction : uint16
{
	send = 1,
	resume,
	next
};

enum class MacAlgorithm : Byte
{
	hmacMd5,
	hmacSha1,
	md5,
	sha1
};

static const std::pair<MacAlgorithm, const char*> macAlgorithmMap[] =
{
	{ MacAlgorithm::hmacMd5, "HMAC-MD5" },
	{ MacAlgorithm::hmacSha1, "HMAC-SHA1" },
	{ MacAlgorithm::md5, "MD5" },
	{ MacAlgorithm::sha1, "SHA1" }
};

enum class Compression : Byte
{
	gzip,
	none
};

static const std::pair<Compression, const char*> compressionMap[] =
{
	{ Compression::gzip, "GZIP" },
	{ Compression::none, lpszNone }
};

enum class Cipher : Byte
{
	blowfish,
	idea,
	none,
	rc4
};

static const std::pair<Cipher, const char*> cipherMap[] =
{
	{ Cipher::blowfish, "BLOWFISH" },
	{ Cipher::idea, "IDEA" },
	{ Cipher::none, lpszNone },
	{ Cipher::rc4, "RC4" }
};

enum class IrcStrId : Byte
{
	invite,
	join,
	kick,
	lagTime,
	mode,
	nick,
	part,
	ping,
	privMsg,
	quit,
	who,
	whoIs
};

static const std::pair<IrcStrId, const char*> ircMap[] =
{
	{ IrcStrId::invite, "INVITE" },
	{ IrcStrId::join, "JOIN" },
	{ IrcStrId::kick, "KICK" },
	{ IrcStrId::lagTime, "LAGTIME" },
	{ IrcStrId::mode, "MODE" },
	{ IrcStrId::nick, "NICK" },
	{ IrcStrId::part, "PART" },
	{ IrcStrId::ping, "PING" },
	{ IrcStrId::privMsg, "PRIVMSG" },
	{ IrcStrId::quit, "QUIT" },
	{ IrcStrId::who, "WHO" },
	{ IrcStrId::whoIs, "WHOIS" }
};

enum class IrcNumId : uint16
{
	welcome = 1,
	yourHost,
	created,
	myInfo,
	bounce,
	away = 301,
	userHost,
	isOn,
	unAway = 305,
	noAway,
	whoIsUser = 311,
	whoIsServer,
	whoIsOperator,
	whoAsUser,
	endOfWho,
	whoIsIdle = 317,
	endOfWhoIs,
	whoIsChannels,
	list = 322,
	listEnd,
	channelModeIs,
	uniqOpts,
	noTopic = 331,
	topic,
	inviting = 341,
	summoning,
	inviteList = 346,
	endOfInviteList,
	exceptList,
	endOfExceptList,
	version = 351,
	whoReply,
	namReply,
	links = 364,
	endOfLinks,
	endOfNames,
	banList,
	endOfBanList,
	info = 371,
	motd,
	endOfInfo = 374,
	motdStart,
	endOfMotd,
	youreOper = 381,
	rehashing,
	youreServer,
	time = 391,
	userStart,
	users,
	endOfUsers,
	noUsers,
	noSuchNick = 401,
	noSuchServer,
	noSuchChannel,
	cannotSendToChan,
	tooManyChannels,
	wasNoSuchNick,
	tooManyTargets,
	noSuchService,
	noOrigin,
	noRecipient = 411,
	noTextToSend,
	noTopLevel,
	wildTopLevel,
	badMask,
	unknownCommand = 421,
	noMotd,
	noAdmiInfo,
	fileError,
	noNicknameGiven = 431,
	errOneUsNickname,
	nicknameInUse,
	nickCollision = 436,
	unavailResource,
	userNotInChannel = 441,
	noLogin = 444
};

#endif // _ID_H
