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

Address& Connection::getAddress() const
{
	return socket.remote_endpoint().address();
}

std::string Connection::getHostName() const
{
	Resolver resolver(hive->getService());
	return resolver.resolve(getAddress(), std::to_string(getPort()))->host_name();
}

uint16 Connection::getPort() const
{
	return socket.remote_endpoint().port();
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

void Connection::dispatchReceive(Size totalBytes)
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

void Connection::startReceive(Size totalBytes)
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

void Connection::handleReceive(Error error, Size receivedBytes)
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

void Connection::receive(Size totalBytes = 0)
{
	strand.post(std::bind(&Connection::dispatchReceive, shared_from_this(), totalBytes));
}

void Connection::send(const ByteString &outString)
{
	strand.post(std::bind(&Connection::dispatchSend, shared_from_this(), buffer));
}

Size Connection::getInBufferSize() const
{
	return inBufferSize;
}

void Connection::setInBufferSize(Size newSize)
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
