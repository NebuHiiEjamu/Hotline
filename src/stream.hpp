#ifndef _HLSTREAM_H
#define _HLSTREAM_H

#include <algorithm>
#include <boost/endian/conversion.hpp>
#include <boost/predef.h>
#include <ctime>
#include <string_view>

#include "common/src/stream.hpp"
#include "id.hpp"

struct Transaction
{
	bool reply;
	TransId op;
	uint32 id;
	uint32 error;
	uint32 totalSize;
	uint32 chunkSize;
};

class HLInStream : public InStream
{
public:
	template <class T> T read()
	{
		T t;
#if BOOST_ENDIAN_BIG_BYTE
		t = read(false);
#else
		t = read(true);
#endif
	return t;
	}

	template <> bool read()
	{
		Byte b = read();
		return b == 1 ? true : false;
	}

	template <> FilePath&& read()
	{
		FilePath path;
		uint16 depth = read();

		for (uint16 i = 0; i < depth; i++)
		{
			ignore(2); // unknown
			Byte length = read();
			path /= read(length);
		}

		return std::move(path);
	}

	template <> std::string&& read()
	{
		std::string s = read(read());
		std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\r') c = '\n'; });
		return std::move(s);
	}

	template <> Timestamp&& read()
	{
		uint16 year = read();
		ignore(2); // milliseconds, not needed?
		uint32 seconds = read();
		std::time_t time = static_cast<std::time_t>(seconds * (year - 1900));

		return std::chrono::system_clock::from_time_t(time);
	}

	template <> Transaction&& read()
	{
		Transaction t;

		ignore(1); // padding
		t.reply = read();
		t.op = read();
		t.id = read();
		t.error = read();
		t.totalSize = read();
		t.chunkSize = read();

		return std::move(t);
	}

	template <class T> T readField()
	{
		ignore(4); // should know ID, size is irrelevant for POD
		return read();
	}

	template <class String> String&& readStringField()
	{
		ignore(2); // should know ID
		uint16 size = read();
		return std::move(read(size));
	}
};

class HLOutStream : public OutStream
{
public:
	void write16(uint16 i) // for ambiguity
	{
#if BOOST_ENDIAN_BIG_BYTE
		write16(i, false);
#else
		write16(i, true);
#endif
	}

	void write32(uint32 i) // for ambiguity
	{
#if BOOST_ENDIAN_BIG_BYTE
		write32(i, false);
#else
		write32(i, true);
#endif
	}

	template <class T> void write(T t)
	{
#if BOOST_ENDIAN_BIG_BYTE
		write(t, false);
#else
		write(t, true);
#endif
}

	template <> void write(bool b)
	{
		write16(b ? 1 : 0);
	}

	template <> void write(const FilePath &path)
	{
		std::string_view generic = path.generic_string();
	
		write16(std::count_if(generic.begin(), generic.end(), [](char c) { return c == '/'; }));
		for (auto level : path)
		{
			std::string_view slevel = level.string();

			if (!slevel.empty() && slevel != FilePath::preferred_separator &&
				slevel.find(":") == std::string::npos)
			{
				ignore(2); // unknown
				write8(slevel.size());
				seek(1);
				write(slevel);
			}
		}
	}

	template <> void write(const Timestamp &time)
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

	void write(const std::string_view &s, Size padding = 0)
	{
		// strip carriage returns (might have \r\n), make line feeds into carriage returns
		std::string s2(s);
		std::remove(s2.begin(), s2.end(), [](char c) { return c == '\r'; });
		std::for_each(s2.begin(), s2.end(), [](char &c) { if (c == '\n') c = '\r'; });

		write16(s2.size());
		writeString(s2);
		if (padding > s2.size()) ignore(padding - s2.size());
	}

	template <class T> void write(Field field, T t)
	{
		write(field);
		write16(sizeof(T));
		write(t);
	}

	template <class String> void writeString(Field field, const String &s)
	{
		write(field);
		write16(s.size());
		writeString(s);
	}
};

#endif // _HLSTREAM_H
