#ifndef _TRACKERCONNECTION_H
#define _TRACKERCONNECTION_H

#include "forward.hpp"
#include "common/src/forward.hpp"
#include "common/src/connection.hpp"

class TrackerConnection : public Connection<boost::asio::ip::udp>
{
public:
	TrackerConnection(HivePtr);
	void setSession(TrackerSessionRef);
protected:
	void onAccept(const std::string_view&, uint16) override;
	void onSend(const Buffer&) override;
	void onReceive(Buffer&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	TrackerSessionRef session;
};

#endif // _TRACKERCONNECTION_H
