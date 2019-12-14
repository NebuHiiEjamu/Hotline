#include <algorithm>
#include <array>
#include <boost/predef.h>
#include <ctime>
#include <utility>

#include "common.hpp"

using boost::endian;

static constexpr std::array<uint32, 12> monthSeconds = { 0, 2678400, 5097600, 7776000, 10368000,
	13046400, 15638400, 18316400, 20995200, 23587200, 26265600, 28857600 };

template <class T> T HLInStream::read()
{
	T t;
#if BOOST_ENDIAN_BIG_BYTE
	t = read(false);
#else
	t = read(true);
#endif
	return t;
}

template <> bool HLInStream::read()
{
	Byte b = read();
	return b == 1 ? true : false;
}

template <> FilePath&& HLInStream::read()
{
	FilePath path;
	uint16 depth = read();

	for (uint16 i = 0; i < depth; i++)
	{
		skip(2); // unknown
		Byte length = read();
		path /= read(length);
	}

	return std::move(path);
}

template <> std::string&& HLInStream::read()
{
	std::string s = read(read());
	std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\r') c = '\n'; });
	return std::move(s);
}

template <> Timestamp&& HLInStream::read()
{
	uint16 year = read();
	skip(2); // milliseconds, not needed?
	uint32 seconds = read();
	std::time_t time = static_cast<std::time_t>(seconds * (year - 1900));

	return std::chrono::system_clock::from_time_t(time);
}

template <> Transaction&& HLInStream::read()
{
	Transaction t;

	skip(1); // padding
	t.reply = read();
	t.op = read();
	t.id = read();
	t.error = read();
	t.totalSize = read();
	t.thisSize = read();

	return std::move(t);
}

template <class T> T HLInStream::readField()
{
	skip(4); // should know ID, size is irrelevant for POD
	return read();
}

template <class String> String&& HLInStream::readStringField()
{
	skip(2); // should know ID
	uint16 size = read();
	return std::move(read(size));
}

template<> void HLOutStream::write(bool b)
{
	internal.put(b ? 1 : 0);
}

template<> void HLOutStream::write(const FilePath &path)
{
	std::string_view generic = path.generic_string();
	
	write16(std::count_if(generic.begin(), generic.end(), [](char c) { return c == '/'; }));
	for (auto level : path)
	{
		std::string_view slevel = level.string();

		if (!slevel.empty() && slevel != FilePath::preferred_separator &&
			slevel.find(":") == std::string::npos)
		{
			pad(2); // unknown
			internal.put(slevel.size());
			write(slevel);
		}
	}
}

template<> void HLOutStream::write(const Timestamp &time)
{
	std::time_t cTime = std::chrono::system_clock::to_time_t(time);
	std::tm timeTm = *std::localtime(&cTime);
	uint16 year = timeTm.tm_year + 1900;

	write(year);
	write16(std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count());
	write32(monthSeconds[timeTm.tm_mon] + (timeTm.tm_mon > 1 && !(year % 4) ? 86400 : 0) +
		(timeTm.tm_sec + (60 * (timeTm.tm_min + 60 * ((timeTm.tm_hour + 24 *
		(timeTm.tm_mday - 1)))))));
}

void HLOutStream::write(const std::string_view &s, Size padding = 0)
{
	// strip carriage returns (might have \r\n), make line feeds into carriage returns
	std::string s2(s);
	std::remove(s2.begin(), s2.end(), [](char c) { return c == '\r'; });
	std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\n') c = '\r'; });

	write16(s2.size());
	write(s2);
	if (padding > s2.size()) pad(padding - s2.size());
}

void HLOutStream::write(const Transaction &t)
{
	pad(1); // padding
	write(t.reply);
	write(t.op)
	write(t.id);
	write(t.error);
	write(t.totalSize);
	write(t.thisSize);
}

template <class T> void HLOutStream::write(T t)
{
#if BOOST_ENDIAN_BIG_BYTE
	write(t, false);
#else
	write(t, true);
#endif
}

template <class T> void HLOutStream::write(Field field, T t)
{
	write(field);
	write16(sizeof(T));
	write(t);
}

template <class String> void HLOutStream::write(Field field, const String &s)
{
	write(field);
	write16(s.size());
	write(s);
}

void HLOutStream::write16(uint16 i)
{
#if BOOST_ENDIAN_BIG_BYTE
	write(i, false);
#else
	write(i, true);
#endif
}

void HLOutStream::write32(uint32 i)
{
#if BOOST_ENDIAN_BIG_BYTE
	write(i, false);
#else
	write(i, true);
#endif
}
