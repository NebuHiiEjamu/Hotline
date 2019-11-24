#include "hlconnection.hpp"
#include "../net/hive.hpp"
#include "../net/listener.hpp"
#include "../net/packet.hpp"
#include "../server.hpp"

HLConnection::HLConnection(HivePtr hive, ListenerPtr listener):
	Connection(hive),
	listener(listener)
{
}

void HLConnection::setSession(SessionRef session)
{
	this->session = session;
}

void HLConnection::onAccept(std::string_view, uint16)
{
	HLConnectionPtr connection(new HLConnection(hive, listener));
	listener->accept(connection);

	Server::getInstance()->createSession(id, std::dynamic_pointer_cast<HLConnection>
		shared_from_this()));
}

void HLConnection::onSend(const ByteString&)
{
}

void HLConnection::onReceive(ByteString &inString)
{
	ByteBuffer buffer(inString);
}

void HLConnection::onError(Error)
{
}

void HLConnection::onDisconnect()
{
}
