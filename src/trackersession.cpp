#include "trackersession.hpp"
#include "trackerconnection.hpp"

TrackerSession::TrackerSession(uint16 id, TrackerConnectionPtr connection):
	connection(connection)
{
}
