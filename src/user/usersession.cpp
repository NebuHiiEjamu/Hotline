#include <fmt/core.h>
#include <sstream>

#include "usersession.hpp"
#include "hlconnection.hpp"

UserSession::UserSession(uint16 id, HLConnectionPtr connection):
	connection(connection),
	lastTransactionId(0),
	replies(0),
	id(id)
{
}

uint16 UserSession::getId() const
{
	return id;
}

uint16 UserSession::getIcon()
{
	LockGuard lock(mutex);
	return icon;
}

uint16 UserSession::getStatus()
{
	LockGuard lock(mutex);
	return static_cast<uint16>(status.to_ulong());
}

uint32 UserSession::getStatusEx()
{
	LockGuard lock(mutex);
	return static_cast<uint32>(statusEx.to_ulong());
}

std::string&& UserSession::getClientInfoText()
{
	static constexpr int spacing1 = 22;
	static constexpr int spacing2 = 32;
	LockGuard lock(mutex);
	std::ostringstream ss;

	ss << fmt::format("{:<{}}{:>{}}\r", "Name:", spacing1, nickname, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Login:", spacing1, account->getLogin(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Address:", spacing1, connection->getAddress().to_string(),
		spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Host:", spacing1, connection->getHostName(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "ID:", spacing1, id, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Icon:", spacing1, icon, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Version:", spacing1, getVersionString(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Client:", spacing1, getClient(), spacing2);

	return ss.str();
}

std::string&& UserSession::getVersionString() const
{
	std::string s(std::to_string(version));
	s.insert(1, 1, '.');
	s.insert(3, 1, '.');
	return std::move(s);
}

/*std::string_view&& UserSession::getClient() const
{
	if (statusEx.test(UserStatusEx::hotline)) return "Hotline";
	if (statusEx.test(UserStatusEx::tide)) return "Panorama";
	if (statusEx.test(UserStatusEx::aniclient)) return "AniClient";
	if (statusEx.test(UserStatusEx::heidrun)) return "Heidrun";
	if (statusEx.test(UserStatusEx::frogblast)) return "Frogblast";
	return "";
}*/

void UserSession::setStatus(uint16 flags)
{
	LockGuard lock(mutex);
	status = std::bitset<UserStatus::all>(flags);
}

void UserSession::setIcon(uint16 newIcon)
{
	LockGuard lock(mutex);
	icon = newIcon;
}

void UserSession::setStatusEx(uint32 flags)
{
	LockGuard lock(mutex);
	statusEx = std::bitset<UserStatusEx::all>(flags);
}

void UserSession::handleLogin(HLInStream &stream, const Transaction &transaction)
{
	uint16 fieldCount = stream.read();
	std::string login = stream.readStringField();
	ByteString password = stream.readStringField();
	uint16 version = stream.readField();

	
}
