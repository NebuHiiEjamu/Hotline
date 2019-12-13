#ifndef _TRACKERSESSION_H
#define _TRACKERSESSION_H

#include "forward.hpp"
#include "common/src/forward.hpp"
#include "common/src/typedefs.hpp"
#include "stream.hpp"

class TrackerSession : public std::enable_shared_from_this<TrackerSession>
{
public:
	TrackerSession(TrackerConnectionPtr);
private:
	TrackerConnectionPtr connection;
	std::string login;
	ByteString password;
	std::mutex mutex;
	uint32 seed;
};

#endif // _TRACKERSESSION_H
