#include <functional>

#include "connection.hpp"
#include "hive.hpp"

using boost::asio;

Connection::Connection(HivePtr hive):
	hive(hive),
	socket(hive->getIOContext()),
	strand(hive->getIOContext()),
	errorState(0)
{
}

HivePtr Connection::getHive()
{
	return hive;
}

Strand& Connection::getStrand()
{
	return strand;
}

Socket& Connection::getSocket()
{
	return socket;
}

bool Connection::hasError()
{
	uint32 v1 = 1;
	uint32 v2 = 1;
	return errorState.compare_exchange_strong(v1, v2);
}

void Connection::disconnect()
{
	onDisconnect();
	socket.close();
}

void Connection::startError(Error error)
{
	uint32 v1 = 1;
	uint32 v2 = 0;

	if (!errorState.compare_exchange_strong(v1, v2))
	{
		Error errorCode;

		socket.shutdown(Socket::shutdown_both, errorCode);
		socket.close(errorCode);
		onError(error);
	}
}

void Connection::dispatchReceive(uint32 totalBytes)
{
	pendingReceives.push(totalBytes);
	if (pendingReceives.empty()) startReceive(totalBytes);
}

void Connection::dispatchSend(const ByteString &outString)
{
	bool shouldStartSend = pendingSends.empty();
	pendingSends.push(outString);
	if (shouldStartSend) startSend();
}

void Connection::startReceive(uint32 totalBytes)
{
	if (totalBytes > 0)
	{
		inBuffer.resize(totalBytes);
		asio::async_read(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
	else
	{
		inBuffer.resize(inBufferSize);
		asio::async_read_some(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
}

void Connection::startSend()
{
	if (!pendingSends.empty())
		asio::async_write(socket, asio::buffer(pendingSends.front()), asio::bind_executor(strand,
			std::bind(&Connection::handleSend, shared_from_this(), std::placeholders::_1,
			pendingSends.begin())));
}

void Connection::handleReceive(Error error, uint32 receivedBytes)
{
	if (error || hasError() || hive->stopped()) startError(error);
	else
	{
		inBuffer.resize(receivedBytes);
		onReceive(inBuffer);
		receive();
		pendingReceives.pop();
		if (!pendingReceives.empty()) startReceive(pendingReceives.front());
	}
}

void Connection::handleSend(Error error, const ByteString &outString)
{
	if (error || hasError() || hive->stopped()) startError(error);
	else
	{
		onSend(outString);
		pendingSends.pop();
		startSend();
	}
}

void Connection::receive(uint32 totalBytes = 0)
{
	strand.post(std::bind(&Connection::dispatchReceive, shared_from_this(), totalBytes));
}

void Connection::send(const ByteString &outString)
{
	strand.post(std::bind(&Connection::dispatchSend, shared_from_this(), buffer));
}

uint32 Connection::getInBufferSize() const
{
	return inBufferSize;
}

void Connection::setInBufferSize(uint32 newSize)
{
	inBufferSize = newSize;
}

void Connection::onAccept(std::string_view, uint16)
{
}

void Connection::onConnect(std::string_view, uint16)
{
}

void Connection::onSend(const ByteString&)
{
}

void Connection::onReceive(ByteString&)
{
}

void Connection::onError(Error)
{
}

void Connection::onDisconnect()
{
}
