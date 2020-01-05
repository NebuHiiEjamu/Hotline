#ifndef _FILECONNECTION_H
#define _FILECONNECTION_H

#include "forward.hpp"
#include "../common/src/forward.hpp"
#include "../common/src/connection.hpp"

class FileConnection : public Connection<boost::asio::ip::tcp>
{
public:
	FileConnection(HivePtr, AcceptorPtr);
	void setSession(SessionRef);
protected:
	void onAccept(const std::string_view&, uint16) override;
	void onSend(const Buffer&) override;
	void onReceive(Buffer&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	FileSessionRef session;
	AcceptorPtr acceptor;
};

#endif // _FILECONNECTION_H
