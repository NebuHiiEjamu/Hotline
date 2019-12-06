#include <algorithm>
#include <array>
#include <boost/endian/conversion.hpp>
#include <ctime>
#include <iterator>
#include <utility>

#include "common.hpp"

using boost::endian;

static constexpr std::array<uint32, 12> monthSeconds = { 0, 2678400, 5097600, 7776000, 10368000,
	13046400, 15638400, 18316400, 20995200, 23587200, 26265600, 28857600 };

ByteBuffer::ByteBuffer()
	position(data.begin())
{
}

ByteBuffer::ByteBuffer(ByteString &inString):
	data(std::move(inString)),
	position(data.begin())
{
}

ByteBuffer&& ByteBuffer::clone(Size bytes) const
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

template <class StringType> StringType&& ByteBuffer::read(Size bytes)
{
	StringType s(position, position + bytes);
	position += bytes;
	return std::move(s);
}

template <class T> T ByteBuffer::read()
{
	T t;
	std::copy(position, position + sizeof(T), reinterpret_cast<T*>(&t));
	position += sizeof(T);
	return t;
}

void ByteBuffer::readNull(Size bytes)
{
	position += bytes;
}

template <> bool ByteBuffer::read()
{
	Byte b = read();
	return b == 1 ? true : false;
}

template <> FilePath&& ByteBuffer::read()
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

template <> std::string&& ByteBuffer::read()
{
	std::string s = read(read16());
	std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\r') c = '\n'; });
	return std::move(s);
}

template <> Timestamp&& ByteBuffer::read()
{
	uint16 year = read();
	readNull(2); // milliseconds, not needed?
	uint32 seconds = read();
	std::time_t time = static_cast<std::time_t>(seconds * (year - 1900));

	return std::chrono::system_clock::from_time_t(time);
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

template <class T> void ByteBuffer::write(T t)
{
	for (int i = sizeof(T) - 1; i >= 0; i--)
		data.push_back(static_cast<Byte>((t & (0xFF << (i * 8))) >> (i * 8)));
}

void ByteBuffer::writeNull(Size bytes)
{
	for (Size i = 0; i < bytes; i++) data.push_back(0);
}

template<> void ByteBuffer::write(bool b)
{
	data.push_back(b ? 1 : 0);
}

template<> void ByteBuffer::write(const FilePath &path)
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

template<> void ByteBuffer::write(const Timestamp &time)
{
	std::time_t cTime = std::chrono::system_clock::to_time_t(time);
	std::tm timeTm = *std::localtime(&cTime);
	uint16 year = timeTm.tm_year + 1900;

	write16(year);
	write16(std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count());
	write32(monthSeconds[timeTm.tm_mon] + (timeTm.tm_mon > 1 && !(year % 4) ? 86400 : 0) +
		(timeTm.tm_sec + (60 * (timeTm.tm_min + 60 * ((timeTm.tm_hour + 24 *
		(timeTm.tm_mday - 1)))))));
}

void ByteBuffer::writeString(std::string_view s, Size padding = 0)
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
