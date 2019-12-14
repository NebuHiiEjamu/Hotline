#include "hlconnection.hpp"
#include "usersession.hpp"
#include "../common/src/hive.hpp"
#include "../common/src/listener.hpp"
#include "../id.hpp
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

	HLServer::getInstance()->createSession(id, std::dynamic_pointer_cast<HLConnection>
		shared_from_this()));
}

void HLConnection::onSend(const Buffer&)
{
}

void HLConnection::onReceive(Buffer &buffer)
{
	HLInStream stream(buffer);
	LoggerRef log = HLServer::getInstance()->getLogger();
	
	if (stream.peek() == 'T')
	{
		uint32 trtp = stream.read();
		uint32 hotl = stream.read();
		uint32 version = stream.read();
		log->debug("Session {}: Got initial data: {0:X} {0:X} {0:X}", session->getId(),
			trtp, hotl, version);
		
		if (static_cast<Magic>(trtp) = Magic::TRTP && static_cast<Magic>(hotl) == Magic::HOTL &&
			version == UserSession::trtpVersion)
		{
			HLOutStream reply;

			reply.write(Magic::TRTP);
			reply.write32(errorState);
			send(getBuffer());
		}
	}
	else
	{
		Transaction trans = stream.read();
		log->debug("Session {}: Got transaction: <reply: {}, type: {}, ID: {}, error: {}, total: {}, data: {}>",
			trans.reply, static_cast<uint16>(trans.op), trans.id, trans.error, trans.totalSize,
			trans.thisSize);

		switch (trans.op)
		{
			case TransId::login: session->handleLogin(stream, trans); break;
			default: ;
		}
	}
	
}

void HLConnection::onError(Error)
{
}

void HLConnection::onDisconnect()
{
}
