#ifndef _LISTENER_H
#define _LISTENER_H

#include <atomic>

#include "forward.hpp"
#include "../common.hpp"

using boost::asio;

class Listener : public std::enable_shared_from_this<Listener>
{
public:
	Listener(HivePtr);
	HivePtr getHive();
	Acceptor& getAcceptor();
	Strand& getStrand();
	bool hasError();
	void listen(std::string_view, uint16);
	void accept(ConnectionPtr);
	void stop();
private:
	void dispatchAccept(ConnectionPtr);
	void handleAccept(Error, ConnectionPtr);
protected:
	virtual bool onAccept(ConnectionPtr, std::string_view, uint16);
	virtual void onError(Error);
protected:
	HivePtr hive;
	Acceptor acceptor;
	Strand strand;
	std::atomic_uint32_t errorState;
};

#endif // _LISTENER_H
