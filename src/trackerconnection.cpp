#include "trackerconnection.hpp"
#include "trackersession.hpp"
#include "common/src/hive.hpp"
#include "common/src/listener.hpp"
#include "id.hpp
#include "server.hpp"

TrackerConnection::TrackerConnection(HivePtr hive):
	Connection(hive)
{
}

void TrackerConnection::setSession(TrackerSessionRef session)
{
	this->session = session;
}

void TrackerConnection::onAccept(std::string_view, uint16)
{
	TrackerConnectionPtr connection(new TrackerConnection(hive));
}

void TrackerConnection::onSend(const Buffer &buffer)
{
}

void TrackerConnection::onReceive(Buffer &buffer)
{	
}

void TrackerConnection::onError(Error)
{
}

void TrackerConnection::onDisconnect()
{
}
