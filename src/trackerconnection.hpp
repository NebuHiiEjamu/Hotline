#ifndef _TRACKERCONNECTION_H
#define _TRACKERCONNECTION_H

#include "forward.hpp"
#include "common/src/forward.hpp"
#include "common/src/connection.hpp"

class TrackerConnection : public Connection<boost::asio::ip::udp>
{
public:
	static constexpr uint16 defaultPort = 5499;
	
	TrackerConnection(HiveRef);
protected:
	void onConnect(const std::string_view&, uint16) override;
	void onSend(const Buffer&) override;
	void onReceive(Buffer&) override;
	void onError(Error) override;
	void onDisconnect() override;
};

#endif // _TRACKERCONNECTION_H
