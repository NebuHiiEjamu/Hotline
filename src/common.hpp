#ifndef _COMMON_H
#define _COMMON_H

#include <boost/asio.hpp>
#include <boost/safe_numerics/safe_integer.hpp>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

using Acceptor = boost::asio::ip::tcp::acceptor;
using Address = boost::asio::ip::address;
using Byte = std::uint8_t;
using ByteString = std::vector<Byte>;
using Endpoint = boost::asio::ip::tcp::endpoint;
using Error = boost::asio::error_code;
using FilePath = std::filesystem::path;
using LockGuard = std::lock_guard<std::mutex>;
using Resolver = boost::asio::ip::tcp::resolver;
using Size = std::size_t;
using Socket = boost::asio::ip::tcp::socket;
using Strand = boost::asio::io_context::strand;
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
using uint16 = std::uint16_t;
using suint16 = boost::numeric::safe<uint16>;
using uint32 = std::uint32_t;
using suint32 = boost::numeric::safe<uint32>;
using uint64 = std::uint64_t;

class ByteBuffer : std::enable_shared_from_this<ByteBuffer>
{
public:
	ByteBuffer();
	ByteBuffer(ByteString&);
	ByteBuffer&& clone(Size) const;
	ByteString& getBytes() const;
	void setBytes(ByteString&);
	void flush();
	template <class StringType> StringType&& read(Size);
	template <class T> T read();
	template <> bool read();
	template <> Timestamp&& read();
	template <> FilePath&& read();
	template <> std::string&& read();
	void readNull(Size);
	template <class StringType> void write(const StringType&);
	template <class T> void write(T);
	template<> void write(bool);
	template<> void write(const FilePath&);
	template<> void write(const Timestamp&);
	void write(std::string_view, Size);
	void writeNull(Size);
	void write16(uint16); // for ambiguity
	void write32(uint32); // for ambiguity
private:
	ByteString data;
	ByteString::iterator position;
};

using ByteBufferPtr = std::shared_ptr<ByteBuffer>;

#endif // _COMMON_H
