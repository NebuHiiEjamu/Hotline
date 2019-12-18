#ifndef _HLSTREAM_H
#define _HLSTREAM_H

#include <string>
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
	uint32 thisSize;
};

class HLInStream : public InStream
{
public:
	template <class T> T read();
	template <> bool read();
	template <> Timestamp&& read();
	template <> FilePath&& read();
	template <> std::string&& read();
	template <> Transaction&& read();
	template <class T> T readField();
	template <class String> String&& readStringField();
};

class HLOutStream : public InStream
{
public:
	void write(bool);
	void write(const FilePath&);
	void write(const Timestamp&);
	void write(const std::string_view&, Size);
	void write(const Transaction&);
	template <class T> void write(T);
	template <class T> void write(Field, T);
	template <class String> void write(Field, const String&);
	void write16(uint16); // for ambiguity
	void write32(uint32); // for ambiguity
};

#endif // _HLSTREAM_H
