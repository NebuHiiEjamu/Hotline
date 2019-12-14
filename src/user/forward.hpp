#ifndef _USER_FORWARD_H
#define _USER_FORWARD_H

#include <memory>

class Account;
class HLConnection;
class Session;

using AccountPtr = std::shared<Account>;
using AccountRef = std::weak_ptr<Account>;
using HLConnectionPtr = std::shared_ptr<HLConnection>;
using HLConnectionPtr = std::shared_ptr<HLConnection>;
using SessionPtr = std::shared_ptr<UserSession>;
using SessionRef = std::weak_ptr<UserSession>;

#endif // _USER_FORWARD_H
