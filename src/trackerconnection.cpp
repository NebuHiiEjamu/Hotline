#include "trackerconnection.hpp"
#include "common/src/hive.hpp"
#include "hlserver.hpp"
#include "stream.hpp"

TrackerConnection::TrackerConnection(HiveRef hive):
	Connection(hive)
{
}

void TrackerConnection::onConnect(const std::string_view&, uint16)
{
	TrackerConnectionPtr connection(new TrackerConnection(hive));
	Buffer buffer;
	HLOutStream stream(buffer);
	HLServerRef inst = HLServer::getInstance();
	std::string_view name = inst->getName();
	std::string_view description = inst->getDescription();

	stream.write16(1); // version?
	stream.write(inst->getPort());
	stream.write(inst->getUserCount());
	stream.pad(2); // ?
	stream.write(HLServer::getRandomSeed());
	stream.write(name, name.size());
	stream.write(description, description.size());
	send(buffer);
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
