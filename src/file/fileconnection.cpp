#include "fileconnection.hpp"
#include "filesession.hpp"
#include "../../common/src/hive.hpp"
#include "../../common/src/listener.hpp"
#include "../server.hpp"

FileConnection::FileConnection(HivePtr hive, AcceptorPtr acceptor):
	Connection(hive),
	acceptor(acceptor)
{
}

void FileConnection::setSession(SessionRef session)
{
	this->session = session;
}

void FileConnection::onAccept(const std::string_view&, uint16)
{
	FileConnectionPtr connection(new FileConnection(hive, acceptor));
	acceptor->accept(connection);

	HLServer::getInstance()->createSession(id, std::dynamic_pointer_cast<FileConnection>
		shared_from_this()));
}

void FileConnection::onSend(const Buffer&)
{
}

void FileConnection::onReceive(Buffer &buffer)
{	
}

void FileConnection::onError(Error)
{
}

void FileConnection::onDisconnect()
{
}
