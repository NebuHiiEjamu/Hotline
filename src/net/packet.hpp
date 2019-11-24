#ifndef _PACKET_H
#define _PACKET_H

#include "../common.hpp"

constexpr uint32 idBMP = 0x424D5020;
constexpr uint32 idDATA = 0x44415441;
constexpr uint32 idfldr = 0x666C6472;
constexpr uint32 idGIFf = 0x47494666;
constexpr uint32 idHTXF = 0x48545846;
constexpr uint32 idJPEG = 0x4A504547;
constexpr uint32 idPICT = 0x50494354;
constexpr uint32 idRFLT = 0x52464C54;
constexpr uint32 idTRTP = 0x54525450;
constexpr uint64 idTRTPHOTL = 0x54525450484F544C;
constexpr uint32 idURL = 0x55524C20;

enum
{
	idError = 100,
	idGetMessages,
	idNewMessage,
	idOldPostNews,
	idServerMessage,
	idSendChat,
	idChatMessage,
	idLogin,
	idSendPrivateMessage,
	idShowAgreement,
	idKickUser,
	idKickMessage,
	idNewChatInvite,
	idChatInvite,
	idRejectChatInvite,
	idJoinChat,
	idLeaveChat,
	idNotifyChatAccountEdit,
	idNotifyChatDeleteAccount,
	idNotifyChatTopic,
	idSetChatTopic,
	idAgreed,
	idServerBanner,
	idGetFileNameList = 200,
	idDownloadFile = 202,
	idUploadFile,
	idDeleteFile,
	idNewFolder,
	idGetFileInfo,
	idSetFileInfo,
	idMoveFile,
	idMakeFileAlias,
	idDownloadFolder,
	idDownloadInfo,
	idDownloadBanner,
	idUploadFolder,
	idGetUserNameList = 300,
	idNotifyEditAccount,
	idNotifyDeleteAccount,
	idGetClientInfoText,
	idSetClientUserInfo,
	idNewAccount = 350,
	idDeleteAccount,
	idGetAccount,
	idSetAccount,
	idAccountAccess,
	idUserBroadcast,
	idGetNewsCategoryNameList = 370,
	idGetNewsArticleNameList,
	idDeleteNewsItem = 380,
	idNewNewsFolder,
	idNewNewsCategory,
	idGetNewsArticleData = 400,
	idPostNewsArticle = 410,
	idDeleteNewsArticle
};

enum
{
	idErrorText = 100,
	idData,
	idUserName,
	idUserId,
	idUserIcon,
	idUserLogin,
	idUserPassword,
	idReferenceNumber,
	idTransferSize,
	idChatOptions,
	idUserAccess,
	idUserAlias,
	idUserFlags,
	idOptions,
	idChatId,
	idChatTopic,
	idWaitingCount,
	idServerAgreement = 150,
	idServerBanner,
	idServerBannerType,
	idServerBannerUrl,
	idNoServerAgreement,
	idVersion = 160,
	idCommunityBannerId,
	idServerName,
	idFileNameWithInfo = 200,
	idFileName,
	idFilePath,
	idFileResumeData,
	idFileTransferOptions,
	idFileTypeString,
	idFileCreatorString,
	idFileSize,
	idFileCreateDate,
	idFileEditDate,
	idFileComment,
	idFileNewName,
	idFileNewPath,
	idFileType,
	idQuotingMessage,
	idAutoReply,
	idFolderItemCount = 220,
	idUserNameWithInfo = 300,
	idNewsCategoryGuid = 319,
	idNewsCategoryListData,
	idNewsArticleListData,
	idNewsCategoryName,
	idNewsCategoryListData1_5,
	idNewsPath = 325,
	idNewsArticleId,
	idNewsArticleDataFlavor,
	idNewsArticleTitle,
	idNewsArticlePoster,
	idNewsArticleDate,
	idPreviousNewsArticle,
	idNextNewsArticle,
	idNewsArticleData
	idNewsParentArticle,
	idNewsFirstChildArticle,
	idNewsArticleRecursiveDelete
};

#endif // _PACKET_H
