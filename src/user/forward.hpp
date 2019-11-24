#ifndef _USER_FORWARD_H
#define _USER_FORWARD_H

#include <memory>

class HLConnection;
class Session;

using HLConnectionPtr = std::shared_ptr<HLConnection>;
using SessionPtr = std::shared_ptr<Session>;
using SessionRef = std::weak_ptr<Session>;

#endif // _USER_FORWARD_H
