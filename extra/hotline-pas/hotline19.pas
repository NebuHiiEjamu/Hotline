unit hotline19;

{$mode objfpc}{$H+}

interface
	uses fpsock, sysutils;

	const
		HTLC_MAGIC = 'TRTPHOTL#0#1#0#2';
		HTLS_MAGIC = 'TRTP#0#0#0#0';
		HTRK_MAGIC = 'HTRK#0#1';
		HTXF_MAGIC = $48545846;
		HTRK_TCPPORT = 5498;
		HTRK_UDPPORT = 5499;
		HTLS_TCPPORT = 5500;
		HTXF_TCPPORT = 5501;
		HL_BOOKMARK_MAGIC = 'HTsc';

		STATUS_AWAY = 1 shl 0;
		STATUS_ADMIN = 1 shl 1;
		STATUS_NOMSG = 1 shl 2;
		STATUS_NOCHAT = 1 shl 3;
		
		myTran_Error = 100;
		myTran_GetMsgs = 101;
		myTran_NewMsg = 102;
		myTran_OldPostNews = 103;
		myTran_ServerMsg = 104;
		myTran_ChatSend = 105;
		myTran_ChatMsg = 106;
		myTran_Login = 107;
		myTran_SendInstantMsg = 108;
		myTran_ShowAgreement = 109;
		myTran_DisconnectUser = 110;
		myTran_DisconnectMsg = 111;
		myTran_InviteNewChat = 112;
		myTran_InviteToChat = 113;
		myTran_RejectChatInvite = 114;
		myTran_JoinChat = 115;
		myTran_LeaveChat = 116;
		myTran_NotifyChatChangeUser = 117;
		myTran_NotifyChatDeleteUser = 118;
		myTran_NotifyChatSubject = 119;
		myTran_SetChatSubject = 120;
		myTran_Agreed = 121;
		myTran_ServerBanner = 122;
		myTran_GetFileNameList = 200;
		myTran_DownloadFile = 202;
		myTran_UploadFile = 203;
		myTran_DeleteFile = 204;
		myTran_NewFolder = 205;
		myTran_GetFileInfo = 206;
		myTran_SetFileInfo = 207;
		myTran_MoveFile = 208;
		myTran_MakeFileAlias = 209;
		myTran_DownloadFldr = 210;
		myTran_DownloadInfo = 211;
		myTran_DownloadBanner = 212;
		myTran_UploadFldr = 213;
		myTran_GetUserNameList = 300;
		myTran_NotifyChangeUser = 301;
		myTran_NotifyDeleteUser = 302;
		myTran_GetClientInfoText = 303;
		myTran_SetClientUserInfo = 304;
		myTran_NewUser = 350;
		myTran_DeleteUser = 351;
		myTran_GetUser = 352;
		myTran_SetUser = 353;
		myTran_UserAccess = 354;
		myTran_UserBroadcast = 355;
		myTran_GetNewsCatNameList = 370;
		myTran_GetNewsArtNameList = 371;
		myTran_DelNewsItem = 380;
		myTran_NewNewsFldr = 381;
		myTran_NewNewsCat = 382;
		myTran_GetNewsArtData = 400;
		myTran_PostNewsArt = 410;
		myTran_DelNewsArt = 411;
		myTran_KeepConnectionAlive = 500;

		myField_ErrorText = 100;
		myField_Data = 101;
		myField_UserName = 102;
		myField_UserID = 103;
		myField_UserIconID = 104;
		myField_UserLogin = 105;
		myField_UserPassword = 106;
		myField_RefNum = 107;
		myField_TransferSize = 108;
		myField_ChatOptions = 109;
		myField_UserAccess = 110;
		myField_UserAlias = 111;
		myField_UserFlags = 112;
		myField_Options = 113;
		myField_ChatID = 114;
		myField_ChatSubject = 115;
		myField_WaitingCount = 116;
		myField_ServerAgreement = 150;
		myField_ServerBanner = 151;
		myField_ServerBannerType = 152;
		myField_ServerBannerUrl = 153;
		myField_NoServerAgreement = 154;
		myField_Version = 160;
		myField_CommunityBannerID = 161;
		myField_ServerName = 162;
		myField_FileNameWithInfo = 200;
		myField_FileName = 201;
		myField_FilePath = 202;
		myField_FileResumeData = 203;
		myField_FileXferOptions = 204;
		myField_FileTypeString = 205;
		myField_FileCreatorString = 206;
		myField_FileSize = 207;
		myField_FileCreateDate = 208;
		myField_FileModifyDate = 209;
		myField_FileComment = 210;
		myField_FileNewName = 211;
		myField_FileNewPath = 212;
		myField_FileType = 213;
		myField_QuotingMsg = 214;
		myField_AutomaticResponse = 215;
		myField_FldrItemCount = 220;
		myField_UserNameWithInfo = 300;
		myField_NewsCatGUID = 319;
		myField_NewsCatListData = 320;
		myField_NewsArtListData = 321;
		myField_NewsCatName = 322;
		myField_NewsCatListData15 = 323;
		myField_NewsPath = 325;
		myField_NewsArtID = 326;
		myField_NewsArtDataFlav = 327;
		myField_NewsArtTitle = 328;
		myField_NewsArtPoster = 329;
		myField_NewsArtDate = 330;
		myField_NewsArtPrevArt = 331;
		myField_NewsArtNextArt = 332;
		myField_NewsArtData = 333;
		myField_NewsArtFlags = 334;
		myField_NewsArtParentArt = 335;
		myField_NewsArt1stChildArt = 336;
		myField_NewsArtRecurseDel = 337;

		myAcc_DeleteFile = 0;
		myAcc_UploadFile = 1;
		myAcc_DownloadFile = 2;
		myAcc_RenameFile = 3;
		myAcc_MoveFile = 4;
		myAcc_CreateFolder = 5;
		myAcc_DeleteFolder = 6;
		myAcc_RenameFolder = 7;
		myAcc_MoveFolder = 8;
		myAcc_ReadChat = 9;
		myAcc_SendChat = 10;
		myAcc_OpenChat = 11;
		myAcc_CloseChat = 12;
		myAcc_ShowInList = 13;
		myAcc_CreateUser = 14;
		myAcc_DeleteUser = 15;
		myAcc_OpenUser = 16;
		myAcc_ModifyUser = 17;
		myAcc_ChangeOwnPass = 18;
		myAcc_SendPrivMsg = 19;
		myAcc_NewsReadArt = 20;
		myAcc_NewsPostArt = 21;
		myAcc_DisconUser = 22;
		myAcc_CannotBeDiscon = 23;
		myAcc_GetClientInfo = 24;
		myAcc_UploadAnywhere = 25;
		myAcc_AnyName = 26;
		myAcc_NoAgreement = 27;
		myAcc_SetFileComment = 28;
		myAcc_SetFolderComment = 29;
		myAcc_ViewDropBoxes = 30;
		myAcc_MakeAlias = 31;
		myAcc_Broadcast = 32;
		myAcc_NewsDeleteArt = 33;
		myAcc_NewsCreateCat = 34;
		myAcc_NewsDeleteCat = 35;
		myAcc_NewsCreateFldr = 36;
		myAcc_NewsDeleteFldr = 37;
		myAcc_UploadFolder = 38;
		myAcc_DownloadFolder = 39;
		myAcc_SendMessage = 40;

		dlFldrAction_SendFile = 1;
		dlFldrAction_ResumeFile = 2;
		dlFldrAction_NextFile = 3;
	
	type
		THotlineStream = class(tsocketstream)
		public
			function ReadBinary: tbytes;
			function ReadFilePath: rawbytestring;
			function ReadInteger: word;
			function ReadString: rawbytestring;
			procedure WriteBinary(b: tbytes);
			procedure WriteFilePath(fp: rawbytestring);
			procedure WriteInteger(i: word);
			procedure WriteString(s: rawbytestring);
		end;

	function CR2LF(s: rawbytestring): rawbytestring;
	function LF2CR(s: rawbytestring): rawbytestring;
	function EncStr(s: rawbytestring): tbytes;

implementation

	function THotlineStream.ReadBinary: tbytes;
	var
		len: word;
	begin
		len := ReadInteger;
		setlength(result, len);
		readbuffer(result, len);
	end;

	function THotlineStream.ReadInteger: word;
	begin
		result := beton(readword);
	end;

	function THotlineStream.ReadString: rawbytestring;
	var
		len: word;
	begin
		len := ReadInteger;
		setlength(result, len);
		readbuffer(result, len);
	end;

	procedure THotlineStream.WriteBinary(b: tbytes);
	begin
		WriteInteger(length(b));
		writebuffer(b, length(b));
	end;

	procedure THotlineStream.WriteInteger(i: word);
	begin
		writeword(ntobe(i));
	end;

	procedure THotlineStream.WriteString(s: rawbytestring);
	begin
		WriteInteger(length(s));
		writebuffer(s, length(s));
	end;

	function CR2LF(s: rawbytestring): rawbytestring;
	var
		i: integer;
	begin
		for i := 0 to length(s) - 1 do
			if s[i] = #13 then result[i] := #10
			else result[i] := s[i];
	end;

	function LF2CR(s: rawbytestring): rawbytestring;
	var
		i: integer;
	begin
		for i := 0 to length(s) - 1 do
			if s[i] = #10 then result[i] := #13
			else result[i] := s[i];
	end;

	function EncStr(s: rawbytestring): tbytes;
	var
		i: integer;
	begin
		setlength(result, length(s));
		for i := 0 to length(s) - 1 do
			result[i] := 255 - byte(s[i]);
	end;
end.
