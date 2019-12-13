#ifndef _HLCONNECTION_H
#define _HLCONNECTION_H

#include "forward.hpp"
#include "../common/src/forward.hpp"
#include "../common/src/connection.hpp"

class HLConnection : public Connection<boost::asio::ip::tcp>
{
public:
	HLConnection(HivePtr, ListenerPtr);
	void setSession(UserSessionRef);
protected:
	void onAccept(const std::string_view&, uint16) override;
	void onSend(const Buffer&) override;
	void onReceive(Buffer&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	UserSessionRef session;
	ListenerPtr listener;
};

#endif // _HLCONNECTION_H
