#include <boost/predef.h>

#include "filesession.hpp"

FileSession::FileSession(uint16 id, FileConnectionPtr connection):
	connection(connection)
{
}