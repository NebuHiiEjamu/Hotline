#ifndef _FILESESSION_H
#define _FILESESSION_H

#include <array>
#include <bitset>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <string>

#include "forward.hpp"
#include "../common/src/forward.hpp"
#include "../common/src/typedefs.hpp"

class FileSession : public std::enable_shared_from_this<FileSession>
{
public:
	FileSession(uint16, FileConnectionPtr);
private:
	std::string comment;
	std::array<Byte, MD5_DIGEST_LENGTH> md5;
	std::array<Byte, SHA_DIGEST_LENGTH> sha1;
	ByteString haval;
	FilePath path;
	Timestamp created;
	Timestamp modified;
	Size size;
	std::array<char, 4> macType;
	std::array<char, 4> macCreator;
};

#endif // _FILESESSION_H
