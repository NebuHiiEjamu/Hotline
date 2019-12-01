#include <algorithm>
#include <boost/endian/conversion.hpp>
#include <iterator>
#include <utility>

#include "common.hpp"

using boost::endian;

ByteBuffer::ByteBuffer()
	position(data.begin())
{
}

ByteBuffer::ByteBuffer(ByteString &inString):
	data(std::move(inString)),
	position(data.begin())
{
}

ByteBuffer&& ByteBuffer::clone(std::size_t bytes) const
{
	ByteBuffer newBuffer;
	newBuffer.data.insert(std::back_inserter(data), position, position + bytes);
	return std::move(newBuffer);
}

ByteString& ByteBuffer::getBytes() const
{
	return data;
}

void ByteBuffer::setBytes(ByteString &inString)
{
	data = std::move(inString);
}

void ByteBuffer::flush()
{
	data.clear();
}

template <class StringType> StringType&& ByteBuffer::read(std::size_t bytes)
{
	StringType s(position, position + bytes);
	position += bytes;
	return std::move(s);
}

Byte ByteBuffer::readByte()
{
	Byte b;
	std::copy(position, position + sizeof(Byte), reinterpret_cast<Byte*>(&b));
	position += sizeof(Byte);
	return b;
}

void ByteBuffer::readNull(std::size_t bytes)
{
	position += bytes;
}

FilePath&& ByteBuffer::readPath()
{
	FilePath path;
	uint16 depth = read16();

	for (uint16 i = 0; i < depth; i++)
	{
		readNull(2); // unknown
		Byte length = readByte();
		path /= read(length);
	}

	return std::move(path);
}

std::string&& ByteBuffer::readString()
{
	std::string s = read(read16());
	std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\r') c = '\n'; });
	return std::move(s);
}

uint16 ByteBuffer::read16()
{
	uint16 i;
	std::copy(position, position + sizeof(uint16), reinterpret_cast<uint16*>(&i));
	position += sizeof(uint16);
	endian::big_to_native_inplace(i);
	return i;
}

uint32 ByteBuffer::read32()
{
	uint32 i;
	std::copy(position, position + sizeof(uint32), reinterpret_cast<uint32*>(&i));
	position += sizeof(uint32);
	endian::big_to_native_inplace(i);
	return i;
}

uint64 ByteBuffer::read64()
{
	uint64 i;
	std::copy(position, position + sizeof(uint64), reinterpret_cast<uint64*>(&i));
	position += sizeof(uint64);
	endian::big_to_native_inplace(i);
	return i;
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

void ByteBuffer::writeByte(Byte b)
{
	data.push_back(b);
}

void ByteBuffer::writeNull(std::size_t bytes)
{
	for (std::size_t i = 0; i < bytes; i++) data.push_back(0);
}

void ByteBuffer::writePath(const FilePath &path)
{
	std::string_view generic = path.generic_string();
	
	write16(std::count_if(generic.begin(), generic.end(), [](char c) { return c == '/'; }));
	for (auto level : path)
	{
		std::string_view slevel = level.string();

		if (!slevel.empty() && slevel != FilePath::preferred_separator &&
			slevel.find(":") == std::string::npos)
		{
			writeNull(2); // unknown
			writeByte(slevel.size());
			write(slevel);
		}
	}
}

void ByteBuffer::writeString(std::string_view s, std::size_t padding = 0)
{
	// strip carriage returns (might have \r\n), make line feeds into carriage returns
	std::string s2(s);
	std::remove(s2.begin(), s2.end(), [](char c) { return c == '\r'; });
	std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\n') c = '\r'; });

	write16(s2.size());
	write(s2);
	if (padding > 0) writeNull(padding - s2.size());
}

void ByteBuffer::write16(uint16 i)
{
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>(i & 0xFF);
}

void ByteBuffer::write32(uint32 i)
{
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>(i & 0xFF);
}

void ByteBuffer::write64(uint64 i)
{
	data.push_back(static_cast<Byte>((i & 0xFF00000000000000) >> 56);
	data.push_back(static_cast<Byte>((i & 0xFF000000000000) >> 48);
	data.push_back(static_cast<Byte>((i & 0xFF0000000000) >> 40);
	data.push_back(static_cast<Byte>((i & 0xFF00000000) >> 32);
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>(i & 0xFF);
}
