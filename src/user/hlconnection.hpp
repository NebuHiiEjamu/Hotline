#ifndef _HLCONNECTION_H
#define _HLCONNECTION_H

#include "forward.hpp"
#include "../net/forward.hpp"
#include "../net/connection.hpp"

class HLConnection : public Connection
{
public:
	HLConnection(HivePtr, ListenerPtr);
	void setSession(SessionRef);
protected:
	void onAccept(std::string_view, uint16) override;
	void onSend(const ByteString&) override;
	void onReceive(ByteString&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	SessionRef session;
	ListenerPtr listener;
};

#endif // _PALACECONNECTION_H
