#ifndef _FORWARD_H
#define _FORWARD_H

#include <memory>

class Server;

using ServerRef = std::weak_ptr<Server>;

#endif // _FORWARD_H
