#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <atomic>
#include <queue>

#include "forward.hpp"
#include "../common.hpp"

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	HivePtr getHive();
	Strand& getStrand();
	Socket& getSocket();
	Address& getAddress() const;
	std::string getHostName() const;
	uint16 getPort() const;
	Size getInBufferSize() const;
	void setInBufferSize(Size);
	bool hasError();
	void disconnect();
	void receive(Size);
	void send(const ByteString&);
private:
	void dispatchReceive(Size);
	void dispatchSend(const ByteString&);
	void startReceive(Size);
	void startSend();
	void handleReceive(Error, Size);
	void handleSend(Error, const ByteString&);
	void startError(Error);
protected:
	Connection(HivePtr);
	virtual void onAccept(std::string_view, uint16);
	virtual void onConnect(std::string_view, uint16);
	virtual void onSend(const ByteString&);
	virtual void onReceive(ByteString&);
	virtual void onError(Error);
	virtual void onDisconnect();
protected:
	HivePtr hive;
	Socket socket;
	Strand strand;
	ByteString inBuffer;
	std::atomic_uint32_t errorState;
	std::queue<Size> pendingReceives;
	std::queue<ByteString> pendingSends;
	Size inBufferSize;
};

#endif // _CONNECTION_H
